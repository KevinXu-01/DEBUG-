///////////////////////////////////////////////////////
// �ļ����ƣ�	Zergling.cpp
//   �����ˣ�	��ʫ��
//     ѧ�ţ�	2018302060048
//   ��������	170��
// ���뻷����	Visual Studio 2015 + EasyX 20190415(beta) 
// ����޸ģ�	2019-6-12
// ʵ�ֹ��ܣ�	���������������ж�
////////////////////////////////////////////////////////
#include"Zergling.h"
#include"Person.h"
#include<math.h>
#include<stdlib.h>
#include<time.h>
#include"Coins.h"

extern Person personA, personB;
int zergp;
int Zergling::lastx = 200;
int Zergling::lasty = 200;

Zergling* zerglings[5] = { nullptr,nullptr,nullptr,nullptr,nullptr };
bool addZergling(Zergling* z);
bool deleteZergling(Zergling* z);

//����
Zergling::Zergling()
{
	val = 10;											//����Ȩ��10
	coinsodds = 30;										//��ҵ�����1/30
	gettarget();
	rotate(26, 22);
	d = a;
	attackgap = 40;										//������ȴ
	skillgap = 120;										//������ʱ��
	type = 0;
	srand(time(NULL));
	zergv = 0.75* stdv;									//3/4��׼��
	if (zergv > 15)
		zergv = 15;
	maxHP = 1;											//һ��λѪ
	if (Zerg::getgraveyard() > 60)
		maxHP = 2;
	HP = maxHP;											//��ʼ����ֵ��
	do
	{
		x = rand() % 640;
		y = rand() % 480;
	} while (60 < y && y < 419 && 40 < x && x < 579
		|| personA.getHealthPoint()>0 && getdistance(personA) < 12250
		|| personB.getHealthPoint() > 0 && getdistance(personB) < 12250 
		|| (x - lastx)*(x - lastx) + (y - lasty)*(y - lasty)<10000);
	lastx = x;
	lasty = y;
}

//���������
bool  addZergling(Zergling* z)
{
	if (zergp > 4)
		return false;
	else
	{
		zerglings[zergp] = z;
		(zergp)++;
		return true;
	}
}

//ɾ������������
bool deleteZergling(Zergling* z)
{
	int i;
	for (i = 0; i < zergp; i++)
	{
		if (z == zerglings[i])
			break;
	}
	if (zerglings[i]->ifcoins() == true)
		addCoin(new Coins(zerglings[i]->x, zerglings[i]->y));//coins
	if (i == zergp)
		return false;
	else
	{
		delete z;
		for (; i < zergp - 1; i++)
			zerglings[i] = zerglings[i + 1];
		zerglings[i] = nullptr;
		zergp--;
		return true;
	}
}

//�ж�
void Zergling::act()
{
	clock++;
	if (clock % 300==0)
		zergv++;
	if (type == 0||type==1)
	{
		gettarget();										//��ȡĿ��
		rotate(26, 22);										//ת��
		e = d;
		d = c;
		c = b;
		b = a;
		if (!block(26, 22))
		{
			x += unum(zergv * cos(e));
			y -= unum(zergv * sin(e));
		}													//�ƶ�
		drawzergling();										//����
	}
	else if (type == 2)
	{
		if (!block(26, 22))
		{
			x += unum(zergv * cos(e));
			y -= unum(zergv * sin(e));
		}
		drawzergling();
	}
	if(attackgap<=0)
		attack();
	if (attackgap > 0)
		attackgap--;
	shift();
}

//����
void Zergling::attack()
{
	if (getdistance(personA) >= 2500 && getdistance(personB) >= 2500)
		;													//��Ҫ�Ŀ���䣬����ɴ�˳����ṹ
	else if (getdistance(personA) < 2500 && (getdistance(personB) >= 2500 || personB.getHealthPoint() <= 0))
	{
		personA.getHit();
		attackgap = 40;
	}
	else if ((getdistance(personA) >= 2500 || personA.getHealthPoint() <= 0) && getdistance(personB) < 2500)
	{
		personB.getHit();
		attackgap = 40;
	}
	else if (getdistance(personA) < 2500 && getdistance(personB) < 2500 && type != 2)
	{
		rand() % 2 ? personA.getHit() : personB.getHit();
		attackgap = 40;
	}
	else if (getdistance(personA) < 2500 && getdistance(personB) < 2500 && type == 2)
	{
		personA.getHit();
		personB.getHit();
		attackgap = 30;
	}
}

//shift �ı���̬������
void Zergling::shift()
{
	skillgap--;
	if (skillgap == 65)
	{
		type = 1;
		zergv += 3;
	}
	else if (skillgap == 20)
	{
		type = 2;
		zergv += 5;
	}
	else if (skillgap == 0)
	{
		type = 0;
		zergv -= 8;
		skillgap = 250;
	}
}