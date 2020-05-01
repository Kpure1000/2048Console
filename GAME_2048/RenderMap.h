/*******************
*RenderMap:
*游戏主窗口控制类
********************/
#pragma once
#include"Map.h"
#include"Event.h"
class RenderMap
{
public:
	//构造游戏窗口（这里只是假设有一个窗口）
	RenderMap()
		:StartTime(0), FPS(0), FrameTime(0),
		isOpening(true), isGameOver(false), isMoved(true)
	{
		StartTime = clock();
	}
public:

	//清空画面
	void clear()
	{
		//如果游戏退出、游戏结束、没有操作，不需要刷新
		if (isOpen() == false or isGameOver == true or isMoved == false)
			return;
		system("cls");
	}

	//渲染
	void draw(Map const& map) //  Map
	{
		//如果游戏退出、游戏结束、没有操作，不需要渲染
		if (isOpen() == false or isGameOver == true or isMoved == false)
			return;
		map.Draw();
	}

	//控制
	void display()
	{
		//如果游戏退出，不需要控制
		if (isOpen() == false)return;
		//帧率控制
		while (clock() - StartTime < FrameTime)
			;
		StartTime = clock();
		//确保每次游戏循环结束，操作判断被刷新为未操作
		isMoved = false;
	}

	//设置帧率
	void SetFPS(int const& fps)
	{
		FPS = fps;
		if (FPS > 0)
			FrameTime = (time_t)(1000.0 * static_cast<double>(1.0 / FPS));
	}

	//获取事件
	void PushEvent(Event const& ev)
	{
		for (auto it = ev.state.begin(); it != ev.state.end(); it++)
		{
			switch (*it)
			{
			////游戏退出
			case STATE::ESCAPE: 
				this->exit();
				break;
			////游戏结束
			//注意，游戏结束并不会直接退出游戏
			case STATE::GAME_OVER: 
				//而是通过消息等待退出按钮（ESC）被按下，再退出
				//这也是为了解耦
				if (isGameOver == false)
					GameOver();
				break;
			////检测到键盘事件，isMoved设置为有操作
			case STATE::UP:
				this; isMoved = true; 
				break;
			case STATE::DOWN:
				this; isMoved = true; 
				break;
			case STATE::LEFT:
				this; isMoved = true; 
				break;
			case STATE::RIGHT:
				this; isMoved = true; 
				break;
			}
		}
	}

	//窗口是否为打开状态
	bool isOpen()const { return isOpening; }

private:

	//退出游戏
	void exit() { isOpening = false; }

	//游戏结束
	void GameOver()
	{
		isGameOver = true;
		cout << "Game Over!\npress Esc to quit..." << endl;
	}

private:
	//是否打开
	bool isOpening;

	//是否结束
	bool isGameOver;

	//是否操作了矩阵
	bool isMoved;

	//每一帧的开始事件
	time_t StartTime;

	//帧率
	int FPS;

	//帧间间隔
	time_t FrameTime;
};

