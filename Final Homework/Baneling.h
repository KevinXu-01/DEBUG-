///////////////////////////////////////////////////////
// 文件名称：	Baneling.h
//   负责人：	江诗烨
//     学号：	2018302060048
//   代码量：	27行
// 编译环境：	Visual Studio 2015 + EasyX 20190415(beta) 
// 最后修改：	2019-6-12
// 实现功能：	爆虫个体的生成与行动
////////////////////////////////////////////////////////
#pragma once
#include"Zerg.h"

class Baneling :public Zerg								//毒爆
{
public:
	Baneling(); 										//构造
	~Baneling()
	{
		Zerg::ToGraveyard();							//已死亡虫子数加一
	}
	void act();											//行动
	int i = 0;											//绘制计数
	int j = 0;											//爆炸前读秒
	int drawexplode();
	void drawbaneling();								//绘制
	int type = 0;										//状态（是否爆炸
	double staa=0;										//静滞状态转向角
private:
	void explode();										//explode
	static int lastx;
	static int lasty;									//上一只同类出现位置
};

extern int banep;										//计数
static float baneling_Max;								//最大数目
static int baneling_generate_gap;						//出生冷却时间