///////////////////////////////////////////////////////
// �ļ����ƣ�	Baneling.h
//   �����ˣ�	��ʫ��
//     ѧ�ţ�	2018302060048
//   ��������	27��
// ���뻷����	Visual Studio 2015 + EasyX 20190415(beta) 
// ����޸ģ�	2019-6-12
// ʵ�ֹ��ܣ�	���������������ж�
////////////////////////////////////////////////////////
#pragma once
#include"Zerg.h"

class Baneling :public Zerg								//����
{
public:
	Baneling(); 										//����
	~Baneling()
	{
		Zerg::ToGraveyard();							//��������������һ
	}
	void act();											//�ж�
	int i = 0;											//���Ƽ���
	int j = 0;											//��ըǰ����
	int drawexplode();
	void drawbaneling();								//����
	int type = 0;										//״̬���Ƿ�ը
	double staa=0;										//����״̬ת���
private:
	void explode();										//explode
	static int lastx;
	static int lasty;									//��һֻͬ�����λ��
};

extern int banep;										//����
static float baneling_Max;								//�����Ŀ
static int baneling_generate_gap;						//������ȴʱ��