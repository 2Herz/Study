#include "DefenceGame.h"
#include <MMsystem.h>
#pragma comment(lib, "winmm.lib")

VOID ViewString(HDC hdc, LPCSTR s, int x, int y)
{
	TextOutA(hdc, x, y, s, strlen(s));
}

LRESULT DefenceGame::MyWndProc(HWND hWnd, UINT message, WPARAM wParam, LPARAM lParam)
{
	switch (message)
	{
		case WM_KEYDOWN:
		{
			switch (wParam)
			{
				case VK_ESCAPE:
				{
					if (IDYES == MessageBox(hWnd, L"종료하시겠습니까?", L"게임종료", MB_YESNO))
					{
						PostQuitMessage(0);
					}
					else if (IDNO)
					{
						break;
					}
				}break;

				case VK_SPACE:
				{
					switch (Screen)
					{
					case GM_RUN:
					{
						if (BulletDelay >= DelayMax)
						{
							BulletDelay = 0;
							Bullet temp(User.GetShotPoint(), true, DEFAULT_BULLET_SPEED, User.PresentAngle());
							BulletList.push_back(temp);
						}
					}break;
					}
				}break;

				case VK_UP:
				{
					PlaySound(TEXT("호미들 - 사이렌 Remix.wav"), nullptr, SND_ASYNC | SND_LOOP);
				}break;

				case VK_DOWN:
				{
					PlaySound(nullptr, nullptr, SND_ASYNC);
				}break;

				case 'b':
				case 'B':
				{
					if (BombDelay >= DEFAULT_BOMB_DELAY)
					{
						BombDelay = 0;
						Bullet temp(User.GetShotPoint(), true, DEFAULT_BOMB_SPEED, User.PresentAngle());
						BulletList.push_back(temp);
					}
				}
			}
		}break;
		
		case WM_MOUSEMOVE:
		{
			MousePos.x = GET_X_LPARAM(lParam);
			MousePos.y = GET_Y_LPARAM(lParam);
		}break;

		case WM_LBUTTONDOWN:
		{
			switch (Screen)
			{
				case GM_START:
				{
					if (MousePos.x > Button.left && MousePos.x < Button.right && MousePos.y > Button.top && MousePos.y < Button.bottom)
					{
						Screen = GM_RUN;
					}
				}break;
				
				case GM_END:
				case GM_CLEAR:
				{
					if (MousePos.x > Button.left && MousePos.x < Button.right && MousePos.y > Button.top && MousePos.y < Button.bottom)
					{
						Screen = GM_START;
						Init();
					}
				}break;
			}
		}break;

		//case WM_RBUTTONDOWN:
		//{
		//	if (BombDelay >= DEFAULT_BOMB_DELAY)
		//	{
		//		BombDelay = 0;
		//		Bullet temp(User.GetShotPoint(), true, DEFAULT_BOMB_SPEED, User.PresentAngle());
		//		BulletList.push_back(temp);
		//	}
		//}break;
	}
	return WinBase::MyWndProc(hWnd, message, wParam, lParam);
}

