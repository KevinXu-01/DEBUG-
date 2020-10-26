///////////////////////////////////////////////////////
// 文件名称：	InterfaceOfScore.cpp
//   负责人：	范承祥
//     学号：	2018302060043
//   代码量：	197行
// 编译环境：	Visual Studio 2015 + EasyX_20180321(春分版) 
// 最后修改：	2019-6-12
// 实现功能：	分数结算界面数字处理、数字显示、界面跳转等
////////////////////////////////////////////////////////
#include<easyx.h>
#include"Person.h"
#include"Score.h"
#include"resource.h"
#include"GameStart.h"
#include"CoreInterface.h"
#include"InterfaceOfScore.h"
#include"State.h"

extern Person personA, personB;				//外部引用
extern Score score;
extern MOUSEMSG mouse;
extern int mode;
extern bool gameWillRestart;

struct State sta1;							//定义结构体

//数字处理函数(数组名，数组长度，处理数字)
short numberProcess(short n[],int l,int s)
{
	for (int i = 0; i < l; i++)
	{
		if (s % 10 == s)					//判断当前数值是否为个位
		{
			n[i] = s;						//当前元素=当前数值
			return 0;						//结束处理
		}
		else
		{
			n[i] = s % 10;					//当前元素=当前数值的个位
			s /= 10;						//当前元素去掉最低位
		}
	}
}

//数字显示函数
void showNumber()
{
	short s[10];																//存储处理数字
	short c[10];
	short vs = 0;																//数字有效位数
	short vc = 0;
	IMAGE numberMaskPtr[11];													//存储遮罩的图像指针
	IMAGE coinsNumberMaskPtr[12];
	IMAGE numberPtr[11];														//存储数字的图像指针
	IMAGE coinsNumberPtr[12];
	loadimage(&numberMaskPtr[10], _T("IMAGE"), _T("numberMask"));				//载入遮罩
	loadimage(&coinsNumberMaskPtr[11], _T("IMAGE"), _T("coinsNumberMask"));
	loadimage(&numberPtr[10], _T("IMAGE"), _T("number"));						//载入数字
	loadimage(&coinsNumberPtr[11], _T("IMAGE"), _T("coinsNumber"));
	for (int i = 0; i < 10; i++)												//图像切割并储存
	{
		SetWorkingImage(&numberMaskPtr[10]);
		getimage(&numberMaskPtr[i], 39 * i, 0, 39, 60);
		SetWorkingImage(&numberPtr[10]);
		getimage(&numberPtr[i], 39 * i, 0, 39, 60);
		SetWorkingImage(NULL);
	}
	for (int j = 0; j < 11; j++)
	{
		SetWorkingImage(&coinsNumberMaskPtr[11]);
		getimage(&coinsNumberMaskPtr[j], 22 * j, 0, 22, 35);
		SetWorkingImage(&coinsNumberPtr[11]);
		getimage(&coinsNumberPtr[j], 22 * j, 0, 22, 35);
		SetWorkingImage(NULL);
	}
	for (int i = 0; i < 10; i++)													//数组初始化为-1
		s[i] = c[i] = -1;
	numberProcess(s, 10, score.getScore());											//分数数字处理	
	numberProcess(c, 10, Person::getCoins());										//金币数数字处理
	for (int i = 0; i < 10; i++)													//数字有效位数计算
	{
		if (s[i] != -1)
			vs++;
		if (c[i] != -1)
			vc++;
	}
	for (int k = 0; k < 10; k++)													//数字显示
	{
		if (s[k] != -1)																//判断是否为无效位
		{
			putimage(320 + 39 * (vs / 2 - k-1), 175, &numberMaskPtr[s[k]], SRCAND); //通过有效位数计算使数字居中显示
			putimage(320 + 39 * (vs / 2 - k-1), 175, &numberPtr[s[k]], SRCPAINT);	
		}
		if (k == 0)
		{
			putimage(288, 275, &coinsNumberMaskPtr[k], SRCAND);
			putimage(288, 275, &coinsNumberPtr[k], SRCPAINT);
		}
		if(c[k] != -1)
		{
			putimage(320 + 22 * (vc / 2 - k + 1 ), 275, &coinsNumberMaskPtr[c[k] + 1], SRCAND);
			putimage(320 + 22 * (vc / 2 - k + 1 ), 275, &coinsNumberPtr[c[k] + 1], SRCPAINT);
		}
	}
}

