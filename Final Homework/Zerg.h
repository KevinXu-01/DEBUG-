///////////////////////////////////////////////////////
// �ļ����ƣ�	Zerg.h
//   �����ˣ�	��ʫ��
//     ѧ�ţ�	2018302060048
//   ��������	51��
// ���뻷����	Visual Studio 2015 + EasyX 20190415(beta) 
// ����޸ģ�	2019-6-12
// ʵ�ֹ��ܣ�	�棨���ࣩ�Ļ�������
////////////////////////////////////////////////////////
#pragma once
#include"Person.h"
#define stdv 3
//enum ztype { baneling, hydralisk, roach, zergling,zergspit };	//���������ߣ���룬���棬�̣��ɱ��ӵ��赲�������棩

class Zerg
{
public:
	bool block(int hx,int hy);							//��Ͱ������
	double aofblock1(int halfx,int halfy);
	double aofblock2(int halfx,int halfy);				//������
	int distofblock1();
	int distofblock2();									//��Ͱ����
	int clock=0;										//���ʱ���ʱ��
	void getscore();									//��ɱ����
	bool ifcoins();										//�Ƿ������
	int at;												//ת���ٶ�
	double e;											//����Ƕ�
	double b, c, d, a;									//��ʱ��ŽǶȣ��ӳ�ת��
	void rotate(int halfx,int halfy);					//�ı�a��ֵ
	int HP;												//��ǰ����
	int maxHP;											//�������ֵ
	int skillgap;										//������ȴʱ��
	int zergv;											//�ٶ�
	int scorevalue();									//����
	int val=0;											//Ȩ
	int coinsodds=10;									//���伸��
	static int graveyard;								//��������������
	static void ToGraveyard()
	{
		graveyard++;									//ͳ����������������
	}
	static int getgraveyard()
	{
		return graveyard;
	}
	bool judgeDie()										//�Ƿ�����
	{
		if (HP <= 0)
			return true;
		else
			return false;
	}
	void gettarget();									//Ѱ��Ŀ�꣨�ı䲢��ȡ
	bool ifhunting = 0;									//�Ƿ�����Ŀ��
	Person *target=nullptr;								//target
	int getdistance(Person person);						//��ȡ���루ƽ��ֵ
	void damaged(int damage);							//�ܵ��˺�
	int x, y;											//x���꼰y����
};
int unum(double a);										//����ȡ��