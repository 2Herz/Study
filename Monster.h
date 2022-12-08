#pragma once
#include "BaseClass.h"
class Monster : public BaseC
{
private:
	COLORREF Color;

public:
	RECT Body;
	int Speed;
	BOOL isLive;
	int HP;
	int Damage;
	int DealDelay;
	int Size;

public:
	Monster(POINT pos, BOOL isLive, int speed, bool type);
	~Monster();
	VOID Render(HDC hdc);
	BOOL CheckBodySect(POINT pt, int rad);
	VOID MoveMonster();
};