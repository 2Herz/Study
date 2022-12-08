#include "Bullet.h"

Bullet::Bullet()
{
}

Bullet::Bullet(POINT pos, BOOL isLive, int speed, int angle)
{
	Pos = pos;
	isLive = isLive;
	Speed = speed;
	Angle = angle;

	if (speed == DEFAULT_BULLET_SPEED)
	{
		Rad = DEFAULT_BULLET_RADIUS;
	}
	else
	{
		Rad = DEFAULT_BULLET_RADIUS * 10;
	}
}

Bullet::~Bullet()
{
}

VOID Bullet::Render(HDC hdc)
{
	HBRUSH brush = CreateSolidBrush(CELESTE);
	HBRUSH oldBrush = (HBRUSH)SelectObject(hdc, brush);
	Ellipse(hdc, Pos.x - Rad, Pos.y - Rad, Pos.x + Rad, Pos.y + Rad);
	SelectObject(hdc, oldBrush);
	DeleteObject(brush);
}