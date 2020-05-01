#include"RenderMap.h"
int main()
{
	RenderMap App;
	App.SetFPS(100);

	Map map;
	
	Event ev;

	//游戏循环
	while (App.isOpen())//是否退出
	{
		//事件检测
		ev.CheckKeyEvent();

		//主窗口消息处理
		App.PushEvent(ev);

		//矩阵地图更新
		map.Update(ev);

		//刷新
		App.clear();

		//渲染地图
		App.draw(map);

		//控制帧率
		App.display();

	}

}


