#pragma once
#include "Headers.h"

class UIBox
{
public:
	void SetPos(float x, float y);
	void SetSize(float x, float y);
	float GetPosX();
	float GetposY();
	float GetWidth();
	float GetHeight();
private:
	ofVec2f pos;
	float width;
	float height;
};