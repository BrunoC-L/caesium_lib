#pragma once
#include "util.hpp"
#include <filesystem>

namespace caesium_lib {
	namespace filesystem {
		namespace file {
			WRAPPER_FOR(std::filesystem::directory_entry,);
		}
	}
}

DISABLE_BAD_MOVE(caesium_lib::filesystem::file::type)
