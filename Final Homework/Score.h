///////////////////////////////////////////////////////
// �ļ����ƣ�	Score.h
//   �����ˣ�	������
//     ѧ�ţ�	2018302060043
//   ��������	21��
// ���뻷����	Visual Studio 2015 + EasyX_20180321(���ְ�) 
// ����޸ģ�	2019-6-12
// ʵ�ֹ��ܣ�	����������
////////////////////////////////////////////////////////
#pragma once

//������
class Score		
{
public:
	Score();								//���캯��
	~Score();								//��������
	void bugsPlus(int s);					//���Ӽӷ֣�������
	void coinsPlus(int c);					//��Ҽӷ֣���Ҹ�����
	int getScore();							//��ȡ��ǰ����
	int getHighestScore();					//��ȡ��߷�
	void gerRecordScore(int s[],int l);		//��ȡ��ʷ����
	void readScore();						//��ȡ�����ļ�
	int judgeScore();						//�жϷ���
	void writeScore();						//д������ļ�
private:
	int score ;								//��ҹ�ͬ����
	int highestScore;						//��߷�
	int recordScore[10];					//��ʷ����
};