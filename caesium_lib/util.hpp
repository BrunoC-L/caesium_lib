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

#define WRAPPER_FOR(T, constexpr) \
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

template <typename T> T copy(T t) { return std::move(t); }
constexpr inline bool copy(bool e) { return e; }
constexpr inline char copy(char e) { return e; }
constexpr inline int copy(int e) { return e; }
constexpr inline float copy(float e) { return e; }
constexpr inline unsigned copy(unsigned e) { return e; }
constexpr inline std::size_t copy(std::size_t e) { return e; }
constexpr inline double copy(double e) { return e; }
