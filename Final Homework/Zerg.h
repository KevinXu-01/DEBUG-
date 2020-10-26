///////////////////////////////////////////////////////
// 文件名称：	Zerg.h
//   负责人：	江诗烨
//     学号：	2018302060048
//   代码量：	51行
// 编译环境：	Visual Studio 2015 + EasyX 20190415(beta) 
// 最后修改：	2019-6-12
// 实现功能：	虫（父类）的基本功能
////////////////////////////////////////////////////////
#pragma once
#include"Person.h"
#define stdv 3
//enum ztype { baneling, hydralisk, roach, zergling,zergspit };	//毒爆，刺蛇，蟑螂，跳虫，刺（可被子弹阻挡，视作虫）

class Zerg
{
public:
	bool block(int hx,int hy);							//油桶的阻塞
	double aofblock1(int halfx,int halfy);
	double aofblock2(int halfx,int halfy);				//阻塞角
	int distofblock1();
	int distofblock2();									//油桶距离
	int clock=0;										//存活时间计时器
	void getscore();									//击杀给分
	bool ifcoins();										//是否掉落金币
	int at;												//转身速度
	double e;											//朝向角度
	double b, c, d, a;									//临时存放角度，延迟转向
	void rotate(int halfx,int halfy);					//改变a的值
	int HP;												//当前生命
	int maxHP;											//最大生命值
	int skillgap;										//技能冷却时间
	int zergv;											//速度
	int scorevalue();									//分数
	int val=0;											//权
	int coinsodds=10;									//掉落几率
	static int graveyard;								//已死亡虫子数量
	static void ToGraveyard()
	{
		graveyard++;									//统计已死亡虫子数量
	}
	static int getgraveyard()
	{
		return graveyard;
	}
	bool judgeDie()										//是否死亡
	{
		if (HP <= 0)
			return true;
		else
			return false;
	}
	void gettarget();									//寻找目标（改变并获取
	bool ifhunting = 0;									//是否已有目标
	Person *target=nullptr;								//target
	int getdistance(Person person);						//获取距离（平方值
	void damaged(int damage);							//受到伤害
	int x, y;											//x坐标及y坐标
};
int unum(double a);										//向上取整