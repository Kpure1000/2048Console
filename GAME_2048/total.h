#pragma once
#include<iostream>
#include<conio.h>
#include<ctime>
#include<cassert>
#include<vector>

using namespace std;

////���ֺ�
//ESC��ASCII
#define ESC_ASC 27
//�������ǰ�ַ�ASCII
#define DIRECTION_ASC 224
//��������ַ�ASCII
#define UP_ASC 72
#define DOWN_ASC 80
#define LEFT_ASC 75
#define RIGHT_ASC 77

//��Ϸ�����¼���ö����
enum class STATE
{
	//��Ϸ�����¼�
	GAME_OVER = 0,
	//��������¼�
	UP, DOWN, LEFT, RIGHT,
	//��Ϸ�˳��¼�
	ESCAPE
};