#include"RenderMap.h"
int main()
{
	RenderMap App;
	App.SetFPS(100);

	Map map;
	
	Event ev;

	//��Ϸѭ��
	while (App.isOpen())//�Ƿ��˳�
	{
		//�¼����
		ev.CheckKeyEvent();

		//��������Ϣ����
		App.PushEvent(ev);

		//�����ͼ����
		map.Update(ev);

		//ˢ��
		App.clear();

		//��Ⱦ��ͼ
		App.draw(map);

		//����֡��
		App.display();

	}

}


