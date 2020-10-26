///////////////////////////////////////////////////////
// �ļ����ƣ�	zergclock.cpp
//   �����ˣ�	��ʫ��
//     ѧ�ţ�	2018302060048
//   ��������	164��
// ���뻷����	Visual Studio 2015 + EasyX 20190415(beta) 
// ����޸ģ�	2019-6-12
// ʵ�ֹ��ܣ�	�����������ж�
////////////////////////////////////////////////////////
#include"Bugs.h"
//���ɡ���š����ٶ�ֻ����
extern Baneling* banelings[5];
extern bool addBaneling(Baneling* z);
extern bool deleteBaneling(Baneling* z);
extern Hydralisk*hydralisks[3];
extern bool addHydralisk(Hydralisk*z);
extern bool deleteHydralisk(Hydralisk*z);
extern Hydraspit*hydraspits[3];
extern bool deleteHydraspit(Hydraspit*z);
extern Roach* roachs[4];
extern bool addRoach(Roach* z);
extern bool deleteRoach(Roach* z);
extern Zergling* zerglings[5];
extern bool addZergling(Zergling* z);
extern bool deleteZergling(Zergling* z);
int ifbane=120;

void initzergclock()//��ʼ������ʱ��
{
	banep = 0;
	hydrap = 0;
	spitp = 0;
	rop = 0;
	zergp = 0;
	baneling_Max = 0;
	hydralisk_Max = 0;
	hydraspit_Max = 0;
	roach_Max = 0;
	zergling_Max = 1;
	baneling_generate_gap = 0;
	hydralisk_generate_gap = 120;
	roach_generate_gap = 80;
	zergling_generate_gap = 20;
}

void renewzergclock()//���³���ʱ�ӣ��������ӣ�
{
	//baneling
	if (banep < baneling_Max&&banep!=5&&baneling_generate_gap <= 0&&ifbane>400)//�����µĳ���
	{
		addBaneling(new Baneling);
		baneling_generate_gap = 25;
	}
	for (int banei = 0; banei<banep; banei++)									//��������
	{
		if (banelings[banei]->judgeDie())
		{
			banelings[banei]->getscore();
			deleteBaneling(banelings[banei]);
		}
	}

	//hydralisk
	if (hydrap < hydralisk_Max&&hydrap != 3 && hydralisk_generate_gap <= 0)		//����
	{
		addHydralisk(new Hydralisk);
		hydralisk_generate_gap = 50;
	}
	for (int hydrai = 0; hydrai<hydrap; hydrai++)								//��������
	{
		if (hydralisks[hydrai]->judgeDie())
		{
			hydralisks[hydrai]->getscore();
			deleteHydralisk (hydralisks[hydrai]);
		}
	}

	//hydralisk____spit
	for (int spiti = 0; spiti<spitp; spiti++)									//����
	{
		if (hydraspits[spiti]->judgeDie())
		{
			deleteHydraspit(hydraspits[spiti]);
		}
		else if (hydraspits[spiti]->x <= 0 || hydraspits[spiti]->x >= 640 || hydraspits[spiti]->y <= 0 || hydraspits[spiti]->y >= 480)
		{
			deleteHydraspit(hydraspits[spiti]);
		}
	}

	//roach
	if (rop < roach_Max && rop != 4 && roach_generate_gap <= 0)					//����
	{
		addRoach(new Roach);
		roach_generate_gap = 50;
	}
	for (int roi = 0; roi < rop; roi++)											//��������
	{
		if (roachs[roi]->judgeDie())
		{
			roachs[roi]->getscore();
			deleteRoach(roachs[roi]);
		}
	}

	//zergling
	if (zergp < zergling_Max && zergp != 5 && zergling_generate_gap <= 0)		//����
	{
		addZergling(new Zergling);
		zergling_generate_gap = 30;
	}
	for (int zergi = 0; zergi < zergp; zergi++)									//��������
	{
		if (zerglings[zergi]->judgeDie())
		{
			zerglings[zergi]->getscore();
			deleteZergling(zerglings[zergi]);
		}
	}

	//��Ϸ��ʼ����ʱ�����ƣ�����Խ��Խ��
	if(baneling_Max<4)
		baneling_Max += 0.001f;
	if (baneling_generate_gap > 0)
		baneling_generate_gap--;

	if (hydralisk_Max < 2)
		hydralisk_Max += 0.0015f;
	if (hydralisk_generate_gap > 0)
		hydralisk_generate_gap--;

	if (hydraspit_Max < 2)
		hydraspit_Max += 0.0015f;

	if (roach_Max < 3)
		roach_Max += 0.0015f;
	if (roach_generate_gap > 0)
		roach_generate_gap--;

	if (zergling_Max < 4)
		zergling_Max += 0.001f;
	if (zergling_generate_gap > 0)
		zergling_generate_gap--;

	ifbane++;
	if (ifbane >= 600)
		ifbane = 0;
}

//�������г��ӵ��ж�
void allzergsact()
{
	for (int banei = 0; banei < banep; banei++)
	{
		banelings[banei]->act();
	}
	for (int hydrai = 0; hydrai < hydrap; hydrai++)
	{
		hydralisks[hydrai]->act();
	}
	for (int spiti = 0; spiti < spitp; spiti++)
	{
		hydraspits[spiti]->act();
	}
	for (int roi = 0; roi < rop; roi++)
	{
		roachs[roi]->act();
	}
	for (int zergi = 0; zergi < zergp; zergi++)
	{
		zerglings[zergi]->act();
	}
}