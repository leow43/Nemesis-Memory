#include "memory.hpp"

bool memory::attach_to_process(const std::string& process_name)
{
	details::process_id = memory::find_process_id(process_name);
	details::base_address = memory::find_base_address(process_name);

	return true;
}

uintptr_t memory::find_process_id(const std::string& process_name)
{
	HANDLE snapshot = CreateToolhelp32Snapshot(TH32CS_SNAPPROCESS, 0);
	PROCESSENTRY32 entry32;

	entry32.dwSize = sizeof(PROCESSENTRY32);
	if (Process32First(snapshot, &entry32)) {
		do
		{
			if (!lstrcmpi(entry32.szExeFile, process_name.c_str())) {
				CloseHandle(snapshot);
				memory::details::process_id = entry32.th32ProcessID;
				return entry32.th32ProcessID;
			}
		} while (Process32Next(snapshot, &entry32));
	}

	CloseHandle(snapshot);
	return NULL;
}

uintptr_t memory::find_base_address(const std::string& process_name)
{
	HANDLE snapshot = CreateToolhelp32Snapshot(TH32CS_SNAPMODULE | TH32CS_SNAPMODULE32, details::process_id);
	MODULEENTRY32 entry32;

	entry32.dwSize = sizeof(MODULEENTRY32);
	if (Module32First(snapshot, &entry32))
	{
		do
		{
			if (!lstrcmpi(entry32.szModule, process_name.c_str())) {
				CloseHandle(snapshot);
				details::base_address = (uintptr_t)entry32.modBaseAddr;
				return (uintptr_t)entry32.modBaseAddr;
			}
		} while (Module32Next(snapshot, &entry32));
	}
	
	CloseHandle(snapshot);
	return NULL;
}