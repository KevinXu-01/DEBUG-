///////////////////////////////////////////////////////
// �ļ����ƣ�	Item.h
//   �����ˣ�	���
//     ѧ�ţ�	2018302060060
//   ��������	53��
// ���뻷����	Visual Studio 2015 + EasyX_20190415(beta)
// ����޸ģ�	2019-6-22
// ʵ�ֹ��ܣ�	���������Ȱ����������Ϻ���Ͱ���ߵĹ���ʵ��
////////////////////////////////////////////////////////

#pragma once
#include"Person.h"
#include "Bugs.h"

extern Person personA, personB;
extern Baneling* banelings[5];
extern Hydralisk*hydralisks[3];
extern Roach* roachs[4];
extern Zergling* zerglings[5];
extern Hydraspit*hydraspits[3];
extern int banep;
extern int rop;
extern int zergp;
extern int spitp;
extern int hydrap;
extern int spitp;
static bool OTa = 0, OTb = 0;
static bool ifPut_A = false;
static bool ifPut_B = false;

class Item
{
public:
	Item();
	~Item() {};
	void EnergyDrinkA();                        //���ּ���
	void EnergyDrinkB();                        //���ּ���
	void BandageA();                            //�����ָ�����ֵ
	void BandageB();                            //�����ָ�����ֵ
	void FirstAidA();                           //���Ȱ�
	void FirstAidB();                           //���Ȱ�
	void SetOilTankA();                         //��Ͱ�ķ���
	void SetOilTankB();                         //��Ͱ�ķ���
	int OilTankExplodeA();                      //��Ͱ�ı�ըЧ��
	int OilTankExplodeB();
	void setControl();                          //��ҹ�����߲ٿ�
	void OilTankA();                        //��Ͱ����
	void OilTankB();
	void loadoilTankA();                        //������ͰͼƬ
	void loadoilTankB();                        //������ͰͼƬ
	int AgetOilTankPositionX();                   //��ȡ��Ͱλ��
	int AgetOilTankPositionY();
	int BgetOilTankPositionX();
	int BgetOilTankPositionY();
	int i = 0;
private:
	int x0;
	int y0;
	int x_oilA = 1000;
	int y_oilA = 1000;
	int x_oilB = 1000;
	int y_oilB = 1000;
};