///////////////////////////////////////////////////////
// 文件名称：	Bugs.h
//   负责人：	江诗烨
//     学号：	2018302060048
//   代码量：	9行
// 编译环境：	Visual Studio 2015 + EasyX 20190415(beta) 
// 最后修改：	2019-6-12
// 实现功能：	管理虫子
////////////////////////////////////////////////////////
#pragma once
#include"Baneling.h"
#include"Hydralisk.h"
#include"Roach.h"
#include"Zergling.h"
void initzergdraw();//绘制初始化
void initzergclock();//虫子出现时钟初始化
void renewzergclock();//更新虫子时钟（产生虫子）
void allzergsact();//虫子们行动