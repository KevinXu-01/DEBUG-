///////////////////////////////////////////////////////
// 文件名称：	Score.cpp
//   负责人：	范承祥
//     学号：	2018302060043
//   代码量：	146行
// 编译环境：	Visual Studio 2015 + EasyX_20180321(春分版) 
// 最后修改：	2019-6-12
// 实现功能：	分数的获取、变更、分数判断、分数文件读入写入等
////////////////////////////////////////////////////////
#include<iostream>
#include<fstream>
#include"Score.h"
#include"Person.h"

#define COINS_PLUS_WEIGHT 50	//金币加分权重

using namespace std;

//构造函数
Score::Score()
{
	score = 0;													//初始化分数
	recordScore[10] = { 0 };									//初始化历史分数
	readScore();												//读取历史文件
}

//析构函数
Score::~Score()
{
	score = 0;													//恢复初始化分数
	recordScore[10] = { 0 };									//恢复初始化历史分数
	readScore();												//读取历史文件
}

//虫子加分（分数）
void Score::bugsPlus(int i)
{
	score += i;
}


//金币加分（金币个数）
void Score::coinsPlus(int c)									
{
	score += COINS_PLUS_WEIGHT*c;									//金币加分=金币权重*金币个数
}

//获取当前分数
int Score::getScore()									
{
	return score;
}

//获取最高分
int Score::getHighestScore()
{
	return highestScore;
}

//获取历史分数
void Score::gerRecordScore(int s[],int l)
{
	for (int i = 0; i < l; i++)
	{
		if (i <= 10)
			s[i] = recordScore[i];
		else
			s[i] = 0;
	}
}

//读取分数文件
void Score::readScore()
{
	ifstream fin;													//定义文件读取对象fin
	fin.open("data\\score.dat", ios::in | ios::_Nocreate);			//打开分数记录文件
	if (fin.is_open())												//判断文件是否已打开
	{
		char temp[10] = {0};										//存储分隔符的数组								
		fin >> recordScore[0] >> temp[0]							//读取文件到历史分数
			>> recordScore[1] >> temp[1]
			>> recordScore[2] >> temp[2]
			>> recordScore[3] >> temp[3]
			>> recordScore[4] >> temp[4]
			>> recordScore[5] >> temp[5]
			>> recordScore[6] >> temp[6]
			>> recordScore[7] >> temp[7]
			>> recordScore[8] >> temp[8]
			>> recordScore[9] >> temp[9];
		highestScore = recordScore[0];								//读取最高分到highestScore
		fin.close();												//关闭文件
	}
	else															//若未成功打开文件
	{
		highestScore = 0;											//则默认最高分为0
	}
}

//判断分数
int Score::judgeScore()
{
	if (score > highestScore)										//判断当前得分是否为最高分
		highestScore = score;										//为真则最高分=当前得分
	if (score > recordScore[9])										//判断是否需要更新记录
	{
		for (int i = 0; i < 10; i++)
			if (score == recordScore[i])							//判断当前分数是否已存在分数记录中
				return 0;											//已存在则返回0
		return 1;													//否则返回1
	}
	else
		return 0;													//否则返回0
}

//写入分数文件
void Score::writeScore()
{
	ofstream fout;													//定义文件读取对象fout
	fout.open("data\\score.dat", ios::out);							//打开分数记录文件
	if (fout.is_open())												//判断文件是否已打开
	{
		if (judgeScore())											//判断是否需要更新分数记录
		{
			recordScore[9] = score;									//为真则分数记录更新
			for (int i = 9; i > 0; i--)
			{
				if (recordScore[i] > recordScore[i - 1])
				{
					int temp;
					temp = recordScore[i - 1];
					recordScore[i - 1] = recordScore[i];
					recordScore[i] = temp;
				}
				else
					break;
			}
			recordScore[0] = highestScore;
			fout << recordScore[0] << '#'							//写入分数记录到文件
				<< recordScore[1] << '#'
				<< recordScore[2] << '#'
				<< recordScore[3] << '#'
				<< recordScore[4] << '#'
				<< recordScore[5] << '#'
				<< recordScore[6] << '#'
				<< recordScore[7] << '#'
				<< recordScore[8] << '#'
				<< recordScore[9] << '#';
		}
		fout.close();												//关闭文件
	}
	else															//若未成功打开文件
	{
		cout << "Can't write score!" << endl;						//则提示错误信息
	}
}