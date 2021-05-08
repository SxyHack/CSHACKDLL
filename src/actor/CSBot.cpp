#include "CSBot.h"
#include "../dump/Offsets.h"
#include <iostream>

CSBot::CSBot(uintptr_t baseAddr)
	: BaseAddr(baseAddr)
	, HealthPtr(0)
	, XPtr(0)
	, YPtr(0)
	, ZPtr(0)
{
	HealthPtr = BaseAddr + Offsets::Bot::BOT_HEALTH;
	XPtr = BaseAddr + Offsets::Bot::BOT_X;
	YPtr = BaseAddr + Offsets::Bot::BOT_Y;
	ZPtr = BaseAddr + Offsets::Bot::BOT_Z;

	std::cout << "HealthPtr:" << std::hex << HealthPtr << std::endl;
	std::cout << "XPtr:" << std::hex << XPtr << std::endl;
	std::cout << "YPtr:" << std::hex << YPtr << std::endl;
	std::cout << "ZPtr:" << std::hex << ZPtr << std::endl;
}

CSBot::~CSBot()
{
}

INT32 CSBot::Health()
{
	return *(INT32*)HealthPtr;
}

float CSBot::X()
{
	return *(float*)XPtr;
}

float CSBot::Y()
{
	return *(float*)YPtr;
}

float CSBot::Z()
{
	return *(float*)ZPtr;
}
