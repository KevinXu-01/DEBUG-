///////////////////////////////////////////////////////
// 文件名称：	Bullet_Double.cpp
//   负责人：	许静宇
//     学号：	2018302060052
//   代码量：	583行
// 编译环境：	Visual Studio 2015 + EasyX_20190415(beta)
// 最后修改：	2019-6-12
// 实现功能：	发射子弹、销毁子弹、攻击虫子等
////////////////////////////////////////////////////////

#include "Bullet_Double.h"
Bullet_Double::Bullet_Double() :v(20)
{
	//B的子弹的初始化
	if(MouseHit())
	mouse = GetMouseMsg();
	mousex = mouse.x, mousey = mouse.y;
	const double a = -8.0 / 44.0;
	const double angle_1 = atan(a);
	xB = personB.getPersonPositionX() - sqrt(44*44+8*8)*sin(angle_1+personB.getRotateDegree());
	yB = personB.getPersonPositionY() - sqrt(44*44+8*8)*cos(angle_1+personB.getRotateDegree());
	vxB = v * (mousex - personB.getPersonPositionX()) / sqrt((mousex - personB.getPersonPositionX()) * (mousex - personB.getPersonPositionX()) + (mousey - personB.getPersonPositionY()) * (mousey - personB.getPersonPositionY()));
	vyB = v * (mousey - personB.getPersonPositionY()) / sqrt((mousex - personB.getPersonPositionX()) * (mousex - personB.getPersonPositionX()) + (mousey - personB.getPersonPositionY()) * (mousey - personB.getPersonPositionY()));
	//A的子弹的初始化
	xA = personA.getPersonPositionX() - sqrt(44 * 44 + 8 * 8) * sin(angle_1 + personA.getRotateDegree());
	yA = personA.getPersonPositionY() - sqrt(44 * 44 + 8 * 8) * cos(angle_1 + personA.getRotateDegree());
	vxA = -v * sin(personA.getRotateDegree());
	vyA = -v * cos(personA.getRotateDegree());
}

