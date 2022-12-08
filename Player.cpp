#include "Player.h"

VOID Player::Render(HDC hdc, POINT _mousepos)
{
	HBRUSH brush = (HBRUSH)CreateSolidBrush(BLACK);
	HBRUSH oldBrush = (HBRUSH)SelectObject(hdc, brush);
	HPEN pen = CreatePen(PS_SOLID, 4, WHITE);
	HPEN oldPen = (HPEN)SelectObject(hdc, pen);

	Rectangle(hdc, tPlayer.left, tPlayer.top, tPlayer.right, tPlayer.bottom);

	SelectObject(hdc, oldPen);
	DeleteObject(pen);
	SelectObject(hdc, oldBrush);
	DeleteObject(brush);

	brush = (HBRUSH)CreateSolidBrush(CRIMSON);
	oldBrush = (HBRUSH)SelectObject(hdc, brush);
	pen = CreatePen(PS_SOLID, 3, SKY);
	oldPen = (HPEN)SelectObject(hdc, pen);

	int x0 = (WIN_WIDTH / 2);
	int y0 = (WIN_HEIGHT - 10);

	//	yÃà ÁÂÇ¥ Á¦ÇÑ
	POINT mousePos = _mousepos;
	if (mousePos.y > tPlayer.top)
	{
		mousePos.y = tPlayer.top;
	}

	double dx = (mousePos.x - x0);
	double dy = (mousePos.y - y0);
	tAngle = -atan2(dy, dx) * (180 / PI);

	double len = sqrt(pow(dx, 2) + pow(dy, 2));
	double div = (shotLen / len);

	tPos.x = long(cosf(tAngle * PI / 180) * shotLen + x0);
	tPos.y = long(-sinf(tAngle * PI / 180) * shotLen + y0);

	int ax = long(-cosf((90 - tAngle) * PI / 180) * (shotLen / -2) + x0);
	int ay = long(-sinf((90 - tAngle) * PI / 180) * (shotLen / -2) + y0);

	int bx = long(cosf((90 - tAngle) * PI / 180) * (shotLen / -2) + x0);
	int by = long(sinf((90 - tAngle) * PI / 180) * (shotLen / -2) + y0);

	POINT vert[] = { { ax, ay },{ tPos.x, tPos.y },{ bx, by }};
	Polygon(hdc, vert, sizeof(vert) / sizeof(vert[0]));
	Ellipse(hdc, tPos.x - 5, tPos.y - 7, tPos.x + 5, tPos.y + 7);

	SelectObject(hdc, oldPen);
	DeleteObject(pen);
	SelectObject(hdc, oldBrush);
	DeleteObject(brush);
}

RECT Player::GetPlayerRect()
{
	return tPlayer;
}

POINT Player::GetShotPoint()
{
	return tPos;
}

int Player::PresentAngle()
{
	return tAngle;
}

int Player::GetHP()
{
	return HP;
}

VOID Player::FullHP()
{
	HP = DEFAULT_PLAYER_HP;
}

VOID Player::RechargeHP(int dmg)
{
	HP -= dmg;
}

Player::Player()
{
	tPlayer = { -10, WIN_WIDTH - 100, WIN_WIDTH + 10, WIN_HEIGHT + 10 };
}

Player::~Player()
{
}