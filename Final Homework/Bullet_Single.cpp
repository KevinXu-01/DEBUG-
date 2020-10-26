///////////////////////////////////////////////////////
// 文件名称：   Bullet_Single.cpp
//   负责人：	许静宇
//     学号：	2018302060052
//   代码量：	275行
// 编译环境：   Visual Studio 2015 + EasyX_20190415(beta)
// 最后修改：   2019-6-12
// 实现功能：   发射子弹、销毁子弹、攻击虫子等
////////////////////////////////////////////////////////

#include "Bullet_Single.h"
Bullet_Single::Bullet_Single():v(20)
{
	if (MouseHit())
		mouse = GetMouseMsg();
	mousex = mouse.x, mousey = mouse.y;
	const double a = -8.0 / 44.0;
	const double angle_1 = atan(a);
	x = personA.getPersonPositionX() - sqrt(44 * 44 + 8 * 8)*sin(angle_1 + personA.getRotateDegree());
	y = personA.getPersonPositionY() - sqrt(44 * 44 + 8 * 8)*cos(angle_1 + personA.getRotateDegree());
	vx = v * (mousex - personA.getPersonPositionX()) / sqrt((mousex - personA.getPersonPositionX()) * (mousex - personA.getPersonPositionX()) + (mousey - personA.getPersonPositionY()) * (mousey - personA.getPersonPositionY()));
	vy = v * (mousey - personA.getPersonPositionY()) / sqrt((mousex - personA.getPersonPositionX()) * (mousex - personA.getPersonPositionX()) + (mousey - personA.getPersonPositionY()) * (mousey - personA.getPersonPositionY()));
}

