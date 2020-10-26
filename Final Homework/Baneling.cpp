///////////////////////////////////////////////////////
// �ļ����ƣ�	Baneling.cpp
//   �����ˣ�	��ʫ��
//     ѧ�ţ�	2018302060048
//   ��������	142��
// ���뻷����	Visual Studio 2015 + EasyX 20190415(beta) 
// ����޸ģ�	2019-6-12
// ʵ�ֹ��ܣ�	���������������ж�
////////////////////////////////////////////////////////
#include"Baneling.h"
#include"Person.h"
#include<math.h>
#include<stdlib.h>
#include<time.h>
#include"Coins.h"

extern Person personA, personB;
int banep;
int Baneling::lastx = 200;
int Baneling::lasty = 200;

Baneling* banelings[5] = {nullptr,nullptr,nullptr,nullptr,nullptr};
bool addBaneling(Baneling* z);
bool deleteBaneling(Baneling* z);

//����Baneling
Baneling::Baneling()
{
	val = 15;											//��ֵȨ��Ϊ15
	coinsodds = 10;										//��ҵ�����ʮ��֮һ
	gettarget();
	rotate(26, 20);
	d = a;												//��һ��ת����Ҫ��ʱ
	srand(time(NULL));
	zergv = 1 * stdv+Zerg::getgraveyard()/60;			//������ʼʱ1����׼��
	if (zergv > 14)
		zergv = 14;
	maxHP = 1;											//����һ��λѪ
	HP = maxHP;											//��ʼ����ֵ��
	do
	{
		x = rand() % 640;
		y = rand() % 480;
	} while (60 < y && y < 419 && 40 < x && x < 579
		|| personA.getHealthPoint()>0 && getdistance(personA) < 10000
		|| personB.getHealthPoint() > 0 && getdistance(personB) < 10000
		||(x-lastx)*(x-lastx)+(y-lasty)*(y-lasty)<10000);
	lastx = x;
	lasty = y;
}

//����������Baneling
bool  addBaneling(Baneling* z)							//����µ�Baneling
{
	if (banep > 4)
		return false;
	else
	{
		banelings[banep] = z;
		(banep)++;
		return true;
	}
}

//ɾ��Baneling����������Ԫ����������
bool deleteBaneling(Baneling* z)						//ɾ��������Baneling
{
	int i;
	for (i = 0; i < banep; i++)
	{
		if (z == banelings[i])
			break;
	}													//�ҵ�Ŀ������������е�λ��
	if(banelings[i]->ifcoins()==true)
		addCoin(new Coins(banelings[i]->x, banelings[i]->y));//coins
	if (i == banep)
		return false;
	else
	{
		delete z;
		for (; i < banep - 1; i++)
			banelings[i] = banelings[i + 1];			//�����ڵĳ�����������
		banelings[i] = nullptr;
		banep--;
		return true;
	}
}

//�ж�
void Baneling::act()
{
	clock++;
	if (clock % 30 == 0&&zergv<12)
		zergv++;
	if (type==0)
	{
		gettarget();										//��ȡĿ��
		rotate(26, 20);										//ת��
		e = d;
		d = c;
		c = b;
		b = a;												//�ӳ�ת�򣬼�¼����ʱ�̷���
		if (!block(26,20))
		{
			x += unum(zergv*cos(e));
			y -= unum(zergv*sin(e));
		}													//�ƶ�
		drawbaneling();										//����
		if (((personA.getHealthPoint() >= 0 && getdistance(personA) < 2200 )|| personB.getHealthPoint()>=0&&getdistance(personB) < 2200))
		{
			type = 1; staa = a;
		}													//����ƽ��С��2200��λʱ����
	}
	else if(type==1)
	{
		a = staa;
		drawbaneling();
		j++;
		if (j >= 10)
		{
			if (judgeDie() == false) 
			{
				explode();									//���ݾ��ͺ�ը
				type = 2; i = 0;
			}
		}
	}
	else if (type == 2) 
	{
		if (drawexplode())									//���Ʊ�ը
			type = 4;
	}
	else
	{
		HP = 0;												//��������
	}
}

//��ը�˺�����
void Baneling::explode()
{
	coinsodds = 50;
	if (personA.getHealthPoint()>0&&getdistance(personA) <= 2500)
	{
		personA.getHit(); personA.getHit();
	}														//��ը��������������˺�
	if (personB.getHealthPoint()>0&&getdistance(personB) <= 2500)
	{
		personB.getHit(); personB.getHit();
	}
}