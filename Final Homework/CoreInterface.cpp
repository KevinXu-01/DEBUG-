///////////////////////////////////////////////////////
// 文件名称：	CoreInterface.cpp
//   负责人：	许静宇
//     学号：	2018302060052
//   代码量：	319行
// 编译环境：	Visual Studio 2015 + EasyX_20190415(beta)
// 最后修改：	2019-6-12
// 实现功能：	实时显示信息、播放音乐、显示商店等
////////////////////////////////////////////////////////

#include "CoreInterface.h"
#include "Person.h"
#include "Score.h"

extern Score score;//全局变量
extern Person personA, personB;
bool ifPlayMusic = true;
void showMap()
{
	IMAGE Background;
	IMAGE Black_Background;
	loadimage(&Background, _T("IMAGE"), _T("BACKGROUND"));//载入背景图片
	loadimage(&Black_Background, _T("IMAGE"), _T("BLACKBACKGROUND"));//载入黑色图片
	putimage(0, 0, &Background);
	putimage(640, 0, &Black_Background);
}

void showInfo_init_single()
{
	IMAGE scorepic;
	IMAGE heart;
	//绘制分界线
	setlinecolor(RED);
	line(640, 240, 800, 240);
	line(640, 239, 800, 239);
	line(640, 241, 800, 241);
	//载入分数部分
	loadimage(&scorepic, _T("IMAGE"), _T("SCORE"));//载入分数图片
	putimage(645, 35, &scorepic);
	settextcolor(WHITE);
	settextstyle(25, 0, _T("黑体"), 0, 0, 500, false, false, false);
	if(score.getScore()==0)
	outtextxy(650, 85, _T("0"));//输出字符
	//载入金币部分
	settextcolor(WHITE);
	settextstyle(20, 0, _T("黑体"), 0, 0, 500, false, false, false);
	outtextxy(650, 105, _T("金币："));//输出字符
	if(Person::getCoins()==0)
	outtextxy(705, 105, _T("0"));//输出字符
	//载入生命值部分
	settextcolor(YELLOW);
	settextstyle(30, 0, _T("黑体"), 0, 0, 500, false, false, false);
	outtextxy(680, 135, _T("生命值"));//输出字符
	loadimage(&heart, _T("IMAGE"), _T("HEART"));//载入心图片
	if(personA.getHealthPoint()>0)
	putimage(652, 175, &heart);
	if(personA.getHealthPoint()>1)
	putimage(687, 175, &heart);
	if(personA.getHealthPoint()>2)
	putimage(722, 175, &heart);//放置心的图案
}

void showInfo_init_double()
{
	IMAGE score;
	IMAGE heart;
	//绘制分界线
	setlinecolor(RED);
	line(640, 240, 800, 240);
	line(640, 239, 800, 239);
	line(640, 241, 800, 241);
	//载入分数部分
	loadimage(&score, _T("IMAGE"), _T("SCORE"));//载入分数图片
	putimage(645, 35, &score);
	settextcolor(WHITE);
	settextstyle(25, 0, _T("黑体"), 0, 0, 500, false, false, false);
	outtextxy(650, 85, _T("0"));//输出字符
	//载入金币部分
	settextcolor(WHITE);
	settextstyle(20, 0, _T("黑体"), 0, 0, 500, false, false, false);
	outtextxy(650, 105, _T("金币："));//输出字符
	if (Person::getCoins() == 0)
	outtextxy(705, 105, _T("0"));//输出字符
	//载入生命值部分
	settextcolor(YELLOW);
	settextstyle(30, 0, _T("黑体"), 0, 0, 500, false, false, false);
	outtextxy(680, 135, _T("生命值"));//输出字符
	loadimage(&heart, _T("IMAGE"), _T("HEART"));//载入心图片
	//实现复活
	int ReviveTimeA = personA.getReviveTime();
	int ReviveTimeB = personB.getReviveTime();
#define ReviveTime_1 ReviveTimeA
#define ReviveTime_2 ReviveTimeB
	loadimage(&heart, _T("IMAGE"), _T("HEART"));//载入心图片
	if (personA.getHealthPoint()<=0&& personB.getHealthPoint() > 0)
	{
		settextcolor(WHITE);
		settextstyle(20, 0, _T("黑体"), 0, 0, 500, false, false, false);
		TCHAR reviveA[10];
		_stprintf_s(reviveA, _T("%d"), ReviveTime_1);
		outtextxy(652, 175, reviveA);//输出字符
		outtextxy(672, 175, _T("秒后可以复活"));//输出字符
	}
	if (personB.getHealthPoint() <= 0&&personA.getHealthPoint() > 0)
	{
		settextcolor(WHITE);
		settextstyle(20, 0, _T("黑体"), 0, 0, 500, false, false, false);
		TCHAR reviveB[10];
		_stprintf_s(reviveB, _T("%d"), ReviveTime_2);
		outtextxy(652, 204, reviveB);//输出字符
		outtextxy(672, 204, _T("秒后可以复活"));//输出字符
	}
	//放置玩家A的心图案
	if(personA.getHealthPoint()>0)
	putimage(652, 175, &heart);
	if(personA.getHealthPoint()>1)
	putimage(687, 175, &heart);
	if (personA.getHealthPoint()>2)
	putimage(722, 175, &heart);
	//放置玩家B的心图案
	if (personB.getHealthPoint()>0)
	putimage(652, 204, &heart);
	if (personB.getHealthPoint()>1)
	putimage(687, 204, &heart);
	if (personB.getHealthPoint()>2)
	putimage(722, 204, &heart);
}

