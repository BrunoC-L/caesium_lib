#pragma once
#include "util.hpp"
#include <string>
#include "optional.hpp"

namespace caesium_lib {
	namespace string {
		WRAPPER_FOR(std::string)

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

		inline constexpr type reserve(int new_capacity) {
			type str = "";
			str._value.reserve(new_capacity);
			return std::move(str);
		}

		inline constexpr type reserve(type str, int new_capacity) {
			str._value.reserve(new_capacity);
			return std::move(str);
		}

		inline constexpr type join(type str1, type str2) {
			str1._value += std::move(str2)._value;
			return std::move(str1);
		}

		inline constexpr type join(type str1, type str2, auto&&... strs) {
			return join(join(std::move(str1), std::move(str2), std::forward<decltype(strs)>(strs)...));
		}
	}

	constexpr inline string::type copy(const string::type& x) {
		return { x._value };
	}

	constexpr inline std::string copy(const std::string& t) {
		return t;
	}
}

DISABLE_BAD_MOVE(caesium_lib::string::type)
