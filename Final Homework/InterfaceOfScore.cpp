///////////////////////////////////////////////////////
// �ļ����ƣ�	InterfaceOfScore.cpp
//   �����ˣ�	������
//     ѧ�ţ�	2018302060043
//   ��������	197��
// ���뻷����	Visual Studio 2015 + EasyX_20180321(���ְ�) 
// ����޸ģ�	2019-6-12
// ʵ�ֹ��ܣ�	��������������ִ���������ʾ��������ת��
////////////////////////////////////////////////////////
#include<easyx.h>
#include"Person.h"
#include"Score.h"
#include"resource.h"
#include"GameStart.h"
#include"CoreInterface.h"
#include"InterfaceOfScore.h"
#include"State.h"

extern Person personA, personB;				//�ⲿ����
extern Score score;
extern MOUSEMSG mouse;
extern int mode;
extern bool gameWillRestart;

struct State sta1;							//����ṹ��

//���ִ�����(�����������鳤�ȣ���������)
short numberProcess(short n[],int l,int s)
{
	for (int i = 0; i < l; i++)
	{
		if (s % 10 == s)					//�жϵ�ǰ��ֵ�Ƿ�Ϊ��λ
		{
			n[i] = s;						//��ǰԪ��=��ǰ��ֵ
			return 0;						//��������
		}
		else
		{
			n[i] = s % 10;					//��ǰԪ��=��ǰ��ֵ�ĸ�λ
			s /= 10;						//��ǰԪ��ȥ�����λ
		}
	}
}

