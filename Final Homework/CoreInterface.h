///////////////////////////////////////////////////////
// �ļ����ƣ�	CoreInterface.h
//   �����ˣ�	����
//     ѧ�ţ�	2018302060052
//   ��������	26��
// ���뻷����	Visual Studio 2015 + EasyX_20190415(beta)
// ����޸ģ�	2019-6-12
// ʵ�ֹ��ܣ�	�Ժ�����������
////////////////////////////////////////////////////////

#pragma once
#include<easyx.h>
#include"conio.h"
#include"graphics.h"
#include <windows.h>
#include <mmsystem.h>
#include <stdio.h>
#pragma comment(lib, "WINMM.LIB")

void showMap();
void showInfo_init_single();
void showInfo_init_double();
void showStore();
void showButtons();
void reshowInfo_playerA_hp();//���A������ֵ�ӿ�
void reshowInfo_playerB_hp();//���B������ֵ�ӿ�
void reshowInfo_score();//�����ӿ�
void reshowInfo_coin_single();//����ģʽ�Ľ�ҽӿ�
void reshowInfo_coin_double();//˫��ģʽ�Ľ�ҽӿ�
bool ExtractResource(LPCTSTR strDstFile, LPCTSTR strResType, LPCTSTR strResName);
void playMusic();
void CoreInterface_main_single();//����ģʽ
void CoreInterface_main_double();//˫��ģʽ
void CoreInterface_main(int mode);//���Ը���Ŀǰ��mode���ж�
void showInfo_init(int mode);
void reshowInfo_coin(int mode);