VOID DefenceGame::Render(HDC hdc)
{
	if (Screen == GM_START)
	{
		HBRUSH brush = (HBRUSH)CreateSolidBrush(GRAY);
		HBRUSH oldBrush = (HBRUSH)SelectObject(hdc, brush);
		SetBkColor(hdc, GRAY);
		SetTextColor(hdc, WHITE);
		HFONT font = CreateFont(20, 0, 0, 0, 500, 0, 0, 0, HANGEUL_CHARSET, 0, 0, 0, 0, L"고딕");
		HFONT oldFont = (HFONT)SelectObject(hdc, font);
		Rectangle(hdc, Button.left, Button.top - 130, Button.right, Button.bottom - 130);
		TextOutA(hdc, (WIN_WIDTH / 2) - 50, 250, "디펜스게임", strlen("디펜스게임"));
		SelectObject(hdc, font);
		DeleteObject(oldFont);
		SelectObject(hdc, oldBrush);
		DeleteObject(brush);

		brush = (HBRUSH)CreateSolidBrush(SKYBLUE);
		oldBrush = (HBRUSH)SelectObject(hdc, brush);
		SetBkColor(hdc, SKYBLUE);
		SetTextColor(hdc, RED);
		font = CreateFont(20, 0, 0, 0, 600, 0, 0, 0, HANGEUL_CHARSET, 0, 0, 0, 0, L"굴림");
		oldFont = (HFONT)SelectObject(hdc, font);
		Rectangle(hdc, Button.left, Button.top - 20, Button.right, Button.bottom - 20);
		TextOutA(hdc, (WIN_WIDTH / 2) - 43, 360, "게임시작", strlen("게임시작"));
		SelectObject(hdc, font);
		DeleteObject(oldFont);
		SelectObject(hdc, brush);
		DeleteObject(oldBrush);
	}
	else if (Screen == GM_RUN)
	{
		User.Render(hdc, MousePos);
		for (auto b : BulletList)
		{
			b.Render(hdc);
		}
		for (auto e : MonsterList)
		{
 			e.Render(hdc);
		}

		//health bar
		HBRUSH brush = (HBRUSH)CreateSolidBrush(WHITE);
		HBRUSH oldBrush = (HBRUSH)SelectObject(hdc, brush);
		SetBkColor(hdc, BLACK);
		SetTextColor(hdc, WHITE);
		TextOutA(hdc, 10, User.GetPlayerRect().top + 30, "체력 ", strlen("체력 "));
		Rectangle(hdc, 60, User.GetPlayerRect().top + 30, 160, User.GetPlayerRect().top + 40);
		SelectObject(hdc, oldBrush);
		DeleteObject(brush);

		brush = (HBRUSH)CreateSolidBrush(RED);
		oldBrush = (HBRUSH)SelectObject(hdc, brush);
		Rectangle(hdc, 60, User.GetPlayerRect().top + 30, 60 + (User.GetHP() / 10), User.GetPlayerRect().top + 40);
		SelectObject(hdc, oldBrush);
		DeleteObject(brush);

		//progress bar
		brush = (HBRUSH)CreateSolidBrush(WHITE);
		oldBrush = (HBRUSH)SelectObject(hdc, brush);
		SetBkColor(hdc, BLACK);
		SetTextColor(hdc, WHITE);
		TextOutA(hdc, 4, User.GetPlayerRect().bottom - 40, "진행도 ", strlen("진행도 "));
		Rectangle(hdc, 60, User.GetPlayerRect().bottom - 40, 160, User.GetPlayerRect().bottom - 20);
		SelectObject(hdc, oldBrush);
		DeleteObject(brush);

		brush = (HBRUSH)CreateSolidBrush(BLUE);
		oldBrush = (HBRUSH)SelectObject(hdc, brush);
		stringstream s;    
		SetBkColor(hdc, BLUE);
		SetTextColor(hdc, WHITE);
		s << (float)(MonsterCount / 2) << "%";
		Rectangle(hdc, 60, User.GetPlayerRect().bottom - 40, 60 + (MonsterCount / 2), User.GetPlayerRect().bottom - 20);
		TextOutA(hdc, 100, User.GetPlayerRect().bottom - 38, s.str().c_str(), s.str().length());
		SelectObject(hdc, oldBrush);
		DeleteObject(brush);

		//LButton Cool Down
		brush = (HBRUSH)CreateSolidBrush(WHITE);
		oldBrush = (HBRUSH)SelectObject(hdc, brush);
		SetBkColor(hdc, BLACK);
		SetTextColor(hdc, WHITE);
		TextOutA(hdc, WIN_WIDTH - 160, User.GetPlayerRect().top + 17, "총", strlen("총"));
		Rectangle(hdc, WIN_WIDTH - 120, User.GetPlayerRect().top + 20, WIN_WIDTH - 20, User.GetPlayerRect().top + 30);
		SelectObject(hdc, oldBrush);
		DeleteObject(brush);

		brush = (HBRUSH)CreateSolidBrush(CRIMSON);
		oldBrush = (HBRUSH)SelectObject(hdc, brush);
		Rectangle(hdc, WIN_WIDTH - 120, User.GetPlayerRect().top + 20, WIN_WIDTH - 120 + (10 * BulletDelay), User.GetPlayerRect().top + 30);
		SelectObject(hdc, oldBrush);
		DeleteObject(brush);

		//RButton Cool Down
		brush = (HBRUSH)CreateSolidBrush(WHITE);
		oldBrush = (HBRUSH)SelectObject(hdc, brush);
		SetBkColor(hdc, BLACK);
		SetTextColor(hdc, WHITE);
		TextOutA(hdc, WIN_WIDTH - 185, User.GetPlayerRect().top + 42, "대포", strlen("대포"));
		Rectangle(hdc, WIN_WIDTH - 120, User.GetPlayerRect().top + 45, WIN_WIDTH - 20, User.GetPlayerRect().top + 55);
		SelectObject(hdc, oldBrush);
		DeleteObject(brush);

		brush = (HBRUSH)CreateSolidBrush(CRIMSON);
		oldBrush = (HBRUSH)SelectObject(hdc, brush);
		Rectangle(hdc, WIN_WIDTH - 120, User.GetPlayerRect().top + 45, WIN_WIDTH - 120 + (1 * BombDelay), User.GetPlayerRect().top + 55);
		SelectObject(hdc, oldBrush);
		DeleteObject(brush);
	}
	else if (Screen == GM_END)
	{
		SetBkColor(hdc, BLACK);
		SetTextColor(hdc, WHITE);
		HFONT font = CreateFont(20, 0, 0, 0, 500, 0, 0, 0, HANGEUL_CHARSET, 0, 0, 0, 0, L"고딕");
		HFONT oldFont = (HFONT)SelectObject(hdc, font);
		TextOutA(hdc, (WIN_WIDTH / 2) - 53, 250, "GAME OVER!", strlen("GAME OVER!"));
		HPEN pen = (HPEN)CreatePen(PS_SOLID, 5, BLACK);
		HPEN oldPen = (HPEN)SelectObject(hdc, pen);
		HBRUSH brush = (HBRUSH)CreateSolidBrush(SKYBLUE);
		HBRUSH oldBrush = (HBRUSH)SelectObject(hdc, brush);
		Rectangle(hdc, Button.left, Button.top - 50, Button.right, Button.bottom - 50);
		SetBkColor(hdc, SKYBLUE);
		SetTextColor(hdc, BLACK);
		font = CreateFont(20, 0, 0, 0, 600, 0, 0, 0, HANGEUL_CHARSET, 0, 0, 0, 0, L"굴림");
		oldFont = (HFONT)SelectObject(hdc, font);
		TextOutA(hdc, (WIN_WIDTH / 2) - 40, 330, "돌아가기", strlen("돌아가기"));
		SelectObject(hdc, brush);
		DeleteObject(oldBrush);
		SelectObject(hdc, pen);
		DeleteObject(oldPen);
		SelectObject(hdc, font);
		DeleteObject(oldFont);
	}
	else if (Screen == GM_CLEAR)
	{
		SetBkColor(hdc, BLACK);
		SetTextColor(hdc, WHITE);
		HFONT font = CreateFont(20, 0, 0, 0, 500, 0, 0, 0, HANGEUL_CHARSET, 0, 0, 0, 0, L"고딕");
		HFONT oldFont = (HFONT)SelectObject(hdc, font);
		TextOutA(hdc, (WIN_WIDTH / 2) - 36, 250, "클리어!", strlen("클리어!"));
		HPEN pen = (HPEN)CreatePen(PS_SOLID, 5, BLACK);
		HPEN oldPen = (HPEN)SelectObject(hdc, pen);
		HBRUSH brush = (HBRUSH)CreateSolidBrush(SKYBLUE);
		HBRUSH oldBrush = (HBRUSH)SelectObject(hdc, brush);
		Rectangle(hdc, Button.left, Button.top - 50, Button.right, Button.bottom - 50);
		SetBkColor(hdc, SKYBLUE);
		SetTextColor(hdc, BLACK);
		font = CreateFont(20, 0, 0, 0, 600, 0, 0, 0, HANGEUL_CHARSET, 0, 0, 0, 0, L"굴림");
		oldFont = (HFONT)SelectObject(hdc, font);
		TextOutA(hdc, (WIN_WIDTH / 2) - 40, 330, "돌아가기", strlen("돌아가기"));
		SelectObject(hdc, brush);
		DeleteObject(oldBrush);
		SelectObject(hdc, pen);
		DeleteObject(oldPen);
		SelectObject(hdc, font);
		DeleteObject(oldFont);
	}
}

