#include "Headers.h"

void UIBox::SetPos(float x, float y)
{
	pos.x = x;
	pos.y = y;
}

void UIBox::SetSize(float x, float y)
{
	width = x;
	height = y;
}

float UIBox::GetPosX()
{
	return pos.x;
}

float UIBox::GetposY()
{
	return pos.y;
}
float UIBox::GetWidth()
{
	return width;
}
float UIBox::GetHeight()
{
	return height;
}