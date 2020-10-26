///////////////////////////////////////////////////////
// 文件名称：	Zergling.cpp
//   负责人：	江诗烨
//     学号：	2018302060048
//   代码量：	170行
// 编译环境：	Visual Studio 2015 + EasyX 20190415(beta) 
// 最后修改：	2019-6-12
// 实现功能：	跳虫个体的生成与行动
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

//构造
Zergling::Zergling()
{
	val = 10;											//分数权重10
	coinsodds = 30;										//金币掉落率1/30
	gettarget();
	rotate(26, 22);
	d = a;
	attackgap = 40;										//攻击冷却
	skillgap = 120;										//加速用时钟
	type = 0;
	srand(time(NULL));
	zergv = 0.75* stdv;									//3/4标准速
	if (zergv > 15)
		zergv = 15;
	maxHP = 1;											//一单位血
	if (Zerg::getgraveyard() > 60)
		maxHP = 2;
	HP = maxHP;											//初始生命值满
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

//数组内添加
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

//删除并重新排序
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

//行动
void Zergling::act()
{
	clock++;
	if (clock % 300==0)
		zergv++;
	if (type == 0||type==1)
	{
		gettarget();										//获取目标
		rotate(26, 22);										//转向
		e = d;
		d = c;
		c = b;
		b = a;
		if (!block(26, 22))
		{
			x += unum(zergv * cos(e));
			y -= unum(zergv * sin(e));
		}													//移动
		drawzergling();										//绘制
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

//攻击
void Zergling::attack()
{
	if (getdistance(personA) >= 2500 && getdistance(personB) >= 2500)
		;													//必要的空语句，以完成此顺序检查结构
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

//shift 改变形态（变速
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