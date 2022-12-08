#pragma once
#include <Windows.h>
#include <cmath>
#include "Global.h"

class BaseC
{
public:
	virtual ~BaseC() = default;
	virtual VOID Render(HDC hdc) {}
};