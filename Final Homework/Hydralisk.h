///////////////////////////////////////////////////////
// �ļ����ƣ�	Baneling.h
//   �����ˣ�	��ʫ��
//     ѧ�ţ�	2018302060048
//   ��������	36��
// ���뻷����	Visual Studio 2015 + EasyX 20190415(beta) 
// ����޸ģ�	2019-6-12
// ʵ�ֹ��ܣ�	�̳������������ж�
////////////////////////////////////////////////////////
#pragma once
#include"Zerg.h"
class Hydralisk :public Zerg							//����
{
public:
	Hydralisk(); 										//����
	~Hydralisk()
	{
		Zerg::ToGraveyard();							//��������������һ
	}
	int hypv=0;											//ǿ���ٶ�
	void act();											//�ж�
	int i = 0;											//���Ƽ���
	int j = 1;											//Ť������
	void drawhydralisk();								//����
private:
	void spit();										//spit
	static int lastx;
	static int lasty;									//��һֻͬ�����λ��
};

extern int hydrap;										//����
static float hydralisk_Max;								//�����Ŀ
static int hydralisk_generate_gap;						//������ȴʱ��

class Hydraspit:public Zerg								//�̳棨���ߵĹ���
{
public:
	Hydraspit(int ix, int iy, float ia,int hv) ; 		//����
	~Hydraspit() {};
	void act();											//�ж�
	void drawhydraspit();								//����
};

extern int spitp;										//�������д̵�����
extern float hydraspit_Max;								//���������ֵĴ̵���Ŀ