///////////////////////////////////////////////////////
// �ļ����ƣ�	Coins.h
//   �����ˣ�	��ʫ��
//     ѧ�ţ�	2018302060048
//   ��������	23��
// ���뻷����	Visual Studio 2015 + EasyX 20190415(beta) 
// ����޸ģ�	2019-6-12
// ʵ�ֹ��ܣ�	��ҵ�������
////////////////////////////////////////////////////////
#pragma once
#include"Person.h"

class Coins
{
public:
	Coins(int zx,int zy);
	~Coins() {};
	void drawcoins();						//���ƽ��
	void CoinsPlay();						//������
private:
	int x, y;
	void getcoins();						//��ȡ���
	int t=300;								//�ݻٵ���ʱ
	int i=0;								//��˸����
};

extern int coinsp;							//�������ͬʱ���ֽ�������ޣ��������
void initcoinsdraw();						//��ʼ������
void allcoinsact();							//ִ�е��������й���

bool addCoin( Coins* c);
bool deleteCoin(Coins* c);