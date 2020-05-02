/*******************
*Map:
*游戏4*4矩阵类
********************/
#pragma once
#include"total.h"
#include"Event.h"
class Map
{
public:

	////Map的构造函数
	Map()
		:Mapper(nullptr), m_size(4)
	{
		//申请内存
		Mapper = new int* [4]; assert(Mapper);
		for (size_t i = 0; i < 4; i++)
		{
			Mapper[i] = new int[4]; assert(Mapper[i]);
		}
		//初始化
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

	////随机生成方块
	void RandomCreate()
	{
		srand((unsigned int)time(NULL));

		//记录生成个数，不能超过两个
		int createcount = 0;

		//是否已经满了，无法生成
		bool isFull;

		//这个循环用于随机生成，直到满足要求才退出
		while (1)
		{
			//先假设满了
			isFull = true;

			//如果已经生成2个，退出
			if (createcount >= AdditionNumber)
			{
				return;
			}

			//遍历矩阵
			for (size_t i = 0; i < this->m_size; i++)
			{
				for (size_t j = 0; j < this->m_size; j++)
				{
					//已经2个
					if (createcount >= AdditionNumber)
					{
						return;
					}

					//如果元素为0，则可以生成：
					if (Mapper[i][j] == 0)
					{
						//有百分之十的概率会在此处生成
						//这是为了减少生成位置不均匀分布程度
						int randnum = rand() % 10;
						if (randnum == 0)
						{
							//有百分之十的概率生成4
							randnum = rand() % 10;
							if (randnum == 0)
								Mapper[i][j] = 4;
							else
								Mapper[i][j] = 2;
							//生成数加一
							createcount++;
						}
						//找到了0元素，矩阵没有满
						isFull = false;
					}
				}
			}
			//如果满了，退出
			if (isFull)return;
		}
	}

	//渲染矩阵，不解释
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

	//更新，检测事件
	void Update(Event& ev)
	{
		//判断是否操作了矩阵
		bool isMoved = false;
		//遍历消息队列
		for (auto it = ev.state.begin(); it != ev.state.end(); it++)
		{
			//如果有操作，isMoved为真
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
		//如果操作过了
		if (isMoved == true)
		{
			//随机生成
			RandomCreate();

			//如果游戏已经结束
			if (isOver() == true)
			{
				//压入游戏结束事件
				ev.state.push_back(STATE::GAME_OVER);
			}
		}
	}

	//返回矩阵大小
	size_t size()const { return m_size; }

private:

	//向上操作
	void Move_UP()
	{
		//转置矩阵，使之与向左等效
		ReverseMap();
		Move_LEFT();
		//转置回来
		ReverseMap();
	}

	//向下
	void Move_DOWN()
	{
		//垂直翻转，使之与向上等效
		InverseMap_ver();
		Move_UP();
		//垂直翻转
		InverseMap_ver();
	}

	//向左
	void Move_LEFT()
	{
		//用于记录遍历过的非零元素，重置时为0
		int flag_num = 0;
		//非零元素的位置
		size_t flag = 0;
		//开始按层（行）遍历
		for (size_t i = 0; i < this->m_size; i++)
		{
			flag_num = 0;
			flag = 0;
			//  Union
			//合并相同的数字
			for (size_t j = 0; j < this->m_size; j++)
			{
				//如果检测到非零元素
				if (Mapper[i][j] != 0)
				{
					//如果元素与上一个非零元素不同
					if (Mapper[i][j] != flag_num)
					{
						//更新非零元素
						flag_num = Mapper[i][j], flag = j;
					}
					//如果与上一个非零相同
					else if (Mapper[i][j] == flag_num)
					{
						//合并到上一个的位置，相加
						Mapper[i][flag] += Mapper[i][j];
						//更新位置，重置非零数字
						Mapper[i][j] = 0, flag_num = 0, flag = j;
					}
				}
			}

			//  Move
			//用类似冒泡排序的算法
			//每次遍历把0提到最后
			for (size_t k = 0; k < this->m_size; k++)
			{
				for (size_t j = 0; j + 1 < this->m_size - k; j++)
				{
					//如果前一个元素是0 且后一个非零
					if (Mapper[i][j] == 0 and Mapper[i][j + 1] != 0)
					{
						//交换
						swap(Mapper[i][j], Mapper[i][j + 1]);
					}
				}
			}
		}
	}

	//向右
	void Move_RIGHT()
	{
		//水平翻转，使之与向左等效
		InverseMap_hor();
		Move_LEFT();
		//水平翻转
		InverseMap_hor();
	}

	//转置矩阵
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

	//垂直翻转矩阵
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

	//水平翻转矩阵
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

	//是否游戏结束
	bool isOver()
	{
		//遍历矩阵
		for (size_t i = 0; i < this->m_size; i++)
		{
			for (size_t j = 0; j < this->m_size; j++)
			{
				//如果没有满，直接返回游戏未结束
				if (Mapper[i][j] == 0)
				{
					return false;
				}
			}
		}
		//算法与LEFT操作相同
		//判断是否有能够相加的数字
		//这里判断横向:
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
				//有相同元素，游戏未结束
				else if (Mapper[i][j] == flag_num)
				{
					return false;
				}
			}
		}
		//判断纵向:
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
				//有相同元素，游戏未结束
				else if (Mapper[i][j] == flag_num)
				{
					return false;
				}
			}
		}

		//都不满足，则返回游戏结束
		return true;
	}

private:

	//Map的矩阵
	int** Mapper;

	//每次随机生成的方块数量不能超过2:
	const int AdditionNumber = 2;

	//矩阵大小
	size_t m_size;
};
