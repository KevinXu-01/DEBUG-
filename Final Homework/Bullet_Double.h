///////////////////////////////////////////////////////
// �ļ����ƣ�	Bullet_Double.h
//   �����ˣ�	����
//     ѧ�ţ�	2018302060052
//   ��������	53��
// ���뻷����	Visual Studio 2015 + EasyX_20190415(beta)
// ����޸ģ�	2019-6-12
// ʵ�ֹ��ܣ�	����Bullet_Double�࣬�Ժ�����������
////////////////////////////////////////////////////////

#pragma once
#include "Person.h"
#include <easyx.h>
#include "Bugs.h"
#include"conio.h"
#include"graphics.h"
#include <math.h>
#include <windows.h>
#include "Item.h"
#define PI 3.1415926               //����PI

class Bullet_Double;
extern MOUSEMSG mouse;
extern Person personA, personB;
extern Baneling* banelings[5];
extern Hydralisk*hydralisks[3];
extern Roach* roachs[4];
extern Zergling* zerglings[5];
extern Hydraspit*hydraspits[3];
extern Bullet_Double* bullets_DoubleA[20];
extern Bullet_Double* bullets_DoubleB[20];
extern int bp_DoubleA;
extern int bp_DoubleB;
extern int banep;
extern int rop;
extern int zergp;
extern int spitp;
extern int hydrap;
extern int spitp;
extern Item item;

class Bullet_Double
{
public:
	Bullet_Double();
	~Bullet_Double() {};
	bool act_A();                           //A�ӵ�����
	bool act_B();                           //B�ӵ�����
	void draw();                             //�����ӵ�
private:
	int xA, yA, xB, yB, mousex, mousey;
	double vxA, vyA, vxB, vyB;
	const int v;
};
void fire_DoubleA();                                     //A����
bool addBullet_DoubleA(Bullet_Double *p);//ɾ��A�ӵ�
bool deleteBullet_DoubleA(Bullet_Double *p);//���A�ӵ�

void fire_DoubleB();                                        //B����
bool addBullet_DoubleB(Bullet_Double *p);//ɾ��B�ӵ�
bool deleteBullet_DoubleB(Bullet_Double *p);//���B�ӵ�

void deleteAllBullets_Double();  //˫��ģʽ��ɾ�������ӵ