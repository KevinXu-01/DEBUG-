///////////////////////////////////////////////////////
// 文件名称：	Baneling.h
//   负责人：	江诗烨
//     学号：	2018302060048
//   代码量：	36行
// 编译环境：	Visual Studio 2015 + EasyX 20190415(beta) 
// 最后修改：	2019-6-12
// 实现功能：	刺虫个体的生成与行动
////////////////////////////////////////////////////////
#pragma once
#include"Zerg.h"
class Hydralisk :public Zerg							//刺蛇
{
public:
	Hydralisk(); 										//构造
	~Hydralisk()
	{
		Zerg::ToGraveyard();							//已死亡虫子数加一
	}
	int hypv=0;											//强化速度
	void act();											//行动
	int i = 0;											//绘制计数
	int j = 1;											//扭动方向
	void drawhydralisk();								//绘制
private:
	void spit();										//spit
	static int lastx;
	static int lasty;									//上一只同类出现位置
};

extern int hydrap;										//计数
static float hydralisk_Max;								//最大数目
static int hydralisk_generate_gap;						//出生冷却时间

class Hydraspit:public Zerg								//刺虫（刺蛇的攻击
{
public:
	Hydraspit(int ix, int iy, float ia,int hv) ; 		//构造
	~Hydraspit() {};
	void act();											//行动
	void drawhydraspit();								//绘制
};

extern int spitp;										//场上所有刺的数量
extern float hydraspit_Max;								//最多允许出现的刺的数目