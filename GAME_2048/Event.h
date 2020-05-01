/*******************
*Event:
*能够存储游戏中的事件消息，
*不关心接收方与发送方，
*只关心消息本身的内容
*起到解耦的作用
********************/
#pragma once
#include"total.h"

class Event //  
{
public:

	//  由键盘事件获取消息
	void CheckKeyEvent()
	{

		////先遍历一次消息队列
		for (auto it = state.begin(); it != state.end(); it++)
		{
			////如果包含游戏结束的消息
			if (*it == STATE::GAME_OVER)
			{
				////清空
				state.clear();

				////压入 游戏结束的消息
				state.push_back(STATE::GAME_OVER);

				////检测游戏退出的按键
				while (_kbhit() and _getch() == ESC_ASC)
					state.push_back(STATE::ESCAPE);

				////之所以弄这么麻烦不直接退出游戏，是为了避免功能耦合
				//要保证Event只关心消息
				//而不能控制游戏
				//控制游戏是由其他对象，截获消息再进行操作
				return;
			}
		}

		////清空消息队列
		state.clear();

		////获取键盘事件
		//_kbhit()方法是C提供的键盘按下检测
		while (_kbhit()) {
			////  _getch()方法是获取一个字符输入，返回ASCII码
			int Key1 = _getch(); 

			//ESC键被按下：
			if (Key1 == ESC_ASC)
			{
				////push_back是vector的方法，用于从数组末端新建数据元素
				state.push_back(STATE::ESCAPE);
			}

			//某个方向键被按下：
			if (Key1 == DIRECTION_ASC)
			{
				//方向键是由 '\224' 和 另一个字符组成的“双字符型”字符
				//因此检测第二次输入的字符
				int Key2 = _getch();
				switch (Key2) {
				case UP_ASC: state.push_back(STATE::UP); break;
				case DOWN_ASC: state.push_back(STATE::DOWN); break;
				case LEFT_ASC: state.push_back(STATE::LEFT); break;
				case RIGHT_ASC: state.push_back(STATE::RIGHT); break;
				}
			}
		}
	}

	//原本应该有的push和get方法（公有），游戏对象能够发送消息
	//但本游戏几乎不需要，因此省略
	/*
	void pushEvent(){
		//code here
	}
	vector<STATE> getEvent()const{
		//code here
	}
	*/

	////使用vector容器搭建的数组，作为消息队列:
	vector<STATE>state;

};

