///////////////////////////////////////////////////////
// 文件名称：	Person.cpp
//   负责人：	范承祥
//     学号：	2018302060043
//   代码量：	480行
// 编译环境：	Visual Studio 2015 + EasyX_20180321(春分版) 
// 最后修改：	2019-6-12
// 实现功能：	人物的属性修改、属性获取、人物控制、人物显示、复活等
////////////////////////////////////////////////////////
#include<windows.h>
#include<easyx.h>
#include<cmath>
#include "Person.h"
#include "State.h"
#include "Score.h"
#include "CoreInterface.h"

#define PI 3.1415926								//定义PI
#define MAPWIDTH 480								//定义地图长度
#define MAPLENGTH 640								//定义地图宽度
#define NORTH 0x1									//定义方向
#define SOUTH 0x2
#define EAST 0x4
#define WEST 0x8

extern Score score;									//外部引用
extern Person personA, personB;
extern int mode;

struct State sta;									//定义名为sta的结构体
IMAGE personMaskPtr[12];							//定义用于存储人物遮罩的图像指针
IMAGE personPtr[2][12];								//定义用于存储人物的图像指针
void imageProcess();								//图像处理函数声明

//构造函数
Person::Person()									
{
	healthPoint = 3;								//默认生命值
	limitedHP = 3;									//默认上限生命值
	reviveTime = 15;								//默认复活时间
	personPositionX = MAPLENGTH/2;					//默认起始X坐标
	personPositionY = MAPWIDTH/2;					//默认起始Y坐标
	int personPositionShift = 0;					//默认人物位置偏移量
	int personDirection = NULL;						//默认人物方向
	speed = 5;										//默认移动速度
	player = 'A';									//默认玩家代号
	weapon = 'A';									//默认操纵武器类型

}

//析构函数
Person::~Person()
{
	healthPoint = 3;								//恢复默认生命值
	limitedHP = 3;									//恢复默认上限生命值
	personPositionX = MAPLENGTH / 2;				//恢复默认起始X坐标
	personPositionY = MAPWIDTH / 2;					//恢复默认起始Y坐标
	int personPositionShift = 0;					//恢复默认人物位置偏移量
	int personDirection = NULL;						//恢复默认人物方向
	speed = 5;										//恢复默认移动速度
	weapon = 'A';									//恢复默认操纵武器类型
}

//设置人物代号（人物代号）
void Person::setPlayer(char p)						
{
	player = p;
}

//获取人物代号
char Person::getPlayer()
{
	return player;
}

//设置生命值（初始生命值，上限生命值）
void Person::setHealthPoint(int initHP, int limtHP)	
{
	healthPoint = initHP;
	limitedHP = limtHP;
}

//设置人的位置(x坐标，y坐标）
void Person::setPersonPosition(int x, int y)		
{
	personPositionX = x;
	personPositionY = y;
}

//设置移动速度（移动速度）
void Person::setSpeed(int s)						
{
	speed = s;
}

