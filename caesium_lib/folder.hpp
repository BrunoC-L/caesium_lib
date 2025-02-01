#pragma once
#include "util.hpp"
#include <filesystem>

namespace caesium_lib {

	namespace filesystem {
		namespace folder {
			WRAPPER_FOR(std::filesystem::directory_entry)
		}

		inline vector::type<variant::type<file::type, folder::type>> entries(const std::filesystem::directory_iterator& it) {
			vector::type<variant::type<file::type, folder::type>> res{ std::vector<variant::type<file::type, folder::type>>{} };
			for (const auto& file_or_folder : std::filesystem::directory_iterator(it))
				if (file_or_folder.is_directory())
					res._value.push_back(folder::type{ file_or_folder });
				else
					res._value.push_back(file::type{ file_or_folder });
			return res;
		}

		inline vector::type<variant::type<file::type, folder::type>> entries(const folder::type& folder) {
			return entries(std::filesystem::directory_iterator(folder._value));
		}

		inline vector::type<variant::type<file::type, folder::type>> entries(const char* folder_name) {
			return entries(std::filesystem::directory_iterator(folder_name));
		}

		inline vector::type<variant::type<file::type, folder::type>> entries(const std::string& folder_name) {
			return entries(folder_name.c_str());
		}

		inline vector::type<variant::type<file::type, folder::type>> entries(const caesium_lib::string::type& folder_name) {
			return entries(folder_name._value.c_str());
		}
	}
}

inline caesium_lib::filesystem::folder::type copy(const caesium_lib::filesystem::folder::type& e) {
	return e._value;
}

DISABLE_BAD_MOVE(caesium_lib::filesystem::folder::type)