//������ʾ����
void showNumber()
{
	short s[10];																//�洢��������
	short c[10];
	short vs = 0;																//������Чλ��
	short vc = 0;
	IMAGE numberMaskPtr[11];													//�洢���ֵ�ͼ��ָ��
	IMAGE coinsNumberMaskPtr[12];
	IMAGE numberPtr[11];														//�洢���ֵ�ͼ��ָ��
	IMAGE coinsNumberPtr[12];
	loadimage(&numberMaskPtr[10], _T("IMAGE"), _T("numberMask"));				//��������
	loadimage(&coinsNumberMaskPtr[11], _T("IMAGE"), _T("coinsNumberMask"));
	loadimage(&numberPtr[10], _T("IMAGE"), _T("number"));						//��������
	loadimage(&coinsNumberPtr[11], _T("IMAGE"), _T("coinsNumber"));
	for (int i = 0; i < 10; i++)												//ͼ���и����
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
	for (int i = 0; i < 10; i++)													//�����ʼ��Ϊ-1
		s[i] = c[i] = -1;
	numberProcess(s, 10, score.getScore());											//�������ִ���	
	numberProcess(c, 10, Person::getCoins());										//��������ִ���
	for (int i = 0; i < 10; i++)													//������Чλ������
	{
		if (s[i] != -1)
			vs++;
		if (c[i] != -1)
			vc++;
	}
	for (int k = 0; k < 10; k++)													//������ʾ
	{
		if (s[k] != -1)																//�ж��Ƿ�Ϊ��Чλ
		{
			putimage(320 + 39 * (vs / 2 - k-1), 175, &numberMaskPtr[s[k]], SRCAND); //ͨ����Чλ������ʹ���־�����ʾ
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

//��귶Χ�жϺ���
bool mouseRange(MOUSEMSG m,int left,int right,int bottom,int top )
{	
		if (left <= mouse.x&&mouse.x <= right
			&&bottom <= mouse.y&&mouse.y <= top)
			return true;
		else
			return false;
}

//�����������
void interfaceOfScore()
{
	IMAGE scoresBackgroundPtr;													//�洢ͼ���ͼ��ָ��
	IMAGE btnMenuPtr;
	IMAGE btnMenuOverPtr;
	IMAGE btnResetPtr;
	IMAGE btnResetOverPtr;
	IMAGE btnMaskPtr;															//�洢���ֵ�ͼ��ָ��
	loadimage(&scoresBackgroundPtr, _T("IMAGE"), _T("scoresBackground"));		//����ͼ��
	loadimage(&btnMenuPtr, _T("IMAGE"), _T("btnMenu"));
	loadimage(&btnMenuOverPtr, _T("IMAGE"), _T("btnMenuOver"));
	loadimage(&btnResetPtr, _T("IMAGE"), _T("btnReset"));
	loadimage(&btnResetOverPtr, _T("IMAGE"), _T("btnResetOver"));
	loadimage(&btnMaskPtr, _T("IMAGE"), _T("btnMask"));							//��������
	gameWillRestart = false;

	//������������ͼ��ѭ��
	while (!(gameWillRestart))
	{
		BeginBatchDraw();														//��ʼ������ͼ
		putimage(0, 0, 640, 480, &scoresBackgroundPtr, 0, 0);					//��ʾͼ��
		putimage(344, 352, 72, 72, &btnMaskPtr, 0, 0, SRCAND);
		putimage(344, 352, 72, 72, &btnMenuPtr, 0, 0, SRCPAINT);
		putimage(220, 352, 72, 72, &btnMaskPtr, 0, 0, SRCAND);
		putimage(220, 352, 72, 72, &btnResetPtr, 0, 0, SRCPAINT);
		showNumber();															//��ʾ����
		if (sta1.processed == false)											//�ж��Ƿ��Ѿ��ӷ�
		{
			score.coinsPlus(Person::getCoins());								//��Ҽӷ�
			reshowInfo_score();													//��������
			sta1.processed = true;												//����״̬����
			score.writeScore();													//������¼�ļ�д��
		}
		if (MouseHit())															//�ж��Ƿ��������Ϣ
			mouse = GetMouseMsg();												//���������Ϣ
		switch (mouse.uMsg)
		{
		case WM_MOUSEMOVE:
			if (mouseRange(mouse, 344, 416, 352, 424))							//����ƶ�����Ӧ����
			{
				putimage(344, 352, 72, 72, &btnMaskPtr, 0, 0, SRCAND);			//��ť���
				putimage(344, 352, 72, 72, &btnMenuOverPtr, 0, 0, SRCPAINT);
			}
			else if (mouse, mouseRange(mouse, 220, 292, 352, 424))
			{
				putimage(220, 352, 72, 72, &btnMaskPtr, 0, 0, SRCAND);
				putimage(220, 352, 72, 72, &btnResetOverPtr, 0, 0, SRCPAINT);
			}
			break;
		case WM_LBUTTONDOWN:													//����������
			if (mouseRange(mouse, 344, 416, 352, 424))
			{
				sta1.processed = false;											//����״̬�ָ�
				personA.~Person();												//�����ʼ��
				personB.~Person();
				personB.setPersonPosition(370, 370);
				Person::spendCoins(Person::getCoins());							//��ҹ���
				score.~Score();													//������ʼ��																		//FlushMouseMsgBuffer();												//��������Ϣ
				gameStart();													//�������˵�
				gameWillRestart = true;											//��Ϸ�����ٴο�ʼ
				FlushMouseMsgBuffer();											//��������Ϣ
			}
			else if (mouse, mouseRange(mouse, 220, 292, 352, 424))
			{
				sta1.processed = false;											//����״̬�ָ�
				switch (mode)
				{
				case 0: personA.~Person();										//����ģʽ��ʼ��
					score.~Score();
					Person::spendCoins(Person::getCoins());						//��ҹ���
					gameWillRestart = true;										//��Ϸ�����ٴο�ʼ
					FlushMouseMsgBuffer();										//��������Ϣ
					break;
				case 1: personA.~Person();										//˫��ģʽ��ʼ��
					personB.~Person();
					personB.setPersonPosition(370, 370);
					Person::spendCoins(Person::getCoins());						//��ҹ���
					score.~Score();
					gameWillRestart = true;
					FlushMouseMsgBuffer();
					break;
				}
			}
			break;
		}
		EndBatchDraw();
		FlushMouseMsgBuffer();													//��������Ϣ
	}
}