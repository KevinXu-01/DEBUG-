///////////////////////////////////////////////////////
// �ļ����ƣ�	Baneling.cpp
//   �����ˣ�	��ʫ��
//     ѧ�ţ�	2018302060048
//   ��������	196��
// ���뻷����	Visual Studio 2015 + EasyX 20190415(beta) 
// ����޸ģ�	2019-6-12
// ʵ�ֹ��ܣ�	�̳������������ж�
////////////////////////////////////////////////////////
#include"Hydralisk.h"
#include"Person.h"
#include<math.h>
#include<stdlib.h>
#include<time.h>
#include"Coins.h"

extern Person personA, personB;
int hydrap;
int spitp;
float hydraspit_Max;
int Hydralisk::lastx = 200;
int Hydralisk::lasty = 200;

Hydralisk* hydralisks[3] = { nullptr,nullptr,nullptr };
Hydraspit* hydraspits[3] = { nullptr,nullptr,nullptr };
bool addHydraspit(Hydraspit*z);
bool deleteHydraspit(Hydraspit*z);
bool addHydralisk(Hydralisk* z);
bool deleteHydralisk(Hydralisk* z);

//����hydralisk
Hydralisk::Hydralisk()
{
	val = 15;											//����Ȩ��15
	coinsodds = 20;										//�����Ҽ���1/20
	gettarget();
	rotate(25, 21);
	d = a;
	i = 0;
	srand(time(NULL));
	zergv = stdv;										//����һ����׼�٣������ٶ��ڷ�Χ�ڲ���
	maxHP = 2;											//��������λѪ
	HP = maxHP;											//��ʼ����ֵ��
	skillgap = 20;										//skill_CD
	do
	{
		x = rand() % 640;
		y = rand() % 480;
	} while (60 < y && y < 419 && 40 < x && x < 579
		|| personA.getHealthPoint()>0 && getdistance(personA) < 16000
		|| personB.getHealthPoint() > 0 && getdistance(personB) < 16000
		|| (x - lastx)*(x - lastx) + (y - lasty)*(y - lasty)<10000);
	lastx = x;
	lasty = y;
}

//��hydralisks��������µ�hydralisk
bool  addHydralisk(Hydralisk* z)
{
	if (hydrap > 2)
		return false;
	else
	{
		hydralisks[hydrap] = z;
		(hydrap)++;
		return true;
	}
}

//ɾ��hydralisk����������Ԫ����������
bool deleteHydralisk(Hydralisk* z)
{
	int i;
	for (i = 0; i < hydrap; i++)
	{
		if (z == hydralisks[i])
			break;
	}													//�ҵ�Ŀ������������е�λ��
	if (hydralisks[i]->ifcoins() == true)
		addCoin(new Coins(hydralisks[i]->x, hydralisks[i]->y));//coins
	if (i == hydrap)
		return false;
	else
	{
		delete z;
		for (; i < hydrap - 1; i++)
			hydralisks[i] = hydralisks[i + 1];			//�����ڵĳ�����������
		hydralisks[i] = nullptr;
		hydrap--;
		return true;
	}
}

//�ж�
void Hydralisk::act()
{
	clock++;
	if (clock % 100==0)
		hypv++;
	if (clock % 500==0)
		hypv += 2;
	zergv =stdv+ ((rand() % 5) - 2);					//�ٶȿɱ䣨��Ȼ���ص�
	gettarget();										//��ȡĿ��
	rotate(25, 21);										//ת��
	e = d;
	d = c;
	c = b;
	b = a;
	int k;
	for (k = 0; k < hydrap; k++)
	{
		if (this == hydralisks[k])
			break;
	}
	if (getdistance(*target) > 22500+500*k) 
	{
		if (!block(25, 21))
		{
			x += unum(zergv*cos(e));
			y -= unum(zergv*sin(e));
		}
	}													//�ƶ�
	drawhydralisk();									//����
	skillgap--;
	spit();
}

//spit �³���
void Hydralisk::spit()
{
	if (skillgap <= 0 && spitp<hydraspit_Max&&spitp != 3)
	{
		addHydraspit(new Hydraspit(x, y, e,hypv));
		skillgap = 30;
	}
}

//�����µĴ�
Hydraspit::Hydraspit(int ix,int iy,float ia,int hv)
{
	e = ia;
	x =ix+ unum(15*cos(e));
	y =iy+ unum(15*sin(e));
	zergv = 2*stdv+hv;
	maxHP = 1;											//��λѪ
	HP = maxHP;
}

//������������µĴ�
bool  addHydraspit(Hydraspit* z)
{
	if (spitp > 2)
		return false;
	else
	{
		hydraspits[spitp] = z;
		(spitp)++;
		return true;
	}
}

//ɾ����������������
bool deleteHydraspit(Hydraspit* z)
{
	int i;
	for (i = 0; i < spitp; i++)
	{
		if (z == hydraspits[i])
			break;
	}
	if (i == spitp)
		return false;
	else
	{
		delete z;
		for (; i < spitp - 1; i++)
			hydraspits[i] = hydraspits[i + 1];
		hydraspits[i] = nullptr;
		spitp--;
		return true;
	}
}

//���ж�
void Hydraspit::act()
{
	x += unum(zergv*cos(e));
	y -= unum(zergv*sin(e));									//�ƶ�
	if (personA.getHealthPoint()>0&&getdistance(personA) <= 2500 && (getdistance(personB) > 2500 || personB.getHealthPoint() <= 0))
	{
		personA.getHit();
		HP = 0;
	}
	else if ((getdistance(personA) > 2500 || personA.getHealthPoint() <= 0) && getdistance(personB) <= 2500&&personB.getHealthPoint()>0)
	{
		personB.getHit();
		HP = 0;
	}
	else if (getdistance(personA) <= 2500 && getdistance(personB) <= 2500)
	{
		rand() % 2 ? personA.getHit() : personB.getHit();
		HP = 0;
	}
	drawhydraspit();											//����
}