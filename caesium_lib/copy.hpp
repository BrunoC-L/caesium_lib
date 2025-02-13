#pragma once

template <typename T>
struct copy_t {
	static constexpr T copy(const T& t) { return t; }
};

template <typename T>
T copy(const T& t) {
	return copy_t<T>::copy(t);
}
