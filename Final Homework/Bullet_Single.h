///////////////////////////////////////////////////////
// �ļ����ƣ�	Bullet_Single.h
//   �����ˣ�	����
//     ѧ�ţ�	2018302060052
//   ��������	44��
// ���뻷����	Visual Studio 2015 + EasyX_20190415(beta)
// ����޸ģ�	2019-6-12
// ʵ�ֹ��ܣ�	����Bullet_Single�࣬�Ժ�����������
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

class Bullet_Single;
extern MOUSEMSG mouse;
extern Person personA, personB;
extern Baneling* banelings[5];
extern Hydralisk*hydralisks[3];
extern Roach* roachs[4];
extern Zergling* zerglings[5];
extern Hydraspit*hydraspits[3];
extern Bullet_Single* bullets_Single[20];
extern int bp_Single;
extern int banep;
extern int rop;
extern int zergp;
extern int spitp;
extern int hydrap;
extern int spitp;
extern Item item;

class Bullet_Single
{
public:
	Bullet_Single();
	~Bullet_Single() {};
	bool act();                                //�ӵ�����
	void draw();                             //�����ӵ�
private:
	int x, y, mousex, mousey;
	double vx, vy;
	const int v;
};
void fire_Single();
bool addBullet_Single(Bullet_Single *p);//ɾ���ӵ�
bool deleteBullet_Single(Bullet_Single *p);//����ӵ�
void deleteAllBullets_Single();    //����ģʽ��ɾ�������ӵ