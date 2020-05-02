/*******************
*Map:
*��Ϸ4*4������
********************/
#pragma once
#include"total.h"
#include"Event.h"
class Map
{
public:

	////Map�Ĺ��캯��
	Map()
		:Mapper(nullptr), m_size(4)
	{
		//�����ڴ�
		Mapper = new int* [4]; assert(Mapper);
		for (size_t i = 0; i < 4; i++)
		{
			Mapper[i] = new int[4]; assert(Mapper[i]);
		}
		//��ʼ��
		for (size_t i = 0; i < 4; i++)
		{
			for (size_t j = 0; j < 4; j++)
			{
				Mapper[i][j] = 0;
			}
		}
		RandomCreate();
	}

	~Map()
	{
		if (Mapper != NULL)
		{
			for (size_t i = 0; i < 4; i++)
			{
				delete[] Mapper[i];
			}
		delete[] Mapper;
		}
	}

	////������ɷ���
	void RandomCreate()
	{
		srand((unsigned int)time(NULL));

		//��¼���ɸ��������ܳ�������
		int createcount = 0;

		//�Ƿ��Ѿ����ˣ��޷�����
		bool isFull;

		//���ѭ������������ɣ�ֱ������Ҫ����˳�
		while (1)
		{
			//�ȼ�������
			isFull = true;

			//����Ѿ�����2�����˳�
			if (createcount >= AdditionNumber)
			{
				return;
			}

			//��������
			for (size_t i = 0; i < this->m_size; i++)
			{
				for (size_t j = 0; j < this->m_size; j++)
				{
					//�Ѿ�2��
					if (createcount >= AdditionNumber)
					{
						return;
					}

					//���Ԫ��Ϊ0����������ɣ�
					if (Mapper[i][j] == 0)
					{
						//�аٷ�֮ʮ�ĸ��ʻ��ڴ˴�����
						//����Ϊ�˼�������λ�ò����ȷֲ��̶�
						int randnum = rand() % 10;
						if (randnum == 0)
						{
							//�аٷ�֮ʮ�ĸ�������4
							randnum = rand() % 10;
							if (randnum == 0)
								Mapper[i][j] = 4;
							else
								Mapper[i][j] = 2;
							//��������һ
							createcount++;
						}
						//�ҵ���0Ԫ�أ�����û����
						isFull = false;
					}
				}
			}
			//������ˣ��˳�
			if (isFull)return;
		}
	}

	//��Ⱦ���󣬲�����
	void Draw()const
	{
		printf("\n");
		for (size_t i = 0; i < m_size; i++)
		{
			for (size_t j = 0; j < m_size; j++)
			{
				if (Mapper[i][j] == 0)
					printf("---    ");
				else
					printf("%-5d  ", Mapper[i][j]);
			}
			printf("\n\n\n");
		}
	}

	//���£�����¼�
	void Update(Event& ev)
	{
		//�ж��Ƿ�����˾���
		bool isMoved = false;
		//������Ϣ����
		for (auto it = ev.state.begin(); it != ev.state.end(); it++)
		{
			//����в�����isMovedΪ��
			switch (*it)
			{
			case STATE::UP: 
				this; isMoved = true; Move_UP();
				break;
			case STATE::DOWN: 
				this; isMoved = true; Move_DOWN();
				break;
			case STATE::LEFT: 
				this; isMoved = true; Move_LEFT();
				break;
			case STATE::RIGHT: 
				this; isMoved = true; Move_RIGHT();
				break;
			}
		}
		//�����������
		if (isMoved == true)
		{
			//�������
			RandomCreate();

			//�����Ϸ�Ѿ�����
			if (isOver() == true)
			{
				//ѹ����Ϸ�����¼�
				ev.state.push_back(STATE::GAME_OVER);
			}
		}
	}

	//���ؾ����С
	size_t size()const { return m_size; }

private:

	//���ϲ���
	void Move_UP()
	{
		//ת�þ���ʹ֮�������Ч
		ReverseMap();
		Move_LEFT();
		//ת�û���
		ReverseMap();
	}

	//����
	void Move_DOWN()
	{
		//��ֱ��ת��ʹ֮�����ϵ�Ч
		InverseMap_ver();
		Move_UP();
		//��ֱ��ת
		InverseMap_ver();
	}

