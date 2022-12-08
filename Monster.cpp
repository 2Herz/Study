#include "Monster.h"

Monster::Monster(POINT pos, BOOL isLive, int speed, bool type)
{
	if (type)
	{
		Color = SMALL_MONSTER;
		Size = DEFAULT_MONSTER_SIZE_S;
	}
	else
	{
		Color = BIG_MONSTER;
		Size = DEFAULT_MONSTER_SIZE_L;
	}

	isLive = isLive;
	Speed = speed;
	Damage = DEFAULT_MONSTER_DAMAGE;
	HP = DEFAULT_MONSTER_HP;
	Body = { pos.x - Size, pos.y - Size, pos.x + Size, pos.y + Size };
	DealDelay = 0;
}

Monster::~Monster()
{
}

VOID Monster::Render(HDC hdc)
{
	HBRUSH brush = (HBRUSH)CreateSolidBrush(Color);
	HBRUSH oldBrush = (HBRUSH)SelectObject(hdc, brush);

	Rectangle(hdc, Body.left, Body.top, Body.right, Body.bottom);

	SelectObject(hdc, oldBrush);
	DeleteObject(brush);
}

BOOL Monster::CheckBodySect(POINT pt, int rad)
{
	int cx = Body.right - Size / 2;
	int cy = Body.bottom - Size / 2;
	int len = sqrt(pow(abs(pt.x - cx), 2) + pow(abs(pt.y - cy), 2));

	if (len < (rad + Size / 2) || PtInRect(&Body, pt))
	{
		return true;
	}
	else
	{
		return false;
	}
}

VOID Monster::MoveMonster()
{
	Body.top += Speed;
	Body.bottom += Speed;
}