///////////////////////////////////////////////////////
// �ļ����ƣ�	GameStart.cpp
//   �����ˣ�	���
//     ѧ�ţ�	2018302060060
//   ��������	316��
// ���뻷����	Visual Studio 2015 + EasyX_20190415(beta)
// ����޸ģ�	2019-6-12
// ʵ�ֹ��ܣ�	��Ҫ���桢��Ҫ�����Լ�������ת��
////////////////////////////////////////////////////////

#include "GameStart.h"
using namespace std;
#define WINDOWS_X 800	//���ڴ�СX
#define WINDOWS_Y 480	//���ڴ�СY
#define BBLACK 80		//�ո��С
#define ESC 27
#define ESCEXIT (_kbhit()&&_getch()==ESC)

#pragma comment (lib,"ws2_32.lib")						// ���� Windows Multimedia API
#pragma comment(lib,"Winmm.lib")

extern bool gameWillRestart;
extern Score score;

void gameStart()
{
	IMAGE StartbackgroundPtr;
	IMAGE GeneralbackgroundPtr;
	IMAGE MM[11] = { 0 };
	setbkmode(TRANSPARENT);					//͸������

	loadimage(&StartbackgroundPtr, _T("IMAGE"), _T("startBackground"));
	putimage(0, 0, &StartbackgroundPtr/*, SRCAND*/);

	const int bblack = 10;

	LOGFONT f;
	gettextstyle(&f);												// ��ȡ������ʽ
	f.lfHeight = BBLACK;												// ��������߶�
																		//strcpy(f.lfFaceName, _T("����"));								// ��������
	f.lfQuality = ANTIALIASED_QUALITY;								// �������Ч��Ϊ�����  
	settextstyle(&f);												// ����������ʽ

	settextstyle(BBLACK / 4, 0, _T("����"));
	RECT r1 = { WINDOWS_X / 2 - BBLACK,WINDOWS_Y / 3,WINDOWS_X / 2 + BBLACK ,WINDOWS_Y / 3 + BBLACK / 2 };
	rectangle(WINDOWS_X / 2 - BBLACK, WINDOWS_Y / 3, WINDOWS_X / 2 + BBLACK, WINDOWS_Y / 3 + BBLACK / 2);
	drawtext(_T("����ģʽ"), &r1, DT_CENTER | DT_VCENTER | DT_SINGLELINE);

	RECT r2 = { WINDOWS_X / 2 - BBLACK,WINDOWS_Y / 3 + BBLACK / 2 + bblack,WINDOWS_X / 2 + BBLACK,WINDOWS_Y / 3 + BBLACK + bblack };
	rectangle(WINDOWS_X / 2 - BBLACK, WINDOWS_Y / 3 + BBLACK / 2 + bblack, WINDOWS_X / 2 + BBLACK, WINDOWS_Y / 3 + BBLACK + bblack);
	drawtext(_T("˫��ģʽ"), &r2, DT_CENTER | DT_VCENTER | DT_SINGLELINE);

	RECT r3 = { WINDOWS_X / 2 - BBLACK,WINDOWS_Y / 3 + BBLACK + 2 * bblack,WINDOWS_X / 2 + BBLACK,(int)(WINDOWS_Y / 3 + BBLACK * 1.5 + 2 * bblack) };
	rectangle(WINDOWS_X / 2 - BBLACK, WINDOWS_Y / 3 + BBLACK + 2 * bblack, WINDOWS_X / 2 + BBLACK, (int)(WINDOWS_Y / 3 + BBLACK * 1.5 + 2 * bblack));
	drawtext(_T("��Ϸ����"), &r3, DT_CENTER | DT_VCENTER | DT_SINGLELINE);

	RECT r4 = { WINDOWS_X / 2 - BBLACK,(int)(WINDOWS_Y / 3 + BBLACK * 1.5 + 3 * bblack),WINDOWS_X / 2 + BBLACK,WINDOWS_Y / 3 + BBLACK * 2 + 3 * bblack };
	rectangle(WINDOWS_X / 2 - BBLACK, (int)(WINDOWS_Y / 3 + BBLACK * 1.5 + 3 * bblack), WINDOWS_X / 2 + BBLACK, WINDOWS_Y / 3 + BBLACK * 2 + 3 * bblack);
	drawtext(_T("��Ϸ����"), &r4, DT_CENTER | DT_VCENTER | DT_SINGLELINE);

	RECT r5 = { WINDOWS_X / 2 - BBLACK,WINDOWS_Y / 3 + BBLACK * 2 + 4 * bblack,WINDOWS_X / 2 + BBLACK,(int)(WINDOWS_Y / 3 + BBLACK * 2.5 + 4 * bblack) };
	rectangle(WINDOWS_X / 2 - BBLACK, WINDOWS_Y / 3 + BBLACK * 2 + 4 * bblack, WINDOWS_X / 2 + BBLACK, (int)(WINDOWS_Y / 3 + BBLACK * 2.5 + 4 * bblack));
	drawtext(_T("���а�"), &r5, DT_CENTER | DT_VCENTER | DT_SINGLELINE);

	RECT r6 = { WINDOWS_X / 2 - BBLACK,(int)(WINDOWS_Y / 3 + BBLACK * 2.5 + 5 * bblack),WINDOWS_X / 2 + BBLACK,WINDOWS_Y / 3 + BBLACK * 3 + 5 * bblack };
	rectangle(WINDOWS_X / 2 - BBLACK, (int)(WINDOWS_Y / 3 + BBLACK * 2.5 + 5 * bblack), WINDOWS_X / 2 + BBLACK, WINDOWS_Y / 3 + BBLACK * 3 + 5 * bblack);
	drawtext(_T("��������"), &r6, DT_CENTER | DT_VCENTER | DT_SINGLELINE);


	for (int i = 0; i < 6; i++)																						//���水ťͼƬ
		getimage(MM + i, WINDOWS_X / 2 - BBLACK, WINDOWS_Y / 3 + i * bblack + i * BBLACK / 2, 2 * BBLACK, BBLACK / 2);
	getimage(MM + 6, WINDOWS_X - BBLACK, WINDOWS_Y - BBLACK / 2, BBLACK - 11, BBLACK / 2 - 11);

	bool _HOME = true, _BACKGROUND = false, _HELP = false, _SCORE = false, _SETTINGS = false, _DRMS = false;			//TRUE��ʾ���ڵ�ǰҳ��
	MOUSEMSG m;
	while (_HOME)
	{
		BeginBatchDraw();
		m = GetMouseMsg();
		switch (m.uMsg)
		{
		case WM_LBUTTONDOWN:												//������������ʱ
			EndBatchDraw();
			if (m.x > WINDOWS_X / 2 - BBLACK && m.x<WINDOWS_X / 2 + BBLACK && m.y>WINDOWS_Y / 3 && m.y < WINDOWS_Y / 3 + BBLACK / 2 && _HOME && !_BACKGROUND && !_HELP && !_SCORE && !_SETTINGS && !_DRMS)//����ģʽ
			{
				//What does _DRMS mean?
				//_DRMS = true;									
				_HOME = false;								//�뿪HOME����
				mode = 0;										//����ģʽ
				gameWillRestart = true;
				cleardevice();
				break;
			}
			else if (m.x > WINDOWS_X / 2 - BBLACK && m.x<WINDOWS_X / 2 + BBLACK && m.y>WINDOWS_Y / 3 + BBLACK / 2 + bblack && m.y < WINDOWS_Y / 3 + BBLACK + bblack && _HOME && !_BACKGROUND && !_HELP && !_SCORE && !_SETTINGS && !_DRMS)//˫��ģʽ
			{
				_HOME = false;									//�뿪HOME����
				mode = 1;											//����˫��ģʽ
				gameWillRestart = true;

				break;
			}
			else if (m.x > WINDOWS_X / 2 - BBLACK && m.x<WINDOWS_X / 2 + BBLACK && m.y> WINDOWS_Y / 3 + BBLACK + 2 * bblack && m.y < (int)(WINDOWS_Y / 3 + BBLACK * 1.5 + 2 * bblack) && _HOME && !_BACKGROUND && !_HELP && !_SCORE && !_SETTINGS && !_DRMS)	//��Ϸ����
			{
				_BACKGROUND = true;
				cleardevice();
				loadimage(&StartbackgroundPtr, _T("IMAGE"), _T("generalBackground"));				//����
				putimage(0, 0, &GeneralbackgroundPtr);
				string data[16] = {
					"��Ϸ������" ,
					"����һ���г���Ԫ��ũ��",
					"ĳһ�죬�����ǣ�BUGS��ͻȻϮ�����ׯ�ڡ�",
					"Ϊ�˱���ׯ��",
					"���������չ����һ������������������DEBUG��",
				};
				rectangle(BBLACK, BBLACK, WINDOWS_X - BBLACK, WINDOWS_Y - BBLACK);
				settextstyle(BBLACK / 2 - 5, 0, _T("����"));
				settextcolor(RGB(0, 255, 255));
				outtextxy(WINDOWS_X / 3 - 100, 90, data[0].data());
				settextstyle(BBLACK / 4, 0, _T("����"));
				settextcolor(WHITE);
				int LEFT, TOP = 75;
				for (int i = 1; i < 16; i++)
				{	
					LEFT = WINDOWS_X / 8;
					if (i == 5 || i >= 10)LEFT -= 25;
					if (i == 5 || i == 10 || i == 6)TOP += 30;
					outtextxy(LEFT, TOP + 70 * i, data[i].data());
				}
				RECT R = { WINDOWS_X - BBLACK,WINDOWS_Y - BBLACK / 2,WINDOWS_X - 10,WINDOWS_Y - 10 };
				rectangle(WINDOWS_X - BBLACK, WINDOWS_Y - BBLACK / 2, WINDOWS_X - 10, WINDOWS_Y - 10);
				drawtext(_T("����"), &R, DT_CENTER | DT_VCENTER | DT_SINGLELINE);
				break;
			}
			else if (m.x > WINDOWS_X / 2 - BBLACK && m.x<WINDOWS_X / 2 + BBLACK && m.y>(int)(WINDOWS_Y / 3 + BBLACK * 1.5 + 3 * bblack) && m.y < WINDOWS_Y / 3 + BBLACK * 2 + 3 * bblack && _HOME && !_BACKGROUND && !_HELP && !_SCORE && !_SETTINGS && !_DRMS)	//����˵��
			{
				_HELP = true;
				cleardevice();
				loadimage(&StartbackgroundPtr, _T("IMAGE"), _T("generalBackground"));				//����
				string data[16] = {
					"����˵��" ,
					"��Ϸ��Ϊ����ģʽ��˫��ģʽ",
					"����ģʽ��ʹ��W���ϡ�S���¡�A����D���ң�����ʹ����ϼ�",
					"���������������ɱ��һֻ���ӿ��Ի�÷�����",
					"������һ�����ʵ�����,�ڽ���ʱ��ҿ�����Ϊ����",
					"��ҿ����������̵��й�����Ʒ",
					"����Z�����Թ���ʹ�ü��Ȱ�����ʱ����ֵ�ָ������",
					"����X�����Թ���ʹ�ñ�������ʱ���Իָ�һ������ֵ",
					"����C�����Թ���ʹ���������ϣ�����һ��ʱ���ڻ�ü���",
					"����V�����Թ���ʹ����Ͱ���ڵ�ͼ�Ϸ��ú󼴿��赲����",
					"���ӵ�����Ͱ����˲���ɱ��Ͱ�������еĳ���",
					"��Ϸ�ṩ������ǹ������Q��E���ɽ����л�",
					"����P��������ͣ��Ϸ����Ҫ�ָ���ֻ���ٰ���P��",
					"��˫��ģʽ�£�����Э������Ҵ��ڸ�����ƣ��뾡��̽��",
				};
				rectangle(BBLACK, BBLACK, WINDOWS_X - BBLACK, WINDOWS_Y - BBLACK);
				settextstyle(BBLACK / 2 - 5, 0, _T("����"));
				settextcolor(RGB(0, 255, 255));
				outtextxy(WINDOWS_X / 3 - 100, 90, data[0].data());
				settextstyle(BBLACK / 4, 0, _T("����"));
				settextcolor(WHITE);
				int LEFT, TOP = 110;
				for (int i = 1; i < 16; i++)
				{
					LEFT = WINDOWS_X / 8;
					outtextxy(LEFT, TOP + 20 * i, data[i].data());
				}
				RECT R = { WINDOWS_X - BBLACK,WINDOWS_Y - BBLACK / 2,WINDOWS_X - 10,WINDOWS_Y - 10 };
				rectangle(WINDOWS_X - BBLACK, WINDOWS_Y - BBLACK / 2, WINDOWS_X - 10, WINDOWS_Y - 10);
				drawtext(_T("����"), &R, DT_CENTER | DT_VCENTER | DT_SINGLELINE);
				break;
			}
			else if (m.x > WINDOWS_X / 2 - BBLACK && m.x<WINDOWS_X / 2 + BBLACK && m.y>WINDOWS_Y / 3 + BBLACK * 2 + 4 * bblack && m.y < (int)(WINDOWS_Y / 3 + BBLACK * 2.5 + 4 * bblack) && _HOME && !_BACKGROUND && !_HELP && !_SCORE && !_SETTINGS && !_DRMS)//���а�
			{
				_SCORE = true;
				cleardevice();
				int scores[10];
				char temp[5];
				string data[10] = {
					"��һ����",
					"�ڶ�����",
					"��������",
					"��������",
					"��������",
					"��������",
					"��������" ,
					"�ڰ�����" ,
					"�ھ�����" ,
					"��ʮ����" ,
				};
				score.gerRecordScore(scores, 10);
				settextstyle(BBLACK / 4, 0, _T("����"));
				settextcolor(WHITE);
				int LEFT, TOP = 85;
				for (int i = 0; i < 10; i++)
				{
					_stprintf_s(temp, 5, "%d", scores[i]);
					LEFT = WINDOWS_X / 8;
					outtextxy(LEFT, TOP + 30 * i, data[i].data());
					outtextxy(LEFT + 80, TOP + 30 * i, temp);
				}
				rectangle(BBLACK, BBLACK, WINDOWS_X - BBLACK, WINDOWS_Y - BBLACK);
				RECT R3 = { WINDOWS_X - BBLACK,WINDOWS_Y - BBLACK / 2,WINDOWS_X - 10,WINDOWS_Y - 10 };
				rectangle(WINDOWS_X - BBLACK, WINDOWS_Y - BBLACK / 2, WINDOWS_X - 10, WINDOWS_Y - 10);
				drawtext(_T("����"), &R3, DT_CENTER | DT_VCENTER | DT_SINGLELINE);
				break;
			}
			else if (m.x > WINDOWS_X / 2 - BBLACK && m.x<WINDOWS_X / 2 + BBLACK && m.y>(int)(WINDOWS_Y / 3 + BBLACK * 2.5 + 5 * bblack) && m.y < WINDOWS_Y / 3 + BBLACK * 3 + 5 * bblack && _HOME && !_BACKGROUND && !_HELP && !_SCORE && !_SETTINGS && !_DRMS)//����
			{
				_SETTINGS = true;									//�뿪HOME����
				cleardevice();
				loadimage(&StartbackgroundPtr, _T("IMAGE"), _T("generalBackground"));				//����
				putimage(0, 0, &GeneralbackgroundPtr);
				string data[16] = {
					"�������ǣ�" ,
					"������ WHU2018��6��",
					"�����ˡ��������Լ��������",
					"��ʫ�� WHU2018��6��",
					"������Լ������",
					"���� WHU2018�ƿ�8��",
					"����ǹ���Լ����Ľ���",
					"��� WHU2018�ƿ�7��",
					"����������Լ��������桢��Ҫ����"
				};
				settextstyle(BBLACK / 2 - 5, 0, _T("����"));
				settextcolor(RGB(0, 255, 255));
				outtextxy(WINDOWS_X / 3 - 100, 90, data[0].data());
				rectangle(BBLACK, BBLACK, WINDOWS_X - BBLACK, WINDOWS_Y - BBLACK);
				settextstyle(BBLACK / 4, 0, _T("����"));
				settextcolor(WHITE);
				int LEFT, TOP = 100;
				for (int i = 1; i < 16; i++)
				{
					LEFT = WINDOWS_X / 8;
					outtextxy(LEFT, TOP + 35 * i, data[i].data());
				}
				RECT R = { WINDOWS_X - BBLACK,WINDOWS_Y - BBLACK / 2,WINDOWS_X - 10,WINDOWS_Y - 10 };
				rectangle(WINDOWS_X - BBLACK, WINDOWS_Y - BBLACK / 2, WINDOWS_X - 10, WINDOWS_Y - 10);
				drawtext(_T("����"), &R, DT_CENTER | DT_VCENTER | DT_SINGLELINE);
				break;
			}
			else if (m.x > WINDOWS_X - BBLACK && m.x<WINDOWS_X - 10 && m.y>WINDOWS_Y - BBLACK / 2 && m.y < WINDOWS_Y - 10 && (_BACKGROUND || _HELP || _SCORE || _SETTINGS || _DRMS))					//����
			{
				cleardevice();
				_HOME = false, _BACKGROUND = false, _HELP = false, _SCORE = false, _SETTINGS = false, _DRMS = false;
				gameStart();
			}
			else break;

		case WM_MOUSEMOVE:									//�ƶ����
			RECT r;
			if (_BACKGROUND || _HELP || _SCORE || _SETTINGS || _DRMS)				//�����ǰ������Ϸ���� ����˵�� ���߹��ڽ��� ����������ս���� ���ߵ���ģʽ����
			{
				if (ESCEXIT)gameStart();							//���ֽ��水ESC�˳�
				if (m.x > WINDOWS_X - BBLACK && m.x<WINDOWS_X - 10 && m.y>WINDOWS_Y - BBLACK / 2 && m.y < WINDOWS_Y - 10)
				{
					r.left = WINDOWS_X - BBLACK;
					r.top = WINDOWS_Y - BBLACK / 2;
					r.right = WINDOWS_X - 10;
					r.bottom = WINDOWS_Y - 10;
					POINT points[8] = { { r.left,r.top },{ r.right,r.top },{ r.right,r.bottom },{ r.left,r.bottom } };
					setfillcolor(RED);
					fillpolygon(points, 4);
					setbkmode(TRANSPARENT);
					drawtext(_T("����"), &r, DT_CENTER | DT_VCENTER | DT_SINGLELINE);
				}
				else
				{
					if (getpixel(WINDOWS_X - BBLACK + 1, WINDOWS_Y - BBLACK / 2 + 1) == RED)
					{
						putimage(WINDOWS_X - BBLACK + 1, WINDOWS_Y - BBLACK / 2 + 1, MM + 8);
						setbkmode(TRANSPARENT);
						drawtext(_T("����"), &r, DT_CENTER | DT_VCENTER | DT_SINGLELINE);
					}
				}
			}
			else
			{
				for (int i = 0; i < 6; i++)
				{
					if (m.x > WINDOWS_X / 2 - BBLACK && m.x<WINDOWS_X / 2 + BBLACK && m.y>WINDOWS_Y / 3 + i * bblack + i * BBLACK / 2 && m.y < WINDOWS_Y / 3 + i * bblack + i * BBLACK / 2 + BBLACK / 2)
					{
						r.left = WINDOWS_X / 2 - BBLACK;
						r.top = WINDOWS_Y / 3 + i * bblack + i * BBLACK / 2;
						r.right = WINDOWS_X / 2 + BBLACK;
						r.bottom = WINDOWS_Y / 3 + i * bblack + i * BBLACK / 2 + BBLACK / 2;
						POINT points[8] = { { r.left,r.top },{ r.right,r.top },{ r.right,r.bottom },{ r.left,r.bottom } };
						setfillcolor(RED);
						fillpolygon(points, 4);
						setbkmode(TRANSPARENT);
						switch (i)
						{
						case 0:
							drawtext(_T("����ģʽ"), &r, DT_CENTER | DT_VCENTER | DT_SINGLELINE);
							break;
						case 1:
							drawtext(_T("˫��ģʽ"), &r, DT_CENTER | DT_VCENTER | DT_SINGLELINE);
							break;
						case 2:
							drawtext(_T("��Ϸ����"), &r, DT_CENTER | DT_VCENTER | DT_SINGLELINE);
							break;
						case 3:
							drawtext(_T("��Ϸ����"), &r, DT_CENTER | DT_VCENTER | DT_SINGLELINE);
							break;
						case 4:
							drawtext(_T("���а�"), &r, DT_CENTER | DT_VCENTER | DT_SINGLELINE);
							break;
						case 5:
							drawtext(_T("��������"), &r, DT_CENTER | DT_VCENTER | DT_SINGLELINE);
							break;
						}
					}
					else
					{
						if (getpixel(WINDOWS_X / 2 - BBLACK + 1, WINDOWS_Y / 3 + i * bblack + i * BBLACK / 2 + 1) == RED)
						{
							putimage(WINDOWS_X / 2 - BBLACK, WINDOWS_Y / 3 + i * bblack + i * BBLACK / 2, MM + i);	//���ԭ��ͼƬ
						}
					}
				}
			}
			FlushBatchDraw();
			break;
		default: break;
		}
	}
}