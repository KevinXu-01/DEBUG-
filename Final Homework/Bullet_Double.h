///////////////////////////////////////////////////////
// 文件名称：	Bullet_Double.h
//   负责人：	许静宇
//     学号：	2018302060052
//   代码量：	53行
// 编译环境：	Visual Studio 2015 + EasyX_20190415(beta)
// 最后修改：	2019-6-12
// 实现功能：	定义Bullet_Double类，对函数进行声明
////////////////////////////////////////////////////////

#pragma once
#include "Person.h"
#include <easyx.h>
#include "Bugs.h"
#include"conio.h"
#include"graphics.h"
#include <math.h>
#include <windows.h>
#include "Item.h"
#define PI 3.1415926               //定义PI

class Bullet_Double;
extern MOUSEMSG mouse;
extern Person personA, personB;
extern Baneling* banelings[5];
extern Hydralisk*hydralisks[3];
extern Roach* roachs[4];
extern Zergling* zerglings[5];
extern Hydraspit*hydraspits[3];
extern Bullet_Double* bullets_DoubleA[20];
extern Bullet_Double* bullets_DoubleB[20];
extern int bp_DoubleA;
extern int bp_DoubleB;
extern int banep;
extern int rop;
extern int zergp;
extern int spitp;
extern int hydrap;
extern int spitp;
extern Item item;

class Bullet_Double
{
public:
	Bullet_Double();
	~Bullet_Double() {};
	bool act_A();                           //A子弹表现
	bool act_B();                           //B子弹表现
	void draw();                             //绘制子弹
private:
	int xA, yA, xB, yB, mousex, mousey;
	double vxA, vyA, vxB, vyB;
	const int v;
};
void fire_DoubleA();                                     //A攻击
bool addBullet_DoubleA(Bullet_Double *p);//删除A子弹
bool deleteBullet_DoubleA(Bullet_Double *p);//添加A子弹

void fire_DoubleB();                                        //B攻击
bool addBullet_DoubleB(Bullet_Double *p);//删除B子弹
bool deleteBullet_DoubleB(Bullet_Double *p);//添加B子弹

void deleteAllBullets_Double();  //双人模式下删除所有子弹