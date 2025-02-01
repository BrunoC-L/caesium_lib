#pragma once
#include <vector>

namespace caesium_lib {
	namespace vector {
		template <typename T>
		WRAPPER_FOR(std::vector<T>);

		template <typename T>
		type<T> make_empty() {
			return std::vector<T>{};
		}

		template <typename T>
		type<T> make_with_capacity(size_t n) {
			auto res = make_empty<T>();
			reserve(res, n);
			return res;
		}

		template <typename T>
		type<T> push(type<T>&& vec, auto&& e) {
			type<T> res{ std::move(vec) };
			res._value.push_back(std::forward<decltype(e)>(e));
			return res;
		}

		template <typename T>
		auto begin(type<T>& vec) {
			return begin(vec._value);
		}

		template <typename T>
		auto begin(const type<T>& vec) {
			return begin(vec._value);
		}

		template <typename T>
		auto end(type<T>& vec) {
			return end(vec._value);
		}

		template <typename T>
		auto end(const type<T>& vec) {
			return end(vec._value);
		}

		template <typename T>
		void reserve(const type<T>& vec, size_t n) {
			vec._value.reserve(n);
		}

		template <typename T>
		type<T> reserve(type<T>&& vec, size_t n) {
			vec._value.reserve(n);
			return std::move(vec);
		}
	}
}

// forward declare to allow copy(std::vector<caesium_lib::vector::type<T>>)
template <typename T>
constexpr inline caesium_lib::vector::type<T> copy(const caesium_lib::vector::type<T>& x);

template <typename T>
constexpr inline std::vector<T> copy(const std::vector<T>& x) {
	std::vector<T> res{};
	res.reserve(x.size());
	for (const T& e : x)
		res.push_back(copy(e));
	return res;
}

template <typename T>
constexpr inline caesium_lib::vector::type<T> copy(const caesium_lib::vector::type<T>& x) {
	return copy(x._value);
}

DISABLE_BAD_MOVE_TEMPLATE(caesium_lib::vector::type)
