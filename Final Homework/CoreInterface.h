///////////////////////////////////////////////////////
// 文件名称：	CoreInterface.h
//   负责人：	许静宇
//     学号：	2018302060052
//   代码量：	26行
// 编译环境：	Visual Studio 2015 + EasyX_20190415(beta)
// 最后修改：	2019-6-12
// 实现功能：	对函数进行声明
////////////////////////////////////////////////////////

#pragma once
#include<easyx.h>
#include"conio.h"
#include"graphics.h"
#include <windows.h>
#include <mmsystem.h>
#include <stdio.h>
#pragma comment(lib, "WINMM.LIB")

void showMap();
void showInfo_init_single();
void showInfo_init_double();
void showStore();
void showButtons();
void reshowInfo_playerA_hp();//玩家A的生命值接口
void reshowInfo_playerB_hp();//玩家B的生命值接口
void reshowInfo_score();//分数接口
void reshowInfo_coin_single();//单人模式的金币接口
void reshowInfo_coin_double();//双人模式的金币接口
bool ExtractResource(LPCTSTR strDstFile, LPCTSTR strResType, LPCTSTR strResName);
void playMusic();
void CoreInterface_main_single();//单人模式
void CoreInterface_main_double();//双人模式
void CoreInterface_main(int mode);//可以根据目前的mode来判断
void showInfo_init(int mode);
void reshowInfo_coin(int mode);