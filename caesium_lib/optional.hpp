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

	template <typename T>
	inline constexpr optional::type<T> copy(const optional::type<T>& x) {
		if (optional::has_value(x))
			return optional::type<T>{ caesium_lib::copy(x._value.value()) };
		else
			return optional::type<T>{ std::nullopt };
	}
}

DISABLE_BAD_MOVE_TEMPLATE(caesium_lib::optional::type)
