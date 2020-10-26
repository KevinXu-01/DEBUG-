///////////////////////////////////////////////////////
// 文件名称：	Zergling.h
//   负责人：	江诗烨
//     学号：	2018302060048
//   代码量：	26行
// 编译环境：	Visual Studio 2015 + EasyX 20190415(beta) 
// 最后修改：	2019-6-12
// 实现功能：	跳虫个体的生成与行动
////////////////////////////////////////////////////////
#pragma once
#include"Zerg.h"

class Zergling :public Zerg								//毒爆
{
public:
	Zergling(); 										//构造
	~Zergling()
	{
		Zerg::ToGraveyard();							//已死亡虫子数加一
	}
	void act();											//行动
	int i = 64;											//绘制计数
	void drawzergling();								//绘制
	int type = 0;										//状态（是否加速
private:
	void shift();										//shift
	void attack();										//attack
	int attackgap;										//attackgap
	static int lastx;
	static int lasty;									//上一只同类出生位置
};

extern int zergp;										//已有数量
static float zergling_Max;								//最大存在数量
static int zergling_generate_gap;						//重生间隔