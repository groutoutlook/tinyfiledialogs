#include "tfd.hpp"
#include <print>
#include <iostream>
auto main() -> int {

	auto retPathFiles = tfd::openFile(
		"Open File",
		std::filesystem::current_path().parent_path(),
		std::vector<std::string>{ "*.txt", "*.cpp", ".h", ".hpp" },
		"Text Files"
	);

	std::println("files : {}", retPathFiles);

	{
		auto retPath = tfd::openFolder(
			"Open A Folder",
			std::filesystem::path{ retPathFiles }.parent_path()
		);

		std::println("folder: {}", retPath.string());
	}
	std::println("Press any key to continue...");
	int ch = std::cin.get();
	return 0;
}