#pragma once
#include <Windows.h>
#include <iostream>
#include <vector>
#include <string>
#include <TlHelp32.h>
#include <Psapi.h>

namespace memory
{
	namespace details
	{
		inline std::string process_name = "notepad.exe";
		inline std::uintptr_t base_address = 0;
		inline std::uintptr_t process_id = 0;
		inline HANDLE process_handle = 0;
	}

	bool attach_to_process(const std::string& process_name);
	std::uintptr_t find_process_id(const std::string& process_name);
	std::uintptr_t find_base_address(const std::string& process_name);

	template<typename T>
	T read(uint64_t address)
	{
		T buffer{};

		ReadProcessMemory(details::process_handle, (PVOID)address, &buffer, sizeof(T), nullptr);
		return buffer;
	}

	template<typename T>
	T write(uint64_t address, T& buffer)
	{
		WriteProcessMemory(details::process_handle, (PVOID)address, (PVOID)&buffer, sizeof(T), nullptr);
	}
}