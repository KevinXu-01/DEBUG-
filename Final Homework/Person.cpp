///////////////////////////////////////////////////////
// �ļ����ƣ�	Person.cpp
//   �����ˣ�	������
//     ѧ�ţ�	2018302060043
//   ��������	480��
// ���뻷����	Visual Studio 2015 + EasyX_20180321(���ְ�) 
// ����޸ģ�	2019-6-12
// ʵ�ֹ��ܣ�	����������޸ġ����Ի�ȡ��������ơ�������ʾ�������
////////////////////////////////////////////////////////
#include<windows.h>
#include<easyx.h>
#include<cmath>
#include "Person.h"
#include "State.h"
#include "Score.h"
#include "CoreInterface.h"

#define PI 3.1415926								//����PI
#define MAPWIDTH 480								//�����ͼ����
#define MAPLENGTH 640								//�����ͼ���
#define NORTH 0x1									//���巽��
#define SOUTH 0x2
#define EAST 0x4
#define WEST 0x8

extern Score score;									//�ⲿ����
extern Person personA, personB;
extern int mode;

struct State sta;									//������Ϊsta�Ľṹ��
IMAGE personMaskPtr[12];							//�������ڴ洢�������ֵ�ͼ��ָ��
IMAGE personPtr[2][12];								//�������ڴ洢�����ͼ��ָ��
void imageProcess();								//ͼ����������

//���캯��
Person::Person()									
{
	healthPoint = 3;								//Ĭ������ֵ
	limitedHP = 3;									//Ĭ����������ֵ
	reviveTime = 15;								//Ĭ�ϸ���ʱ��
	personPositionX = MAPLENGTH/2;					//Ĭ����ʼX����
	personPositionY = MAPWIDTH/2;					//Ĭ����ʼY����
	int personPositionShift = 0;					//Ĭ������λ��ƫ����
	int personDirection = NULL;						//Ĭ�����﷽��
	speed = 5;										//Ĭ���ƶ��ٶ�
	player = 'A';									//Ĭ����Ҵ���
	weapon = 'A';									//Ĭ�ϲ�����������

}

//��������
Person::~Person()
{
	healthPoint = 3;								//�ָ�Ĭ������ֵ
	limitedHP = 3;									//�ָ�Ĭ����������ֵ
	personPositionX = MAPLENGTH / 2;				//�ָ�Ĭ����ʼX����
	personPositionY = MAPWIDTH / 2;					//�ָ�Ĭ����ʼY����
	int personPositionShift = 0;					//�ָ�Ĭ������λ��ƫ����
	int personDirection = NULL;						//�ָ�Ĭ�����﷽��
	speed = 5;										//�ָ�Ĭ���ƶ��ٶ�
	weapon = 'A';									//�ָ�Ĭ�ϲ�����������
}

//����������ţ�������ţ�
void Person::setPlayer(char p)						
{
	player = p;
}

//��ȡ�������
char Person::getPlayer()
{
	return player;
}

//��������ֵ����ʼ����ֵ����������ֵ��
void Person::setHealthPoint(int initHP, int limtHP)	
{
	healthPoint = initHP;
	limitedHP = limtHP;
}

//�����˵�λ��(x���꣬y���꣩
void Person::setPersonPosition(int x, int y)		
{
	personPositionX = x;
	personPositionY = y;
}

//�����ƶ��ٶȣ��ƶ��ٶȣ�
void Person::setSpeed(int s)						
{
	speed = s;
}

