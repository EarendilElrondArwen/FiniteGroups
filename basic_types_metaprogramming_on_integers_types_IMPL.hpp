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

#ifndef BASIC_TYPES_METAPROGRAMMING_ON_INTEGRAL_TYPES_IMPL__HPP___INCLUDED
#define BASIC_TYPES_METAPROGRAMMING_ON_INTEGRAL_TYPES_IMPL__HPP___INCLUDED

#include <cstdlib>
#include <cstdint>
#include <cmath>
#include <string>
#include <limits>

#include "basic_types.hpp"

namespace tfg::impl {
	
	template< typename A >
	struct is_integer_type {
		static constexpr bool value{is_integer_type::get_value()};
		
		static constexpr 
		bool get_value() {
			if constexpr (
				std::is_same_v<A,uint>   ||
				std::is_same_v<A,usint>  ||
				std::is_same_v<A,ulint>  ||
				std::is_same_v<A,ullint> ||
				std::is_same_v<A,sint>	||
				std::is_same_v<A,ssint>	||
				std::is_same_v<A,slint>	||
				std::is_same_v<A,sllint>
			) 
				return true;
			else 
				return false;
		} 
	};

		
	template<	typename A ,
				typename B	>
	struct less_equal {
		static constexpr bool value = false;
	};

	template<typename B>
	struct less_equal<uint,B> {
		static constexpr get_value() {
			if constexpr (
					std::is_same_v<B,uint>		||
					std::is_same_v<B,usint>		||
					std::is_same_v<B,ulint>		||
					std::is_same_v<B,ullint>	||
					std::is_same_v<B,ssint> 	||
					std::is_same_v<B,slint> 	||
					std::is_same_v<B,sllint>
				)
				return true;
			else
				return false;
		}
		static constexpr bool value = get_value();
	};

	template<typename B>
	struct less_equal<usint,B> {
		static constexpr get_value() {
			if constexpr (
					std::is_same_v<B,usint>		||
					std::is_same_v<B,ulint>		||
					std::is_same_v<B,ullint>	||
					std::is_same_v<B,slint> 	||
					std::is_same_v<B,sllint>
				)
				return true;
			else
				return false;
		}
		static constexpr bool value = get_value();
	};

	template<typename B>
	struct less_equal<ulint,B> {
		static constexpr get_value() {
			if constexpr (
					std::is_same_v<B,ulint>		||
					std::is_same_v<B,ullint>	||
					std::is_same_v<B,sllint>
				)
				return true;
			else
				return false;
		}
		static constexpr bool value = get_value();
	};

	template<>
	struct less_equal<ullint,ullint> {
		static constexpr bool value = true;
	};

	template<typename B>
	struct less_equal<sint,B> {
		static constexpr get_value() {
			if constexpr (
					std::is_same_v<B,sint>		||
					std::is_same_v<B,ssint>		||
					std::is_same_v<B,slint>		||
					std::is_same_v<B,sllint>	||
					std::is_same_v<B,uint>		||
					std::is_same_v<B,usint>		||
					std::is_same_v<B,ulint>		||
					std::is_same_v<B,ullint>
				)
				return true;
			else
				return false;
		}
		static constexpr bool value = get_value();
	};

	template<typename B>
	struct less_equal<ssint,B> {
		static constexpr get_value() {
			if constexpr (
					std::is_same_v<B,ssint>		||
					std::is_same_v<B,slint>		||
					std::is_same_v<B,sllint>	||
					std::is_same_v<B,uint>		||
					std::is_same_v<B,usint>		||
					std::is_same_v<B,ulint>		||
					std::is_same_v<B,ullint>
				)
				return true;
			else
				return false;
		}
		static constexpr bool value = get_value();
	};

	template<typename B>
	struct less_equal<slint,B> {
		static constexpr get_value() {
			if constexpr (
					std::is_same_v<B,slint>		||
					std::is_same_v<B,sllint>	||
					std::is_same_v<B,usint>		||
					std::is_same_v<B,ulint>		||
					std::is_same_v<B,ullint>
				)
				return true;
			else
				return false;
		}
		static constexpr bool value = get_value();
	};