bool Bullet_Double::act_B()
{
	xB += int(vxB) * 1;
	yB += int(vyB) * 1;
	if (xB < 0 || xB>640 || yB < 0 || yB>480)
		return false;
	if (personB.getWeapon() == 'A')
	{
		for (int i = 0; i < banep; i++)
		{
			if (sqrt((xB - banelings[i]->x) * (xB - banelings[i]->x) + (yB - banelings[i]->y) * (yB - banelings[i]->y)) < 30)
			{
				banelings[i]->damaged(1);
				return false;
			}
		}
		for (int i = 0; i < hydrap; i++)
		{
			if (sqrt((xB - hydralisks[i]->x) * (xB - hydralisks[i]->x) + (yB - hydralisks[i]->y) * (yB - hydralisks[i]->y)) < 30)
			{
				hydralisks[i]->damaged(1);
				return false;
			}
		}
		for (int i = 0; i < rop; i++)
		{
			if (sqrt((xB - roachs[i]->x) * (xB - roachs[i]->x) + (yB - roachs[i]->y) * (yB - roachs[i]->y)) < 30)
			{
				roachs[i]->damaged(1);
				return false;
			}
		}
		for (int i = 0; i < zergp; i++)
		{
			if (sqrt((xB - zerglings[i]->x) * (xB - zerglings[i]->x) + (yB - zerglings[i]->y) * (yB - zerglings[i]->y)) < 30)
			{
				zerglings[i]->damaged(1);
				return false;
			}
		}
		for (int i = 0; i < spitp; i++)
		{
			if (sqrt((xB - hydraspits[i]->x) * (xB - hydraspits[i]->x) + (yB - hydraspits[i]->y) * (yB - hydraspits[i]->y)) < 30)
			{
				hydraspits[i]->damaged(1);
				return false;
			}
		}
		if (sqrt((xB - item.AgetOilTankPositionX()) * (xB - item.AgetOilTankPositionX()) + (yB - item.AgetOilTankPositionY()) * (yB - item.AgetOilTankPositionY())) < 30)
		{
			item.OilTankExplodeA();
			return false;
		}
		if (sqrt((xB - item.BgetOilTankPositionX()) * (xB - item.BgetOilTankPositionX()) + (yB - item.BgetOilTankPositionY()) * (yB - item.BgetOilTankPositionY())) < 30)
		{
			item.OilTankExplodeB();
			return false;
		}
	}
	if (personB.getWeapon() == 'B')
	{
		for (int i = 0; i < banep; i++)
		{
			if (sqrt((xB - banelings[i]->x) * (xB - banelings[i]->x) + (yB - banelings[i]->y) * (yB - banelings[i]->y)) < 80)
			{
				banelings[i]->damaged(1);
				return false;
			}
		}
		for (int i = 0; i < hydrap; i++)
		{
			if (sqrt((xB - hydralisks[i]->x) * (xB - hydralisks[i]->x) + (yB - hydralisks[i]->y) * (yB - hydralisks[i]->y)) < 80)
			{
				hydralisks[i]->damaged(1);
				return false;
			}
		}
		for (int i = 0; i < rop; i++)
		{
			if (sqrt((xB - roachs[i]->x) * (xB - roachs[i]->x) + (yB - roachs[i]->y) * (yB - roachs[i]->y)) < 80)
			{
				roachs[i]->damaged(1);
				return false;
			}
		}
		for (int i = 0; i < zergp; i++)
		{
			if (sqrt((xB - zerglings[i]->x) * (xB - zerglings[i]->x) + (yB - zerglings[i]->y) * (yB - zerglings[i]->y)) < 80)
			{
				zerglings[i]->damaged(1);
				return false;
			}
		}
		for (int i = 0; i < spitp; i++)
		{
			if (sqrt((xB - hydraspits[i]->x) * (xB - hydraspits[i]->x) + (yB - hydraspits[i]->y) * (yB - hydraspits[i]->y)) < 30)
			{
				hydraspits[i]->damaged(1);
				return false;
			}
		}
		if (sqrt((xB - item.AgetOilTankPositionX()) * (xB - item.AgetOilTankPositionX()) + (yB - item.AgetOilTankPositionY()) * (yB - item.AgetOilTankPositionY())) < 30)
		{
			item.OilTankExplodeA();
			return false;
		}
		if (sqrt((xB - item.BgetOilTankPositionX()) * (xB - item.BgetOilTankPositionX()) + (yB - item.BgetOilTankPositionY()) * (yB - item.BgetOilTankPositionY())) < 30)
		{
			item.OilTankExplodeB();
			return false;
		}
	}
	if (personB.getWeapon() == 'C')
	{
		for (int i = 0; i < banep; i++)
		{
			if (sqrt((xB - banelings[i]->x) * (xB - banelings[i]->x) + (yB - banelings[i]->y) * (yB - banelings[i]->y)) < 30)
			{
				banelings[i]->damaged(2);
				return false;
			}
		}
		for (int i = 0; i < hydrap; i++)
		{
			if (sqrt((xB - hydralisks[i]->x) * (xB - hydralisks[i]->x) + (yB - hydralisks[i]->y) * (yB - hydralisks[i]->y)) < 30)
			{
				hydralisks[i]->damaged(2);
				return false;
			}
		}
		for (int i = 0; i < rop; i++)
		{
			if (sqrt((xB - roachs[i]->x) * (xB - roachs[i]->x) + (yB - roachs[i]->y) * (yB - roachs[i]->y)) < 30)
			{
				roachs[i]->damaged(2);
				return false;
			}
		}
		for (int i = 0; i < zergp; i++)
		{
			if (sqrt((xB - zerglings[i]->x) * (xB - zerglings[i]->x) + (yB - zerglings[i]->y) * (yB - zerglings[i]->y)) < 30)
			{
				zerglings[i]->damaged(2);
				return false;
			}
		}
		for (int i = 0; i < spitp; i++)
		{
			if (sqrt((xB - hydraspits[i]->x) * (xB - hydraspits[i]->x) + (yB - hydraspits[i]->y) * (yB - hydraspits[i]->y)) < 30)
			{
				hydraspits[i]->damaged(2);
				return false;
			}
		}
		if (sqrt((xB - item.AgetOilTankPositionX()) * (xB - item.AgetOilTankPositionX()) + (yB - item.AgetOilTankPositionY()) * (yB - item.AgetOilTankPositionY())) < 30)
		{
			item.OilTankExplodeA();
			return false;
		}
		if (sqrt((xB - item.BgetOilTankPositionX()) * (xB - item.BgetOilTankPositionX()) + (yB - item.BgetOilTankPositionY()) * (yB - item.BgetOilTankPositionY())) < 30)
		{
			item.OilTankExplodeB();
			return false;
		}
	}
	if (personB.getWeapon() == 'D')
	{
		for (int i = 0; i < banep; i++)
		{
			if (sqrt((xB - banelings[i]->x) * (xB - banelings[i]->x) + (yB - banelings[i]->y) * (yB - banelings[i]->y)) < 80)
			{
				banelings[i]->damaged(2);
				return false;
			}
		}
		for (int i = 0; i < hydrap; i++)
		{
			if (sqrt((xB - hydralisks[i]->x) * (xB - hydralisks[i]->x) + (yB - hydralisks[i]->y) * (yB - hydralisks[i]->y)) < 80)
			{
				hydralisks[i]->damaged(2);
				return false;
			}
		}
		for (int i = 0; i < rop; i++)
		{
			if (sqrt((xB - roachs[i]->x) * (xB - roachs[i]->x) + (yB - roachs[i]->y) * (yB - roachs[i]->y)) < 80)
			{
				roachs[i]->damaged(2);
				return false;
			}
		}
		for (int i = 0; i < zergp; i++)
		{
			if (sqrt((xB - zerglings[i]->x) * (xB - zerglings[i]->x) + (yB - zerglings[i]->y) * (yB - zerglings[i]->y)) < 80)
			{
				zerglings[i]->damaged(2);
				return false;
			}
		}
		for (int i = 0; i < spitp; i++)
		{
			if (sqrt((xB - hydraspits[i]->x) * (xB - hydraspits[i]->x) + (yB - hydraspits[i]->y) * (yB - hydraspits[i]->y)) < 30)
			{
				hydraspits[i]->damaged(2);
				return false;
			}
		}
		if (sqrt((xB - item.AgetOilTankPositionX()) * (xB - item.AgetOilTankPositionX()) + (yB - item.AgetOilTankPositionY()) * (yB - item.AgetOilTankPositionY())) < 30)
		{
			item.OilTankExplodeA();
			return false;
		}
		if (sqrt((xB - item.BgetOilTankPositionX()) * (xB - item.BgetOilTankPositionX()) + (yB - item.BgetOilTankPositionY()) * (yB - item.BgetOilTankPositionY())) < 30)
		{
			item.OilTankExplodeB();
			return false;
		}
	}
	return true;
}
bool Bullet_Double::act_A()
{
		xA += int(vxA) * 1;
		yA += int(vyA) * 1;
		if (xA < 0 || xA>640 || yA < 0 || yA>480)
			return false;
		if (personA.getWeapon() == 'A')
		{
			for (int i = 0; i < banep; i++)
			{
				if (sqrt((xA - banelings[i]->x) * (xA - banelings[i]->x) + (yA - banelings[i]->y) * (yA - banelings[i]->y)) < 30)
				{
					banelings[i]->damaged(1);
					return false;
				}
			}
			for (int i = 0; i < hydrap; i++)
			{
				if (sqrt((xA - hydralisks[i]->x) * (xA - hydralisks[i]->x) + (yA - hydralisks[i]->y) * (yA - hydralisks[i]->y)) < 30)
				{
					hydralisks[i]->damaged(1);
					return false;
				}
			}
			for (int i = 0; i < rop; i++)
			{
				if (sqrt((xA - roachs[i]->x) * (xA - roachs[i]->x) + (yA - roachs[i]->y) * (yA - roachs[i]->y)) < 30)
				{
					roachs[i]->damaged(1);
					return false;
				}
			}
			for (int i = 0; i < zergp; i++)
			{
				if (sqrt((xA - zerglings[i]->x) * (xA - zerglings[i]->x) + (yA - zerglings[i]->y) * (yA - zerglings[i]->y)) < 30)
				{
					zerglings[i]->damaged(1);
					return false;
				}
			}
			for (int i = 0; i < spitp; i++)
			{
				if (sqrt((xA - hydraspits[i]->x) * (xA - hydraspits[i]->x) + (yA - hydraspits[i]->y) * (yA - hydraspits[i]->y)) < 30)
				{
					hydraspits[i]->damaged(1);
					return false;
				}
			}
			if (sqrt((xA - item.AgetOilTankPositionX()) * (xA - item.AgetOilTankPositionX()) + (yA - item.AgetOilTankPositionY()) * (yA - item.AgetOilTankPositionY())) < 30)
			{
				item.OilTankExplodeA();
				return false;
			}
			if (sqrt((xA - item.BgetOilTankPositionX()) * (xA - item.BgetOilTankPositionX()) + (yA - item.BgetOilTankPositionY()) * (yA - item.BgetOilTankPositionY())) < 30)
			{
				item.OilTankExplodeB();
				return false;
			}
		}
		if (personA.getWeapon() == 'B')
		{
			for (int i = 0; i < banep; i++)
			{
				if (sqrt((xA - banelings[i]->x) * (xA - banelings[i]->x) + (yA - banelings[i]->y) * (yA - banelings[i]->y)) < 80)
				{
					banelings[i]->damaged(1);
					return false;
				}
			}
			for (int i = 0; i < hydrap; i++)
			{
				if (sqrt((xA - hydralisks[i]->x) * (xA - hydralisks[i]->x) + (yA - hydralisks[i]->y) * (yA - hydralisks[i]->y)) < 80)
				{
					hydralisks[i]->damaged(1);
					return false;
				}
			}
			for (int i = 0; i < rop; i++)
			{
				if (sqrt((xA - roachs[i]->x) * (xA - roachs[i]->x) + (yA - roachs[i]->y) * (yA - roachs[i]->y)) < 80)
				{
					roachs[i]->damaged(1);
					return false;
				}
			}
			for (int i = 0; i < zergp; i++)
			{
				if (sqrt((xA - zerglings[i]->x) * (xA - zerglings[i]->x) + (yA - zerglings[i]->y) * (yA - zerglings[i]->y)) < 80)
				{
					zerglings[i]->damaged(1);
					return false;
				}
			}
			for (int i = 0; i < spitp; i++)
			{
				if (sqrt((xA - hydraspits[i]->x) * (xA - hydraspits[i]->x) + (yA - hydraspits[i]->y) * (yA - hydraspits[i]->y)) < 30)
				{
					hydraspits[i]->damaged(1);
					return false;
				}
			}
			if (sqrt((xA - item.AgetOilTankPositionX()) * (xA - item.AgetOilTankPositionX()) + (yA - item.AgetOilTankPositionY()) * (yA - item.AgetOilTankPositionY())) < 30)
			{
				item.OilTankExplodeA();
				return false;
			}
			if (sqrt((xA - item.BgetOilTankPositionX()) * (xA - item.BgetOilTankPositionX()) + (yA - item.BgetOilTankPositionY()) * (yA - item.BgetOilTankPositionY())) < 30)
			{
				item.OilTankExplodeB();
				return false;
			}
		}
		if (personA.getWeapon() == 'C')
		{
			for (int i = 0; i < banep; i++)
			{
				if (sqrt((xA - banelings[i]->x) * (xA - banelings[i]->x) + (yA - banelings[i]->y) * (yA - banelings[i]->y)) < 30)
				{
					banelings[i]->damaged(2);
					return false;
				}
			}
			for (int i = 0; i < hydrap; i++)
			{
				if (sqrt((xA - hydralisks[i]->x) * (xA - hydralisks[i]->x) + (yA - hydralisks[i]->y) * (yA - hydralisks[i]->y)) < 30)
				{
					hydralisks[i]->damaged(2);
					return false;
				}
			}
			for (int i = 0; i < rop; i++)
			{
				if (sqrt((xA - roachs[i]->x) * (xA - roachs[i]->x) + (yA - roachs[i]->y) * (yA - roachs[i]->y)) < 30)
				{
					roachs[i]->damaged(2);
					return false;
				}
			}
			for (int i = 0; i < zergp; i++)
			{
				if (sqrt((xA - zerglings[i]->x) * (xA - zerglings[i]->x) + (yA - zerglings[i]->y) * (yA - zerglings[i]->y)) < 30)
				{
					zerglings[i]->damaged(2);
					return false;
				}
			}
			for (int i = 0; i < spitp; i++)
			{
				if (sqrt((xA - hydraspits[i]->x) * (xA - hydraspits[i]->x) + (yA - hydraspits[i]->y) * (yA - hydraspits[i]->y)) < 30)
				{
					hydraspits[i]->damaged(2);
					return false;
				}
			}
			if (sqrt((xA - item.AgetOilTankPositionX()) * (xA - item.AgetOilTankPositionX()) + (yA - item.AgetOilTankPositionY()) * (yA - item.AgetOilTankPositionY())) < 30)
			{
				item.OilTankExplodeA();
				return false;
			}
			if (sqrt((xA - item.BgetOilTankPositionX()) * (xA - item.BgetOilTankPositionX()) + (yA - item.BgetOilTankPositionY()) * (yA - item.BgetOilTankPositionY())) < 30)
			{
				item.OilTankExplodeB();
				return false;
			}
		}
		if (personA.getWeapon() == 'D')
		{
			for (int i = 0; i < banep; i++)
			{
				if (sqrt((xA - banelings[i]->x) * (xA - banelings[i]->x) + (yA - banelings[i]->y) * (yA - banelings[i]->y)) < 80)
				{
					banelings[i]->damaged(2);
					return false;
				}
			}
			for (int i = 0; i < hydrap; i++)
			{
				if (sqrt((xA - hydralisks[i]->x) * (xA - hydralisks[i]->x) + (yA - hydralisks[i]->y) * (yA - hydralisks[i]->y)) < 80)
				{
					hydralisks[i]->damaged(2);
					return false;
				}
			}
			for (int i = 0; i < rop; i++)
			{
				if (sqrt((xA - roachs[i]->x) * (xA - roachs[i]->x) + (yA - roachs[i]->y) * (yA - roachs[i]->y)) < 80)
				{
					roachs[i]->damaged(2);
					return false;
				}
			}
			for (int i = 0; i < zergp; i++)
			{
				if (sqrt((xA - zerglings[i]->x) * (xA - zerglings[i]->x) + (yA - zerglings[i]->y) * (yA - zerglings[i]->y)) < 80)
				{
					zerglings[i]->damaged(2);
					return false;
				}
			}
			for (int i = 0; i < spitp; i++)
			{
				if (sqrt((xA - hydraspits[i]->x) * (xA - hydraspits[i]->x) + (yA - hydraspits[i]->y) * (yA - hydraspits[i]->y)) < 30)
				{
					hydraspits[i]->damaged(2);
					return false;
				}
			}
			if (sqrt((xA - item.AgetOilTankPositionX()) * (xA - item.AgetOilTankPositionX()) + (yA - item.AgetOilTankPositionY()) * (yA - item.AgetOilTankPositionY())) < 30)
			{
				item.OilTankExplodeA();
				return false;
			}
			if (sqrt((xA - item.BgetOilTankPositionX()) * (xA - item.BgetOilTankPositionX()) + (yA - item.BgetOilTankPositionY()) * (yA - item.BgetOilTankPositionY())) < 30)
			{
				item.OilTankExplodeB();
				return false;
			}
		}
		return true;
}