//����������ݷ�ʽ
void Person::setControl()							
{
	personDirection = NULL;
	if (healthPoint)										//�ж������Ƿ�����
	{
		if (player == 'A')									//�ж��������
		{
			//���A���ݷ�ʽ�趨
			if (GetAsyncKeyState('W') & 0x8000)				//GetAsyncKeyState(input)�����ж�input���Ƿ��£������򷵻�0x8000
				personDirection |= NORTH;					//�����﷽�򴢴�
			if (GetAsyncKeyState('S') & 0x8000)
				personDirection |= SOUTH;
			if (GetAsyncKeyState('A') & 0x8000)
				personDirection |= WEST;
			if (GetAsyncKeyState('D') & 0x8000)
				personDirection |= EAST;

			if (GetAsyncKeyState('E') & 0x8000)				//�ж������л����Ƿ���
			{
				if (!sta.pressed)							//�ж��Ƿ��ظ�����
					if (weapon != 'O')						//������Ͱʱ�޷��л�
						if (weapon != 'D')					//�ж����������Ƿ�ΪD
						{
							weapon++;						//�����仯Ϊ��һ������
							sta.pressed = true;				//���Ϊ�Ѱ��£������ظ��л�
						}
						else
						{
							weapon = 'A';					//�����ָ�ΪA��
							sta.pressed = true;				//���Ϊ�Ѱ��£������ظ��л�
						}
			}

			if (GetAsyncKeyState('Q') & 0x8000)				//���������л�
			{
				if (!sta.pressed)
					if (weapon != 'O')
						if (weapon != 'A')
						{
							weapon--;
							sta.pressed = true;
						}
						else
						{
							weapon = 'D';
							sta.pressed = true;
						}
			}
			if (!(GetAsyncKeyState('E') & 0x8000) &&			//�ж��л����Ƿ�δ�ٰ���
				!(GetAsyncKeyState('Q') & 0x8000))
				sta.pressed = false;							//����״̬�ָ�Ϊδ����
			if (mode == 0)										//����ģʽ������������Ʒ���
			{
				MOUSEMSG mouse;
				if (MouseHit())
				{
					mouse = GetMouseMsg();						//��ȡ�����Ϣ
					sta.mw = mouse.wheel;						//���������Ϣ
					sta.mx = mouse.x;
					sta.my = mouse.y;
				}
				if (sta.mx < personPositionX)					//�������λ�ü�����ת�Ƕ�
					rotateDegree = acos(double((personPositionY - sta.my)
						/ sqrt(pow((personPositionY - sta.my), 2) + pow((personPositionX - sta.mx), 2))));
				else
					rotateDegree = -acos(double((personPositionY - sta.my)
						/ sqrt(pow((personPositionY - sta.my), 2) + pow((personPositionX - sta.mx), 2))));
			}
		}

		//���B���ݷ�ʽ�趨
		else
		{
			MOUSEMSG mouse;
			if (GetAsyncKeyState(VK_UP) & 0x8000)
				personDirection |= NORTH;
			if (GetAsyncKeyState(VK_DOWN) & 0x8000)
				personDirection |= SOUTH;
			if (GetAsyncKeyState(VK_LEFT) & 0x8000)
				personDirection |= WEST;
			if (GetAsyncKeyState(VK_RIGHT) & 0x8000)
				personDirection |= EAST;

			if (MouseHit())
			{
				mouse = GetMouseMsg();						//��ȡ�����Ϣ
				sta.mw = mouse.wheel;						//���������Ϣ
				sta.mx = mouse.x;
				sta.my = mouse.y;
			}
			if (sta.mw > 0)									//�жϻ����Ƿ��Ϲ�
			{
				if (weapon != 'O')							//������Ͱʱ�޷��л�
					if (weapon != 'D')						//�ж����������Ƿ�ΪD
						weapon++;							//�����仯Ϊ��һ������
					else
						weapon = 'A';						//�����ָ�ΪA��
			}
			if (sta.mw < 0)									//���������л�
			{
				if (weapon != 'O')
					if (weapon != 'A')
						weapon--;
					else
						weapon = 'D';
			}
			sta.mw = 0;										//������Ϣ����

			if (sta.mx < personPositionX)					//�������λ�ü�����ת�Ƕ�
				rotateDegree = acos(double((personPositionY - sta.my)
					/ sqrt(pow((personPositionY - sta.my), 2) + pow((personPositionX - sta.mx), 2))));
			else
				rotateDegree = -acos(double((personPositionY - sta.my)
					/ sqrt(pow((personPositionY - sta.my), 2) + pow((personPositionX - sta.mx), 2))));
		}

		//������ת�Ƕȼ�����任
		if (personDirection & NORTH)						//�ж����﷽��
		{
			if (player == 'A' && mode == 1)					//�ж��Ƿ�Ϊ���A����˫��ģʽ��
				rotateDegree = 0;							//Ϊ����ȷ����ת�Ƕ�
			personPositionY -= 1 * speed;					//��������б任
			if (personPositionY < 50)						//�ж�����λ��
				personPositionY = 50;						//�����߳���ͼ		
		}
		if (personDirection & SOUTH)
		{
			if (player == 'A' && mode == 1)
				rotateDegree = PI;
			personPositionY += 1 * speed;
			if (personPositionY > MAPWIDTH - 50)
				personPositionY = MAPWIDTH - 50;
		}
		if (personDirection & WEST)
		{
			if (player == 'A' && mode == 1)
				rotateDegree = PI / 2;
			personPositionX -= 1 * speed;
			if (personPositionX < 50)
				personPositionX = 50;
		}
		if (personDirection & EAST)
		{
			if (player == 'A' && mode == 1)
				rotateDegree = -PI / 2;
			personPositionX += 1 * speed;
			if (personPositionX > MAPLENGTH - 50)
				personPositionX = MAPLENGTH - 50;
		}
		if (personDirection & NORTH && personDirection & WEST)
		{
			if (player == 'A' && mode == 1)
				rotateDegree = PI / 4;
			personPositionY -= int(-0.293 * speed);
			personPositionX -= int(-0.293 * speed);
			if (personPositionY < 50)
				personPositionY = 50;
			if (personPositionX < 50)
				personPositionX = 50;
		}
		if (personDirection & NORTH && personDirection & EAST)
		{
			if (player == 'A' && mode == 1)
				rotateDegree = -PI / 4;
			personPositionY -= int(-0.293 * speed);
			personPositionX += int(-0.293 * speed);
			if (personPositionY < 50)
				personPositionY = 50;
			if (personPositionX > MAPLENGTH - 50)
				personPositionX = MAPLENGTH - 50;
		}
		if (personDirection & SOUTH && personDirection & WEST)
		{
			if (player == 'A' && mode == 1)
				rotateDegree = 3 * PI / 4;
			personPositionY += int(-0.293 * speed);
			personPositionX -= int(-0.293 * speed);
			if (personPositionY > MAPWIDTH - 50)
				personPositionY = MAPWIDTH - 50;
			if (personPositionX < 50)
				personPositionX = 50;
		}
		if (personDirection & SOUTH && personDirection & EAST)
		{
			if (player == 'A' && mode == 1)
				rotateDegree = -3 * PI / 4;
			personPositionY += int(-0.293 * speed);
			personPositionX += int(-0.293 * speed);
			if (personPositionY > MAPWIDTH - 50)
				personPositionY = MAPWIDTH - 50;
			if (personPositionX > MAPLENGTH - 50)
				personPositionX = MAPLENGTH - 50;
		}
	}
}

