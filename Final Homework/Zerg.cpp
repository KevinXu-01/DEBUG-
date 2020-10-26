///////////////////////////////////////////////////////
// �ļ����ƣ�	Zerg.cpp
//   �����ˣ�	��ʫ��
//     ѧ�ţ�	2018302060048
//   ��������	145��
// ���뻷����	Visual Studio 2015 + EasyX 20190415(beta) 
// ����޸ģ�	2019-6-12
// ʵ�ֹ��ܣ�	�棨���ࣩ�Ļ�������
////////////////////////////////////////////////////////
#include"Zerg.h"
#include<stdlib.h>
#include<time.h>
#include<math.h>
#include"Score.h"
#include"Item.h"
#define PI 3.1415

extern Score score;
extern Person personA, personB;
extern Item item;
int Zerg::graveyard = 0;

//�����ƽ��
int Zerg::getdistance(Person p)
{
	return (p.getPersonPositionX() - x)*(p.getPersonPositionX() - x) + (p.getPersonPositionY() - y)*(p.getPersonPositionY() - y);
}

//�ܵ��˺�
void Zerg::damaged(int damage)
{
	HP -= damage;
}


//�Ƿ��н�ҵ���
bool Zerg::ifcoins()
{
	srand(time(NULL));
	if (rand() % coinsodds == 0)
		return 1;
	else
		return 0;
}

//������ֵ
int Zerg::scorevalue()
{
	return 10 * (Zerg::getgraveyard() / 100) + 10;
}

//rotate
void Zerg::rotate(int halfx, int halfy)
{
	if (target->getPersonPositionY()+50 == y + halfy && target->getPersonPositionX()+50 != x+ halfx)
		a = (target->getPersonPositionX()+50 > x + halfx) ? 0 : PI;
	else if (target->getPersonPositionY()+50 < y + halfy)
		a = (PI / 2 + atan((target->getPersonPositionX()+50 - x - halfx) / (double)(target->getPersonPositionY()+50 - y - halfy)));
	else if (target->getPersonPositionY()+50>y + halfy)
		a = (3 * PI / 2 + atan((target->getPersonPositionX()+50 - x - halfx) / (double)(target->getPersonPositionY()+50 - y - halfy)));
}


//Ŀ��
void Zerg::gettarget()
{
	if (personB.getHealthPoint() <= 0)
	{
		target = &personA;
	}
	else if (personA.getHealthPoint() <= 0)
	{
		target = &personB;
	}
	else if (ifhunting == 0) {
		srand(time(NULL));
		if (getdistance(personA) < getdistance(personB)) {
			target = &personA;
		}
		else if (getdistance(personA) > getdistance(personB)) {
			target = &personB;
		}
		else {
			target = rand() % 2 ? &personA : &personB;
		}
		ifhunting = 1;
	}
	else if (ifhunting == 1)
	{
		if ((target == &personA) && (0.7 * getdistance(personA) > getdistance(personB)))
			target = &personB;
		else if ((target == &personB) && (0.7 * getdistance(personB) > getdistance(personA)))
			target = &personA;
	}
}

//����ӷ�
void Zerg::getscore()
{
	if (personA.getHealthPoint() > 0 || personB.getHealthPoint() > 0)
		score.bugsPlus(val);
}

//����ȡ��
int unum(double a)
{
	if (a > 0)
		return -(int)(-a);
	else
		return (int)a;
}

//��ȡ��Ͱ�Ƕ�
double Zerg::aofblock1(int halfx,int halfy)
{
	if (item.AgetOilTankPositionY()+20 == y + halfy && item.AgetOilTankPositionX()+20 != x + halfx)
		return (item.AgetOilTankPositionX()+20 > x + halfx) ? 0 : PI;
	else if (item.AgetOilTankPositionY() + 20 < y + halfy)
		return (PI / 2 + atan((item.AgetOilTankPositionX() + 20 - x - halfx) / (double)(item.AgetOilTankPositionY() + 20 - y - halfy)));
	else if (item.AgetOilTankPositionY() + 20>y + halfy)
		return (3 * PI / 2 + atan((item.AgetOilTankPositionX() + 20 - x - halfx) / (double)(item.AgetOilTankPositionY() + 20 - y - halfy)));
}

double Zerg::aofblock2(int halfx, int halfy)
{
	if (item.BgetOilTankPositionY() + 20 == y + halfy && item.BgetOilTankPositionX() + 20 != x + halfx)
		return (item.BgetOilTankPositionX() + 20 > x + halfx) ? 0 : PI;
	else if (item.BgetOilTankPositionY() + 20 < y + halfy)
		return (PI / 2 + atan((item.BgetOilTankPositionX() + 20 - x - halfx) / (double)(item.BgetOilTankPositionY() + 20 - y - halfy)));
	else if (item.BgetOilTankPositionY() + 20>y + halfy)
		return (3 * PI / 2 + atan((item.BgetOilTankPositionX() + 20 - x - halfx) / (double)(item.BgetOilTankPositionY() + 20 - y - halfy)));
}

//��ȡ��Ͱ���루ƽ��ֵ
int Zerg::distofblock1()
{
	return ((x - item.AgetOilTankPositionX())*(x - item.AgetOilTankPositionX()) + (y - item.AgetOilTankPositionY())*(y - item.AgetOilTankPositionY()));
}

int Zerg::distofblock2()
{
	return ((x - item.BgetOilTankPositionX())*(x - item.BgetOilTankPositionX()) + (y - item.BgetOilTankPositionY())*(y - item.BgetOilTankPositionY()));
}

//�Ƿ�����
bool Zerg::block(int hx,int hy)
{
	if (distofblock1() < 2025 && (aofblock1(hx, hy) - e)*(aofblock1(hx, hy) - e) < (PI / 6)*(PI / 6))
		return true;
	else if (distofblock2() < 2025 && (aofblock2(hx, hy) - e)*(aofblock2(hx, hy) - e) < (PI / 6)*(PI / 6))
		return true;
	else
		return false;
}