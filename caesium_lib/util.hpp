#pragma once
#include <type_traits>
#include <utility>

#define DISABLE_BAD_MOVE_TEMPLATE(tmpl) \
namespace std {\
	template <typename... Ts> tmpl<Ts...>&& move(const tmpl<Ts...>&) = delete;\
	template <typename... Ts> tmpl<Ts...>&& move(tmpl<Ts...>&&) = delete;\
}

#define DISABLE_BAD_MOVE(T) \
namespace std {\
	T&& move(const T&) = delete;\
	T&& move(T&&) = delete;\
}

#define WRAPPER_FOR(T) \
struct type {\
	T _value;\
	constexpr type(type&&) = default;\
	constexpr type& operator=(type&&) = default;\
	constexpr type(const type&) = delete;\
	constexpr type& operator=(const type&) = delete;\
	inline constexpr type(auto&& t) : _value(std::forward<decltype(t)>(t)) {\
		static_assert(!std::is_same_v<std::remove_cvref_t<decltype(t)>, type>, \
		"copy constructor disabled, use caesium_lib::copy(...) to copy and std::move(...) to move");\
	}\
};

namespace caesium_lib {
	template <typename T>
	constexpr inline T copy(T t) {
		static_assert(!sizeof(T*), "missing definition for `T copy<T>(const T& t)` see template instantiation context for information on T");
	}

	constexpr inline int copy(const int& t) {
		return t;
	}

	constexpr inline double copy(const double& t) {
		return t;
	}

	constexpr inline float copy(const float& t) {
		return t;
	}

	constexpr inline size_t copy(const size_t& t) {
		return t;
	}

	constexpr inline char copy(const char& t) {
		return t;
	}

	constexpr inline unsigned copy(const unsigned& t) {
		return t;
	}
}