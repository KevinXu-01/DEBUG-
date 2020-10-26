///////////////////////////////////////////////////////
// 文件名称：	main.cpp
//   负责人：	杨景博
//     学号：	2018302060060
//   代码量：	119行
// 编译环境：	Visual Studio 2015 + EasyX_20190415(beta)
// 最后修改：	2019-6-22
// 实现功能：	游戏整体功能整合与实现
////////////////////////////////////////////////////////

#include<conio.h>
#include"Person.h"
#include"Score.h"
#include"GameStart.h"
#include"InterfaceOfScore.h"
#include"CoreInterface.h"
#include"Bugs.h"
#include"Bullet_Single.h"
#include"Bullet_Double.h"
#include"Coins.h"
#include"PauseAndDelete.h"
#include"Item.h"
using namespace std;

Person personA, personB;							//定义人的对象
Bullet_Double *bullets_DoubleA[20];					//双人模式下A的子弹
Bullet_Double *bullets_DoubleB[20];					//双人模式下B的子弹
Bullet_Single *bullets_Single[20];					//单人模式下的子弹
int bp_Single = 0;									//更新单人模式下子弹使用
int bp_DoubleA = 0, bp_DoubleB = 0;					//更新双人模式下子弹使用
Score score;										//定义分数
MOUSEMSG mouse;										//定义用于存储鼠标状态的变量
Item item;											//定义道具类
int mode=0;											//定义模式变量
bool gameWillRestart = false;						//定义是否重新开始的变量

//主函数
int main()
{
	initgraph(800, 480);							//初始化画布
	playMusic();
	gameStart();									//游戏主菜单
	personB.setPlayer('B');							//人物B初始化
	personB.setPersonPosition(370, 370);
	initzergdraw();									//初始化绘图
	initcoinsdraw();
	initzergclock();

	//绘图主循环
	while (1)										
	{
		if (mode == 0)
			personB.setHealthPoint(0, 0);			//人物B设置为死亡
		renewzergclock();
		BeginBatchDraw();							//开始批量绘图
		CoreInterface_main(mode);
		showInfo_init(mode);
		reshowInfo_score();
		reshowInfo_coin(mode);
		personA.setControl();
		personA.showPerson();
		item.setControl();
		if (mode == 1)
		{
			item.setControl();
			personB.setControl();
			personB.showPerson();
		}
		allzergsact();
		allcoinsact();

		//对A进行开火判定
		if (personA.getHealthPoint() > 0&&personA.getWeapon()!='O')
		{
			if (mode == 0)//单人模式
			{
				fire_Single();
				for (int i = 0; i < bp_Single; i++)				//更新子弹的运动、行为
				{
					bullets_Single[i]->draw();
					if (!(bullets_Single[i]->act()))
						deleteBullet_Single(bullets_Single[i]);
				}
			}
			else//双人模式
			{
				fire_DoubleA();
				for (int i = 0; i < bp_DoubleA; i++)				//更新子弹的运动、行为
				{
					bullets_DoubleA[i]->draw();
					if (!(bullets_DoubleA[i]->act_A()))
						deleteBullet_DoubleA(bullets_DoubleA[i]);
				}
			}
		}
		//对B进行开火判定
		if (personB.getHealthPoint() > 0 && personB.getWeapon() != 'O')
		{
			fire_DoubleB();
			for (int i = 0; i < bp_DoubleB; i++)				//更新子弹的运动、行为
			{
				bullets_DoubleB[i]->draw();
				if (!(bullets_DoubleB[i]->act_B()))
					deleteBullet_DoubleB(bullets_DoubleB[i]);
			}
		}
		item.setControl();
		ifp();
		if (personA.getHealthPoint() <= 0 && personB.getHealthPoint() <= 0)		//判断人物是否都死亡
		{
			deleteallbugsandcoins();											//删除所有虫子和金币
			if (mode == 1)
				deleteAllBullets_Double();										//删除所有子弹
			if (mode == 0)
				deleteAllBullets_Single();										//删除所有子弹
			CoreInterface_main(mode);
			interfaceOfScore();													//死亡则进入分数结算界面
		}
		else if (personA.getHealthPoint() <= 0&&mode==1)						//判断是否只有单人死亡
			personA.personRevive();												//人物A进入复活读秒
		else if (personB.getHealthPoint() <= 0&&mode==1)
			personB.personRevive();												//人物B进入复活读秒
		else;
		Sleep(10);
		EndBatchDraw();															//结束批量绘图						
		FlushMouseMsgBuffer();													//清除鼠标消息
		}		
	return 0;
}