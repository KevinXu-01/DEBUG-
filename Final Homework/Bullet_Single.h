///////////////////////////////////////////////////////
// 文件名称：	Bullet_Single.h
//   负责人：	许静宇
//     学号：	2018302060052
//   代码量：	44行
// 编译环境：	Visual Studio 2015 + EasyX_20190415(beta)
// 最后修改：	2019-6-12
// 实现功能：	定义Bullet_Single类，对函数进行声明
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

class Bullet_Single;
extern MOUSEMSG mouse;
extern Person personA, personB;
extern Baneling* banelings[5];
extern Hydralisk*hydralisks[3];
extern Roach* roachs[4];
extern Zergling* zerglings[5];
extern Hydraspit*hydraspits[3];
extern Bullet_Single* bullets_Single[20];
extern int bp_Single;
extern int banep;
extern int rop;
extern int zergp;
extern int spitp;
extern int hydrap;
extern int spitp;
extern Item item;

class Bullet_Single
{
public:
	Bullet_Single();
	~Bullet_Single() {};
	bool act();                                //子弹表现
	void draw();                             //绘制子弹
private:
	int x, y, mousex, mousey;
	double vx, vy;
	const int v;
};
void fire_Single();
bool addBullet_Single(Bullet_Single *p);//删除子弹
bool deleteBullet_Single(Bullet_Single *p);//添加子弹
void deleteAllBullets_Single();    //单人模式下删除所有子弹