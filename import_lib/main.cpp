#include "lib.hpp"
#include <iostream>
#include <assert.h>

template <typename T>
constexpr bool is_move_constructible_and_not_copy_assignable_v = !std::is_copy_assignable_v<T> && std::is_move_constructible_v<T>;
int main() {
	using namespace caesium_lib;

	{
		static_assert(is_move_constructible_and_not_copy_assignable_v<string::type>);
		static_assert(is_move_constructible_and_not_copy_assignable_v<optional::type<int>>);
		static_assert(is_move_constructible_and_not_copy_assignable_v<variant::type<int>>);
	}
	{
		const string::type str = "123";
		const auto s2 = copy(str);
	}
	{
		const string::type str1 = "123";
		const string::type str2 = "123";
		const string::type str3 = "1234";
		{
			const bool b = string::equals(str1, str2);
			assert(b);
		}
		{
			const bool b = string::equals(str1, "123");
			assert(b);
		}
		{
			const bool b = string::equals(str1, str3);
			assert(!b);
		}
		{
			const bool b = string::equals(str1, "1234");
			assert(!b);
		}
	}
	{
		const string::type str1 = "123";
		const string::type str2 = "123";
		const string::type str3 = "1234";
		const string::type str4 = "12";
		{
			const auto res = string::compare(str1, str2);
			assert(res == res.equal);
		}
		{
			const auto res = string::compare(str1, "123");
			assert(res == res.equal);
		}
		{
			const auto res = string::compare(str1, str3);
			assert(res == res.less);
		}
		{
			const auto res = string::compare(str1, "1234");
			assert(res == res.less);
		}
		{
			const auto res = string::compare(str1, str4);
			assert(res == res.greater);
		}
		{
			const auto res = string::compare(str1, "12");
			assert(res == res.greater);
		}
	}
	{
		const string::type str = "123";
		const bool b = string::begins_with(str, "123");
		assert(b);
	}
	{
		const string::type str = "123";
		const auto it = string::find(str, "2");
		const bool b = optional::has_value(it);
		assert(b);
		const char c = *optional::value(it);
		assert(c == '2');
	}
	{
		string::type str = "123";
		string::type str2 = std::move(str);
		string::type str3 = copy(str2);
		const string::type str4 = "123";
		copy(str4);
		// std::move(str4); // should not compile
	}
	{
		auto s = string::reserve(100);
		auto s2 = copy(s);
		auto s3 = string::join(std::move(s), std::move(s2));
	}
	{
		using namespace std::string_literals;
		auto entries = filesystem::entries(".");
		for (const auto& entry : entries) {
			(void)entry;
		}
	}
	{
		auto v1 = vector::make_empty<vector::type<int>>();
		auto v2 = vector::push(std::move(v1), 3);
		auto v3 = copy(v2);
		auto v4 = std::move(v3);
	}
	{
		auto vstr = variant::type<int, string::type>{ string::type{"123"} };
		auto vint = variant::type<int, string::type>{ 1 };

		assert(std::holds_alternative<string::type>(vstr._value));
		assert(std::holds_alternative<int>(vint._value));

		auto vstr2 = std::move(vstr);
		auto vint2 = std::move(vint);
		auto vstr3 = copy(vstr2);
		auto vint3 = copy(vint2);
		std::swap(vstr3, vint3);
	}

	return 0;
}
