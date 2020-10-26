///////////////////////////////////////////////////////
// �ļ����ƣ�	Coins.cpp
//   �����ˣ�	��ʫ��
//     ѧ�ţ�	2018302060048
//   ��������	125��
// ���뻷����	Visual Studio 2015 + EasyX 20190415(beta) 
// ����޸ģ�	2019-6-12
// ʵ�ֹ��ܣ�	��ҵ�������
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

//����λ�ò������ɽ��
Coins::Coins(int zx, int zy)
{
	i = 0;
	x = zx;
	y = zy;
}

//��ʼ�����ƽ��
void initcoinsdraw()
{
	coinsp = 0;
	loadimage(&Coinsimage, _T("IMAGE"), _T("coins"));
	loadimage(&Coinsimage1, _T("IMAGE"), _T("coins1"));
	loadimage(&CoinsimageMask, _T("IMAGE"), _T("coinsmask"));
}

//���ƽ��
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

//������������
int getdist(int x,int y,Person t)
{
	return ((t.getPersonPositionX() - x) * (t.getPersonPositionX() - x) + (t.getPersonPositionY() - y) * (t.getPersonPositionY() - y));
}

//ִ�н����˸����ʰȡ
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
	}//���ͣ��ʱ�������ɾ��
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
	}//��ұ�ʰȡ��ɾ��
}

//��ӽ��
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

//ɾ�����
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

//���ʰȡ���
void Coins::getcoins()
{
	Person::pickCoins();
}

//�����н��ִ�й���
void allcoinsact()
{
	for (int coinsi = 0; coinsi < coinsp; coinsi++)
	{
		coins[coinsi]->CoinsPlay();
	}
}