	//����
	void Move_LEFT()
	{
		//���ڼ�¼�������ķ���Ԫ�أ�����ʱΪ0
		int flag_num = 0;
		//����Ԫ�ص�λ��
		size_t flag = 0;
		//��ʼ���㣨�У�����
		for (size_t i = 0; i < this->m_size; i++)
		{
			flag_num = 0;
			flag = 0;
			//  Union
			//�ϲ���ͬ������
			for (size_t j = 0; j < this->m_size; j++)
			{
				//�����⵽����Ԫ��
				if (Mapper[i][j] != 0)
				{
					//���Ԫ������һ������Ԫ�ز�ͬ
					if (Mapper[i][j] != flag_num)
					{
						//���·���Ԫ��
						flag_num = Mapper[i][j], flag = j;
					}
					//�������һ��������ͬ
					else if (Mapper[i][j] == flag_num)
					{
						//�ϲ�����һ����λ�ã����
						Mapper[i][flag] += Mapper[i][j];
						//����λ�ã����÷�������
						Mapper[i][j] = 0, flag_num = 0, flag = j;
					}
				}
			}

			//  Move
			//������ð��������㷨
			//ÿ�α�����0�ᵽ���
			for (size_t k = 0; k < this->m_size; k++)
			{
				for (size_t j = 0; j + 1 < this->m_size - k; j++)
				{
					//���ǰһ��Ԫ����0 �Һ�һ������
					if (Mapper[i][j] == 0 and Mapper[i][j + 1] != 0)
					{
						//����
						swap(Mapper[i][j], Mapper[i][j + 1]);
					}
				}
			}
		}
	}

	//����
	void Move_RIGHT()
	{
		//ˮƽ��ת��ʹ֮�������Ч
		InverseMap_hor();
		Move_LEFT();
		//ˮƽ��ת
		InverseMap_hor();
	}

	//ת�þ���
	void ReverseMap()
	{
		for (size_t i = 0; i < this->m_size; i++)
		{
			for (size_t j = 0; j <= i; j++)
			{
				swap(Mapper[i][j], Mapper[j][i]);
			}
		}
	}

	//��ֱ��ת����
	void InverseMap_ver()
	{
		for (size_t j = 0; j < this->m_size; j++)
		{
			for (size_t i = 0; i < this->m_size / 2; i++)
			{
				swap(Mapper[i][j], Mapper[this->m_size - i - 1][j]);
			}
		}
	}

	//ˮƽ��ת����
	void InverseMap_hor()
	{
		for (size_t i = 0; i < this->m_size; i++)
		{
			for (size_t j = 0; j < this->m_size / 2; j++)
			{
				swap(Mapper[i][j], Mapper[i][this->m_size - j - 1]);
			}
		}
	}

	//�Ƿ���Ϸ����
	bool isOver()
	{
		//��������
		for (size_t i = 0; i < this->m_size; i++)
		{
			for (size_t j = 0; j < this->m_size; j++)
			{
				//���û������ֱ�ӷ�����Ϸδ����
				if (Mapper[i][j] == 0)
				{
					return false;
				}
			}
		}
		//�㷨��LEFT������ͬ
		//�ж��Ƿ����ܹ���ӵ�����
		//�����жϺ���:
		int flag_num = 0;
		size_t flag = 0;
		for (size_t i = 0; i < this->m_size; i++)
		{
			flag_num = 0;
			flag = 0;
			for (size_t j = 0; j < this->m_size; j++)
			{
				if (Mapper[i][j] != flag_num)
				{
					flag_num = Mapper[i][j], flag = j;
				}
				//����ͬԪ�أ���Ϸδ����
				else if (Mapper[i][j] == flag_num)
				{
					return false;
				}
			}
		}
		//�ж�����:
		for (size_t j = 0; j < this->m_size; j++)
		{
			flag_num = 0;
			flag = 0;
			for (size_t i = 0; i < this->m_size; i++)
			{
				if (Mapper[i][j] != flag_num)
				{
					flag_num = Mapper[i][j], flag = i;
				}
				//����ͬԪ�أ���Ϸδ����
				else if (Mapper[i][j] == flag_num)
				{
					return false;
				}
			}
		}

		//�������㣬�򷵻���Ϸ����
		return true;
	}

private:

	//Map�ľ���
	int** Mapper;

	//ÿ��������ɵķ����������ܳ���2:
	const int AdditionNumber = 2;

	//�����С
	size_t m_size;
};
