#pragma once
#include<iostream>
#include<conio.h>
#include<ctime>
#include<cassert>
#include<vector>

using namespace std;

////各种宏
//ESC的ASCII
#define ESC_ASC 27
//方向键的前字符ASCII
#define DIRECTION_ASC 224
//方向键后字符ASCII
#define UP_ASC 72
#define DOWN_ASC 80
#define LEFT_ASC 75
#define RIGHT_ASC 77

//游戏公共事件的枚举类
enum class STATE
{
	//游戏结束事件
	GAME_OVER = 0,
	//方向操作事件
	UP, DOWN, LEFT, RIGHT,
	//游戏退出事件
	ESCAPE
};