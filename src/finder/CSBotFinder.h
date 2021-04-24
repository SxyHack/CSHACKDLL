#pragma once

#include "../actor/CSBot.h"
#include <vector>
#include <map>

typedef std::vector<CSBot*> BotList;
typedef std::map<uintptr_t, CSBot*> MapBot;

class CSBotFinder
{
public:
	static bool Execute(MapBot& list);
};

