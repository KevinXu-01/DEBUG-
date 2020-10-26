///////////////////////////////////////////////////////
// 文件名称：	Baneling.cpp
//   负责人：	江诗烨
//     学号：	2018302060048
//   代码量：	196行
// 编译环境：	Visual Studio 2015 + EasyX 20190415(beta) 
// 最后修改：	2019-6-12
// 实现功能：	刺虫个体的生成与行动
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

//生成hydralisk
Hydralisk::Hydralisk()
{
	val = 15;											//分数权重15
	coinsodds = 20;										//掉落金币几率1/20
	gettarget();
	rotate(25, 21);
	d = a;
	i = 0;
	srand(time(NULL));
	zergv = stdv;										//刺蛇一个标准速（刺蛇速度在范围内波动
	maxHP = 2;											//刺蛇两单位血
	HP = maxHP;											//初始生命值满
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

//向hydralisks数组添加新的hydralisk
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

//删除hydralisk并对数组内元素重新排序
bool deleteHydralisk(Hydralisk* z)
{
	int i;
	for (i = 0; i < hydrap; i++)
	{
		if (z == hydralisks[i])
			break;
	}													//找到目标虫子在数组中的位置
	if (hydralisks[i]->ifcoins() == true)
		addCoin(new Coins(hydralisks[i]->x, hydralisks[i]->y));//coins
	if (i == hydrap)
		return false;
	else
	{
		delete z;
		for (; i < hydrap - 1; i++)
			hydralisks[i] = hydralisks[i + 1];			//数组内的虫子重新排序
		hydralisks[i] = nullptr;
		hydrap--;
		return true;
	}
}

//行动
void Hydralisk::act()
{
	clock++;
	if (clock % 100==0)
		hypv++;
	if (clock % 500==0)
		hypv += 2;
	zergv =stdv+ ((rand() % 5) - 2);					//速度可变（不然会重叠
	gettarget();										//获取目标
	rotate(25, 21);										//转向
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
	}													//移动
	drawhydralisk();									//绘制
	skillgap--;
	spit();
}

//spit 吐出刺
void Hydralisk::spit()
{
	if (skillgap <= 0 && spitp<hydraspit_Max&&spitp != 3)
	{
		addHydraspit(new Hydraspit(x, y, e,hypv));
		skillgap = 30;
	}
}

//生成新的刺
Hydraspit::Hydraspit(int ix,int iy,float ia,int hv)
{
	e = ia;
	x =ix+ unum(15*cos(e));
	y =iy+ unum(15*sin(e));
	zergv = 2*stdv+hv;
	maxHP = 1;											//单位血
	HP = maxHP;
}

//刺数组内添加新的刺
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

//删除并重新排序数组
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

//刺行动
void Hydraspit::act()
{
	x += unum(zergv*cos(e));
	y -= unum(zergv*sin(e));									//移动
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
	drawhydraspit();											//绘制
}