#pragma once
#include "util.hpp"
#include <string>
#include "optional.hpp"

template <typename>
struct is_char_array {
	static constexpr bool value = false;
};

template <size_t n>
struct is_char_array<char[n]> {
	static constexpr bool value = true;
};

namespace caesium_lib {
	namespace string {
		struct type {
			std::string _value;
			constexpr type(type&&) = default; 
			constexpr type& operator=(type&&) = default; 
			constexpr type(const type&) = delete; 
			constexpr type& operator=(const type&) = delete; 
			inline constexpr type(auto&& t)
				requires (!std::is_same_v<std::remove_cvref_t<decltype(t)>, type>) &&
			(std::is_same_v<std::remove_cvref_t<decltype(t)>, std::string> ||
				is_char_array<std::remove_cvref_t<decltype(t)>>::value)
				: _value(std::forward<decltype(t)>(t)) {
			}
		};

		inline constexpr int size(const type& str) {
			return (int)str._value.size();
		}

		inline constexpr int capacity(const type& str) {
			return (int)str._value.capacity();
		}

		inline constexpr bool equals(const type& str, const type& other) {
			return str._value == other._value;
		}

		inline constexpr bool equals(const type& str, const auto& other) {
			return str._value == other;
		}

		inline constexpr bool begins_with(const type& str, auto&& substr) {
			return std::string_view(str._value).starts_with(substr);
		}

		inline constexpr bool ends_with(const type& str, auto&& substr) {
			return std::string_view(str._value).ends_with(substr);
		}

		inline constexpr bool contains(const type& str, auto&& substr) {
			auto res = str._value.find(substr);
			return res != std::string::npos;
		}

		inline constexpr std::strong_ordering compare(const type& str, const type& other) {
			return str._value <=> other._value;
		}

		inline constexpr std::strong_ordering compare(const type& str, const auto& other) {
			return str._value <=> other;
		}

		inline constexpr optional::type<std::string::const_iterator> find(const type& str, auto&& substr) {
			if (auto res = str._value.find(substr); res != std::string::npos)
				return str._value.begin() + res;
			else
				return std::nullopt;
		}

		inline constexpr type reserve(unsigned new_capacity) {
			type str = "";
			str._value.reserve(new_capacity);
			return str;
		}

		inline constexpr type reserve(type str, unsigned new_capacity) {
			str._value.reserve(new_capacity);
			return str;
		}

		inline constexpr type join(type str1, type str2) {
			str1._value += std::move(str2)._value;
			return str1;
		}

		inline constexpr type join(type str1, type str2, auto&&... strs) {
			return join(join(std::move(str1), std::move(str2), std::forward<decltype(strs)>(strs)...));
		}
	}
}

template <>
struct copy_t<caesium_lib::string::type> {
	static constexpr caesium_lib::string::type copy(const caesium_lib::string::type& t) { return { t._value }; }
};

template <>
struct copy_t<std::string> {
	static constexpr std::string copy(const std::string& t) { return t; }
};

DISABLE_BAD_MOVE(caesium_lib::string::type)
