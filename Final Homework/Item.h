///////////////////////////////////////////////////////
// 文件名称：	Item.h
//   负责人：	杨景博
//     学号：	2018302060060
//   代码量：	53行
// 编译环境：	Visual Studio 2015 + EasyX_20190415(beta)
// 最后修改：	2019-6-22
// 实现功能：	绷带、急救包、能量饮料和油桶道具的功能实现
////////////////////////////////////////////////////////

#pragma once
#include"Person.h"
#include "Bugs.h"

extern Person personA, personB;
extern Baneling* banelings[5];
extern Hydralisk*hydralisks[3];
extern Roach* roachs[4];
extern Zergling* zerglings[5];
extern Hydraspit*hydraspits[3];
extern int banep;
extern int rop;
extern int zergp;
extern int spitp;
extern int hydrap;
extern int spitp;
static bool OTa = 0, OTb = 0;
static bool ifPut_A = false;
static bool ifPut_B = false;

class Item
{
public:
	Item();
	~Item() {};
	void EnergyDrinkA();                        //可乐加速
	void EnergyDrinkB();                        //可乐加速
	void BandageA();                            //绷带恢复生命值
	void BandageB();                            //绷带恢复生命值
	void FirstAidA();                           //急救包
	void FirstAidB();                           //急救包
	void SetOilTankA();                         //油桶的放置
	void SetOilTankB();                         //油桶的放置
	int OilTankExplodeA();                      //油桶的爆炸效果
	int OilTankExplodeB();
	void setControl();                          //玩家购买道具操控
	void OilTankA();                        //油桶属性
	void OilTankB();
	void loadoilTankA();                        //载入油桶图片
	void loadoilTankB();                        //载入油桶图片
	int AgetOilTankPositionX();                   //获取油桶位置
	int AgetOilTankPositionY();
	int BgetOilTankPositionX();
	int BgetOilTankPositionY();
	int i = 0;
private:
	int x0;
	int y0;
	int x_oilA = 1000;
	int y_oilA = 1000;
	int x_oilB = 1000;
	int y_oilB = 1000;
};