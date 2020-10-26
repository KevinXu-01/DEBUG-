///////////////////////////////////////////////////////
// 文件名称：	ZergDraw.cpp
//   负责人：	江诗烨
//     学号：	2018302060048
//   代码量：	284行
// 编译环境：	Visual Studio 2015 + EasyX 20190415(beta) 
// 最后修改：	2019-6-12
// 实现功能：	虫子及相关素材绘制
////////////////////////////////////////////////////////
#include<easyx.h>
#include"Baneling.h"
#include"Bugs.h"

IMAGE Explodeimage;
IMAGE explodeimage[25];
IMAGE ExplodeimageMask;
IMAGE explodeimageMask[25];
IMAGE Banelingimage;
IMAGE banelingimage[11];
IMAGE BanelingimageMask;
IMAGE banelingimageMask[11];
IMAGE Hydraliskimage;
IMAGE hydraliskimage[30];
IMAGE HydraliskimageMask;
IMAGE hydraliskimageMask[30];
IMAGE spitimage;
IMAGE spitimageMask;
IMAGE Roachimage;
IMAGE roachimage[15];
IMAGE RoachimageMask;
IMAGE roachimageMask[15];
IMAGE Zerglingimage;
IMAGE zerglingimage[96];
IMAGE ZerglingimageMask;
IMAGE zerglingimageMask[96];

void initzergdraw()
{
	//存入相关素材
	loadimage(&Explodeimage, _T("IMAGE"), _T("explode1"));
	loadimage(&ExplodeimageMask, _T("IMAGE"), _T("explodemask1"));
	loadimage(&Banelingimage, _T("IMAGE"), _T("baneling"));
	loadimage(&BanelingimageMask, _T("IMAGE"), _T("banelingmask"));
	loadimage(&Hydraliskimage, _T("IMAGE"), _T("hydralisk"));
	loadimage(&HydraliskimageMask, _T("IMAGE"), _T("hydraliskmask"));
	loadimage(&spitimage, _T("IMAGE"), _T("spit1"));
	loadimage(&spitimageMask, _T("IMAGE"), _T("spitmask1"));
	loadimage(&Roachimage, _T("IMAGE"), _T("roach"));
	loadimage(&RoachimageMask, _T("IMAGE"), _T("roachmask"));
	loadimage(&Zerglingimage, _T("IMAGE"), _T("zergling"));
	loadimage(&ZerglingimageMask, _T("IMAGE"), _T("zerglingmask"));

	//处理毒爆的素材
	SetWorkingImage(&Banelingimage);
	int j = 0;
	for (int k = 0; k <= 3; k++)
	{
		if (j >= 11)break;
		for (int i = 0; i <= 3; i++)
		{
			getimage(&banelingimage[j], i * 53, 40 * k, 53, 40);
			j++;
			if (j >= 11)break;
		}

	}

	j = 0;
	SetWorkingImage(&BanelingimageMask);
	for (int k = 0; k <= 3; k++)
	{
		if (j >= 11)break;
		for (int i = 0; i <= 3; i++)
		{
			getimage(&banelingimageMask[j], i * 53, 40 * k, 53, 40);
			j++;
			if (j >= 11)break;
		}

	}//逐帧存入图片

	//处理爆炸的素材
	SetWorkingImage(&Explodeimage);
	j = 0;
	for (int k = 0; k <= 4; k++)
	{
		if (j >= 25)break;
		for (int i = 0; i <= 4; i++)
		{
			getimage(&explodeimage[j], i * 50, k * 50, 50, 50);
			j++;
			if (j >= 25)break;
		}
	}
	SetWorkingImage(&ExplodeimageMask);
	j = 0;
	for (int k = 0; k <= 4; k++)
	{
		if (j >= 25)break;
		for (int i = 0; i <= 4; i++)
		{
			getimage(&explodeimageMask[j], i * 50, k * 50, 50, 50);
			j++;
			if (j >= 25)break;
		}
	}

	//处理刺蛇的素材
	SetWorkingImage(&Hydraliskimage);
	j = 0;
	for (int k = 0; k <= 4; k++)
	{
		for (int i = 0; i <= 4; i++)
		{
			getimage(&hydraliskimage[j], i * 51, 42 * k, 51, 42);
			j++;
		}

	}

	j = 0;
	SetWorkingImage(&HydraliskimageMask);
	for (int k = 0; k <= 4; k++)
	{
		for (int i = 0; i <= 4; i++)
		{
			getimage(&hydraliskimageMask[j], i * 51, 42 * k, 51, 42);
			j++;
		}

	}

	//处理蟑螂的素材
	SetWorkingImage(&Roachimage);
	j = 0;
	for (int k = 0; k <= 3; k++)
	{
		for (int i = 0; i <= 3; i++)
		{
			if(j==18)
			{
				j++;
				continue;													//舍弃9帧图片（资源问题
			}
			getimage(&roachimage[j], i * 64, 49 * k, 64, 49);
			j++;
		}

	}

	j = 0;
	SetWorkingImage(&RoachimageMask);
	for (int k = 0; k <= 3; k++)
	{
		for (int i = 0; i <= 3; i++)
		{
			if (j == 18)
			{
				j++;
				continue;
			}
			getimage(&roachimageMask[j], i * 64, 49 * k, 64, 49);
			j++;
		}

	}

	//处理跳虫的素材
	SetWorkingImage(&Zerglingimage);
	j = 0;
	for (int k = 0; k <= 9; k++)
	{
		if (j == 90)
			break;
		for (int i = 0; i <= 8; i++)
		{
			getimage(&zerglingimage[j], i * 53, 45 * k, 53, 45);
			j++;
			if (j == 90)
				break;
		}

	}

	j = 0;
	SetWorkingImage(&ZerglingimageMask);
	for (int k = 0; k <= 10; k++)
	{
		if (j == 96)
			break;
		for (int i = 0; i <= 8; i++)
		{
			getimage(&zerglingimageMask[j], i * 53, 45 * k, 53, 45);
			j++;
			if (j == 96)
				break;
		}

	}
	SetWorkingImage();
}

