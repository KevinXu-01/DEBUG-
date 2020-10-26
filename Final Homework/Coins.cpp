///////////////////////////////////////////////////////
// 文件名称：	Coins.cpp
//   负责人：	江诗烨
//     学号：	2018302060048
//   代码量：	125行
// 编译环境：	Visual Studio 2015 + EasyX 20190415(beta) 
// 最后修改：	2019-6-12
// 实现功能：	金币的生成与活动
////////////////////////////////////////////////////////
#include"Coins.h"
#include<easyx.h>
#include"Person.h"

IMAGE Coinsimage;
IMAGE Coinsimage1;
IMAGE CoinsimageMask;
extern Person personA, personB;
int coinsp;

Coins* coins[5] = { nullptr,nullptr,nullptr,nullptr,nullptr };

//根据位置参数生成金币
Coins::Coins(int zx, int zy)
{
	i = 0;
	x = zx;
	y = zy;
}

//初始化绘制金币
void initcoinsdraw()
{
	coinsp = 0;
	loadimage(&Coinsimage, _T("IMAGE"), _T("coins"));
	loadimage(&Coinsimage1, _T("IMAGE"), _T("coins1"));
	loadimage(&CoinsimageMask, _T("IMAGE"), _T("coinsmask"));
}

//绘制金币
void Coins::drawcoins()
{
	SetWorkingImage();
	putimage(x - 23, y - 22, &CoinsimageMask, SRCAND);
	if(i<=9)
		putimage(x - 23, y - 22, &Coinsimage, SRCINVERT);
	else if(i>9&&i<=19)
		putimage(x - 23, y - 22, &Coinsimage1, SRCINVERT);
	i++;
	if (i >= 20)
		i = 0;
}

//计算距人类距离
int getdist(int x,int y,Person t)
{
	return ((t.getPersonPositionX() - x) * (t.getPersonPositionX() - x) + (t.getPersonPositionY() - y) * (t.getPersonPositionY() - y));
}

//执行金币闪烁及被拾取
void Coins::CoinsPlay()
{
	if (t < 0)
	{
		int i;
		for (i = 0; i < coinsp; i++)
		{
			if (this == coins[i])
				break;
		}
		deleteCoin(coins[i]);
	}//金币停留时间过长，删除
	drawcoins();
	if (getdist(x, y, personA) <= 3600&&personA.getHealthPoint()>0 || getdist(x, y, personB) <= 3600&&personB.getHealthPoint()>0)
	{
		getcoins();
		int i;
		for (i = 0; i < coinsp; i++)
		{
			if (this == coins[i])
				break;
		}
		deleteCoin(coins[i]);
	}//金币被拾取，删除
}

//添加金币
bool addCoin( Coins* c)
{
	if (coinsp > 4)
		return false;
	else
	{
		coins[coinsp] = c;
		(coinsp)++;
		return true;
	}
}

//删除金币
bool deleteCoin(Coins* c)
{
	int i;
	for (i = 0; i < coinsp; i++)
	{
		if (c == coins[i])
			break;
	}
	if (i == coinsp)
		return false;
	else
	{
		delete c;
		for (; i < coinsp - 1; i++)
			coins[i] = coins[i + 1];
		coins[i] = nullptr;
		coinsp--;
		return true;
	}
}

//玩家拾取金币
void Coins::getcoins()
{
	Person::pickCoins();
}

//令所有金币执行功能
void allcoinsact()
{
	for (int coinsi = 0; coinsi < coinsp; coinsi++)
	{
		coins[coinsi]->CoinsPlay();
	}
}