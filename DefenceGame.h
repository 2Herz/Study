#pragma once
/*	Standard */
#include <windowsx.h>
#include <sstream>
#include <list>
using namespace std;

/*	Custom */
#include "WinBase.h"
#include "Global.h"
#include "Player.h"
#include "Monster.h"
#include "Bullet.h"

enum GAMEMENU
{
	GM_START,
	GM_RUN,
	GM_END,
	GM_CLEAR
};

class DefenceGame : public WinBase
{
private:
	int Screen = GM_START;
	POINT MousePos;
	Player User;
	list<Monster> MonsterList;
	list<Bullet> BulletList;
	int DelayMax;
	int BulletDelay;
	int BombDelay;
	int MonsterDelay;
	int MonsterCount = 0;
	RECT Title;
	RECT Button;

private:
	LRESULT MyWndProc(HWND hWnd, UINT message, WPARAM wParam, LPARAM lParam);
	VOID Render(HDC hdc);
	VOID Update();
	float GetCos(int angle);
	float GetSin(int angle);
	VOID Init();

public:
	DefenceGame();
	~DefenceGame();
};