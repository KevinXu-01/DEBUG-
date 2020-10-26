///////////////////////////////////////////////////////
// 文件名称：	PauseAndDelete.h
//   负责人：	江诗烨
//     学号：	2018302060048
//   代码量：	79行
// 编译环境：	Visual Studio 2015 + EasyX 20190415(beta) 
// 最后修改：	2019-6-12
// 实现功能：	杂项功能（游戏结束后删除所有虫子、金币；暂停
////////////////////////////////////////////////////////
#pragma once
#include"graphics.h"
#include<easyx.h>
#include"Bugs.h"
#include"Coins.h"
static bool stap=false;//暂停键是否处于按下状态
extern bool deleteBaneling(Baneling* z);
extern bool deleteHydralisk(Hydralisk* z);
extern bool deleteHydraspit(Hydraspit* z);
extern bool deleteRoach(Roach* z);
extern bool deleteZergling(Zergling* z);
extern bool deleteCoin(Coins* c);
extern Coins* coins[5];
extern Hydraspit* hydraspits[3];

//判断并暂停
void ifp()
{
	if(!(GetAsyncKeyState('P') & 0x8000)&&stap==true)
	{
		stap = false;
		SetWorkingImage();
		settextcolor(WHITE);
		settextstyle(20, 0, _T("黑体"), 0, 0, 500, false, false, false);
		outtextxy(670, 450, _T("游戏已暂停"));//输出字符
		HRGN rgn = CreateRectRgn(765, 5, 800, 30);
		setcliprgn(rgn);
		clearcliprgn();//清空暂停图片区域
		IMAGE resume;
		loadimage(&resume, _T("IMAGE"), _T("RESUME"));//载入继续图片
		putimage(765, 5, &resume);
		DeleteObject(rgn);//删除矩形区域
		setcliprgn(NULL);//指向空区域
		EndBatchDraw();
		for (;;)
		{
			if (!(GetAsyncKeyState('P') & 0x8000) && stap == true)
			{
				stap = false;
				SetWorkingImage();
				HRGN rgn1 = CreateRectRgn(645, 445, 800, 480);
				HRGN rgn = CreateRectRgn(765, 5, 800, 30);
				setcliprgn(rgn1);
				clearcliprgn();
				DeleteObject(rgn1);//删除矩形区域
				setcliprgn(rgn);
				clearcliprgn();
				DeleteObject(rgn);//删除矩形区域
				setcliprgn(NULL);//指向空区域
				IMAGE pause;
				loadimage(&pause, _T("IMAGE"), _T("PAUSE"));//载入暂停按钮图片
				EndBatchDraw();
				break;
			}
			if (GetAsyncKeyState('P') & 0x8000)
				stap = true;
		}
	}
	if (GetAsyncKeyState('P') & 0x8000)
		stap = true;
}

//删除所有虫子和金币
void deleteallbugsandcoins()
{
	//由于delete时会重新排序，故每次都删除数组内第一个元素
	for (int i = 0; i < banep; i++)
		deleteBaneling(banelings[0]);
	for (int i = 0; i < hydrap; i++)
		deleteHydralisk(hydralisks[0]);
	for (int i = 0; i < spitp; i++)
		deleteHydraspit(hydraspits[0]);
	for (int i = 0; i < rop; i++)
		deleteRoach(roachs[0]);
	for (int i = 0; i < zergp; i++)
		deleteZergling(zerglings[0]);
	for (int i = 0; i < coinsp; i++)
		deleteCoin(coins[0]);
}