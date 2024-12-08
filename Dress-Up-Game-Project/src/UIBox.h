#pragma once
#include "Headers.h"

class UIBox
{
public:
	void SetPos(float x, float y);
	void SetSize(float x, float y);
	float GetPosX();
	float GetPosY();
	ofVec2f GetPos();
	float GetWidth();
	float GetHeight();
	ofRectangle hitBox;

private:
	ofVec2f pos;
	float width;
	float height;
};