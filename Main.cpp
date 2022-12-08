#include "DefenceGame.h"

/*
	조작키

		스페이스바 : 총알발사
		마우스 오른쪽 버튼 : 대포발사
		메뉴선택 및 발사체 궤적 변경 : 마우스 왼쪽 버튼
		방향키 위쪽 : BGM재생
		방향키 아래쪽 : BGM 끄기
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