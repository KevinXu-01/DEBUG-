///////////////////////////////////////////////////////
// �ļ����ƣ�	Roach.h
//   �����ˣ�	��ʫ��
//     ѧ�ţ�	2018302060048
//   ��������	25��
// ���뻷����	Visual Studio 2015 + EasyX 20190415(beta) 
// ����޸ģ�	2019-6-12
// ʵ�ֹ��ܣ�	��������������ж�
////////////////////////////////////////////////////////
#pragma once
#include"Zerg.h"

class Roach :public Zerg								//���
{
public:
	Roach();	 										//����
	~Roach()
	{
		Zerg::ToGraveyard();							//��������������һ
	}
	void act();											//�ж�
	int i = 0;											//���Ƽ���
	void drawroach();									//����
private:
	void recover();										//recover
	int bite();											//bite
	int type;											//����״̬
	static int lastx;
	static int lasty;									//��һֻͬ�����λ��
};

extern int rop;											//ͳ�����е���Ŀ
static float roach_Max;									//���������Ŀ
static int roach_generate_gap;							//������ȴ�ļ��