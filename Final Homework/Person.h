///////////////////////////////////////////////////////
// �ļ����ƣ�	Person.h
//   �����ˣ�	������
//     ѧ�ţ�	2018302060043
//   ��������	45��
// ���뻷����	Visual Studio 2015 + EasyX_20180321(���ְ�) 
// ����޸ģ�	2019-6-12
// ʵ�ֹ��ܣ�	����������
////////////////////////////////////////////////////////
#pragma once

//������
class Person	
{
public:
	Person();											//���캯��
	~Person();											//��������
	void setPlayer(char p);								//����������ţ�������ţ�
	void setHealthPoint(int initHP, int limHP);			//��������ֵ����ʼ����ֵ����������ֵ��
	void setPersonPosition(int x, int y);				//�����˵�λ��(x���꣬y���꣩
	void setSpeed(int s);								//�����ƶ��ٶȣ��ƶ��ٶȣ�
	void setControl();									//����������ݷ�ʽ
	void setWeapon(char w);								//�����������ͣ��������ţ�
	void showPerson();									//��ʾ����
	int getHealthPoint();								//��ȡ�˵�����ֵ
	int getPersonPositionX();							//��ȡ�˵�λ��x����
	int getPersonPositionY();							//��ȡ�˵�λ��y����
	int getSpeed();										//��ȡ�˵��ٶ�
	int getLimHealthPoint();							//��ȡ�˵��������ֵ
	int getReviveTime();								//��ȡ����ʱ��
	int getPersonDirection();							//��ȡ�˵ķ���
	double getRotateDegree();							//��ȡ�˵���ת�Ƕ�
	char getPlayer();									//��ȡ�������
	char getWeapon();									//��ȡ��������
	static int getCoins();								//��ȡ��ǰ�������
	static void pickCoins();							//ʰȡ���
	static void spendCoins(int m);						//������ѣ�ʹ�ý��������
	void getHit();										//�ܵ��˺�
	void getHelp();										//��Ѫ
	void personRevive();								//���︴��
	friend void imageProcess(Person &p,int w,int l);	//����ͼ�����������ã��زı�ţ��Ƿ�������
private:
	int limitedHP;					//��������ֵ
	int healthPoint;				//��ǰ����ֵ
	int reviveTime;					//����ʱ��
	int personPositionX;			//�˵�λ��x����
	int personPositionY;			//�˵�λ��y����
	double rotateDegree ;			//������ת�Ƕ�
	int personDirection ;			//���﷽��
	int speed;						//�ƶ��ٶ�
	char player;					//�������
	char weapon;					//��������
	static int numOfCoins;			//����ʰȡ��ҵ�����
};	