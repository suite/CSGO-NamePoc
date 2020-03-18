#pragma once

#include <memory>
#include <string>
#include <type_traits>
#include <Windows.h>


#include "Engine.h"

typedef struct configuration_struct
{
	Engine* engine;

	configuration_struct()
	{
		engine = find<Engine>(L"engine", "VEngineClient014");
	}

	template <typename T>
	auto find(const wchar_t* module, const char* name) noexcept
	{
		if (HMODULE moduleHandle = GetModuleHandleW(module))
			if (const auto createInterface = reinterpret_cast<std::add_pointer_t<T * (const char* name, int* returnCode)>>(GetProcAddress(moduleHandle, "CreateInterface")))
				if (T * foundInterface = createInterface(name, nullptr))
					return foundInterface;

		MessageBoxA(nullptr, "find", NULL, MB_OK | MB_ICONERROR);
		std::exit(EXIT_FAILURE);
	}

} configuration_struct;

configuration_struct g_config;
