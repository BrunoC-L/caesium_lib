#pragma once
#include "util.hpp"
#include <filesystem>

namespace caesium_lib {
	namespace filesystem {
		namespace file {
			WRAPPER_FOR(std::filesystem::directory_entry);
		}
	}

	inline filesystem::file::type copy(const filesystem::file::type& e) {
		return e._value;
	}
}

DISABLE_BAD_MOVE(caesium_lib::filesystem::file::type)
