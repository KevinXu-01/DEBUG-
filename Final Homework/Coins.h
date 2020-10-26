///////////////////////////////////////////////////////
// 文件名称：	Coins.h
//   负责人：	江诗烨
//     学号：	2018302060048
//   代码量：	23行
// 编译环境：	Visual Studio 2015 + EasyX 20190415(beta) 
// 最后修改：	2019-6-12
// 实现功能：	金币的生成与活动
////////////////////////////////////////////////////////
#pragma once
#include"Person.h"

class Coins
{
public:
	Coins(int zx,int zy);
	~Coins() {};
	void drawcoins();						//绘制金币
	void CoinsPlay();						//金币相关
private:
	int x, y;
	void getcoins();						//获取金币
	int t=300;								//摧毁倒计时
	int i=0;								//闪烁计数
};

extern int coinsp;							//场上最多同时出现金币数受限，用其计数
void initcoinsdraw();						//初始化绘制
void allcoinsact();							//执行掉落金币所有功能

bool addCoin( Coins* c);
bool deleteCoin(Coins* c);