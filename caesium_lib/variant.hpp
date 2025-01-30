#pragma once
#include <variant>

namespace caesium_lib {
	namespace variant {
		template <typename... Ts>
		WRAPPER_FOR(std::variant<Ts...>);

		template <typename... Ts>
		inline constexpr auto visit(const type<Ts...>& variant, const auto& overload_set) {
			return std::visit(overload_set, variant._value);
		}

		template <typename... Ts>
		inline constexpr auto visit(type<Ts...>&& variant, const auto& overload_set) {
			return std::visit(overload_set, std::move(variant)._value);
		}

		/*template <typename... Ts>
		inline std::weak_ordering operator<=>(const type<Ts...>& l, const type<Ts...>& r) {
			const auto& a = l._value;
			const auto& b = r._value;
			auto index_cmp = a.index() <=> b.index();
			if (index_cmp != 0)
				return index_cmp;
			return std::visit(
				[&](const auto& _a) {
					auto res = _a <=> std::get<std::remove_cvref_t<decltype(_a)>>(b);
					if constexpr (std::is_same_v<std::remove_cvref_t<decltype(res)>, std::strong_ordering>) {
						if (res == std::strong_ordering::equal)
							return std::weak_ordering::equivalent;
						else if (res == std::strong_ordering::less)
							return std::weak_ordering::less;
						return std::weak_ordering::greater;
					}
					else
						return res;
				},
				a
			);
		};*/
	}

	template <typename... Ts>
	inline constexpr variant::type<Ts...> copy(const variant::type<Ts...>& x) {
		return variant::visit(x, [](const auto& t) { return caesium_lib::copy(t); });
	}
}

DISABLE_BAD_MOVE_TEMPLATE(caesium_lib::variant::type)
