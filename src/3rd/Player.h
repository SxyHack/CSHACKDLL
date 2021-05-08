#pragma once
#include "Vector.h"

class Player
{
public:
	static Player& Get();

	bool Initial();
	bool WorldToScreen(Vector3 pos, Vector2& screen);

protected:
	Player();

private:
	int mWindowWidth;
	int mWindowHeight;
	float mViewMatrix[16];
};

