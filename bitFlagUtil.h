#pragma once
#include <cstddef>
#include <math.h>


namespace MyGT {

	//bitによるflag処理系.

	//得た数値からフラグの個所を算出.
	template<std::size_t N>
	struct get_bit_flag {
		constexpr value = pow(2,N);
	};
	//

}