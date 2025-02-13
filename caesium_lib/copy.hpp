#pragma once

template <typename T>
constexpr inline T copy(const T& t);

template <>
constexpr inline bool copy<bool>(const bool& e) { return e; }

template <>
constexpr inline char copy<char>(const char& e) { return e; }

template <>
constexpr inline int copy<int>(const int& e) { return e; }

template <>
constexpr inline float copy<float>(const float& e) { return e; }

template <>
constexpr inline unsigned copy<unsigned>(const unsigned& e) { return e; }

template <>
constexpr inline double copy<double>(const double& e) { return e; }

#include <cstddef>

template <>
constexpr inline size_t copy<size_t>(const size_t& e) { return e; }
