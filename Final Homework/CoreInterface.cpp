///////////////////////////////////////////////////////
// �ļ����ƣ�	CoreInterface.cpp
//   �����ˣ�	����
//     ѧ�ţ�	2018302060052
//   ��������	319��
// ���뻷����	Visual Studio 2015 + EasyX_20190415(beta)
// ����޸ģ�	2019-6-12
// ʵ�ֹ��ܣ�	ʵʱ��ʾ��Ϣ���������֡���ʾ�̵��
////////////////////////////////////////////////////////

#include "CoreInterface.h"
#include "Person.h"
#include "Score.h"

extern Score score;//ȫ�ֱ���
extern Person personA, personB;
bool ifPlayMusic = true;
void showMap()
{
	IMAGE Background;
	IMAGE Black_Background;
	loadimage(&Background, _T("IMAGE"), _T("BACKGROUND"));//���뱳��ͼƬ
	loadimage(&Black_Background, _T("IMAGE"), _T("BLACKBACKGROUND"));//�����ɫͼƬ
	putimage(0, 0, &Background);
	putimage(640, 0, &Black_Background);
}

void showInfo_init_single()
{
	IMAGE scorepic;
	IMAGE heart;
	//���Ʒֽ���
	setlinecolor(RED);
	line(640, 240, 800, 240);
	line(640, 239, 800, 239);
	line(640, 241, 800, 241);
	//�����������
	loadimage(&scorepic, _T("IMAGE"), _T("SCORE"));//�������ͼƬ
	putimage(645, 35, &scorepic);
	settextcolor(WHITE);
	settextstyle(25, 0, _T("����"), 0, 0, 500, false, false, false);
	if(score.getScore()==0)
	outtextxy(650, 85, _T("0"));//����ַ�
	//�����Ҳ���
	settextcolor(WHITE);
	settextstyle(20, 0, _T("����"), 0, 0, 500, false, false, false);
	outtextxy(650, 105, _T("��ң�"));//����ַ�
	if(Person::getCoins()==0)
	outtextxy(705, 105, _T("0"));//����ַ�
	//��������ֵ����
	settextcolor(YELLOW);
	settextstyle(30, 0, _T("����"), 0, 0, 500, false, false, false);
	outtextxy(680, 135, _T("����ֵ"));//����ַ�
	loadimage(&heart, _T("IMAGE"), _T("HEART"));//������ͼƬ
	if(personA.getHealthPoint()>0)
	putimage(652, 175, &heart);
	if(personA.getHealthPoint()>1)
	putimage(687, 175, &heart);
	if(personA.getHealthPoint()>2)
	putimage(722, 175, &heart);//�����ĵ�ͼ��
}

