#include "DefenceGame.h"

/*
	����Ű

		�����̽��� : �Ѿ˹߻�
		���콺 ������ ��ư : �����߻�
		�޴����� �� �߻�ü ���� ���� : ���콺 ���� ��ư
		����Ű ���� : BGM���
		����Ű �Ʒ��� : BGM ����
*/

int APIENTRY WinMain(HINSTANCE hInst, HINSTANCE hPrevInst, LPSTR CmdParam, int CmdShow)
{
	DefenceGame main;

	if (main.NewWin(hInst, WIN_WIDTH, WIN_HEIGHT, WIN_NAME) == FALSE)
	{
		return 0;
	}
	main.SetTimerFlow(20);

	return main.MessageLoop();
}