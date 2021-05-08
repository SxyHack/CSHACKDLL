#pragma once
#include <d3d9.h>

#define PI 3.1415927f

class Vector2
{
public:
	Vector2(float X, float Y) 
	{
		this->X = X;
		this->Y = Y;
	}

public:
	float X;
	float Y;
};

class Vector3
{
public:
	Vector3();
	Vector3(float x, float y, float z);

	// ×ª»»ÎªÆÁÄ»×ø±ê, DX9
	Vector2 ToScreenPos(LPDIRECT3DDEVICE9 pDevice);

	Vector3 operator-(Vector3 vec);
	Vector3 operator/(float num);

	float Magnitude();
	float Dot(Vector3 vec);

public:
	float X;
	float Y;
	float Z;
};

