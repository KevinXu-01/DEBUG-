///////////////////////////////////////////////////////
// �ļ����ƣ�	PauseAndDelete.h
//   �����ˣ�	��ʫ��
//     ѧ�ţ�	2018302060048
//   ��������	79��
// ���뻷����	Visual Studio 2015 + EasyX 20190415(beta) 
// ����޸ģ�	2019-6-12
// ʵ�ֹ��ܣ�	����ܣ���Ϸ������ɾ�����г��ӡ���ң���ͣ
////////////////////////////////////////////////////////
#pragma once
#include"graphics.h"
#include<easyx.h>
#include"Bugs.h"
#include"Coins.h"
static bool stap=false;//��ͣ���Ƿ��ڰ���״̬
extern bool deleteBaneling(Baneling* z);
extern bool deleteHydralisk(Hydralisk* z);
extern bool deleteHydraspit(Hydraspit* z);
extern bool deleteRoach(Roach* z);
extern bool deleteZergling(Zergling* z);
extern bool deleteCoin(Coins* c);
extern Coins* coins[5];
extern Hydraspit* hydraspits[3];

//�жϲ���ͣ
void ifp()
{
	if(!(GetAsyncKeyState('P') & 0x8000)&&stap==true)
	{
		stap = false;
		SetWorkingImage();
		settextcolor(WHITE);
		settextstyle(20, 0, _T("����"), 0, 0, 500, false, false, false);
		outtextxy(670, 450, _T("��Ϸ����ͣ"));//����ַ�
		HRGN rgn = CreateRectRgn(765, 5, 800, 30);
		setcliprgn(rgn);
		clearcliprgn();//�����ͣͼƬ����
		IMAGE resume;
		loadimage(&resume, _T("IMAGE"), _T("RESUME"));//�������ͼƬ
		putimage(765, 5, &resume);
		DeleteObject(rgn);//ɾ����������
		setcliprgn(NULL);//ָ�������
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
				DeleteObject(rgn1);//ɾ����������
				setcliprgn(rgn);
				clearcliprgn();
				DeleteObject(rgn);//ɾ����������
				setcliprgn(NULL);//ָ�������
				IMAGE pause;
				loadimage(&pause, _T("IMAGE"), _T("PAUSE"));//������ͣ��ťͼƬ
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

//ɾ�����г��Ӻͽ��
void deleteallbugsandcoins()
{
	//����deleteʱ���������򣬹�ÿ�ζ�ɾ�������ڵ�һ��Ԫ��
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