//banelingdraw
void Baneling::drawbaneling()
{
	SetWorkingImage();
	IMAGE banelingtemp;														//临时存放图像
	IMAGE banelingmasktemp;
	rotateimage(&banelingmasktemp, &banelingimageMask[i], e, WHITE, 0, 1);
	rotateimage(&banelingtemp, &banelingimage[i], e, BLACK, 0, 1);
	putimage(x-26, y-20, &banelingmasktemp, SRCAND);						//输出图像
	putimage(x-26, y-20, &banelingtemp, SRCINVERT);
	i++;
	if (i >= 11)
		i = 0;
}

//hydraliskdraw
void Hydralisk::drawhydralisk()
{
	SetWorkingImage();
	IMAGE hydralisktemp;
	IMAGE hydraliskmasktemp;
	rotateimage(&hydraliskmasktemp, &hydraliskimageMask[i], e, WHITE, 0, 1);
	rotateimage(&hydralisktemp, &hydraliskimage[i], e, BLACK, 0, 1);
	putimage(x-25, y-21, &hydraliskmasktemp, SRCAND);
	putimage(x-25, y-21, &hydralisktemp, SRCINVERT);
	if (j == 1)
	{
		i++;
		if (i >= 24)
			j = 0;
	}
	else if(j==0)
	{
		i--;
		if (i <= 0)
			j = 1;
	}
}

void Roach::drawroach()
{
	SetWorkingImage();
	IMAGE roachtemp;
	IMAGE roachmasktemp;
	rotateimage(&roachmasktemp, &roachimageMask[i], e, WHITE, 0, 1);
	rotateimage(&roachtemp, &roachimage[i], e, BLACK, 0, 1);
	putimage(x-32, y-25, &roachmasktemp, SRCAND);
	putimage(x-32, y-25, &roachtemp, SRCINVERT);
	i++;
	if (i >= 15)
		i = 0;
}

void Zergling::drawzergling()
{
	SetWorkingImage();
	IMAGE zerglingtemp;														//临时存放图像
	IMAGE zerglingmasktemp;
	rotateimage(&zerglingmasktemp, &zerglingimageMask[i-type*32], e, WHITE, 0, 1);
	rotateimage(&zerglingtemp, &zerglingimage[i-type*32], e, BLACK, 0, 1);
	if(x<640)
		putimage(x-26, y-22, &zerglingmasktemp, SRCAND);					//输出图像
	if(x<640)
		putimage(x-26, y-22, &zerglingtemp, SRCINVERT);
	i++;
	if (i >= 90)
		i = 64;
}

//spitdraw
void Hydraspit::drawhydraspit()
{
	IMAGE spittemp;
	IMAGE spitmasktemp;
	SetWorkingImage();
	rotateimage(&spitmasktemp, &spitimageMask, e, WHITE, 0, 1);
	rotateimage(&spittemp, &spitimage, e, BLACK, 0, 1);
	putimage(x-24, y-24, &spitmasktemp, SRCAND);
	putimage(x-24, y-24, &spittemp, SRCINVERT);
}

//explodedraw
int Baneling::drawexplode()
{
	SetWorkingImage();
	putimage(x-25, y-25, &explodeimageMask[i], SRCAND);						//输出图像
	putimage(x-25, y-25, &explodeimage[i], SRCINVERT);
	i++;
	if (i >= 25)return 1;
	else return 0;
}