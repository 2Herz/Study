#pragma once
#include <Windows.h>
#include <string>
#undef UNICODE

class WinBase
{
private:
	std::string ClassName;
	std::string WinName;
	HWND hWnd;
	HINSTANCE hInst;
	SIZE WinSize;
	int time_flow = 1000;

	VOID RegClass();
	BOOL MakeWindow();
	friend LRESULT CALLBACK WndProc(HWND, UINT, WPARAM, LPARAM);

protected:
	virtual LRESULT MyWndProc(HWND hWnd, UINT message, WPARAM wParam, LPARAM lParam);
	virtual VOID Render(HDC hdc);
	virtual VOID Update();

public:
	virtual ~WinBase() = default;

	bool NewWin(HINSTANCE hInst, int width, int height, LPCSTR winName);
	int MessageLoop();
	void SetTimerFlow(int flow);
	SIZE GetWindowSize();
};