#include "bitfield_helpers.h"
#include <cstdio>

using namespace bitfield_helpers;

int main()
{
	printf("%lu\n", sum_v<1, 2, 3>); // 6
	printf("%lu\n", sizeof(size_type_t<sum_v<1, 2, 3, 10>>)); // 2
	printf("%lu, %lu\n", size_if_v<false, 3, 4>, size_if_v<true, 3, 4>); // 4, 3
	printf("%lu\n", next_size_v<3>); // 8
	printf("%lu\n", next_size_v<13>); // 16
	printf("%lu\n", next_size_v<16>); // 16
	printf("%lu\n", next_size_v<20>); // 32
	printf("%lu\n", next_size_v<31>); // 32
	printf("%lu\n", next_size_v<32>); // 32
	printf("%lu\n", next_size_v<64>); // 64
	printf("%lu\n", sizeof(type_for_bitfield_t<1, 2, 3>)); // 1
	printf("%lu\n", sizeof(type_for_bitfield_t<5, 7>)); // 2
	printf("%lu\n", sizeof(type_for_bitfield_t<10, 10>)); // 4
	printf("%lu\n", sizeof(type_for_bitfield_t<20, 20, 20>)); // 8

	//printf("bitfield 65 = %lu\n", sizeof(type_for_bitfield_t<65>)); // compile error

	return 0;
};
