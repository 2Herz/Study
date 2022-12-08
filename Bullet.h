#pragma once
#include "BaseClass.h"

class Bullet : public BaseC
{
public:
	POINT Pos;
	BOOL isLive;
	int Speed;
	int Angle;
	int Rad;

public:
	Bullet();
	Bullet(POINT pos, BOOL isLive, int speed, int angle);
	~Bullet();
	VOID Render(HDC hdc);
};