#pragma once

#include <Windows.h>

class CSBot
{
public:
	CSBot(uintptr_t offset);
	~CSBot();

	INT32 Health();
	float X();
	float Y();
	float Z();

public:
	uintptr_t  Offset;
	uintptr_t  HealthPtr;
	uintptr_t  XPtr;
	uintptr_t  YPtr;
	uintptr_t  ZPtr;
};

