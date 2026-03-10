#include "memory/memory.hpp"
#include <print>

auto main(int arg[], char* argv) -> int
{
	if (!memory::attach_to_process("notepad.exe")) {
		std::printf("failed to attach to process -> %s\n", memory::details::process_name);
		return 0;
	}
	std::printf("successfully attached to process -> %s\n", memory::details::process_name);

	std::printf("processid -> %d\n", memory::details::process_id);
	std::printf("base address -> 0x%llx\n", memory::details::base_address);

	std::cin.get();
}