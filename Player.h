#pragma once
#include "BaseClass.h"

class Player : public BaseC
{
private:
	RECT tPlayer;
	POINT tPos;
	int tAngle;
	int shotLen = 70;
	int HP = DEFAULT_PLAYER_HP;

public:
	Player();
	~Player();

	VOID Render(HDC hdc, POINT mousepos);
	RECT GetPlayerRect();
	POINT GetShotPoint();
	int PresentAngle();
	int GetHP();
	VOID FullHP();
	VOID RechargeHP(int dmg);
};