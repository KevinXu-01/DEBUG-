///////////////////////////////////////////////////////
// �ļ����ƣ�	Score.cpp
//   �����ˣ�	������
//     ѧ�ţ�	2018302060043
//   ��������	146��
// ���뻷����	Visual Studio 2015 + EasyX_20180321(���ְ�) 
// ����޸ģ�	2019-6-12
// ʵ�ֹ��ܣ�	�����Ļ�ȡ������������жϡ������ļ�����д���
////////////////////////////////////////////////////////
#include<iostream>
#include<fstream>
#include"Score.h"
#include"Person.h"

#define COINS_PLUS_WEIGHT 50	//��Ҽӷ�Ȩ��

using namespace std;

//���캯��
Score::Score()
{
	score = 0;													//��ʼ������
	recordScore[10] = { 0 };									//��ʼ����ʷ����
	readScore();												//��ȡ��ʷ�ļ�
}

//��������
Score::~Score()
{
	score = 0;													//�ָ���ʼ������
	recordScore[10] = { 0 };									//�ָ���ʼ����ʷ����
	readScore();												//��ȡ��ʷ�ļ�
}

//���Ӽӷ֣�������
void Score::bugsPlus(int i)
{
	score += i;
}


//��Ҽӷ֣���Ҹ�����
void Score::coinsPlus(int c)									
{
	score += COINS_PLUS_WEIGHT*c;									//��Ҽӷ�=���Ȩ��*��Ҹ���
}

//��ȡ��ǰ����
int Score::getScore()									
{
	return score;
}

//��ȡ��߷�
int Score::getHighestScore()
{
	return highestScore;
}

//��ȡ��ʷ����
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

//��ȡ�����ļ�
void Score::readScore()
{
	ifstream fin;													//�����ļ���ȡ����fin
	fin.open("data\\score.dat", ios::in | ios::_Nocreate);			//�򿪷�����¼�ļ�
	if (fin.is_open())												//�ж��ļ��Ƿ��Ѵ�
	{
		char temp[10] = {0};										//�洢�ָ���������								
		fin >> recordScore[0] >> temp[0]							//��ȡ�ļ�����ʷ����
			>> recordScore[1] >> temp[1]
			>> recordScore[2] >> temp[2]
			>> recordScore[3] >> temp[3]
			>> recordScore[4] >> temp[4]
			>> recordScore[5] >> temp[5]
			>> recordScore[6] >> temp[6]
			>> recordScore[7] >> temp[7]
			>> recordScore[8] >> temp[8]
			>> recordScore[9] >> temp[9];
		highestScore = recordScore[0];								//��ȡ��߷ֵ�highestScore
		fin.close();												//�ر��ļ�
	}
	else															//��δ�ɹ����ļ�
	{
		highestScore = 0;											//��Ĭ����߷�Ϊ0
	}
}

//�жϷ���
int Score::judgeScore()
{
	if (score > highestScore)										//�жϵ�ǰ�÷��Ƿ�Ϊ��߷�
		highestScore = score;										//Ϊ������߷�=��ǰ�÷�
	if (score > recordScore[9])										//�ж��Ƿ���Ҫ���¼�¼
	{
		for (int i = 0; i < 10; i++)
			if (score == recordScore[i])							//�жϵ�ǰ�����Ƿ��Ѵ��ڷ�����¼��
				return 0;											//�Ѵ����򷵻�0
		return 1;													//���򷵻�1
	}
	else
		return 0;													//���򷵻�0
}

//д������ļ�
void Score::writeScore()
{
	ofstream fout;													//�����ļ���ȡ����fout
	fout.open("data\\score.dat", ios::out);							//�򿪷�����¼�ļ�
	if (fout.is_open())												//�ж��ļ��Ƿ��Ѵ�
	{
		if (judgeScore())											//�ж��Ƿ���Ҫ���·�����¼
		{
			recordScore[9] = score;									//Ϊ���������¼����
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
			fout << recordScore[0] << '#'							//д�������¼���ļ�
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
		fout.close();												//�ر��ļ�
	}
	else															//��δ�ɹ����ļ�
	{
		cout << "Can't write score!" << endl;						//����ʾ������Ϣ
	}
}