///////////////////////////////////////////////////////
// 文件名称：	Roach.h
//   负责人：	江诗烨
//     学号：	2018302060048
//   代码量：	25行
// 编译环境：	Visual Studio 2015 + EasyX 20190415(beta) 
// 最后修改：	2019-6-12
// 实现功能：	蟑螂个体的生成与行动
////////////////////////////////////////////////////////
#pragma once
#include"Zerg.h"

class Roach :public Zerg								//蟑螂
{
public:
	Roach();	 										//构造
	~Roach()
	{
		Zerg::ToGraveyard();							//已死亡虫子数加一
	}
	void act();											//行动
	int i = 0;											//绘制计数
	void drawroach();									//绘制
private:
	void recover();										//recover
	int bite();											//bite
	int type;											//加速状态
	static int lastx;
	static int lasty;									//上一只同类出现位置
};

extern int rop;											//统计已有的数目
static float roach_Max;									//最大允许数目
static int roach_generate_gap;							//重生冷却的间隔