//鼠标范围判断函数
bool mouseRange(MOUSEMSG m,int left,int right,int bottom,int top )
{	
		if (left <= mouse.x&&mouse.x <= right
			&&bottom <= mouse.y&&mouse.y <= top)
			return true;
		else
			return false;
}

//分数结算界面
void interfaceOfScore()
{
	IMAGE scoresBackgroundPtr;													//存储图像的图像指针
	IMAGE btnMenuPtr;
	IMAGE btnMenuOverPtr;
	IMAGE btnResetPtr;
	IMAGE btnResetOverPtr;
	IMAGE btnMaskPtr;															//存储遮罩的图像指针
	loadimage(&scoresBackgroundPtr, _T("IMAGE"), _T("scoresBackground"));		//载入图像
	loadimage(&btnMenuPtr, _T("IMAGE"), _T("btnMenu"));
	loadimage(&btnMenuOverPtr, _T("IMAGE"), _T("btnMenuOver"));
	loadimage(&btnResetPtr, _T("IMAGE"), _T("btnReset"));
	loadimage(&btnResetOverPtr, _T("IMAGE"), _T("btnResetOver"));
	loadimage(&btnMaskPtr, _T("IMAGE"), _T("btnMask"));							//载入遮罩
	gameWillRestart = false;

	//分数结算界面绘图主循环
	while (!(gameWillRestart))
	{
		BeginBatchDraw();														//开始批量绘图
		putimage(0, 0, 640, 480, &scoresBackgroundPtr, 0, 0);					//显示图像
		putimage(344, 352, 72, 72, &btnMaskPtr, 0, 0, SRCAND);
		putimage(344, 352, 72, 72, &btnMenuPtr, 0, 0, SRCPAINT);
		putimage(220, 352, 72, 72, &btnMaskPtr, 0, 0, SRCAND);
		putimage(220, 352, 72, 72, &btnResetPtr, 0, 0, SRCPAINT);
		showNumber();															//显示数字
		if (sta1.processed == false)											//判断是否已经加分
		{
			score.coinsPlus(Person::getCoins());								//金币加分
			reshowInfo_score();													//分数更新
			sta1.processed = true;												//处理状态更改
			score.writeScore();													//分数记录文件写入
		}
		if (MouseHit())															//判断是否有鼠标信息
			mouse = GetMouseMsg();												//捕获鼠标信息
		switch (mouse.uMsg)
		{
		case WM_MOUSEMOVE:
			if (mouseRange(mouse, 344, 416, 352, 424))							//鼠标移动到相应区域
			{
				putimage(344, 352, 72, 72, &btnMaskPtr, 0, 0, SRCAND);			//按钮变黄
				putimage(344, 352, 72, 72, &btnMenuOverPtr, 0, 0, SRCPAINT);
			}
			else if (mouse, mouseRange(mouse, 220, 292, 352, 424))
			{
				putimage(220, 352, 72, 72, &btnMaskPtr, 0, 0, SRCAND);
				putimage(220, 352, 72, 72, &btnResetOverPtr, 0, 0, SRCPAINT);
			}
			break;
		case WM_LBUTTONDOWN:													//鼠标左键按下
			if (mouseRange(mouse, 344, 416, 352, 424))
			{
				sta1.processed = false;											//处理状态恢复
				personA.~Person();												//人物初始化
				personB.~Person();
				personB.setPersonPosition(370, 370);
				Person::spendCoins(Person::getCoins());							//金币归零
				score.~Score();													//分数初始化																		//FlushMouseMsgBuffer();												//清除鼠标消息
				gameStart();													//进入主菜单
				gameWillRestart = true;											//游戏可以再次开始
				FlushMouseMsgBuffer();											//清除鼠标信息
			}
			else if (mouse, mouseRange(mouse, 220, 292, 352, 424))
			{
				sta1.processed = false;											//处理状态恢复
				switch (mode)
				{
				case 0: personA.~Person();										//单人模式初始化
					score.~Score();
					Person::spendCoins(Person::getCoins());						//金币归零
					gameWillRestart = true;										//游戏可以再次开始
					FlushMouseMsgBuffer();										//清除鼠标信息
					break;
				case 1: personA.~Person();										//双人模式初始化
					personB.~Person();
					personB.setPersonPosition(370, 370);
					Person::spendCoins(Person::getCoins());						//金币归零
					score.~Score();
					gameWillRestart = true;
					FlushMouseMsgBuffer();
					break;
				}
			}
			break;
		}
		EndBatchDraw();
		FlushMouseMsgBuffer();													//清除鼠标消息
	}
}