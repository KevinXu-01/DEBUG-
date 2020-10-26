///////////////////////////////////////////////////////
// 文件名称：	Item.cpp
//   负责人：	杨景博
//     学号：	2018302060060
//   代码量：	342行
// 编译环境：	Visual Studio 2015 + EasyX_20190415(beta)
// 最后修改：	2019-6-22
// 实现功能：	绷带、急救包、能量饮料和油桶道具的功能实现
////////////////////////////////////////////////////////

#include<iostream>
#include<easyx.h>
#include"Item.h"
#include"Person.h"
#include"CoreInterface.h"
#include "State.h"
#define NORTH 0x1					//定义方向
#define SOUTH 0x2
#define EAST 0x4
#define WEST 0x8
struct State str,ste;				//定义名为sta的结构体
extern Person personA, personB;


IMAGE personAMaskPtr;				//定义用于存储人物遮罩的图像指针
IMAGE personBMaskPtr;
IMAGE personAPtr;					//定义用于存储人物的图像指针
IMAGE personBPtr;
IMAGE oilTank;						//油桶图片
IMAGE oilTankMask;					//油桶图片遮罩

Item::Item()
{
}
void Item::setControl()
{
	char weaponingA = personA.getWeapon();
	char weaponingB = personB.getWeapon();
	int coins = Person::getCoins();
	if(coins>0)
	{
		if (personA.getPlayer() == 'A'&&personA.getHealthPoint()>0)
		{
			if ((GetAsyncKeyState('Z') & 0x8000)&&coins>=5)                                           //判断键盘输入
			{
				if (personA.getHealthPoint() < personA.getLimHealthPoint())							 //急救包使用条件
				{
						coins -= 5;																     //扣除金币
						Person::spendCoins(5);
						FirstAidA();
				}
			}
			if ((GetAsyncKeyState('X') & 0x8000) && coins >= 3)
			{
				if (personA.getHealthPoint() < personA.getLimHealthPoint())							 //绷带使用条件
				{
					coins -= 3;
					Person::spendCoins(3);
					BandageA();
				}
			}
			if ((GetAsyncKeyState('C') & 0x8000) && coins >= 2)
			{
				coins -= 2;
				Person::spendCoins(2);
				EnergyDrinkA();
			}

			if ((GetAsyncKeyState('V') & 0x8000) && coins >= 7&&x_oilA>640)
			{
				if (!str.pressed)						//判断是否重复按下
				{
					if (weaponingA == 'O')
					{
						personA.setWeapon('A');
						str.pressed = true;				//标记为已按下，避免重复切换
						ifPut_A = true;
					}
					else
					{
						coins -= 7;
						Person::spendCoins(7);
						personA.setWeapon('O');                                                 //
						str.pressed = true;				//标记为已按下，避免重复切换
						ifPut_A = false;
					}
				}
			}
			if (ifPut_A == true)
				SetOilTankA();

		}

		if (!(GetAsyncKeyState('V') & 0x8000))
		{
			str.pressed = false;
		}

		if (personB.getPlayer() == 'B'&&personB.getHealthPoint()>0)
		{
			if ((GetAsyncKeyState('7') & 0x8000) && coins >= 5)
			{
				if (personB.getHealthPoint() < personB.getLimHealthPoint())               //急救包使用条件
				{
					coins -= 5;
					Person::spendCoins(5);
					FirstAidB();
				}
			}
			if ((GetAsyncKeyState('8') & 0x8000) && coins >= 3)
			{
				if (personB.getHealthPoint() < personB.getLimHealthPoint())
				{
					coins -= 3;
					Person::spendCoins(3);
					BandageB();
				}
			}
			if ((GetAsyncKeyState('9') & 0x8000) && coins >= 2)
			{
				coins -= 2;
				Person::spendCoins(2);
				EnergyDrinkB();
			}
			if ((GetAsyncKeyState('0') & 0x8000) && coins >= 7&&x_oilB>640)
			{
				if (!ste.pressed)						//判断是否重复按下
				{
					if (weaponingB == 'O')
					{
						personB.setWeapon('A');
						ste.pressed = true;				//标记为已按下，避免重复切换
						ifPut_B = true;
					}
					else
					{
						coins -= 7;
						Person::spendCoins(7);
						personB.setWeapon('O');                                                 //
						ste.pressed = true;				//标记为已按下，避免重复切换
						ifPut_B = false;
					}
				}
			}
			if (ifPut_B == true)
				SetOilTankB();

		}

		if (!(GetAsyncKeyState('0') & 0x8000))
		{
			ste.pressed = false;
		}
	}
}

//绷带效果：恢复一点生命值
void Item::BandageA()
{
	personA.getHelp();                               //回复生命值
	reshowInfo_playerA_hp();                         //显示新的生命值
}

void Item::BandageB()
{
	personB.getHelp();
	reshowInfo_playerB_hp();
}

//饮料效果：加速
void Item::EnergyDrinkA()
{
	personA.setSpeed(10);
}

void Item::EnergyDrinkB()
{
	personB.setSpeed(10);
}

//急救包效果：恢复至最大生命值
void Item::FirstAidA()
{
	while (personA.getHealthPoint() <= personA.getLimHealthPoint())
		personA.getHelp();
}

void Item::FirstAidB()
{
	while (personB.getHealthPoint() <= personB.getLimHealthPoint())
		personB.getHelp();
}

