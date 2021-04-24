#include "CSBot.h"
#include "../dump/Offsets.h"

CSBot::CSBot(uintptr_t offset)
	: Offset(offset)
	, HealthPtr(0)
	, XPtr(0)
	, YPtr(0)
	, ZPtr(0)
{
	HealthPtr = Offset + Offsets::Bot::BOT_HEALTH;
	XPtr = Offset + Offsets::Bot::BOT_X;
	YPtr = Offset + Offsets::Bot::BOT_Y;
	ZPtr = Offset + Offsets::Bot::BOT_Z;
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
