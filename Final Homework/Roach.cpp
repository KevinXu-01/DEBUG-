///////////////////////////////////////////////////////
// �ļ����ƣ�	Roach.cpp
//   �����ˣ�	��ʫ��
//     ѧ�ţ�	2018302060048
//   ��������	147��
// ���뻷����	Visual Studio 2015 + EasyX 20190415(beta) 
// ����޸ģ�	2019-6-12
// ʵ�ֹ��ܣ�	��������������ж�
////////////////////////////////////////////////////////
#include"Roach.h"
#include"Person.h"
#include<math.h>
#include<stdlib.h>
#include<time.h>
#include"Coins.h"

extern Person personA, personB;
int rop;
int Roach::lastx = 200;
int Roach::lasty = 200;

Roach* roachs[4] = { nullptr,nullptr,nullptr,nullptr };
bool addRoach(Roach* z);
bool deleteRoach(Roach* z);

//�µ�Roach
Roach::Roach()
{
	val = 20;											//��ֵ20
	coinsodds = 10;										//���1/10������
	gettarget();
	rotate(32, 25);
	d = a;
	skillgap = 50;										//��������������
	gettarget();										//������ȡһ��Ŀ�֮꣬�󲻻��ٸı�
	srand(time(NULL));
	zergv =  stdv;										//�������һ����׼��
	maxHP = 3+(Zerg::getgraveyard()/80);				//�������λѪ
	HP = maxHP-1;										//��ʼ����ֵ
	do
	{
		x = rand() % 640;
		y = rand() % 480;
	} while (60 < y && y < 419 && 40 < x && x < 579
		|| personA.getHealthPoint()>0 && getdistance(personA) < 10000
		|| personB.getHealthPoint() > 0 && getdistance(personB) < 10000
		|| (x - lastx)*(x - lastx) + (y - lasty)*(y - lasty)<15000);
	lastx = x;
	lasty = y;
}

//��Roach����������µ�Roach
bool  addRoach(Roach* z)
{
	if (rop > 3)
		return false;
	else
	{
		roachs[rop] = z;
		(rop)++;
		return true;
	}
}

//ɾ��Roach��������������
bool deleteRoach(Roach* z)
{
	int i;
	for (i = 0; i < rop; i++)
	{
		if (z == roachs[i])
			break;
	}
	if (roachs[i]->ifcoins() == true)
		addCoin(new Coins(roachs[i]->x, roachs[i]->y));//coins
	if (i == rop)
		return false;
	else
	{
		delete z;
		for (; i < rop - 1; i++)
			roachs[i] = roachs[i + 1];
		roachs[i] = nullptr;
		rop--;
		return true;
	}
}

//�ж�
void Roach::act()
{
	if (personA.getHealthPoint() <= 0 || personB.getHealthPoint() <= 0)
		gettarget();
	clock++;
	if ((clock % 100 == 0 || clock % 300 == 0) && zergv < 15)
		zergv++;
	int k;
	for (k = 0; k < rop; k++)
	{
		if (this == roachs[k])
			break;
	}
	zergv = stdv + k;									//Խ��Խ��
	rotate(32, 25);										//ת��
	e = d;
	d = c;
	c = b;
	b = a;
	if (!block(32, 25))
	{
		x += unum(zergv * cos(e));
		y -= unum(zergv * sin(e));
	}													//�ƶ�
	drawroach();										//����
	if (bite() == 0 && skillgap <= 0 && HP != 3)
		recover();										//bite or recover or noting
}

//bite ����
int Roach::bite()
{
	if (skillgap > 0)
		return 0;
	else if (getdistance(personA) >= 2500 && getdistance(personB) >= 2500)
	{
		return 0;
	}
	else if (getdistance(personA) < 2500 && (getdistance(personB) >= 2500 || personB.getHealthPoint() <= 0))
	{
		personA.getHit();
		skillgap = 30;
		return 1;
	}
	else if ((getdistance(personA) >= 2500 || personA.getHealthPoint() <= 0) && getdistance(personB) < 2500)
	{
		personB.getHit();
		skillgap = 30;
		return 1;
	}
	else if (getdistance(personA) < 2500 && getdistance(personB) < 2500)
	{
		rand() % 2 ? personA.getHit() : personB.getHit();
		skillgap = 30;
		return 1;
	}
}

//recover �ظ�
void Roach::recover()
{
	if(Zerg::getgraveyard()<=120)
		HP++;
	if (Zerg::getgraveyard() > 120)
		HP = maxHP;										//��Ϸ����ֱ�ӻظ�ȫ������ֵ
	skillgap = 40;										//�ظ���CDʱ���Գ�
}