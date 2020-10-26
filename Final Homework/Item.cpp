///////////////////////////////////////////////////////
// �ļ����ƣ�	Item.cpp
//   �����ˣ�	���
//     ѧ�ţ�	2018302060060
//   ��������	342��
// ���뻷����	Visual Studio 2015 + EasyX_20190415(beta)
// ����޸ģ�	2019-6-22
// ʵ�ֹ��ܣ�	���������Ȱ����������Ϻ���Ͱ���ߵĹ���ʵ��
////////////////////////////////////////////////////////

#include<iostream>
#include<easyx.h>
#include"Item.h"
#include"Person.h"
#include"CoreInterface.h"
#include "State.h"
#define NORTH 0x1					//���巽��
#define SOUTH 0x2
#define EAST 0x4
#define WEST 0x8
struct State str,ste;				//������Ϊsta�Ľṹ��
extern Person personA, personB;


IMAGE personAMaskPtr;				//�������ڴ洢�������ֵ�ͼ��ָ��
IMAGE personBMaskPtr;
IMAGE personAPtr;					//�������ڴ洢�����ͼ��ָ��
IMAGE personBPtr;
IMAGE oilTank;						//��ͰͼƬ
IMAGE oilTankMask;					//��ͰͼƬ����

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
			if ((GetAsyncKeyState('Z') & 0x8000)&&coins>=5)                                           //�жϼ�������
			{
				if (personA.getHealthPoint() < personA.getLimHealthPoint())							 //���Ȱ�ʹ������
				{
						coins -= 5;																     //�۳����
						Person::spendCoins(5);
						FirstAidA();
				}
			}
			if ((GetAsyncKeyState('X') & 0x8000) && coins >= 3)
			{
				if (personA.getHealthPoint() < personA.getLimHealthPoint())							 //����ʹ������
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
				if (!str.pressed)						//�ж��Ƿ��ظ�����
				{
					if (weaponingA == 'O')
					{
						personA.setWeapon('A');
						str.pressed = true;				//���Ϊ�Ѱ��£������ظ��л�
						ifPut_A = true;
					}
					else
					{
						coins -= 7;
						Person::spendCoins(7);
						personA.setWeapon('O');                                                 //
						str.pressed = true;				//���Ϊ�Ѱ��£������ظ��л�
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
				if (personB.getHealthPoint() < personB.getLimHealthPoint())               //���Ȱ�ʹ������
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
				if (!ste.pressed)						//�ж��Ƿ��ظ�����
				{
					if (weaponingB == 'O')
					{
						personB.setWeapon('A');
						ste.pressed = true;				//���Ϊ�Ѱ��£������ظ��л�
						ifPut_B = true;
					}
					else
					{
						coins -= 7;
						Person::spendCoins(7);
						personB.setWeapon('O');                                                 //
						ste.pressed = true;				//���Ϊ�Ѱ��£������ظ��л�
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

//����Ч�����ָ�һ������ֵ
void Item::BandageA()
{
	personA.getHelp();                               //�ظ�����ֵ
	reshowInfo_playerA_hp();                         //��ʾ�µ�����ֵ
}

void Item::BandageB()
{
	personB.getHelp();
	reshowInfo_playerB_hp();
}

//����Ч��������
void Item::EnergyDrinkA()
{
	personA.setSpeed(10);
}

void Item::EnergyDrinkB()
{
	personB.setSpeed(10);
}

//���Ȱ�Ч�����ָ����������ֵ
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
		putimage(x_oilA, y_oilA, &oilTankMask, SRCAND);          //�����Ͱͼ��
		putimage(x_oilA, y_oilA, &oilTank, SRCPAINT);
	}
}

void Item::SetOilTankB()
{
	OilTankB();
	loadoilTankB();
	if (ifPut_B == true)
	{
		putimage(x_oilB, y_oilB, &oilTankMask, SRCAND);          //�����Ͱͼ��
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