void showStore()
{
	IMAGE store;
	IMAGE first_aid_kit;
	IMAGE bandage;
	IMAGE energy_drink;
	IMAGE oil_tank;
	loadimage(&store, _T("IMAGE"), _T("STORE"));//载入商店图片
	loadimage(&first_aid_kit, _T("IMAGE"), _T("FIRST_AID_KIT"));//载入急救包图片
	loadimage(&bandage, _T("IMAGE"), _T("BANDAGE"));//载入绷带图片
	loadimage(&energy_drink, _T("IMAGE"), _T("ENERGY_DRINK"));//载入能量饮料图片
	loadimage(&oil_tank, _T("IMAGE"), _T("OIL_TANK"));//载入油桶图片
	putimage(695, 250, &store);
	putimage(660, 310, &first_aid_kit);
	putimage(730, 310, &bandage);
	putimage(660, 380, &energy_drink);
	putimage(730, 380, &oil_tank);
	settextcolor(WHITE);
	settextstyle(15, 0, _T("黑体"), 0, 0, 500, false, false, false);
	outtextxy(660, 360, _T("5个金币"));//输出字符
	outtextxy(730, 360, _T("3个金币"));//输出字符
	outtextxy(660, 430, _T("2个金币"));//输出字符
	outtextxy(730, 430, _T("7个金币"));//输出字符
}

void showButtons()
{
	IMAGE pause;
	loadimage(&pause, _T("IMAGE"), _T("PAUSE"));//载入暂停按钮图片
	putimage(765, 5, &pause);
}

void reshowInfo_playerA_hp()//玩家A的生命值接口
{
	//设置矩形框，以便于选定该矩形框以实现清空，下面的函数中类似的代码具有相同的功能
	HRGN rgn = CreateRectRgn(641, 175, 800, 203);
	setcliprgn(rgn);
	clearcliprgn();
	IMAGE heart;
	int healthpoint_A = personA.getHealthPoint();
	int i = 0;//循环变量
	loadimage(&heart, _T("IMAGE"), _T("HEART"));//载入心图片
	if(healthpoint_A>0)
	for (i = 0; i <= healthpoint_A - 1; i++)
	{
		putimage(652 + i * 35, 175, &heart);
	}
	//增加一个1ms的延时，防止信息更新时出现闪烁
	Sleep(1);
	//删除该矩形框，并将绘图区域置为默认
	DeleteObject(rgn);
	setcliprgn(NULL);
}

void reshowInfo_playerB_hp()//玩家B的生命值接口
{
	HRGN rgn = CreateRectRgn(641, 204, 800, 238);
	setcliprgn(rgn);
	clearcliprgn();
	IMAGE heart;
	int healthpoint_B = personB.getHealthPoint();
	int i = 0;//循环变量
	loadimage(&heart, _T("IMAGE"), _T("HEART"));//载入心图片
	for (i = 0; i <= healthpoint_B - 1; i++)
	{
		putimage(652 + i * 35, 204, &heart);
	}
	Sleep(1);
	DeleteObject(rgn);
	setcliprgn(NULL);
}

void reshowInfo_score()//分数接口
{
	int score1 = score.getScore();
#define score_1 score1
	HRGN rgn = CreateRectRgn(650, 75, 800, 104);
	setcliprgn(rgn);
	clearcliprgn();
	settextcolor(WHITE);
	settextstyle(25, 0, _T("黑体"), 0, 0, 500, false, false, false);
	TCHAR score[10];
	_stprintf_s(score, _T("%d"), score_1);
	outtextxy(650, 75, score);//输出字符
	Sleep(1);
	DeleteObject(rgn);
	setcliprgn(NULL);
}

