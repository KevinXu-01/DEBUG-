///////////////////////////////////////////////////////
// �ļ����ƣ�	Zergling.h
//   �����ˣ�	��ʫ��
//     ѧ�ţ�	2018302060048
//   ��������	26��
// ���뻷����	Visual Studio 2015 + EasyX 20190415(beta) 
// ����޸ģ�	2019-6-12
// ʵ�ֹ��ܣ�	���������������ж�
////////////////////////////////////////////////////////
#pragma once
#include"Zerg.h"

class Zergling :public Zerg								//����
{
public:
	Zergling(); 										//����
	~Zergling()
	{
		Zerg::ToGraveyard();							//��������������һ
	}
	void act();											//�ж�
	int i = 64;											//���Ƽ���
	void drawzergling();								//����
	int type = 0;										//״̬���Ƿ����
private:
	void shift();										//shift
	void attack();										//attack
	int attackgap;										//attackgap
	static int lastx;
	static int lasty;									//��һֻͬ�����λ��
};

extern int zergp;										//��������
static float zergling_Max;								//����������
static int zergling_generate_gap;						//�������