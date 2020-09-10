#pragma once
#include <cstddef>
#include <tuple>
#include <array>

namespace MyGT { 
	template <char... Chars>
	constexpr static std::array<char, sizeof...(Chars) + 1>
	chars_to_array()
	{
		return  {Chars...,'\0'} ;
	};

	/// グラフィック管理.同値の複数ロードを防ぐようにしている.
	template<char... Chars>
	static constexpr int LoadDeleteGraph(bool deleteFlag = false) {
		static std::pair<int, int> grphNum = std::make_pair<int, int>(-1, 0);
		if (deleteFlag) {
			grphNum.second--;
			if (grphNum.second == 0) {
				DeleteGraph(grphNum.first);
				grphNum.first = -1;
			}
			return 0;
		}
		if (grphNum.first == -1) {
			auto ts = chars_to_array<Chars...>();
			char* str = &ts[0];
			grphNum.first = LoadGraph(str);
		}
		grphNum.second++;
		return grphNum.first;
	}
}
