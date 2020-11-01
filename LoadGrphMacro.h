#pragma once
#include <cstddef>
#include <tuple>
#include <array>
#include "DxLib.h"
#include "TemplateUtil.h"

namespace MyGT { 
	/// グラフィック管理.同値の複数ロードを防ぐようにしている.
	template<MyTU::fixed_string Str >
	struct GraphResource {
		static constexpr int load_graph() {
			if (grphNum.first == -1) {

				grphNum.first = LoadGraph(Str.str);
				grphNum.second++;
			}
			else
			{
				grphNum.second++;
			}
			return grphNum.first;
		}
		static constexpr int delete_graph() {
			grphNum.second--;
			if (grphNum.second == 0) {
				DeleteGraph(grphNum.first);
				grphNum.first = -1;
			}
			return 0;
		}
	private:
		static inline std::pair<int, int> grphNum = std::make_pair<int, int>(-1, 0);
	};
}