void Bullet_Double::draw()
{
	if (personA.getPlayer() == 'A'&&(GetAsyncKeyState('F')&0x8000)&&personA.getHealthPoint()>=0)
	{
		switch (personA.getWeapon())
		{
		case 'A': setfillcolor(YELLOW); break;
		case 'B': setfillcolor(BLUE); break;
		case 'C': setfillcolor(RED); break;
		case 'D': setfillcolor(WHITE); break;
		default: break;
		}
		if (!(personA.getWeapon() == 'O'))
			solidcircle(xA, yA, 3);
	}
	if (personB.getPlayer() == 'B'&&mouse.mkLButton&&personB.getHealthPoint() >= 0)
	{
		switch (personB.getWeapon())
		{
		case 'A': setfillcolor(YELLOW); break;
		case 'B': setfillcolor(BLUE); break;
		case 'C': setfillcolor(RED); break;
		case 'D': setfillcolor(WHITE); break;
		default: break;
		}
		if (!(personB.getWeapon() == 'O'))
			solidcircle(xB, yB, 3);
	}
}

//A攻击
void fire_DoubleA()
{
	double degree[8] = { 0.0,PI,PI / 2.0, -PI / 2,PI / 4,-PI / 4,3 * PI / 4,-3 * PI / 4 };
	int attackGap[8] = { 0,0,0,0,0,0,0,0 };
	if (GetAsyncKeyState('F') & 0x8000)
	{
		for (int i = 0; i <= 7; i++)
		{
			if (attackGap[i] <= 0 && (fabs(personA.getRotateDegree() - degree[i]) <= 0.001) && !(personA.getWeapon() == 'O'))
			{
				addBullet_DoubleA(new Bullet_Double);    //开火
				attackGap[i] = 2;
			}
			else
				attackGap[i]--;
		}
	}
}

