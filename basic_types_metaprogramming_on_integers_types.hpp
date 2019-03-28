/*
 * basic_types_metaprogramming_on_integral_types.hpp
 *
 * Copyright 2018 Julián Calderón Almendros
 * <julian.calderon.almendros@gmail.com>
 *
 * This program is free software; you can redistribute it and/or modify
 * it under the terms of the GNU General Public License as published by
 * the Free Software Foundation; either version 2 of the License, or
 * (at your option) any later version.
 *
 * This program is distributed in the hope that it will be useful,
 * but WITHOUT ANY WARRANTY; without even the implied warranty of
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
 * GNU General Public License for more details.
 *
 * You should have received a copy of the GNU General Public License
 * along with this program; if not, write to the Free Software
 * Foundation, Inc., 51 Franklin Street, Fifth Floor, Boston,
 * MA 02110-1301, USA.
 *
 *
 */

#ifndef BASIC_TYPES_METAPROGRAMMING_ON_INTEGRAL_TYPES__HPP___INCLUDED
#define BASIC_TYPES_METAPROGRAMMING_ON_INTEGRAL_TYPES__HPP___INCLUDED

#include <cstdlib>
#include <cstdint>
#include <cmath>
#include <string>
#include <limits>
#include <type_traits>

#include"basic_types_metaprogramming_on_integers_types_IMPL.hpp"

namespace tfg {
using std::is_same;
using std::is_same_v;
using std::is_integral;
using std::is_integral_v;
using std::conditional;
using std::conditional_t;

template<typename A>
inline constexpr
bool is_integer_type_v =
		impl::is_integer_type<A>::value;

template<typename A,typename B>
inline constexpr
bool less_equal_v =
		impl::less_equal<A,B>::value;

template<typename T>
inline constexpr
bool is_signed_int_t_v =
		impl::is_signed_int_type<T>::value;

template<typename T>
inline constexpr
bool 	is_unsigned_int_t_v =
		impl::is_unsigned_int_type<T>::value;

template<typename T>
using 	unsigned_for_signed_t = typename
		impl::unsigned_type_for_signed_type<T>::type;

template<typename T>
using	signed_for_unsigned_t =	typename
		impl::signed_type_for_unsigned_type<T>::type;

template<typename T>
using 	next_int_t = typename
		impl::next_int_type<T>::type;

template<typename Int_t,typename UIntType,UIntType N>
inline constexpr
UIntType to_UIntType(Int_t k) {
		static_assert(
			is_integer_type_v<UIntType>,
			"El tipo UIntType debe ser entero"
		);
		static_assert(
			is_integer_type_v<Int_t>		,
			"El tipo Int_t debe ser entero"
		);
		static_assert(
			is_integer_type_v<decltype(k)>	,
			"El tipo del argumento no es un entero"
		);
		using SIntType1 = next_int_t<signed_for_unsigned_t<UIntType>>;
		using SIntType2 = next_int_t<signed_for_unsigned_t<Int_t>>;
		using SIntType  = 
			conditional_t<
				less_equal_v<
					SIntType1,SIntType2
				>,
						SIntType2,
						SIntType1
			>;
		const SIntType new_k=static_cast<SIntType>(k);
		using LSIntType = next_int_t<SIntType>;
		static_assert(
			is_integral_v<LSIntType>,
			"LSIntType no es un tipo entero"
		);
		if constexpr (is_signed_int_t_v<Int_t>) {
			if (k<0) {
				const LSIntType 	coc_pos{-(new_k/N)};
				const LSIntType		den_def{coc_pos*N};
				const LSIntType		resto{den_def+new_k};
					 if (resto ==    0  ) {return UIntType(0);}
				else if (resto ==   -1  ) {return UIntType(N-1);}
				else if (resto ==  (-N) ) {return UIntType(0);}
				else if (resto == (-N+1)) {return UIntType(1);}
				else {
					const LSIntType coc_pos_exc{coc_pos+1};
					const LSIntType den_exc{coc_pos_exc*N};
					const LSIntType resto{new_k+den_exc};
					return UIntType((resto==N)?0:resto);
				}
			} else { 
				return UIntType(new_k%N);
			}
		} else if constexpr (is_same_v<UIntType,Int_t>) {
			return UIntType(new_k%N);
		} else	if constexpr  (is_unsigned_int_t_v<Int_t>) { 
			return UIntType(new_k%N);
		} else {
			return UIntType(new_k%N);
		}
	}
}
#endif // BASIC_TYPES_METAPROGRAMMING_ON_INTEGRAL_TYPES__HPP___INCLUDED
