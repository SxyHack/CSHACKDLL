#include "Player.h"
#include "dump/Offsets.h"

Player::Player()
    : mWindowHeight(0)
    , mWindowWidth(0)
{
}

Player& Player::Get()
{
    static Player instance;
    return instance;
}

bool Player::Initial()
{
    HMODULE hMod = GetModuleHandle(L"client.dll");
    uintptr_t matrixAddr = (uintptr_t)(hMod + Offsets::Player::dwViewMatrix);
    //mViewMatrix = (float*)matrixAddr;

    return false;
}

bool Player::WorldToScreen(Vector3 pos, Vector2& screen)
{
    return false;
}