	template<typename B>
	struct less_equal<sllint,B> {
		static constexpr get_value() {
			if constexpr (
					std::is_same_v<B,sllint>	||
					std::is_same_v<B,ulint>		||
					std::is_same_v<B,ullint>
				)
				return true;
			else
				return false;
		}
		static constexpr bool value = get_value();
	};

	template<typename T>
	struct is_signed_int_type {
		static constexpr bool value = false;
	};

	template<>
	struct is_signed_int_type<sint> {
		static constexpr bool value = true;
	};

	template<>
	struct is_signed_int_type<ssint> {
		static constexpr bool value = true;
	};

	template<>
	struct is_signed_int_type<slint> {
		static constexpr bool value = true;
	};

	template<>
	struct is_signed_int_type<sllint> {
		static constexpr bool value = true;
	};

	template<typename T>
	struct is_unsigned_int_type       {
		static constexpr bool value = false;
	};

	template<>
	struct is_unsigned_int_type<uint> {
		static constexpr bool value = true;
	};

	template<>
	struct is_unsigned_int_type<usint> {
		static constexpr bool value = true;
	};

	template<>
	struct is_unsigned_int_type<ulint> {
		static constexpr bool value = true;
	};

	template<>
	struct is_unsigned_int_type<ullint> {
		static constexpr bool value = true;
	};
	
	template<typename T>
	struct unsigned_type_for_signed_type {
		using type = null_t;
	};

	template<>
	struct unsigned_type_for_signed_type<sint> {
		using type = uint;
	};

	template<>
	struct unsigned_type_for_signed_type<ssint> {
		using type = usint;
	};

	template<>
	struct unsigned_type_for_signed_type<slint> {
		using type = ulint;
	};

	template<>
	struct unsigned_type_for_signed_type<sllint>{
		using type = ullint;
	};
	
	template<>
	struct unsigned_type_for_signed_type<uint>{
		using type = uint;
	};
	
	template<>
	struct unsigned_type_for_signed_type<usint>{
		using type = usint;
	};
	
	template<>
	struct unsigned_type_for_signed_type<ulint>{
		using type = ulint;
	};
	
	template<>
	struct unsigned_type_for_signed_type<ullint>{
		using type = ullint;
	};

	template<typename T>
	struct signed_type_for_unsigned_type 	    {
		using type = null_t;
	};

	template<>
	struct signed_type_for_unsigned_type<uint>  {
		using type = ssint;
	};

	template<>
	struct signed_type_for_unsigned_type<usint> {
		using type = slint;
	};

	template<>
	struct signed_type_for_unsigned_type<ulint> {
		using type = sllint;
	};
	
	template<>
	struct signed_type_for_unsigned_type<sint> {
		using type = sint;
	};
	
	template<>
	struct signed_type_for_unsigned_type<ssint> {
		using type = ssint;
	};
	
	template<>
	struct signed_type_for_unsigned_type<slint> {
		using type = slint;
	};
	
	template<>
	struct signed_type_for_unsigned_type<sllint> {
		using type = sllint;
	};
	
	template<typename T>
	struct next_int_type                        {
		using type = null_t;
	};

	template<>
	struct next_int_type<sint>                  {
		using type = ssint;
	};

	template<>
	struct next_int_type<uint>                  {
		using type = usint;
	};

	template<>
	struct next_int_type<ssint>                 {
		using type = slint;
	};

	template<>
	struct next_int_type<usint>                 {
		using type = ulint;
	};

	template<>
	struct next_int_type<slint>                 {
		using type = sllint;
	};

	template<>
	struct next_int_type<ulint>                 {
		using type = ullint;
	};
	
	template<>
	struct next_int_type<sllint>                 {
		using type = sllint;
	};

	template<>
	struct next_int_type<ullint>                 {
		using type = ullint;
	};

}
#endif // BASIC_TYPES_METAPROGRAMMING_ON_INTEGRAL_TYPES_IMPL__HPP___INCLUDED
