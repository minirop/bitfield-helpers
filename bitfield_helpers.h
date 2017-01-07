/*
MIT License

Copyright (c) 2017 Alexander Roper

Permission is hereby granted, free of charge, to any person obtaining a copy
of this software and associated documentation files (the "Software"), to deal
in the Software without restriction, including without limitation the rights
to use, copy, modify, merge, publish, distribute, sublicense, and/or sell
copies of the Software, and to permit persons to whom the Software is
furnished to do so, subject to the following conditions:

The above copyright notice and this permission notice shall be included in all
copies or substantial portions of the Software.

THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND, EXPRESS OR
IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF MERCHANTABILITY,
FITNESS FOR A PARTICULAR PURPOSE AND NONINFRINGEMENT. IN NO EVENT SHALL THE
AUTHORS OR COPYRIGHT HOLDERS BE LIABLE FOR ANY CLAIM, DAMAGES OR OTHER
LIABILITY, WHETHER IN AN ACTION OF CONTRACT, TORT OR OTHERWISE, ARISING FROM,
OUT OF OR IN CONNECTION WITH THE SOFTWARE OR THE USE OR OTHER DEALINGS IN THE
SOFTWARE.
*/
#pragma once

#include <cstdint>

namespace bitfield_helpers {

using size_t = std::size_t;

template<bool B, size_t X, size_t Y>
struct size_if
{
	static constexpr size_t value = (B ? X : Y);
};

template<bool B, size_t X, size_t Y>
constexpr size_t size_if_v = size_if<B, X, Y>::value;

////////////////////////////////////////////////////////////////////////////////

template<size_t X, size_t... Y>
struct sum
{
	static constexpr size_t value = X + sum<Y...>::value;
};

template<size_t X>
struct sum<X>
{
	static constexpr size_t value = X;
};

template<size_t... X>
constexpr size_t sum_v = sum<X...>::value;

////////////////////////////////////////////////////////////////////////////////

// takes a number between 1 and 64 and returns the next integer size.
template<size_t N>
struct next_size
{
	//static_assert(N > 0 && N <= 64);
	static constexpr size_t value = size_if_v<(N < 9), 8,
										size_if_v<(N < 17), 16,
											size_if_v<(N < 33), 32, 64>>>;
};

template<size_t N>
constexpr size_t next_size_v = next_size<N>::value;

////////////////////////////////////////////////////////////////////////////////

template<size_t>
struct size_type;

template<> struct size_type<8>  { using type = uint8_t;  };
template<> struct size_type<16> { using type = uint16_t; };
template<> struct size_type<32> { using type = uint32_t; };
template<> struct size_type<64> { using type = uint64_t; };

template<size_t N>
using size_type_t = typename size_type<N>::type;

////////////////////////////////////////////////////////////////////////////////

template<size_t... N>
struct type_for_bitfield
{
	using type = size_type_t<next_size_v<sum_v<N...>>>;
};

template<size_t... N>
using type_for_bitfield_t = typename type_for_bitfield<N...>::type;

} // namespace bitfield_helpers
