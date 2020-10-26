///////////////////////////////////////////////////////
// �ļ����ƣ�	main.cpp
//   �����ˣ�	���
//     ѧ�ţ�	2018302060060
//   ��������	119��
// ���뻷����	Visual Studio 2015 + EasyX_20190415(beta)
// ����޸ģ�	2019-6-22
// ʵ�ֹ��ܣ�	��Ϸ���幦��������ʵ��
////////////////////////////////////////////////////////

#include<conio.h>
#include"Person.h"
#include"Score.h"
#include"GameStart.h"
#include"InterfaceOfScore.h"
#include"CoreInterface.h"
#include"Bugs.h"
#include"Bullet_Single.h"
#include"Bullet_Double.h"
#include"Coins.h"
#include"PauseAndDelete.h"
#include"Item.h"
using namespace std;

Person personA, personB;							//�����˵Ķ���
Bullet_Double *bullets_DoubleA[20];					//˫��ģʽ��A���ӵ�
Bullet_Double *bullets_DoubleB[20];					//˫��ģʽ��B���ӵ�
Bullet_Single *bullets_Single[20];					//����ģʽ�µ��ӵ�
int bp_Single = 0;									//���µ���ģʽ���ӵ�ʹ��
int bp_DoubleA = 0, bp_DoubleB = 0;					//����˫��ģʽ���ӵ�ʹ��
Score score;										//�������
MOUSEMSG mouse;										//�������ڴ洢���״̬�ı���
Item item;											//���������
int mode=0;											//����ģʽ����
bool gameWillRestart = false;						//�����Ƿ����¿�ʼ�ı���

//������
int main()
{
	initgraph(800, 480);							//��ʼ������
	playMusic();
	gameStart();									//��Ϸ���˵�
	personB.setPlayer('B');							//����B��ʼ��
	personB.setPersonPosition(370, 370);
	initzergdraw();									//��ʼ����ͼ
	initcoinsdraw();
	initzergclock();

	//��ͼ��ѭ��
	while (1)										
	{
		if (mode == 0)
			personB.setHealthPoint(0, 0);			//����B����Ϊ����
		renewzergclock();
		BeginBatchDraw();							//��ʼ������ͼ
		CoreInterface_main(mode);
		showInfo_init(mode);
		reshowInfo_score();
		reshowInfo_coin(mode);
		personA.setControl();
		personA.showPerson();
		item.setControl();
		if (mode == 1)
		{
			item.setControl();
			personB.setControl();
			personB.showPerson();
		}
		allzergsact();
		allcoinsact();

		//��A���п����ж�
		if (personA.getHealthPoint() > 0&&personA.getWeapon()!='O')
		{
			if (mode == 0)//����ģʽ
			{
				fire_Single();
				for (int i = 0; i < bp_Single; i++)				//�����ӵ����˶�����Ϊ
				{
					bullets_Single[i]->draw();
					if (!(bullets_Single[i]->act()))
						deleteBullet_Single(bullets_Single[i]);
				}
			}
			else//˫��ģʽ
			{
				fire_DoubleA();
				for (int i = 0; i < bp_DoubleA; i++)				//�����ӵ����˶�����Ϊ
				{
					bullets_DoubleA[i]->draw();
					if (!(bullets_DoubleA[i]->act_A()))
						deleteBullet_DoubleA(bullets_DoubleA[i]);
				}
			}
		}
		//��B���п����ж�
		if (personB.getHealthPoint() > 0 && personB.getWeapon() != 'O')
		{
			fire_DoubleB();
			for (int i = 0; i < bp_DoubleB; i++)				//�����ӵ����˶�����Ϊ
			{
				bullets_DoubleB[i]->draw();
				if (!(bullets_DoubleB[i]->act_B()))
					deleteBullet_DoubleB(bullets_DoubleB[i]);
			}
		}
		item.setControl();
		ifp();
		if (personA.getHealthPoint() <= 0 && personB.getHealthPoint() <= 0)		//�ж������Ƿ�����
		{
			deleteallbugsandcoins();											//ɾ�����г��Ӻͽ��
			if (mode == 1)
				deleteAllBullets_Double();										//ɾ�������ӵ�
			if (mode == 0)
				deleteAllBullets_Single();										//ɾ�������ӵ�
			CoreInterface_main(mode);
			interfaceOfScore();													//�������������������
		}
		else if (personA.getHealthPoint() <= 0&&mode==1)						//�ж��Ƿ�ֻ�е�������
			personA.personRevive();												//����A���븴�����
		else if (personB.getHealthPoint() <= 0&&mode==1)
			personB.personRevive();												//����B���븴�����
		else;
		Sleep(10);
		EndBatchDraw();															//����������ͼ						
		FlushMouseMsgBuffer();													//��������Ϣ
		}		
	return 0;
}