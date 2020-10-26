///////////////////////////////////////////////////////
// 文件名称：	Score.h
//   负责人：	范承祥
//     学号：	2018302060043
//   代码量：	21行
// 编译环境：	Visual Studio 2015 + EasyX_20180321(春分版) 
// 最后修改：	2019-6-12
// 实现功能：	分数类声明
////////////////////////////////////////////////////////
#pragma once

//定义类
class Score		
{
public:
	Score();								//构造函数
	~Score();								//析构函数
	void bugsPlus(int s);					//虫子加分（分数）
	void coinsPlus(int c);					//金币加分（金币个数）
	int getScore();							//获取当前分数
	int getHighestScore();					//获取最高分
	void gerRecordScore(int s[],int l);		//获取历史分数
	void readScore();						//读取分数文件
	int judgeScore();						//判断分数
	void writeScore();						//写入分数文件
private:
	int score ;								//玩家共同分数
	int highestScore;						//最高分
	int recordScore[10];					//历史分数
};