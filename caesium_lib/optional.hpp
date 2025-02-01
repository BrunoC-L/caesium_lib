#pragma once
#include <optional>

namespace caesium_lib {
	namespace optional {
		template <typename T>
		WRAPPER_FOR(std::optional<T>);

		template <typename T>
		inline constexpr bool has_value(const type<T>& optional) {
			return optional._value.has_value();
		}

		template <typename T>
		inline constexpr bool is_empty(const type<T>& optional) {
			return !optional._value.has_value();
		}

		template <typename T>
		inline constexpr const T& value(const type<T>& optional) {
			return optional._value.value();
		}

		template <typename T>
		inline constexpr T& value(type<T>& optional) {
			return optional._value.value();
		}

		template <typename T>
		inline constexpr T value(type<T>&& optional) {
			return std::move(optional)._value.value();
		}
	}
}

template <typename T>
inline constexpr caesium_lib::optional::type<T> copy(const caesium_lib::optional::type<T>& x);

template <typename T>
inline constexpr std::optional<T> copy(const std::optional<T>& x) {
	if (x.has_value())
		return std::optional<T>{ copy(x.value()) };
	else
		return std::optional<T>{ std::nullopt };
}

template <typename T>
inline constexpr caesium_lib::optional::type<T> copy(const caesium_lib::optional::type<T>& x) {
	if (caesium_lib::optional::has_value(x))
		return caesium_lib::optional::type<T>{ copy(x._value.value()) };
	else
		return caesium_lib::optional::type<T>{ std::nullopt };
}

DISABLE_BAD_MOVE_TEMPLATE(caesium_lib::optional::type)
