///////////////////////////////////////////////////////
// 文件名称：	Baneling.cpp
//   负责人：	江诗烨
//     学号：	2018302060048
//   代码量：	142行
// 编译环境：	Visual Studio 2015 + EasyX 20190415(beta) 
// 最后修改：	2019-6-12
// 实现功能：	爆虫个体的生成与行动
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

//生成Baneling
Baneling::Baneling()
{
	val = 15;											//分值权重为15
	coinsodds = 10;										//金币掉落率十分之一
	gettarget();
	rotate(26, 20);
	d = a;												//第一次转向不需要延时
	srand(time(NULL));
	zergv = 1 * stdv+Zerg::getgraveyard()/60;			//毒爆开始时1个标准速
	if (zergv > 14)
		zergv = 14;
	maxHP = 1;											//毒爆一单位血
	HP = maxHP;											//初始生命值满
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

//数组内增加Baneling
bool  addBaneling(Baneling* z)							//添加新的Baneling
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

//删除Baneling并对数组内元素重新排序
bool deleteBaneling(Baneling* z)						//删除死亡的Baneling
{
	int i;
	for (i = 0; i < banep; i++)
	{
		if (z == banelings[i])
			break;
	}													//找到目标虫子在数组中的位置
	if(banelings[i]->ifcoins()==true)
		addCoin(new Coins(banelings[i]->x, banelings[i]->y));//coins
	if (i == banep)
		return false;
	else
	{
		delete z;
		for (; i < banep - 1; i++)
			banelings[i] = banelings[i + 1];			//数组内的虫子重新排序
		banelings[i] = nullptr;
		banep--;
		return true;
	}
}

//行动
void Baneling::act()
{
	clock++;
	if (clock % 30 == 0&&zergv<12)
		zergv++;
	if (type==0)
	{
		gettarget();										//获取目标
		rotate(26, 20);										//转向
		e = d;
		d = c;
		c = b;
		b = a;												//延迟转向，记录各个时刻方向
		if (!block(26,20))
		{
			x += unum(zergv*cos(e));
			y -= unum(zergv*sin(e));
		}													//移动
		drawbaneling();										//绘制
		if (((personA.getHealthPoint() >= 0 && getdistance(personA) < 2200 )|| personB.getHealthPoint()>=0&&getdistance(personB) < 2200))
		{
			type = 1; staa = a;
		}													//距离平方小于2200单位时引爆
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
				explode();									//短暂静滞后爆炸
				type = 2; i = 0;
			}
		}
	}
	else if (type == 2) 
	{
		if (drawexplode())									//绘制爆炸
			type = 4;
	}
	else
	{
		HP = 0;												//彻底死亡
	}
}

//爆炸伤害人类
void Baneling::explode()
{
	coinsodds = 50;
	if (personA.getHealthPoint()>0&&getdistance(personA) <= 2500)
	{
		personA.getHit(); personA.getHit();
	}														//爆炸对人类造成两点伤害
	if (personB.getHealthPoint()>0&&getdistance(personB) <= 2500)
	{
		personB.getHit(); personB.getHit();
	}
}