//������������
void Person::setWeapon(char o)							
{
	weapon = o;
}

//��ȡ��������
char Person::getWeapon()
{
	return weapon;
}

//��ʾ����
void Person::showPerson()																				
{	
	if(sta.processed==false)														//�ж�ͼ���Ƿ��Ѿ�����
		imageProcess();	
	if (player== 'A')																//�ж��������
	{
		switch (weapon)																//�жϲ��ݺ�������
		{
		case 'A':imageProcess(personA, 0, !healthPoint);break;						//����A������ʱ����
		case 'B':imageProcess(personA, 1, !healthPoint);break;						//����B������ʱ����
		case 'C':imageProcess(personA, 2, !healthPoint);break;						//����C������ʱ����
		case 'D':imageProcess(personA, 3, !healthPoint);break;						//����D������ʱ����
		case 'O':imageProcess(personA, 8, !healthPoint);break;						//����O������ʱ����
		}
	}
	else
	{
		switch (weapon)
		{
		case 'A':imageProcess(personB, 4, !healthPoint);break;
		case 'B':imageProcess(personB, 5, !healthPoint);break;
		case 'C':imageProcess(personB, 6, !healthPoint);break;
		case 'D':imageProcess(personB, 7, !healthPoint);break;
		case 'O':imageProcess(personB, 9, !healthPoint);break;
		}
	}
}

//��ȡ�˵�����ֵ
int Person::getHealthPoint()						
{
	return healthPoint;
}

//��ȡ�˵��������ֵ
int Person::getLimHealthPoint()
{
	return limitedHP;
}

//��ȡ����ʱ��
int Person::getReviveTime()
{
	return reviveTime;
}

//��ȡ�˵�λ��x����
int Person::getPersonPositionX()					
{
	return personPositionX;
}