void showInfo_init_double()
{
	IMAGE score;
	IMAGE heart;
	//���Ʒֽ���
	setlinecolor(RED);
	line(640, 240, 800, 240);
	line(640, 239, 800, 239);
	line(640, 241, 800, 241);
	//�����������
	loadimage(&score, _T("IMAGE"), _T("SCORE"));//�������ͼƬ
	putimage(645, 35, &score);
	settextcolor(WHITE);
	settextstyle(25, 0, _T("����"), 0, 0, 500, false, false, false);
	outtextxy(650, 85, _T("0"));//����ַ�
	//�����Ҳ���
	settextcolor(WHITE);
	settextstyle(20, 0, _T("����"), 0, 0, 500, false, false, false);
	outtextxy(650, 105, _T("��ң�"));//����ַ�
	if (Person::getCoins() == 0)
	outtextxy(705, 105, _T("0"));//����ַ�
	//��������ֵ����
	settextcolor(YELLOW);
	settextstyle(30, 0, _T("����"), 0, 0, 500, false, false, false);
	outtextxy(680, 135, _T("����ֵ"));//����ַ�
	loadimage(&heart, _T("IMAGE"), _T("HEART"));//������ͼƬ
	//ʵ�ָ���
	int ReviveTimeA = personA.getReviveTime();
	int ReviveTimeB = personB.getReviveTime();
#define ReviveTime_1 ReviveTimeA
#define ReviveTime_2 ReviveTimeB
	loadimage(&heart, _T("IMAGE"), _T("HEART"));//������ͼƬ
	if (personA.getHealthPoint()<=0&& personB.getHealthPoint() > 0)
	{
		settextcolor(WHITE);
		settextstyle(20, 0, _T("����"), 0, 0, 500, false, false, false);
		TCHAR reviveA[10];
		_stprintf_s(reviveA, _T("%d"), ReviveTime_1);
		outtextxy(652, 175, reviveA);//����ַ�
		outtextxy(672, 175, _T("�����Ը���"));//����ַ�
	}
	if (personB.getHealthPoint() <= 0&&personA.getHealthPoint() > 0)
	{
		settextcolor(WHITE);
		settextstyle(20, 0, _T("����"), 0, 0, 500, false, false, false);
		TCHAR reviveB[10];
		_stprintf_s(reviveB, _T("%d"), ReviveTime_2);
		outtextxy(652, 204, reviveB);//����ַ�
		outtextxy(672, 204, _T("�����Ը���"));//����ַ�
	}
	//�������A����ͼ��
	if(personA.getHealthPoint()>0)
	putimage(652, 175, &heart);
	if(personA.getHealthPoint()>1)
	putimage(687, 175, &heart);
	if (personA.getHealthPoint()>2)
	putimage(722, 175, &heart);
	//�������B����ͼ��
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
	loadimage(&store, _T("IMAGE"), _T("STORE"));//�����̵�ͼƬ
	loadimage(&first_aid_kit, _T("IMAGE"), _T("FIRST_AID_KIT"));//���뼱�Ȱ�ͼƬ
	loadimage(&bandage, _T("IMAGE"), _T("BANDAGE"));//�������ͼƬ
	loadimage(&energy_drink, _T("IMAGE"), _T("ENERGY_DRINK"));//������������ͼƬ
	loadimage(&oil_tank, _T("IMAGE"), _T("OIL_TANK"));//������ͰͼƬ
	putimage(695, 250, &store);
	putimage(660, 310, &first_aid_kit);
	putimage(730, 310, &bandage);
	putimage(660, 380, &energy_drink);
	putimage(730, 380, &oil_tank);
	settextcolor(WHITE);
	settextstyle(15, 0, _T("����"), 0, 0, 500, false, false, false);
	outtextxy(660, 360, _T("5�����"));//����ַ�
	outtextxy(730, 360, _T("3�����"));//����ַ�
	outtextxy(660, 430, _T("2�����"));//����ַ�
	outtextxy(730, 430, _T("7�����"));//����ַ�
}

void showButtons()
{
	IMAGE pause;
	loadimage(&pause, _T("IMAGE"), _T("PAUSE"));//������ͣ��ťͼƬ
	putimage(765, 5, &pause);
}

void reshowInfo_playerA_hp()//���A������ֵ�ӿ�
{
	//���þ��ο��Ա���ѡ���þ��ο���ʵ����գ�����ĺ��������ƵĴ��������ͬ�Ĺ���
	HRGN rgn = CreateRectRgn(641, 175, 800, 203);
	setcliprgn(rgn);
	clearcliprgn();
	IMAGE heart;
	int healthpoint_A = personA.getHealthPoint();
	int i = 0;//ѭ������
	loadimage(&heart, _T("IMAGE"), _T("HEART"));//������ͼƬ
	if(healthpoint_A>0)
	for (i = 0; i <= healthpoint_A - 1; i++)
	{
		putimage(652 + i * 35, 175, &heart);
	}
	//����һ��1ms����ʱ����ֹ��Ϣ����ʱ������˸
	Sleep(1);
	//ɾ���þ��ο򣬲�����ͼ������ΪĬ��
	DeleteObject(rgn);
	setcliprgn(NULL);
}

void reshowInfo_playerB_hp()//���B������ֵ�ӿ�
{
	HRGN rgn = CreateRectRgn(641, 204, 800, 238);
	setcliprgn(rgn);
	clearcliprgn();
	IMAGE heart;
	int healthpoint_B = personB.getHealthPoint();
	int i = 0;//ѭ������
	loadimage(&heart, _T("IMAGE"), _T("HEART"));//������ͼƬ
	for (i = 0; i <= healthpoint_B - 1; i++)
	{
		putimage(652 + i * 35, 204, &heart);
	}
	Sleep(1);
	DeleteObject(rgn);
	setcliprgn(NULL);
}

