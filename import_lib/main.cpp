#include "lib.hpp"
#include <iostream>

template <typename T>
constexpr bool is_move_constructible_and_not_copy_assignable_v = !std::is_copy_assignable_v<T> && std::is_move_constructible_v<T>;
int main() {

	{
		static_assert(is_move_constructible_and_not_copy_assignable_v<caesium_lib::string::type>);
		static_assert(is_move_constructible_and_not_copy_assignable_v<caesium_lib::optional::type<int>>);
		static_assert(is_move_constructible_and_not_copy_assignable_v<caesium_lib::variant::type<int>>);
	}
	{
		const caesium_lib::string::type str = "123";
		const auto s2 = caesium_lib::copy(str);
	}
	{
		const caesium_lib::string::type str1 = "123";
		const caesium_lib::string::type str2 = "123";
		const caesium_lib::string::type str3 = "1234";
		{
			const bool b = caesium_lib::string::equals(str1, str2);
			_ASSERT(b);
		}
		{
			const bool b = caesium_lib::string::equals(str1, "123");
			_ASSERT(b);
		}
		{
			const bool b = caesium_lib::string::equals(str1, str3);
			_ASSERT(!b);
		}
		{
			const bool b = caesium_lib::string::equals(str1, "1234");
			_ASSERT(!b);
		}
	}
	{
		const caesium_lib::string::type str1 = "123";
		const caesium_lib::string::type str2 = "123";
		const caesium_lib::string::type str3 = "1234";
		const caesium_lib::string::type str4 = "12";
		{
			const auto res = caesium_lib::string::compare(str1, str2);
			_ASSERT(res == res.equal);
		}
		{
			const auto res = caesium_lib::string::compare(str1, "123");
			_ASSERT(res == res.equal);
		}
		{
			const auto res = caesium_lib::string::compare(str1, str3);
			_ASSERT(res == res.less);
		}
		{
			const auto res = caesium_lib::string::compare(str1, "1234");
			_ASSERT(res == res.less);
		}
		{
			const auto res = caesium_lib::string::compare(str1, str4);
			_ASSERT(res == res.greater);
		}
		{
			const auto res = caesium_lib::string::compare(str1, "12");
			_ASSERT(res == res.greater);
		}
	}
	{
		const caesium_lib::string::type str = "123";
		const bool b = caesium_lib::string::begins_with(str, "123");
		_ASSERT(b);
	}
	{
		const caesium_lib::string::type str = "123";
		const auto it = caesium_lib::string::find(str, "2");
		const bool b = caesium_lib::optional::has_value(it);
		_ASSERT(b);
		const char c = *caesium_lib::optional::value(it);
		_ASSERT(c == '2');
	}
	{
		caesium_lib::string::type str = "123";
		caesium_lib::string::type str2 = std::move(str);
		caesium_lib::string::type str3 = caesium_lib::copy(str2);
		const caesium_lib::string::type str4 = "123";
		caesium_lib::copy(str4);
		// std::move(str4); // should not compile
	}
	{
		auto s = caesium_lib::string::reserve(100);
		auto s2 = caesium_lib::copy(s);
		auto s3 = caesium_lib::string::join(std::move(s), std::move(s2));
	}
	{
		using namespace std::string_literals;
		auto entries = caesium_lib::filesystem::entries("C:/"s);
		for (const auto& entry : entries) {

		}
	}
	{
		auto v1 = caesium_lib::vector::make_empty<caesium_lib::vector::type<int>>();
		auto v2 = caesium_lib::vector::push(std::move(v1), 3);
		auto v3 = caesium_lib::copy(v2);
		auto v4 = std::move(v3);
	}

	return 0;
}
