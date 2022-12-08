#undef UNICODE
#include "WinBase.h"

WinBase *MainWindow = nullptr;

LRESULT CALLBACK WndProc(HWND hWnd, UINT message, WPARAM wParam, LPARAM lParam)
{
	return MainWindow->MyWndProc(hWnd, message, wParam, lParam);
}

VOID WinBase::RegClass()
{
	WNDCLASS mywnd = {};

	mywnd.lpszClassName = ClassName.c_str();
	mywnd.hInstance = hInst;
	mywnd.lpfnWndProc = WndProc;
	mywnd.hbrBackground = (HBRUSH)GetStockObject(BLACK_BRUSH);
	mywnd.hIcon = LoadIcon(hInst, IDI_APPLICATION);
	mywnd.hCursor = LoadCursor(hInst, IDC_ARROW);

	RegisterClass(&mywnd);
}

BOOL WinBase::MakeWindow()
{
	MainWindow = this;

	RECT rect = { 0, 0, WinSize.cx, WinSize.cy };

	AdjustWindowRect(&rect, WS_OVERLAPPEDWINDOW, FALSE);

	hWnd = CreateWindow(ClassName.c_str(), WinName.c_str(), WS_OVERLAPPEDWINDOW, 750, 50, rect.right - rect.left, rect.bottom - rect.top, nullptr, nullptr, hInst, nullptr);

	if (hWnd == nullptr)
	{
		MainWindow = nullptr;
		return FALSE;
	}

	ShowWindow(hWnd, SW_SHOW);

	return TRUE;
}

LRESULT WinBase::MyWndProc(HWND hWnd, UINT message, WPARAM wParam, LPARAM lParam)
{		
	switch (message)
	{

	case WM_TIMER:
	{
		Update();
		InvalidateRect(hWnd, nullptr, TRUE);
	}break;

	case WM_PAINT:
	{
		PAINTSTRUCT	ps;
		HDC			hdc = BeginPaint(hWnd, &ps);

		Render(hdc);

		EndPaint(hWnd, &ps);
	}break;

	case WM_DESTROY:
	{
		PostQuitMessage(0);
	}break;

	}

	return DefWindowProc(hWnd, message, wParam, lParam);
}

VOID WinBase::Render(HDC hdc)
{
	return VOID();
}

VOID WinBase::Update()
{
	return VOID();
}

bool WinBase::NewWin(HINSTANCE hInst, int width, int height, LPCSTR winName)
{
	hInst = hInst;
	ClassName = winName;
	WinName = winName;
	WinSize.cx = width;
	WinSize.cy = height;

	RegClass();

	if (MakeWindow() == FALSE)
	{
		return FALSE;
	}

	return TRUE;
}

int WinBase::MessageLoop()
{
	SetTimer(hWnd, 1, time_flow, nullptr);

	MSG msg = {};

	while (GetMessage(&msg, nullptr, 0u, 0u))
	{
		TranslateMessage(&msg);
		DispatchMessage(&msg);
	}

	KillTimer(hWnd, 0);

	return msg.wParam;
}

void WinBase::SetTimerFlow(int flow)
{
	time_flow = flow;
}

SIZE WinBase::GetWindowSize()
{
	return WinSize;
}