void reshowInfo_score()//�����ӿ�
{
	int score1 = score.getScore();
#define score_1 score1
	HRGN rgn = CreateRectRgn(650, 75, 800, 104);
	setcliprgn(rgn);
	clearcliprgn();
	settextcolor(WHITE);
	settextstyle(25, 0, _T("����"), 0, 0, 500, false, false, false);
	TCHAR score[10];
	_stprintf_s(score, _T("%d"), score_1);
	outtextxy(650, 75, score);//����ַ�
	Sleep(1);
	DeleteObject(rgn);
	setcliprgn(NULL);
}

void reshowInfo_coin_single()//����ģʽ�Ľ�ҽӿ�
{
	int coin1 = Person::getCoins();
#define coin_1 coin1
	HRGN rgn = CreateRectRgn(705, 105, 800, 135);
	setcliprgn(rgn);
	clearcliprgn();
	settextcolor(WHITE);
	settextstyle(20, 0, _T("����"), 0, 0, 500, false, false, false);
	TCHAR coin[10];
	_stprintf_s(coin, _T("%d"), coin_1);
	outtextxy(705, 105, coin);//����ַ�
	Sleep(1);
	DeleteObject(rgn);
	setcliprgn(NULL);
}

void reshowInfo_coin_double()//˫��ģʽ�Ľ�ҽӿ�
{
	int coin1 = Person::getCoins();
#define coin_1 coin1
	HRGN rgn = CreateRectRgn(705, 105, 800, 135);
	setcliprgn(rgn);
	clearcliprgn();
	settextcolor(WHITE);
	settextstyle(20, 0, _T("����"), 0, 0, 500, false, false, false);
	TCHAR coin[10];
	_stprintf_s(coin, _T("%d"), coin_1);
	outtextxy(705, 105, coin);//����ַ�
	Sleep(1);
	DeleteObject(rgn);
	setcliprgn(NULL);
}

bool ExtractResource(LPCTSTR strDstFile, LPCTSTR strResType, LPCTSTR strResName)//����Դ�ļ�����ȡ�ļ������ص��ڴ��У��Ա�MciSendString��ȡ
{
	if (ifPlayMusic == true)
	{
		//�����ļ�
		HANDLE hFile = ::CreateFile(strDstFile, GENERIC_WRITE, NULL, NULL, CREATE_ALWAYS, FILE_ATTRIBUTE_TEMPORARY, NULL);
		if (hFile == INVALID_HANDLE_VALUE)
			return false;
		//������Դ�ļ��С�������Դ���ڴ桢�õ���Դ��С
		HRSRC	hRes = ::FindResource(NULL, strResName, strResType);
		HGLOBAL	hMem = ::LoadResource(NULL, hRes);
		DWORD	dwSize = ::SizeofResource(NULL, hRes);
		//д���ļ�
		DWORD dwWrite = 0;  	// ����д���ֽ�
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
		_tcscat_s(tmpmp3, _T("testapp_background.mp3"));// ������ʱ�ļ����ļ���
		ExtractResource(tmpmp3, _T("WAVE"), _T("GAME_MUSIC_MARCH"));// �� MP3 ��Դ��ȡΪ��ʱ�ļ�
		TCHAR mcicmd[300];
		_stprintf_s(mcicmd, _T("open \"%s\" alias BackMusic"), tmpmp3);
		mciSendString(mcicmd, NULL, 0, NULL);// ������
		mciSendString(_T("play BackMusic"), NULL, 0, NULL);    // ��������
		mciSendString(TEXT("setaudio BackMusic volume to 300"), NULL, 0, NULL);		//����������С
		mciSendString(TEXT("play BackMusic repeat"), NULL, 0, NULL);				//ѭ������
		DeleteFile(tmpmp3);//ɾ����ʱ�ļ�
	}
}

void CoreInterface_main_single()//����ģʽ������ֱ������������������cpp�ļ���ĺ���
{
	showMap();
	showInfo_init_single();
	showStore();
	showButtons();
}//����ֱ������������������cpp�ļ���ĺ���

void CoreInterface_main_double()//˫��ģʽ������ֱ������������������cpp�ļ���ĺ���
{
	showMap();
	showInfo_init_double();
	showStore();
	showButtons();
}

 //���������������Ը��ݵ���˫��ģʽѡ����ʵĺ���
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