//��ȡ�˵�λ��y����
int Person::getPersonPositionY()					
{
	return personPositionY;
}

//��ȡ�˵��ٶ�
int Person::getSpeed()								
{
	return speed;
}

//��ȡ�˵ķ���
int Person::getPersonDirection()
{
	return personDirection;
}

//��ȡ�˵���ת�Ƕ�
double Person::getRotateDegree()
{
	return rotateDegree;
}

//ʰȡ���
void Person::pickCoins()							
{
	numOfCoins++;
	reshowInfo_coin(mode);
}

//��ȡ��ǰ�������
int Person::getCoins()								
{
	return numOfCoins;
}

//������ѣ�ʹ�ý��������
void Person::spendCoins(int m)
{
	if(numOfCoins>=m)								//�ж������������Ƿ��㹻
		numOfCoins -= m;							//�����������m
	reshowInfo_coin(mode);
}

//�ܵ��˺�
void Person::getHit()								
{	
	if(healthPoint>0)								//�ж������Ƿ�����
		healthPoint--;								//ÿ���ú���һ������ֵ��1
	reshowInfo_playerA_hp();
	reshowInfo_playerB_hp();						//��������
}

//��Ѫ
void Person::getHelp()
{
	healthPoint++;									//ÿ���ú���һ������ֵ��1
	reshowInfo_playerA_hp();
	reshowInfo_playerB_hp();						//��������
}

//���︴��
void Person::personRevive()
{
	static int count = 0;							//��̬��������
	Sleep(10);										//��ʱ����ֵ̫�߻���ɿ��٣�
	count+=4;										//����
	if (!(count % 100))								
	{
		reviveTime--;
		if (reviveTime == 0)
		{
			this->getHelp();
			reviveTime = 15;
		}
		count = 0;
	}
	else if (count >= 50)							//
	{
		if (reviveTime <= 3 && reviveTime > 0)		//
			if (player == 'A')										//�ж��������
			{
				switch (weapon)										//�жϲ��ݺ�������
				{
				case 'A':imageProcess(personA, 0, 0); break;		//����A������ʱ����
				case 'B':imageProcess(personA, 1, 0); break;		//����B������ʱ����
				case 'C':imageProcess(personA, 2, 0); break;		//����C������ʱ����
				case 'D':imageProcess(personA, 3, 0); break;		//����D������ʱ����
				case 'O':imageProcess(personA, 8, 0); break;		//����O������ʱ����
				}
			}
			else
			{
				switch (weapon)
				{
				case 'A':imageProcess(personB, 4, 0); break;
				case 'B':imageProcess(personB, 5, 0); break;
				case 'C':imageProcess(personB, 6, 0); break;
				case 'D':imageProcess(personB, 7, 0); break;
				case 'O':imageProcess(personB, 9, 0); break;
				}
			}
	}
	else ;
}

int Person::numOfCoins = 0;										//��ʼ���������Ϊ0

//����ͼ����
void imageProcess()
{
	loadimage(&personPtr[0][10], _T("IMAGE"), _T("person"));	//��������ͼ��
	SetWorkingImage(&personPtr[0][10]);							//���ù�������Ϊ����ͼ��
	for (int i = 0; i < 10; i++)								//�и�ͼ�񲢴���
	{
		getimage(&personPtr[0][i], 100 * i, 0, 100, 100);
		getimage(&personMaskPtr[i], 100 * i, 100, 100, 100);
		getimage(&personPtr[1][i], 100 * i, 200, 100, 100);
	}
	SetWorkingImage(NULL);										//�ָ�ΪĬ�Ϲ�������
	sta.processed = true;										//���Ϊ�Ѵ��������ظ�����
}

//����ͼ�����������ã��زı��, �Ƿ�������
void imageProcess(Person &p, int w, int l)
{
	rotateimage(&personMaskPtr[11], &personMaskPtr[w], p.rotateDegree, WHITE);								//��ת�����ز�
	rotateimage(&personPtr[l][11], &personPtr[l][w], p.rotateDegree, BLACK);
	putimage(p.personPositionX - 50, p.personPositionY - 50, &personMaskPtr[11], SRCAND);					//����w������ʱ����
	putimage(p.personPositionX - 50, p.personPositionY - 50, &personPtr[l][11], SRCPAINT);
}