//添加A子弹
bool addBullet_DoubleA(Bullet_Double *p)
{
	if (bp_DoubleA>20) return false;
	bullets_DoubleA[bp_DoubleA] = p;
	bp_DoubleA++;
	return true;
}

//删除A子弹
bool deleteBullet_DoubleA(Bullet_Double *p)
{
	int i = 0;
	for (i = 0; i<bp_DoubleA; i++)
		if (p == bullets_DoubleA[i]) break;
	if (i == bp_DoubleA) return false;
	delete p;
	p = nullptr;
	for (; i<bp_DoubleA - 1; i++)
		bullets_DoubleA[i] = bullets_DoubleA[i + 1];
	bp_DoubleA--;
	return true;
}

//B攻击
void fire_DoubleB()
{
	int attackGap = 0;
	if (MouseHit())
	{
		mouse = GetMouseMsg();
		if (attackGap == 0 && mouse.mkLButton && !(personB.getWeapon() == 'O'))
		{
			addBullet_DoubleB(new Bullet_Double);    //开火
			attackGap = 2;
		}
		else
			attackGap--;
	}
}

//添加B子弹
bool addBullet_DoubleB(Bullet_Double *p)
{
	if (bp_DoubleB>20) return false;
	bullets_DoubleB[bp_DoubleB] = p;
	bp_DoubleB++;
	return true;
}

//删除B子弹
bool deleteBullet_DoubleB(Bullet_Double *p)
{
	int i = 0;
	for (i = 0; i<bp_DoubleB; i++)
		if (p == bullets_DoubleB[i]) break;
	if (i == bp_DoubleB) return false;
	delete p;
	p = nullptr;
	for (; i<bp_DoubleB - 1; i++)
		bullets_DoubleB[i] = bullets_DoubleB[i + 1];
	bp_DoubleB--;
	return true;
}

void deleteAllBullets_Double()
{
	for (int i = 0; i < bp_DoubleA; i++)
		deleteBullet_DoubleA(bullets_DoubleA[0]);
	for (int i = 0; i < bp_DoubleB; i++)
		deleteBullet_DoubleB(bullets_DoubleB[0]);
}