bool Bullet_Single::act()
{
	x += int(vx) * 1;
	y += int(vy) * 1;
	if (x < 0 || x>640 || y < 0 || y>480)
		return false;
	if (personA.getWeapon() == 'A')
	{
		for (int i = 0; i < banep; i++)
		{
			if (sqrt((x - banelings[i]->x) * (x - banelings[i]->x) + (y - banelings[i]->y) * (y - banelings[i]->y)) < 30)
			{
				banelings[i]->damaged(1);
				return false;
			}
		}
		for (int i = 0; i < hydrap; i++)
		{
			if (sqrt((x - hydralisks[i]->x) * (x - hydralisks[i]->x) + (y - hydralisks[i]->y) * (y - hydralisks[i]->y)) < 30)
			{
				hydralisks[i]->damaged(1);
				return false;
			}
		}
		for (int i = 0; i < rop; i++)
		{
			if (sqrt((x - roachs[i]->x) * (x - roachs[i]->x) + (y - roachs[i]->y) * (y - roachs[i]->y)) < 30)
			{
				roachs[i]->damaged(1);
				return false;
			}
		}
		for (int i = 0; i < zergp; i++)
		{
			if (sqrt((x - zerglings[i]->x) * (x - zerglings[i]->x) + (y - zerglings[i]->y) * (y - zerglings[i]->y)) < 30)
			{
				zerglings[i]->damaged(1);
				return false;
			}
		}
		for (int i = 0; i < spitp; i++)
		{
			if (sqrt((x - hydraspits[i]->x) * (x - hydraspits[i]->x) + (y - hydraspits[i]->y) * (y - hydraspits[i]->y)) < 30)
			{
				hydraspits[i]->damaged(1);
				return false;
			}
		}
		if (sqrt((x - item.AgetOilTankPositionX()) * (x - item.AgetOilTankPositionX()) + (y - item.AgetOilTankPositionY()) * (y - item.AgetOilTankPositionY())) < 30)
		{
			item.OilTankExplodeA();
			return false;
		}
	}
	if(personA.getWeapon()=='B')
	{
		for (int i = 0; i < banep; i++)
		{
			if (sqrt((x - banelings[i]->x) * (x - banelings[i]->x) + (y - banelings[i]->y) * (y - banelings[i]->y)) < 80)
			{
				banelings[i]->damaged(1);
				return false;
			}
		}
		for (int i = 0; i < hydrap; i++)
		{
			if (sqrt((x - hydralisks[i]->x) * (x - hydralisks[i]->x) + (y - hydralisks[i]->y) * (y - hydralisks[i]->y)) < 80)
			{
				hydralisks[i]->damaged(1);
				return false;
			}
		}
		for (int i = 0; i < rop; i++)
		{
			if (sqrt((x - roachs[i]->x) * (x - roachs[i]->x) + (y - roachs[i]->y) * (y - roachs[i]->y)) < 80)
			{
				roachs[i]->damaged(1);
				return false;
			}
		}
		for (int i = 0; i < zergp; i++)
		{
			if (sqrt((x - zerglings[i]->x) * (x - zerglings[i]->x) + (y - zerglings[i]->y) * (y - zerglings[i]->y)) < 80)
			{
				zerglings[i]->damaged(1);
				return false;
			}
		}
		for (int i = 0; i < spitp; i++)
		{
			if (sqrt((x - hydraspits[i]->x) * (x - hydraspits[i]->x) + (y - hydraspits[i]->y) * (y - hydraspits[i]->y)) < 30)
			{
				hydraspits[i]->damaged(1);
				return false;
			}
		}
		if (sqrt((x - item.AgetOilTankPositionX()) * (x - item.AgetOilTankPositionX()) + (y - item.AgetOilTankPositionY()) * (y - item.AgetOilTankPositionY())) < 30)
		{
			item.OilTankExplodeA();
			return false;
		}
	}
	if (personA.getWeapon() == 'C')
	{
		for (int i = 0; i < banep; i++)
		{
			if (sqrt((x - banelings[i]->x) * (x - banelings[i]->x) + (y - banelings[i]->y) * (y - banelings[i]->y)) < 30)
			{
				banelings[i]->damaged(2);
				return false;
			}
		}
		for (int i = 0; i < hydrap; i++)
		{
			if (sqrt((x - hydralisks[i]->x) * (x - hydralisks[i]->x) + (y - hydralisks[i]->y) * (y - hydralisks[i]->y)) < 30)
			{
				hydralisks[i]->damaged(2);
				return false;
			}
		}
		for (int i = 0; i < rop; i++)
		{
			if (sqrt((x - roachs[i]->x) * (x - roachs[i]->x) + (y - roachs[i]->y) * (y - roachs[i]->y)) < 30)
			{
				roachs[i]->damaged(2);
				return false;
			}
		}
		for (int i = 0; i < zergp; i++)
		{
			if (sqrt((x - zerglings[i]->x) * (x - zerglings[i]->x) + (y - zerglings[i]->y) * (y - zerglings[i]->y)) < 30)
			{
				zerglings[i]->damaged(2);
				return false;
			}
		}
		for (int i = 0; i < spitp; i++)
		{
			if (sqrt((x - hydraspits[i]->x) * (x - hydraspits[i]->x) + (y - hydraspits[i]->y) * (y - hydraspits[i]->y)) < 30)
			{
				hydraspits[i]->damaged(2);
				return false;
			}
		}
		if (sqrt((x - item.AgetOilTankPositionX()) * (x - item.AgetOilTankPositionX()) + (y - item.AgetOilTankPositionY()) * (y - item.AgetOilTankPositionY())) < 30)
		{
			item.OilTankExplodeA();
			return false;
		}
	}
	if (personA.getWeapon() == 'D')
	{
		for (int i = 0; i < banep; i++)
		{
			if (sqrt((x - banelings[i]->x) * (x - banelings[i]->x) + (y - banelings[i]->y) * (y - banelings[i]->y)) < 80)
			{
				banelings[i]->damaged(2);
				return false;
			}
		}
		for (int i = 0; i < hydrap; i++)
		{
			if (sqrt((x - hydralisks[i]->x) * (x - hydralisks[i]->x) + (y - hydralisks[i]->y) * (y - hydralisks[i]->y)) < 80)
			{
				hydralisks[i]->damaged(2);
				return false;
			}
		}
		for (int i = 0; i < rop; i++)
		{
			if (sqrt((x - roachs[i]->x) * (x - roachs[i]->x) + (y - roachs[i]->y) * (y - roachs[i]->y)) < 80)
			{
				roachs[i]->damaged(2);
				return false;
			}
		}
		for (int i = 0; i < zergp; i++)
		{
			if (sqrt((x - zerglings[i]->x) * (x - zerglings[i]->x) + (y - zerglings[i]->y) * (y - zerglings[i]->y)) < 80)
			{
				zerglings[i]->damaged(2);
				return false;
			}
		}
		for (int i = 0; i < spitp; i++)
		{
			if (sqrt((x - hydraspits[i]->x) * (x - hydraspits[i]->x) + (y - hydraspits[i]->y) * (y - hydraspits[i]->y)) < 30)
			{
				hydraspits[i]->damaged(2);
				return false;
			}
		}
		if (sqrt((x - item.AgetOilTankPositionX()) * (x - item.AgetOilTankPositionX()) + (y - item.AgetOilTankPositionY()) * (y - item.AgetOilTankPositionY())) < 30)
		{
			item.OilTankExplodeA();
			return false;
		}
	}
	return true;
}

void Bullet_Single::draw()
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
		solidcircle(x, y, 3);
}

//添加子弹
bool addBullet_Single(Bullet_Single *p)
{
	if (bp_Single>20) return false;
	bullets_Single[bp_Single] = p;
	bp_Single++;
	return true;
}

//删除子弹
bool deleteBullet_Single(Bullet_Single *p)
{
	int i = 0;
	for (i = 0; i<bp_Single; i++)
		if (p == bullets_Single[i]) break;
	if (i == bp_Single) return false;
	delete p;
	p = nullptr;
	for (; i<bp_Single - 1; i++)
		bullets_Single[i] = bullets_Single[i + 1];
	bp_Single--;
	return true;
}

void fire_Single()
{
	int attackGap = 0;
	if (MouseHit())
	{
		mouse = GetMouseMsg();
		if (attackGap == 0 && mouse.mkLButton && !(personA.getWeapon() == 'O'))
		{
			addBullet_Single(new Bullet_Single);    //开火
			attackGap = 2;
		}
		else
			attackGap--;
	}
}

void deleteAllBullets_Single()
{
	for (int i = 0; i < bp_Single; i++)
		deleteBullet_Single(bullets_Single[0]);
}