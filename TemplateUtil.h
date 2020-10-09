#pragma once


namespace MyTU {

	//baseとすべての要素が同じか.
	template<typename base, typename...Args>
	struct is_all_base_of {
		 constexpr static auto value = []() constexpr {
			auto v = true;
			return ((v = v * std::is_base_of_v<base, Args>), ..., v);
		}();
	};
	template<typename base, typename...Args>
	constexpr auto is_all_base_of_v = is_all_base_of<base, Args...>::value;

	//全ての要素の最大サイズ取得.
	template<typename...Args>
	struct Sizeof {
		constexpr static std::size_t max = std::max<std::size_t>({ sizeof(Args)... });
	};

	//いづれか一つが同じか
	template<typename base,typename...Args>
	struct is_any_same {
		constexpr static auto value = []() constexpr{
			auto v = false;
			return ((v = v || std::is_same_v<base, Args> ), ...,v);
		}();
	};
	template<typename base, typename...Args>
	constexpr auto is_any_same_v = is_any_same<base, Args>::value;

	//charの可変長を配列にする.2020で不要になった.
	template <char... Chars>
	[[deprecated("please use fixed_string template")]]
	constexpr static std::array<char, sizeof...(Chars) + 1>
		chars_to_array()
	{
		return  { Chars...,'\0' };
	};

	//固定文字列型
	template<typename CharT, std::size_t N>
	struct fixed_string {
		constexpr fixed_string(const CharT(&array)[N + 1]) {
			std::copy_n(array, N + 1, str);
		}

		CharT str[N + 1];
	};
	template<typename CharT, std::size_t N>
	fixed_string(const CharT(&array)[N])->fixed_string<CharT, N - 1>;
}