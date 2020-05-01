/*******************
*Event:
*�ܹ��洢��Ϸ�е��¼���Ϣ��
*�����Ľ��շ��뷢�ͷ���
*ֻ������Ϣ���������
*�𵽽��������
********************/
#pragma once
#include"total.h"

class Event //  
{
public:

	//  �ɼ����¼���ȡ��Ϣ
	void CheckKeyEvent()
	{

		////�ȱ���һ����Ϣ����
		for (auto it = state.begin(); it != state.end(); it++)
		{
			////���������Ϸ��������Ϣ
			if (*it == STATE::GAME_OVER)
			{
				////���
				state.clear();

				////ѹ�� ��Ϸ��������Ϣ
				state.push_back(STATE::GAME_OVER);

				////�����Ϸ�˳��İ���
				while (_kbhit() and _getch() == ESC_ASC)
					state.push_back(STATE::ESCAPE);

				////֮����Ū��ô�鷳��ֱ���˳���Ϸ����Ϊ�˱��⹦�����
				//Ҫ��֤Eventֻ������Ϣ
				//�����ܿ�����Ϸ
				//������Ϸ�����������󣬽ػ���Ϣ�ٽ��в���
				return;
			}
		}

		////�����Ϣ����
		state.clear();

		////��ȡ�����¼�
		//_kbhit()������C�ṩ�ļ��̰��¼��
		while (_kbhit()) {
			////  _getch()�����ǻ�ȡһ���ַ����룬����ASCII��
			int Key1 = _getch(); 

			//ESC�������£�
			if (Key1 == ESC_ASC)
			{
				////push_back��vector�ķ��������ڴ�����ĩ���½�����Ԫ��
				state.push_back(STATE::ESCAPE);
			}

			//ĳ������������£�
			if (Key1 == DIRECTION_ASC)
			{
				//��������� '\224' �� ��һ���ַ���ɵġ�˫�ַ��͡��ַ�
				//��˼��ڶ���������ַ�
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

	//ԭ��Ӧ���е�push��get���������У�����Ϸ�����ܹ�������Ϣ
	//������Ϸ��������Ҫ�����ʡ��
	/*
	void pushEvent(){
		//code here
	}
	vector<STATE> getEvent()const{
		//code here
	}
	*/

	////ʹ��vector����������飬��Ϊ��Ϣ����:
	vector<STATE>state;

};

