// dllmain.cpp : 定义 DLL 应用程序的入口点。
#include "pch.h"
#include "third-party/kiero/kiero.h"
#include "third-party/imgui/backends/imgui_impl_win32.h"
#include "third-party/imgui/backends/imgui_impl_dx9.h"
#include <d3d9.h>

extern IMGUI_IMPL_API LRESULT ImGui_ImplWin32_WndProcHandler(HWND hWnd, UINT msg, WPARAM wParam, LPARAM lParam);

typedef long(__stdcall* EndScene)(LPDIRECT3DDEVICE9);
static EndScene gOldEndScene = NULL;
static WNDPROC  gOldWndProc  = NULL;
static HWND     gHandle      = NULL;
static bool     ginit        = false;


void InitImGui(LPDIRECT3DDEVICE9 pDevice)
{
	ImGui::CreateContext();
	ImGuiIO& io = ImGui::GetIO();
	io.ConfigFlags = ImGuiConfigFlags_NoMouseCursorChange;
	ImGui_ImplWin32_Init(gHandle);
	ImGui_ImplDX9_Init(pDevice);
}


// Declare the detour function
long __stdcall hkEndScene(LPDIRECT3DDEVICE9 pDevice)
{
	if (!ginit) {
		InitImGui(pDevice);
		ginit = true;
	}

	ImGui_ImplDX9_NewFrame();
	ImGui_ImplWin32_NewFrame();
	ImGui::NewFrame();

	ImGui::Begin("ImGui Window");
	ImGui::End();

	ImGui::EndFrame();
	ImGui::Render();
	ImGui_ImplDX9_RenderDrawData(ImGui::GetDrawData());

	return gOldEndScene(pDevice);
}

BOOL CALLBACK EnumWindowsCallback(HWND handle, LPARAM lParam)
{
	DWORD wndProcId;
	GetWindowThreadProcessId(handle, &wndProcId);

	if (GetCurrentProcessId() != wndProcId)
		return TRUE; // skip to next window

	gHandle = handle;
	return FALSE; // window found abort search
}

LRESULT __stdcall WndProc(const HWND hWnd, UINT uMsg, WPARAM wParam, LPARAM lParam) {

	if (true && ImGui_ImplWin32_WndProcHandler(hWnd, uMsg, wParam, lParam))
		return true;

	return CallWindowProc(gOldWndProc, hWnd, uMsg, wParam, lParam);
}

void GetProcessWindow()
{
	gHandle = NULL;
	do 
		EnumWindows(EnumWindowsCallback, NULL);
	while (gHandle == NULL);
}

int gHookThread()
{
	if (kiero::init(kiero::RenderType::D3D9) != kiero::Status::Success) {
		return 0;
	}

	// define KIERO_USE_MINHOOK must be 1
	// the index of the required function can be found in the METHODSTABLE.txt
	kiero::bind(42, (void**)&gOldEndScene, hkEndScene);

	GetProcessWindow();
	
	gOldWndProc = (WNDPROC)SetWindowLongPtr(gHandle, GWL_WNDPROC, (LONG_PTR)WndProc);
	// If you just need to get the function address you can use the kiero::getMethodsTable function
	//oEndScene = (EndScene)kiero::getMethodsTable()[42];
	return 0;
}


BOOL APIENTRY DllMain(HMODULE hModule, DWORD  ul_reason_for_call, LPVOID lpReserved)
{
	DisableThreadLibraryCalls(hModule);

	switch (ul_reason_for_call)
	{
	case DLL_PROCESS_ATTACH:
		CreateThread(NULL, 0, (LPTHREAD_START_ROUTINE)gHookThread, NULL, 0, NULL);
		break;
	case DLL_PROCESS_DETACH:
		kiero::shutdown();
		break;
	}
	return TRUE;
}

