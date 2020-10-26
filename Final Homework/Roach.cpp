///////////////////////////////////////////////////////
// 文件名称：	Roach.cpp
//   负责人：	江诗烨
//     学号：	2018302060048
//   代码量：	147行
// 编译环境：	Visual Studio 2015 + EasyX 20190415(beta) 
// 最后修改：	2019-6-12
// 实现功能：	蟑螂个体的生成与行动
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

//新的Roach
Roach::Roach()
{
	val = 20;											//分值20
	coinsodds = 10;										//金币1/10掉落率
	gettarget();
	rotate(32, 25);
	d = a;
	skillgap = 50;										//出生后稍作休整
	gettarget();										//蟑螂仅获取一次目标，之后不会再改变
	srand(time(NULL));
	zergv =  stdv;										//蟑螂至少一个标准速
	maxHP = 3+(Zerg::getgraveyard()/80);				//蟑螂三单位血
	HP = maxHP-1;										//初始生命值
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

//向Roach数组内添加新的Roach
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

//删除Roach并重新排序数组
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

//行动
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
	zergv = stdv + k;									//越多越快
	rotate(32, 25);										//转向
	e = d;
	d = c;
	c = b;
	b = a;
	if (!block(32, 25))
	{
		x += unum(zergv * cos(e));
		y -= unum(zergv * sin(e));
	}													//移动
	drawroach();										//绘制
	if (bite() == 0 && skillgap <= 0 && HP != 3)
		recover();										//bite or recover or noting
}

//bite 攻击
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

//recover 回复
void Roach::recover()
{
	if(Zerg::getgraveyard()<=120)
		HP++;
	if (Zerg::getgraveyard() > 120)
		HP = maxHP;										//游戏后期直接回复全部生命值
	skillgap = 40;										//回复后CD时间略长
}