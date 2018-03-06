#pragma once
#include "windows.h"

// Standard Sketcher drawing colors
enum class ElementColor : COLORREF
{
	BLACK = RGB(0, 0, 0),
	RED = RGB(255, 0, 0),
	GREEN = RGB(0, 255, 0), 
	BLUE = RGB(0, 0, 255),
	PINK = RGB(255,105,180)
};