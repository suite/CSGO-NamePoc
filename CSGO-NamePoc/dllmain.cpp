// dllmain.cpp : Defines the entry point for the DLL application.
#include "pch.h"
#include <windows.h>
#include <iostream>
#include "Interfaces.h"
#include <stdio.h>
#include <cstdlib>
DWORD WINAPI HackThread(HMODULE hModule)
{
	AllocConsole();
	FILE* f;
	freopen_s(&f, "CONOUT$", "w", stdout);

	DWORD clientAddr = reinterpret_cast<DWORD>(GetModuleHandle(L"client_panorama.dll"));

	while (!GetAsyncKeyState(VK_INSERT) & 1)
	{
		//Loop through all available entities.
		for (int x = 1; x < g_config.engine->getMaxClients(); x++) {

			//Get player information
			player_info_struct player_info;
			g_config.engine->getPlayerInfo(x + 1, player_info);

			//dwEntityList = 0x4D44A04;
			DWORD player = *(DWORD*)(clientAddr + (DWORD)0x4D44A04 + x * 0x10);
			if (player == 0) { continue; }

			bool dormant = *(bool*)(player + (DWORD)0xED);
			if (dormant) { continue; }

			DWORD team = *(DWORD*)(player + (DWORD)0xF4);
			if (team != 2 && team != 3) { continue; }

			//m_iHealth = 0x100;
			INT* healthAddr = reinterpret_cast<INT*>(player + 0x100);

			printf("%s %d \n", player_info.name, *healthAddr);

		}
		
		std::system("cls");
		Sleep(20);
	}

	if (f) fclose(f);
	FreeConsole();
	FreeLibraryAndExitThread(hModule, 0);
	return 0;
}

BOOL APIENTRY DllMain(HMODULE hModule, DWORD  ul_reason_for_call, LPVOID lpReserved)
{
	switch (ul_reason_for_call)
	{
	case DLL_PROCESS_ATTACH:
	{
		HANDLE hdl = CreateThread(nullptr, 0, (LPTHREAD_START_ROUTINE)HackThread, hModule, 0, nullptr);
		if (hdl) CloseHandle(hdl);
		break;
	}
	case DLL_THREAD_ATTACH:
	case DLL_THREAD_DETACH:
	case DLL_PROCESS_DETACH:
		break;
	}
	return TRUE;
}

