#include "CSBotFinder.h"
#include "../dump/Offsets.h"

#include <Windows.h>
#include <iostream>

bool CSBotFinder::Execute(MapBot& result)
{
    static HMODULE hMod = NULL;
    if (hMod == NULL) {
        hMod = GetModuleHandle(L"server.dll");

		if (hMod == NULL) {
			return false;
		}
    }

    uintptr_t dwBaseAddr = ((uintptr_t)hMod) + Offsets::Bot::BOT_ENTRY_ADDRESS;
    uintptr_t* pBaseAddr = (uintptr_t*)dwBaseAddr;
    uintptr_t dwBotAddr = *(uintptr_t*)dwBaseAddr;

	std::cout << "Module: 0x" << std::hex << hMod
        << " Offset: 0x" << std::hex << Offsets::Bot::BOT_ENTRY_ADDRESS
        << " dwBaseAddr: 0x" << std::hex << dwBaseAddr 
        << " Ptr:0x" << pBaseAddr 
        << " PtrValue:0x" << dwBotAddr
        << std::endl;

	std::cout << "========================= Entry =============================" << std::endl;

    while (dwBotAddr != 0)
    {
		std::cout << "dwBotAddr: 0x" << std::hex << dwBotAddr << std::endl;

        auto search = result.find(dwBotAddr);
        if (search != result.end())
        {
            std::cout << "bot: 0x" << std::hex << dwBotAddr << " found" << std::endl;
			dwBotAddr = *(uintptr_t*)(dwBotAddr + Offsets::Bot::BOT_NEXT);
            continue;
        }

		CSBot* pBot = new CSBot(dwBotAddr);
        result[dwBotAddr] = pBot;

		dwBotAddr = *(uintptr_t*)(dwBotAddr + Offsets::Bot::BOT_NEXT);
    }
    
	std::cout << "========================= END ==============================" << std::endl;

    return true;
}