//设置人物操纵方式
void Person::setControl()							
{
	personDirection = NULL;
	if (healthPoint)										//判断人物是否死亡
	{
		if (player == 'A')									//判断人物代号
		{
			//玩家A操纵方式设定
			if (GetAsyncKeyState('W') & 0x8000)				//GetAsyncKeyState(input)用于判断input键是否按下，按下则返回0x8000
				personDirection |= NORTH;					//将人物方向储存
			if (GetAsyncKeyState('S') & 0x8000)
				personDirection |= SOUTH;
			if (GetAsyncKeyState('A') & 0x8000)
				personDirection |= WEST;
			if (GetAsyncKeyState('D') & 0x8000)
				personDirection |= EAST;

			if (GetAsyncKeyState('E') & 0x8000)				//判断武器切换键是否按下
			{
				if (!sta.pressed)							//判断是否重复按下
					if (weapon != 'O')						//操纵油桶时无法切换
						if (weapon != 'D')					//判断武器种类是否为D
						{
							weapon++;						//武器变化为下一级武器
							sta.pressed = true;				//标记为已按下，避免重复切换
						}
						else
						{
							weapon = 'A';					//武器恢复为A型
							sta.pressed = true;				//标记为已按下，避免重复切换
						}
			}

			if (GetAsyncKeyState('Q') & 0x8000)				//反序武器切换
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
			if (!(GetAsyncKeyState('E') & 0x8000) &&			//判断切换键是否都未再按下
				!(GetAsyncKeyState('Q') & 0x8000))
				sta.pressed = false;							//按键状态恢复为未按下
			if (mode == 0)										//单人模式下用鼠标来控制方向
			{
				MOUSEMSG mouse;
				if (MouseHit())
				{
					mouse = GetMouseMsg();						//获取鼠标信息
					sta.mw = mouse.wheel;						//储存鼠标信息
					sta.mx = mouse.x;
					sta.my = mouse.y;
				}
				if (sta.mx < personPositionX)					//根据鼠标位置计算旋转角度
					rotateDegree = acos(double((personPositionY - sta.my)
						/ sqrt(pow((personPositionY - sta.my), 2) + pow((personPositionX - sta.mx), 2))));
				else
					rotateDegree = -acos(double((personPositionY - sta.my)
						/ sqrt(pow((personPositionY - sta.my), 2) + pow((personPositionX - sta.mx), 2))));
			}
		}

		//玩家B操纵方式设定
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
				mouse = GetMouseMsg();						//获取鼠标信息
				sta.mw = mouse.wheel;						//储存鼠标信息
				sta.mx = mouse.x;
				sta.my = mouse.y;
			}
			if (sta.mw > 0)									//判断滑轮是否上滚
			{
				if (weapon != 'O')							//操纵油桶时无法切换
					if (weapon != 'D')						//判断武器种类是否为D
						weapon++;							//武器变化为下一级武器
					else
						weapon = 'A';						//武器恢复为A型
			}
			if (sta.mw < 0)									//反序武器切换
			{
				if (weapon != 'O')
					if (weapon != 'A')
						weapon--;
					else
						weapon = 'D';
			}
			sta.mw = 0;										//滚轮信息清零

			if (sta.mx < personPositionX)					//根据鼠标位置计算旋转角度
				rotateDegree = acos(double((personPositionY - sta.my)
					/ sqrt(pow((personPositionY - sta.my), 2) + pow((personPositionX - sta.mx), 2))));
			else
				rotateDegree = -acos(double((personPositionY - sta.my)
					/ sqrt(pow((personPositionY - sta.my), 2) + pow((personPositionX - sta.mx), 2))));
		}

		//人物旋转角度及坐标变换
		if (personDirection & NORTH)						//判断人物方向
		{
			if (player == 'A' && mode == 1)					//判断是否为玩家A且在双人模式下
				rotateDegree = 0;							//为真则确定旋转角度
			personPositionY -= 1 * speed;					//对坐标进行变换
			if (personPositionY < 50)						//判断人物位置
				personPositionY = 50;						//避免走出地图		
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

//设置武器类型
void Person::setWeapon(char o)							
{
	weapon = o;
}

//获取武器类型
char Person::getWeapon()
{
	return weapon;
}

//显示人物
void Person::showPerson()																				
{	
	if(sta.processed==false)														//判断图像是否已经处理
		imageProcess();	
	if (player== 'A')																//判断人物身份
	{
		switch (weapon)																//判断操纵何种武器
		{
		case 'A':imageProcess(personA, 0, !healthPoint);break;						//载入A型武器时的人
		case 'B':imageProcess(personA, 1, !healthPoint);break;						//载入B型武器时的人
		case 'C':imageProcess(personA, 2, !healthPoint);break;						//载入C型武器时的人
		case 'D':imageProcess(personA, 3, !healthPoint);break;						//载入D型武器时的人
		case 'O':imageProcess(personA, 8, !healthPoint);break;						//载入O型武器时的人
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

//获取人的生命值
int Person::getHealthPoint()						
{
	return healthPoint;
}

//获取人的最大生命值
int Person::getLimHealthPoint()
{
	return limitedHP;
}

//获取复活时间
int Person::getReviveTime()
{
	return reviveTime;
}

//获取人的位置x坐标
int Person::getPersonPositionX()					
{
	return personPositionX;
}

//获取人的位置y坐标
int Person::getPersonPositionY()					
{
	return personPositionY;
}

//获取人的速度
int Person::getSpeed()								
{
	return speed;
}

//获取人的方向
int Person::getPersonDirection()
{
	return personDirection;
}

//获取人的旋转角度
double Person::getRotateDegree()
{
	return rotateDegree;
}

//拾取金币
void Person::pickCoins()							
{
	numOfCoins++;
	reshowInfo_coin(mode);
}

//获取当前金币数量
int Person::getCoins()								
{
	return numOfCoins;
}

//金币消费（使用金币数量）
void Person::spendCoins(int m)
{
	if(numOfCoins>=m)								//判断人物金币数量是否足够
		numOfCoins -= m;							//金币数量减少m
	reshowInfo_coin(mode);
}

//受到伤害
void Person::getHit()								
{	
	if(healthPoint>0)								//判断人物是否死亡
		healthPoint--;								//每调用函数一次生命值减1
	reshowInfo_playerA_hp();
	reshowInfo_playerB_hp();						//绘制生命
}

//回血
void Person::getHelp()
{
	healthPoint++;									//每调用函数一次生命值减1
	reshowInfo_playerA_hp();
	reshowInfo_playerB_hp();						//绘制生命
}

//人物复活
void Person::personRevive()
{
	static int count = 0;							//静态计数变量
	Sleep(10);										//延时（数值太高会造成卡顿）
	count+=4;										//计数
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
			if (player == 'A')										//判断人物身份
			{
				switch (weapon)										//判断操纵何种武器
				{
				case 'A':imageProcess(personA, 0, 0); break;		//载入A型武器时的人
				case 'B':imageProcess(personA, 1, 0); break;		//载入B型武器时的人
				case 'C':imageProcess(personA, 2, 0); break;		//载入C型武器时的人
				case 'D':imageProcess(personA, 3, 0); break;		//载入D型武器时的人
				case 'O':imageProcess(personA, 8, 0); break;		//载入O型武器时的人
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

int Person::numOfCoins = 0;										//初始化金币总数为0

//人物图像处理
void imageProcess()
{
	loadimage(&personPtr[0][10], _T("IMAGE"), _T("person"));	//载入人物图像
	SetWorkingImage(&personPtr[0][10]);							//设置工作区间为人物图像
	for (int i = 0; i < 10; i++)								//切割图像并储存
	{
		getimage(&personPtr[0][i], 100 * i, 0, 100, 100);
		getimage(&personMaskPtr[i], 100 * i, 100, 100, 100);
		getimage(&personPtr[1][i], 100 * i, 200, 100, 100);
	}
	SetWorkingImage(NULL);										//恢复为默认工作区间
	sta.processed = true;										//标记为已处理，避免重复处理
}

//人物图像处理（对象引用，素材标号, 是否死亡）
void imageProcess(Person &p, int w, int l)
{
	rotateimage(&personMaskPtr[11], &personMaskPtr[w], p.rotateDegree, WHITE);								//旋转人物素材
	rotateimage(&personPtr[l][11], &personPtr[l][w], p.rotateDegree, BLACK);
	putimage(p.personPositionX - 50, p.personPositionY - 50, &personMaskPtr[11], SRCAND);					//载入w型武器时的人
	putimage(p.personPositionX - 50, p.personPositionY - 50, &personPtr[l][11], SRCPAINT);
}