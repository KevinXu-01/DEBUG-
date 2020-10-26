///////////////////////////////////////////////////////
// 文件名称：	Person.h
//   负责人：	范承祥
//     学号：	2018302060043
//   代码量：	45行
// 编译环境：	Visual Studio 2015 + EasyX_20180321(春分版) 
// 最后修改：	2019-6-12
// 实现功能：	人物类声明
////////////////////////////////////////////////////////
#pragma once

//定义类
class Person	
{
public:
	Person();											//构造函数
	~Person();											//析构函数
	void setPlayer(char p);								//设置人物代号（人物代号）
	void setHealthPoint(int initHP, int limHP);			//设置生命值（初始生命值，上限生命值）
	void setPersonPosition(int x, int y);				//设置人的位置(x坐标，y坐标）
	void setSpeed(int s);								//设置移动速度（移动速度）
	void setControl();									//设置人物操纵方式
	void setWeapon(char w);								//设置武器类型（武器代号）
	void showPerson();									//显示人物
	int getHealthPoint();								//获取人的生命值
	int getPersonPositionX();							//获取人的位置x坐标
	int getPersonPositionY();							//获取人的位置y坐标
	int getSpeed();										//获取人的速度
	int getLimHealthPoint();							//获取人的最大生命值
	int getReviveTime();								//获取复活时间
	int getPersonDirection();							//获取人的方向
	double getRotateDegree();							//获取人的旋转角度
	char getPlayer();									//获取人物代号
	char getWeapon();									//获取武器类型
	static int getCoins();								//获取当前金币数量
	static void pickCoins();							//拾取金币
	static void spendCoins(int m);						//金币消费（使用金币数量）
	void getHit();										//受到伤害
	void getHelp();										//回血
	void personRevive();								//人物复活
	friend void imageProcess(Person &p,int w,int l);	//人物图像处理（对象引用，素材标号，是否死亡）
private:
	int limitedHP;					//上限生命值
	int healthPoint;				//当前生命值
	int reviveTime;					//复活时间
	int personPositionX;			//人的位置x坐标
	int personPositionY;			//人的位置y坐标
	double rotateDegree ;			//人物旋转角度
	int personDirection ;			//人物方向
	int speed;						//移动速度
	char player;					//人物代号
	char weapon;					//武器种类
	static int numOfCoins;			//人物拾取金币的总数
};	