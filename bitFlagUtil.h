#pragma once
#include <cstddef>
#include <math.h>


namespace MyGT {

	//bit�ɂ��flag�����n.

	//�������l����t���O�̌����Z�o.
	template<std::size_t N>
	struct get_bit_flag {
		constexpr value = pow(2,N);
	};
	//

}