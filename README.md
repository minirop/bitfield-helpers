# Bitfield helpers
Few template helpers that could be used by bitfield implementations. Uses C++14 because of 3 template variables, but the rest is C++11.

### `sum<size_t...>::value`
Adds all its arguments.

### `size_if<bool, size_t, size_t>::value`
Similar to std::conditional but for size_t.

### `next_size<size_t>::value`
Returns the next integer size (8, 16, 32 or 64), for any number between 1 and 64.

### `size_type<size_t>::type`
Returns the unsigned type (uint*X*_t) corresponding to its argument (8, 16, 32 and 64 only).

### `type_for_bitfield<size_t...>::type`
Returns the smallest unsigned integer type for the corresponding bitfields.

### notes
All templates have aliases: `sum_v`, `size_if_v`, `next_size_v`, `size_type_t` and `type_for_bitfield_t`.

## Example
```cpp
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
```