void reshowInfo_coin_single()//单人模式的金币接口
{
	int coin1 = Person::getCoins();
#define coin_1 coin1
	HRGN rgn = CreateRectRgn(705, 105, 800, 135);
	setcliprgn(rgn);
	clearcliprgn();
	settextcolor(WHITE);
	settextstyle(20, 0, _T("黑体"), 0, 0, 500, false, false, false);
	TCHAR coin[10];
	_stprintf_s(coin, _T("%d"), coin_1);
	outtextxy(705, 105, coin);//输出字符
	Sleep(1);
	DeleteObject(rgn);
	setcliprgn(NULL);
}

void reshowInfo_coin_double()//双人模式的金币接口
{
	int coin1 = Person::getCoins();
#define coin_1 coin1
	HRGN rgn = CreateRectRgn(705, 105, 800, 135);
	setcliprgn(rgn);
	clearcliprgn();
	settextcolor(WHITE);
	settextstyle(20, 0, _T("黑体"), 0, 0, 500, false, false, false);
	TCHAR coin[10];
	_stprintf_s(coin, _T("%d"), coin_1);
	outtextxy(705, 105, coin);//输出字符
	Sleep(1);
	DeleteObject(rgn);
	setcliprgn(NULL);
}

bool ExtractResource(LPCTSTR strDstFile, LPCTSTR strResType, LPCTSTR strResName)//从资源文件中提取文件，加载到内存中，以便MciSendString读取
{
	if (ifPlayMusic == true)
	{
		//创建文件
		HANDLE hFile = ::CreateFile(strDstFile, GENERIC_WRITE, NULL, NULL, CREATE_ALWAYS, FILE_ATTRIBUTE_TEMPORARY, NULL);
		if (hFile == INVALID_HANDLE_VALUE)
			return false;
		//查找资源文件中、加载资源到内存、得到资源大小
		HRSRC	hRes = ::FindResource(NULL, strResName, strResType);
		HGLOBAL	hMem = ::LoadResource(NULL, hRes);
		DWORD	dwSize = ::SizeofResource(NULL, hRes);
		//写入文件
		DWORD dwWrite = 0;  	// 返回写入字节
		::WriteFile(hFile, hMem, dwSize, &dwWrite, NULL);
		::CloseHandle(hFile);
		return true;
	}
}

void playMusic()
{
	if (ifPlayMusic == true)
	{
		TCHAR tmpmp3[_MAX_PATH];
		::GetTempPath(_MAX_PATH, tmpmp3);
		_tcscat_s(tmpmp3, _T("testapp_background.mp3"));// 产生临时文件的文件名
		ExtractResource(tmpmp3, _T("WAVE"), _T("GAME_MUSIC_MARCH"));// 将 MP3 资源提取为临时文件
		TCHAR mcicmd[300];
		_stprintf_s(mcicmd, _T("open \"%s\" alias BackMusic"), tmpmp3);
		mciSendString(mcicmd, NULL, 0, NULL);// 打开音乐
		mciSendString(_T("play BackMusic"), NULL, 0, NULL);    // 播放音乐
		mciSendString(TEXT("setaudio BackMusic volume to 300"), NULL, 0, NULL);		//设置音量大小
		mciSendString(TEXT("play BackMusic repeat"), NULL, 0, NULL);				//循环播放
		DeleteFile(tmpmp3);//删除临时文件
	}
}

void CoreInterface_main_single()//单人模式，可以直接用这个函数调用这个cpp文件里的函数
{
	showMap();
	showInfo_init_single();
	showStore();
	showButtons();
}//可以直接用这个函数调用这个cpp文件里的函数

void CoreInterface_main_double()//双人模式，可以直接用这个函数调用这个cpp文件里的函数
{
	showMap();
	showInfo_init_double();
	showStore();
	showButtons();
}

 //以下三个函数可以根据单、双人模式选择合适的函数
void CoreInterface_main(int mode)
{
	if (mode == 0)
		CoreInterface_main_single();
	if (mode == 1)
		CoreInterface_main_double();
}

void showInfo_init(int mode)
{
	if (mode == 0)
		showInfo_init_single();
	if (mode == 1)
		showInfo_init_double();
}

void reshowInfo_coin(int mode)
{
	if (mode == 0)
		reshowInfo_coin_single();
	if (mode == 1)
		reshowInfo_coin_double();
}