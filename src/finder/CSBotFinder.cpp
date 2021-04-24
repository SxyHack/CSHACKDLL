#include "CSBotFinder.h"

#include "../dump/Offsets.h"
#include <Windows.h>

bool CSBotFinder::Execute(MapBot& result)
{
    HMODULE hMod = GetModuleHandle(L"server.dll");
    if (hMod == NULL)
        return false;

    uintptr_t dwBotAddr = (uintptr_t)hMod + Offsets::Bot::BOT_ENTRY_ADDRESS;

    while (dwBotAddr != 0)
    {
        auto search = result.find(dwBotAddr);
        if (search != result.end())
        {
            dwBotAddr += Offsets::Bot::BOT_NEXT;
            continue;
        }

		CSBot* pBot = new CSBot(dwBotAddr);
        result[dwBotAddr] = pBot;

		dwBotAddr += Offsets::Bot::BOT_NEXT;
    }
    
    return true;
}
