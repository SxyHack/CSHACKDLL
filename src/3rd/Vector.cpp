#include "Vector.h"

#include <iostream>
#include <D3dx9math.h>

Vector3::Vector3()
	: X(0)
	, Y(0)
	, Z(0)
{
}

Vector3::Vector3(float x, float y, float z)
	: X(x)
	, Y(y)
	, Z(z)
{

}

Vector2 Vector3::ToScreenPos(LPDIRECT3DDEVICE9 pDevice)
{
	D3DVIEWPORT9 viewPort;
	D3DXMATRIX view, projection, world;

	pDevice->GetViewport(&viewPort);
	pDevice->GetTransform(D3DTS_VIEW, &view);
	pDevice->GetTransform(D3DTS_PROJECTION, &projection);
	D3DXMatrixIdentity(&world);

	D3DXVECTOR3 out;
	D3DXVECTOR3 pos(X, Y, Z);
	D3DXVec3Project(&out, &pos, &viewPort, &projection, &view, &world);

	std::cout << "screen XY:" << out.x << ", " << out.y << std::endl;

    return Vector2(out.x, out.y);
}

Vector3 Vector3::operator-(Vector3 vec)
{
	Vector3 diff;
	diff.X = X - vec.X;
	diff.Y = Y - vec.Y;
	diff.Z = Z - vec.Z;
	return diff;
}

Vector3 Vector3::operator/(float num)
{
	Vector3 ret;
	ret.X = X / num;
	ret.Y = Y / num;
	ret.Z = Z / num;
	return ret;
}

float Vector3::Magnitude()
{
	return sqrtf(X * X + Y * Y + Z * Z);
}

float Vector3::Dot(Vector3 vec)
{
	return X * vec.X + Y * vec.Y + Z * vec.Z;
}
