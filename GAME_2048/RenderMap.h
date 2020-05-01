/*******************
*RenderMap:
*��Ϸ�����ڿ�����
********************/
#pragma once
#include"Map.h"
#include"Event.h"
class RenderMap
{
public:
	//������Ϸ���ڣ�����ֻ�Ǽ�����һ�����ڣ�
	RenderMap()
		:StartTime(0), FPS(0), FrameTime(0),
		isOpening(true), isGameOver(false), isMoved(true)
	{
		StartTime = clock();
	}
public:

	//��ջ���
	void clear()
	{
		//�����Ϸ�˳�����Ϸ������û�в���������Ҫˢ��
		if (isOpen() == false or isGameOver == true or isMoved == false)
			return;
		system("cls");
	}

	//��Ⱦ
	void draw(Map const& map) //  Map
	{
		//�����Ϸ�˳�����Ϸ������û�в���������Ҫ��Ⱦ
		if (isOpen() == false or isGameOver == true or isMoved == false)
			return;
		map.Draw();
	}

	//����
	void display()
	{
		//�����Ϸ�˳�������Ҫ����
		if (isOpen() == false)return;
		//֡�ʿ���
		while (clock() - StartTime < FrameTime)
			;
		StartTime = clock();
		//ȷ��ÿ����Ϸѭ�������������жϱ�ˢ��Ϊδ����
		isMoved = false;
	}

	//����֡��
	void SetFPS(int const& fps)
	{
		FPS = fps;
		if (FPS > 0)
			FrameTime = (time_t)(1000.0 * static_cast<double>(1.0 / FPS));
	}

	//��ȡ�¼�
	void PushEvent(Event const& ev)
	{
		for (auto it = ev.state.begin(); it != ev.state.end(); it++)
		{
			switch (*it)
			{
			////��Ϸ�˳�
			case STATE::ESCAPE: 
				this->exit();
				break;
			////��Ϸ����
			//ע�⣬��Ϸ����������ֱ���˳���Ϸ
			case STATE::GAME_OVER: 
				//����ͨ����Ϣ�ȴ��˳���ť��ESC�������£����˳�
				//��Ҳ��Ϊ�˽���
				if (isGameOver == false)
					GameOver();
				break;
			////��⵽�����¼���isMoved����Ϊ�в���
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

	//�����Ƿ�Ϊ��״̬
	bool isOpen()const { return isOpening; }

private:

	//�˳���Ϸ
	void exit() { isOpening = false; }

	//��Ϸ����
	void GameOver()
	{
		isGameOver = true;
		cout << "Game Over!\npress Esc to quit..." << endl;
	}

private:
	//�Ƿ��
	bool isOpening;

	//�Ƿ����
	bool isGameOver;

	//�Ƿ�����˾���
	bool isMoved;

	//ÿһ֡�Ŀ�ʼ�¼�
	time_t StartTime;

	//֡��
	int FPS;

	//֡����
	time_t FrameTime;
};