VOID DefenceGame::Update()
{
	if (Screen == GM_RUN)
	{
		if (User.GetHP() <= 0)
		{
			Screen = GM_END;
		}
		if (BulletDelay < DelayMax)
		{
			BulletDelay++;
		}
		if (BombDelay < DEFAULT_BOMB_DELAY)
		{
			BombDelay++;
		}

		if (MonsterCount < DEFAULT_MONSTER_MAX)
		{
			if (MonsterDelay % 10 == 0)
			{
				POINT pos = { (rand() % (WIN_WIDTH - 200) + 100), DEFAULT_MONSTER_POS_X };
				Monster temp(pos, true, 5, MONSTER_SMALL);
				MonsterList.push_back(temp);
				MonsterCount++;
			}
			if (MonsterDelay % 30 == 0)
			{
				POINT pos = { (rand() % (WIN_WIDTH - 200) + 100), DEFAULT_MONSTER_POS_X };
				Monster temp(pos, true, 3, MONSTER_LARGE);
				MonsterList.push_back(temp);
				MonsterCount++;
			}
		}

		else
		{
			if (MonsterList.size() == 0)
			{
				Screen = GM_CLEAR;
			}
		}

		MonsterDelay++;

		for (auto i = BulletList.begin(); i != BulletList.end();)
		{
			i->Pos.x = long(cosf(i->Angle * PI / 180) * i->Speed + i->Pos.x);
			i->Pos.y = long(-sinf(i->Angle * PI / 180) * i->Speed + i->Pos.y);

			if (i->Pos.x > WIN_WIDTH || i->Pos.x < 0 || i->Pos.y < 0)
			{
				i = BulletList.erase(i);
			}
			else
			{
				++i;
			}
		}

		for (auto i = MonsterList.begin(); i != MonsterList.end();)
		{
			bool isSect = false;

			for (auto j = BulletList.begin(); j != BulletList.end();)
			{
				if (i->CheckBodySect(j->Pos, j->Rad))
				{
					if (j->Rad == DEFAULT_BULLET_RADIUS)
					{
						j = BulletList.erase(j);
					}
					isSect = true;
					break;
				}
				else
				{
					++j;
				}
			}

			if (i->Body.bottom >= User.GetPlayerRect().top)
			{
				if (i->DealDelay > DEFAULT_MONSTER_DEAL_DELAY)
				{
					User.RechargeHP(i->Damage);
					i->DealDelay = 0;
				}

				i->DealDelay++;
			}
			else
			{
				i->MoveMonster();
			}

			if (isSect)
			{
				i = MonsterList.erase(i);
			}
			else
			{
				++i;
			}
		}
	}
}

DefenceGame::DefenceGame()
{
	srand(GetTickCount());
	Button = { (WIN_WIDTH / 2) - 100, 350, (WIN_WIDTH / 2) + 100, 430 };
	Init();
}

DefenceGame::~DefenceGame()
{
}

float DefenceGame::GetCos(int angle)
{
	return (float)(cos(angle) * PI / 180);
}

float DefenceGame::GetSin(int angle)
{
	return (float)(sin(angle) * PI / 180);
}

VOID DefenceGame::Init()
{
	DelayMax = DEFAULT_BULLET_DELAY;
	BulletDelay = DelayMax;
	BombDelay = DEFAULT_BOMB_DELAY;
	MonsterDelay = 0;
	MonsterCount = 0;
	User.FullHP();
	MonsterList.clear();
	BulletList.clear();
}