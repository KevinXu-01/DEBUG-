///////////////////////////////////////////////////////
// 文件名称：	GameStart.h
//   负责人：	杨景博
//     学号：	2018302060060
//   代码量：	21行
// 编译环境：	Visual Studio 2015 + EasyX_20190415(beta)
// 最后修改：	2019-6-12
// 实现功能：	主要界面、次要界面以及界面间的转换
////////////////////////////////////////////////////////

#pragma once
#include"Score.h"
#include"InterfaceOfScore.h"
#include <graphics.h>
#include <iostream>
#include<stdlib.h>
#include<stdio.h>
#include <conio.h>
#include<algorithm>
#include<math.h>
#include<easyx.h>
#include <string.h>
#include <map>
#include <time.h>
#include<stdio.h>

/************************************
在头文件中包含对mode的extern声明
**************************************/
void gameStart();
extern int mode;