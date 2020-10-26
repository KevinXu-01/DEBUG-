///////////////////////////////////////////////////////
// 文件名称：	GameStart.cpp
//   负责人：	杨景博
//     学号：	2018302060060
//   代码量：	316行
// 编译环境：	Visual Studio 2015 + EasyX_20190415(beta)
// 最后修改：	2019-6-12
// 实现功能：	主要界面、次要界面以及界面间的转换
////////////////////////////////////////////////////////

#include "GameStart.h"
using namespace std;
#define WINDOWS_X 800	//窗口大小X
#define WINDOWS_Y 480	//窗口大小Y
#define BBLACK 80		//空格大小
#define ESC 27
#define ESCEXIT (_kbhit()&&_getch()==ESC)

#pragma comment (lib,"ws2_32.lib")						// 引用 Windows Multimedia API
#pragma comment(lib,"Winmm.lib")

extern bool gameWillRestart;
extern Score score;

void gameStart()
{
	IMAGE StartbackgroundPtr;
	IMAGE GeneralbackgroundPtr;
	IMAGE MM[11] = { 0 };
	setbkmode(TRANSPARENT);					//透明字体

	loadimage(&StartbackgroundPtr, _T("IMAGE"), _T("startBackground"));
	putimage(0, 0, &StartbackgroundPtr/*, SRCAND*/);

	const int bblack = 10;

	LOGFONT f;
	gettextstyle(&f);												// 获取字体样式
	f.lfHeight = BBLACK;												// 设置字体高度
																		//strcpy(f.lfFaceName, _T("宋体"));								// 设置字体
	f.lfQuality = ANTIALIASED_QUALITY;								// 设置输出效果为抗锯齿  
	settextstyle(&f);												// 设置字体样式

	settextstyle(BBLACK / 4, 0, _T("宋体"));
	RECT r1 = { WINDOWS_X / 2 - BBLACK,WINDOWS_Y / 3,WINDOWS_X / 2 + BBLACK ,WINDOWS_Y / 3 + BBLACK / 2 };
	rectangle(WINDOWS_X / 2 - BBLACK, WINDOWS_Y / 3, WINDOWS_X / 2 + BBLACK, WINDOWS_Y / 3 + BBLACK / 2);
	drawtext(_T("单人模式"), &r1, DT_CENTER | DT_VCENTER | DT_SINGLELINE);

	RECT r2 = { WINDOWS_X / 2 - BBLACK,WINDOWS_Y / 3 + BBLACK / 2 + bblack,WINDOWS_X / 2 + BBLACK,WINDOWS_Y / 3 + BBLACK + bblack };
	rectangle(WINDOWS_X / 2 - BBLACK, WINDOWS_Y / 3 + BBLACK / 2 + bblack, WINDOWS_X / 2 + BBLACK, WINDOWS_Y / 3 + BBLACK + bblack);
	drawtext(_T("双人模式"), &r2, DT_CENTER | DT_VCENTER | DT_SINGLELINE);

	RECT r3 = { WINDOWS_X / 2 - BBLACK,WINDOWS_Y / 3 + BBLACK + 2 * bblack,WINDOWS_X / 2 + BBLACK,(int)(WINDOWS_Y / 3 + BBLACK * 1.5 + 2 * bblack) };
	rectangle(WINDOWS_X / 2 - BBLACK, WINDOWS_Y / 3 + BBLACK + 2 * bblack, WINDOWS_X / 2 + BBLACK, (int)(WINDOWS_Y / 3 + BBLACK * 1.5 + 2 * bblack));
	drawtext(_T("游戏背景"), &r3, DT_CENTER | DT_VCENTER | DT_SINGLELINE);

	RECT r4 = { WINDOWS_X / 2 - BBLACK,(int)(WINDOWS_Y / 3 + BBLACK * 1.5 + 3 * bblack),WINDOWS_X / 2 + BBLACK,WINDOWS_Y / 3 + BBLACK * 2 + 3 * bblack };
	rectangle(WINDOWS_X / 2 - BBLACK, (int)(WINDOWS_Y / 3 + BBLACK * 1.5 + 3 * bblack), WINDOWS_X / 2 + BBLACK, WINDOWS_Y / 3 + BBLACK * 2 + 3 * bblack);
	drawtext(_T("游戏帮助"), &r4, DT_CENTER | DT_VCENTER | DT_SINGLELINE);

	RECT r5 = { WINDOWS_X / 2 - BBLACK,WINDOWS_Y / 3 + BBLACK * 2 + 4 * bblack,WINDOWS_X / 2 + BBLACK,(int)(WINDOWS_Y / 3 + BBLACK * 2.5 + 4 * bblack) };
	rectangle(WINDOWS_X / 2 - BBLACK, WINDOWS_Y / 3 + BBLACK * 2 + 4 * bblack, WINDOWS_X / 2 + BBLACK, (int)(WINDOWS_Y / 3 + BBLACK * 2.5 + 4 * bblack));
	drawtext(_T("排行榜"), &r5, DT_CENTER | DT_VCENTER | DT_SINGLELINE);

	RECT r6 = { WINDOWS_X / 2 - BBLACK,(int)(WINDOWS_Y / 3 + BBLACK * 2.5 + 5 * bblack),WINDOWS_X / 2 + BBLACK,WINDOWS_Y / 3 + BBLACK * 3 + 5 * bblack };
	rectangle(WINDOWS_X / 2 - BBLACK, (int)(WINDOWS_Y / 3 + BBLACK * 2.5 + 5 * bblack), WINDOWS_X / 2 + BBLACK, WINDOWS_Y / 3 + BBLACK * 3 + 5 * bblack);
	drawtext(_T("关于我们"), &r6, DT_CENTER | DT_VCENTER | DT_SINGLELINE);


	for (int i = 0; i < 6; i++)																						//保存按钮图片
		getimage(MM + i, WINDOWS_X / 2 - BBLACK, WINDOWS_Y / 3 + i * bblack + i * BBLACK / 2, 2 * BBLACK, BBLACK / 2);
	getimage(MM + 6, WINDOWS_X - BBLACK, WINDOWS_Y - BBLACK / 2, BBLACK - 11, BBLACK / 2 - 11);

	bool _HOME = true, _BACKGROUND = false, _HELP = false, _SCORE = false, _SETTINGS = false, _DRMS = false;			//TRUE表示处于当前页面
	MOUSEMSG m;
	while (_HOME)
	{
		BeginBatchDraw();
		m = GetMouseMsg();
		switch (m.uMsg)
		{
		case WM_LBUTTONDOWN:												//当鼠标左键击下时
			EndBatchDraw();
			if (m.x > WINDOWS_X / 2 - BBLACK && m.x<WINDOWS_X / 2 + BBLACK && m.y>WINDOWS_Y / 3 && m.y < WINDOWS_Y / 3 + BBLACK / 2 && _HOME && !_BACKGROUND && !_HELP && !_SCORE && !_SETTINGS && !_DRMS)//单人模式
			{
				//What does _DRMS mean?
				//_DRMS = true;									
				_HOME = false;								//离开HOME界面
				mode = 0;										//设置模式
				gameWillRestart = true;
				cleardevice();
				break;
			}
			else if (m.x > WINDOWS_X / 2 - BBLACK && m.x<WINDOWS_X / 2 + BBLACK && m.y>WINDOWS_Y / 3 + BBLACK / 2 + bblack && m.y < WINDOWS_Y / 3 + BBLACK + bblack && _HOME && !_BACKGROUND && !_HELP && !_SCORE && !_SETTINGS && !_DRMS)//双人模式
			{
				_HOME = false;									//离开HOME界面
				mode = 1;											//设置双人模式
				gameWillRestart = true;

				break;
			}
			else if (m.x > WINDOWS_X / 2 - BBLACK && m.x<WINDOWS_X / 2 + BBLACK && m.y> WINDOWS_Y / 3 + BBLACK + 2 * bblack && m.y < (int)(WINDOWS_Y / 3 + BBLACK * 1.5 + 2 * bblack) && _HOME && !_BACKGROUND && !_HELP && !_SCORE && !_SETTINGS && !_DRMS)	//游戏介绍
			{
				_BACKGROUND = true;
				cleardevice();
				loadimage(&StartbackgroundPtr, _T("IMAGE"), _T("generalBackground"));				//背景
				putimage(0, 0, &GeneralbackgroundPtr);
				string data[16] = {
					"游戏背景：" ,
					"你是一个叫程旭元的农民。",
					"某一天，虫子们（BUGS）突然袭击你的庄稼。",
					"为了保卫庄稼",
					"你与虫子们展开了一场殊死搏斗……即“DEBUG”",
				};
				rectangle(BBLACK, BBLACK, WINDOWS_X - BBLACK, WINDOWS_Y - BBLACK);
				settextstyle(BBLACK / 2 - 5, 0, _T("宋体"));
				settextcolor(RGB(0, 255, 255));
				outtextxy(WINDOWS_X / 3 - 100, 90, data[0].data());
				settextstyle(BBLACK / 4, 0, _T("宋体"));
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
				drawtext(_T("返回"), &R, DT_CENTER | DT_VCENTER | DT_SINGLELINE);
				break;
			}
			else if (m.x > WINDOWS_X / 2 - BBLACK && m.x<WINDOWS_X / 2 + BBLACK && m.y>(int)(WINDOWS_Y / 3 + BBLACK * 1.5 + 3 * bblack) && m.y < WINDOWS_Y / 3 + BBLACK * 2 + 3 * bblack && _HOME && !_BACKGROUND && !_HELP && !_SCORE && !_SETTINGS && !_DRMS)	//操作说明
			{
				_HELP = true;
				cleardevice();
				loadimage(&StartbackgroundPtr, _T("IMAGE"), _T("generalBackground"));				//背景
				string data[16] = {
					"操作说明" ,
					"游戏分为单人模式和双人模式",
					"单人模式中使用W向上、S向下、A向左、D向右，并可使用组合键",
					"利用鼠标进行射击，杀死一只虫子可以获得分数，",
					"并且有一定几率掉落金币,在结算时金币可折算为分数",
					"金币可以用于在商店中购买物品",
					"按下Z键可以购买并使用急救包，此时生命值恢复到最大",
					"按下X键可以购买并使用绷带，此时可以恢复一点生命值",
					"按下C键可以购买并使用能量饮料，并在一定时间内获得加速",
					"按下V键可以购买并使用油桶，在地图上放置后即可阻挡虫子",
					"用子弹打爆油桶可以瞬间击杀油桶附近所有的虫子",
					"游戏提供了四种枪，按下Q或E键可进行切换",
					"按下P键可以暂停游戏，若要恢复，只需再按下P键",
					"在双人模式下，两人协作完成且存在复活机制，请尽情探索",
				};
				rectangle(BBLACK, BBLACK, WINDOWS_X - BBLACK, WINDOWS_Y - BBLACK);
				settextstyle(BBLACK / 2 - 5, 0, _T("宋体"));
				settextcolor(RGB(0, 255, 255));
				outtextxy(WINDOWS_X / 3 - 100, 90, data[0].data());
				settextstyle(BBLACK / 4, 0, _T("宋体"));
				settextcolor(WHITE);
				int LEFT, TOP = 110;
				for (int i = 1; i < 16; i++)
				{
					LEFT = WINDOWS_X / 8;
					outtextxy(LEFT, TOP + 20 * i, data[i].data());
				}
				RECT R = { WINDOWS_X - BBLACK,WINDOWS_Y - BBLACK / 2,WINDOWS_X - 10,WINDOWS_Y - 10 };
				rectangle(WINDOWS_X - BBLACK, WINDOWS_Y - BBLACK / 2, WINDOWS_X - 10, WINDOWS_Y - 10);
				drawtext(_T("返回"), &R, DT_CENTER | DT_VCENTER | DT_SINGLELINE);
				break;
			}
			else if (m.x > WINDOWS_X / 2 - BBLACK && m.x<WINDOWS_X / 2 + BBLACK && m.y>WINDOWS_Y / 3 + BBLACK * 2 + 4 * bblack && m.y < (int)(WINDOWS_Y / 3 + BBLACK * 2.5 + 4 * bblack) && _HOME && !_BACKGROUND && !_HELP && !_SCORE && !_SETTINGS && !_DRMS)//排行榜
			{
				_SCORE = true;
				cleardevice();
				int scores[10];
				char temp[5];
				string data[10] = {
					"第一名、",
					"第二名、",
					"第三名、",
					"第四名、",
					"第五名、",
					"第六名、",
					"第七名、" ,
					"第八名、" ,
					"第九名、" ,
					"第十名、" ,
				};
				score.gerRecordScore(scores, 10);
				settextstyle(BBLACK / 4, 0, _T("宋体"));
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
				drawtext(_T("返回"), &R3, DT_CENTER | DT_VCENTER | DT_SINGLELINE);
				break;
			}
			else if (m.x > WINDOWS_X / 2 - BBLACK && m.x<WINDOWS_X / 2 + BBLACK && m.y>(int)(WINDOWS_Y / 3 + BBLACK * 2.5 + 5 * bblack) && m.y < WINDOWS_Y / 3 + BBLACK * 3 + 5 * bblack && _HOME && !_BACKGROUND && !_HELP && !_SCORE && !_SETTINGS && !_DRMS)//设置
			{
				_SETTINGS = true;									//离开HOME界面
				cleardevice();
				loadimage(&StartbackgroundPtr, _T("IMAGE"), _T("generalBackground"));				//背景
				putimage(0, 0, &GeneralbackgroundPtr);
				string data[16] = {
					"关于我们：" ,
					"范承祥 WHU2018软工6班",
					"负责人、分数类以及结算界面",
					"江诗烨 WHU2018软工6班",
					"负责虫以及金币类",
					"许静宇 WHU2018计科8班",
					"负责枪类以及核心界面",
					"杨景博 WHU2018计科7班",
					"负责道具类以及启动界面、次要界面"
				};
				settextstyle(BBLACK / 2 - 5, 0, _T("宋体"));
				settextcolor(RGB(0, 255, 255));
				outtextxy(WINDOWS_X / 3 - 100, 90, data[0].data());
				rectangle(BBLACK, BBLACK, WINDOWS_X - BBLACK, WINDOWS_Y - BBLACK);
				settextstyle(BBLACK / 4, 0, _T("宋体"));
				settextcolor(WHITE);
				int LEFT, TOP = 100;
				for (int i = 1; i < 16; i++)
				{
					LEFT = WINDOWS_X / 8;
					outtextxy(LEFT, TOP + 35 * i, data[i].data());
				}
				RECT R = { WINDOWS_X - BBLACK,WINDOWS_Y - BBLACK / 2,WINDOWS_X - 10,WINDOWS_Y - 10 };
				rectangle(WINDOWS_X - BBLACK, WINDOWS_Y - BBLACK / 2, WINDOWS_X - 10, WINDOWS_Y - 10);
				drawtext(_T("返回"), &R, DT_CENTER | DT_VCENTER | DT_SINGLELINE);
				break;
			}
			else if (m.x > WINDOWS_X - BBLACK && m.x<WINDOWS_X - 10 && m.y>WINDOWS_Y - BBLACK / 2 && m.y < WINDOWS_Y - 10 && (_BACKGROUND || _HELP || _SCORE || _SETTINGS || _DRMS))					//返回
			{
				cleardevice();
				_HOME = false, _BACKGROUND = false, _HELP = false, _SCORE = false, _SETTINGS = false, _DRMS = false;
				gameStart();
			}
			else break;

		case WM_MOUSEMOVE:									//移动鼠标
			RECT r;
			if (_BACKGROUND || _HELP || _SCORE || _SETTINGS || _DRMS)				//如果当前处于游戏介绍 操作说明 或者关于界面 或者联机对战界面 或者单人模式界面
			{
				if (ESCEXIT)gameStart();							//部分界面按ESC退出
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
					drawtext(_T("返回"), &r, DT_CENTER | DT_VCENTER | DT_SINGLELINE);
				}
				else
				{
					if (getpixel(WINDOWS_X - BBLACK + 1, WINDOWS_Y - BBLACK / 2 + 1) == RED)
					{
						putimage(WINDOWS_X - BBLACK + 1, WINDOWS_Y - BBLACK / 2 + 1, MM + 8);
						setbkmode(TRANSPARENT);
						drawtext(_T("返回"), &r, DT_CENTER | DT_VCENTER | DT_SINGLELINE);
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
							drawtext(_T("单人模式"), &r, DT_CENTER | DT_VCENTER | DT_SINGLELINE);
							break;
						case 1:
							drawtext(_T("双人模式"), &r, DT_CENTER | DT_VCENTER | DT_SINGLELINE);
							break;
						case 2:
							drawtext(_T("游戏背景"), &r, DT_CENTER | DT_VCENTER | DT_SINGLELINE);
							break;
						case 3:
							drawtext(_T("游戏帮助"), &r, DT_CENTER | DT_VCENTER | DT_SINGLELINE);
							break;
						case 4:
							drawtext(_T("排行榜"), &r, DT_CENTER | DT_VCENTER | DT_SINGLELINE);
							break;
						case 5:
							drawtext(_T("关于我们"), &r, DT_CENTER | DT_VCENTER | DT_SINGLELINE);
							break;
						}
					}
					else
					{
						if (getpixel(WINDOWS_X / 2 - BBLACK + 1, WINDOWS_Y / 3 + i * bblack + i * BBLACK / 2 + 1) == RED)
						{
							putimage(WINDOWS_X / 2 - BBLACK, WINDOWS_Y / 3 + i * bblack + i * BBLACK / 2, MM + i);	//输出原来图片
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