void Item::SetOilTankA()
{
	OilTankA();
	loadoilTankA();
	if (ifPut_A==true)
	{
		putimage(x_oilA, y_oilA, &oilTankMask, SRCAND);          //输出油桶图像
		putimage(x_oilA, y_oilA, &oilTank, SRCPAINT);
	}
}

void Item::SetOilTankB()
{
	OilTankB();
	loadoilTankB();
	if (ifPut_B == true)
	{
		putimage(x_oilB, y_oilB, &oilTankMask, SRCAND);          //输出油桶图像
		putimage(x_oilB, y_oilB, &oilTank, SRCPAINT);
	}
}

void Item::loadoilTankA()
{
	loadimage(&oilTank, _T("IMAGE"), _T("oilTank"));
	loadimage(&oilTankMask, _T("IMAGE"), _T("oilTankMask"));
}

void Item::loadoilTankB()
{
	loadimage(&oilTank, _T("IMAGE"), _T("oilTank"));
	loadimage(&oilTankMask, _T("IMAGE"), _T("oilTankMask"));
}

int Item::OilTankExplodeA()
{	
	for (int i = 0; i < banep; i++)
	{
		if (sqrt((x_oilA - banelings[i]->x) * (x_oilA - banelings[i]->x) + (y_oilA - banelings[i]->y) * (y_oilA - banelings[i]->y)) < 200)
		{
			banelings[i]->damaged(3);
		}
	}
	for (int i = 0; i < hydrap; i++)
	{
		if (sqrt((x_oilA - hydralisks[i]->x) * (x_oilA - hydralisks[i]->x) + (y_oilA - hydralisks[i]->y) * (y_oilA - hydralisks[i]->y)) < 200)
		{
			hydralisks[i]->damaged(3);
		}
	}
	for (int i = 0; i < rop; i++)
	{
		if (sqrt((x_oilA - roachs[i]->x) * (x_oilA - roachs[i]->x) + (y_oilA - roachs[i]->y) * (y_oilA - roachs[i]->y)) < 200)
		{
			roachs[i]->damaged(3);
		}
	}
	for (int i = 0; i < zergp; i++)
	{
		if (sqrt((x_oilA - zerglings[i]->x) * (x_oilA - zerglings[i]->x) + (y_oilA - zerglings[i]->y) * (y_oilA - zerglings[i]->y)) < 200)
		{
			zerglings[i]->damaged(3);
		}
	}
	for (int i = 0; i < spitp; i++)
	{
		if (sqrt((x_oilA - hydraspits[i]->x) * (x_oilA - hydraspits[i]->x) + (y_oilA - hydraspits[i]->y) * (y_oilA - hydraspits[i]->y)) < 200)
		{
			hydraspits[i]->damaged(3);
		}
	}
	ifPut_A = false;
	x_oilA = 1000, y_oilA = 1000;
	return 0;
}

int Item::OilTankExplodeB()
{
	for (int i = 0; i < banep; i++)
	{
		if (sqrt((x_oilB - banelings[i]->x) * (x_oilB - banelings[i]->x) + (y_oilB - banelings[i]->y) * (y_oilB - banelings[i]->y)) < 200)
		{
			banelings[i]->damaged(3);
		}
	}
	for (int i = 0; i < hydrap; i++)
	{
		if (sqrt((x_oilB - hydralisks[i]->x) * (x_oilB - hydralisks[i]->x) + (y_oilB - hydralisks[i]->y) * (y_oilB - hydralisks[i]->y)) < 200)
		{
			hydralisks[i]->damaged(3);
		}
	}
	for (int i = 0; i < rop; i++)
	{
		if (sqrt((x_oilB - roachs[i]->x) * (x_oilB - roachs[i]->x) + (y_oilB - roachs[i]->y) * (y_oilB - roachs[i]->y)) < 200)
		{
			roachs[i]->damaged(3);
		}
	}
	for (int i = 0; i < zergp; i++)
	{
		if (sqrt((x_oilB - zerglings[i]->x) * (x_oilB - zerglings[i]->x) + (y_oilB - zerglings[i]->y) * (y_oilB - zerglings[i]->y)) < 200)
		{
			zerglings[i]->damaged(3);
		}
	}
	for (int i = 0; i < spitp; i++)
	{
		if (sqrt((x_oilB - hydraspits[i]->x) * (x_oilB - hydraspits[i]->x) + (y_oilB - hydraspits[i]->y) * (y_oilB - hydraspits[i]->y)) < 200)
		{
			hydraspits[i]->damaged(3);
		}
	}
	ifPut_B = false;
	x_oilB = 1000, y_oilB = 1000;
	return 0;
}

int Item::AgetOilTankPositionX()
{
	return x_oilA;
}

int Item::AgetOilTankPositionY()
{
	return y_oilA;
}

int Item::BgetOilTankPositionX()
{
	return x_oilB;
}

int Item::BgetOilTankPositionY()
{
	return y_oilB;
}

void Item::OilTankA()
{
	int x0 = personA.getPersonPositionX();
	int y0 = personA.getPersonPositionY();
	if (ifPut_A == true&&x_oilA>640)
	{
		x_oilA = x0 - 80*sin(personA.getRotateDegree())-20;
		y_oilA = y0 - 80*cos(personA.getRotateDegree())-20;
	}
}

void Item::OilTankB()
{
	int x0 = personB.getPersonPositionX();
	int y0 = personB.getPersonPositionY();
	if (ifPut_B == true && x_oilB>640)
	{
		x_oilB = x0 - 80 * sin(personB.getRotateDegree()) - 20;
		y_oilB = y0 - 80 * cos(personB.getRotateDegree()) - 20;
	}
}