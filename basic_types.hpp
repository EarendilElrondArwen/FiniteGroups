/*
 * basic_types.hpp
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

#ifndef BASIC_TYPES_HPP_INCLUDED
#define BASIC_TYPES_HPP_INCLUDED

#include <cstdlib>
#include <cstdint>
#include <cmath>
#include <string>
#include <limits>

namespace tfg {

using std::size_t;
using std::numeric_limits;
template<typename T>
using nl = typename std::numeric_limits<T>;
template<typename T>
auto digits = nl<T>::digits;

using std::uint8_t	;
using std::uint16_t	;
using std::uint32_t	;
using std::uint64_t	;
using std::int8_t	;
using std::int16_t	;
using std::int32_t	;
using std::int64_t	;
using uint		= 	uint8_t	;
using usint		= 	uint16_t;
using ulint		= 	uint32_t;
using ullint	= 	uint64_t;
using sint		= 	int8_t	;
using ssint		= 	int16_t	;
using slint		= 	int32_t	;
using sllint	= 	int64_t	;

struct null_t {
	using type = null_t;
};


enum class group_name : uint
{
	T=1,
	C=2,
	PD=3,
	PD_Cyc=4,
	C2_2=5,
	Dih=6,
	C2_3=7,C4xC2=8,Q=9,Dic=10,
	C3_2=11,
	C6xC2=12,C3__C4=13,C3__C2_2=14,Dih6=15,
	Dih3xC2=16,C6__C2=17,Dic3=18,
	C2_2__C3=19,A4=20,
	C2_4=21,C4xC2_2=22,C4_2=23,C8xC2=24,
	C16=25,M16=26,Dih8=27,Dic4=28,SDih8=29,
	C4__C4=30,Dih4xC2=31,
	Q8xC2=32,Q16=33,Dih4_c_C2=34,
	GDih=35,
	C4xC2__C2=36,
	C6xC3=37,C18=38,GDih9=39,Dih3xC3=40,
	C5__C4=41,
	C7__C3=42
};

inline constexpr
ullint to_ullint(group_name);
std::string to_string(group_name);
inline constexpr bool operator <(group_name, group_name);
inline constexpr bool operator <=(group_name, group_name);
inline constexpr bool operator >(group_name, group_name);
inline constexpr bool operator >=(group_name, group_name);

inline constexpr
ullint to_ullint(group_name arg) {
	switch(arg) {
	case group_name::T 				:	return 1;
	case group_name::C 				:	return 2;
	case group_name::PD 			:	return 3;
	case group_name::PD_Cyc 		:	return 4;
	case group_name::C2_2 			:	return 5;
	case group_name::Dih 			:	return 6;
	case group_name::C2_3 			:	return 7;
	case group_name::C4xC2 			:	return 8;
	case group_name::Q 				:	return 9;
	case group_name::Dic 			:	return 10;
	case group_name::C3_2 			:	return 11;
	case group_name::C6xC2 			:	return 12;
	case group_name::C3__C4 		:	return 13;
	case group_name::C3__C2_2 		:	return 14;
	case group_name::Dih6 			:	return 15;
	case group_name::Dih3xC2 		:	return 16;
	case group_name::C6__C2 		:	return 17;
	case group_name::Dic3 			:	return 18;
	case group_name::C2_2__C3 		:	return 19;
	case group_name::A4 			:	return 20;
	case group_name::C2_4 			:	return 21;
	case group_name::C4xC2_2 		:	return 22;
	case group_name::C4_2 			:	return 23;
	case group_name::C8xC2 			:	return 24;
	case group_name::C16 			:	return 25;
	case group_name::M16 			:	return 26;
	case group_name::Dih8 			:	return 27;
	case group_name::Dic4 			:	return 28;
	case group_name::SDih8 			:	return 29;
	case group_name::C4__C4 		:	return 30;
	case group_name::Dih4xC2 		:	return 31;
	case group_name::Q8xC2 			:	return 32;
	case group_name::Q16 			:	return 33;
	case group_name::Dih4_c_C2 		:	return 34;
	case group_name::GDih 			:	return 35;
	case group_name::C4xC2__C2 		:	return 36;
	case group_name::C6xC3 			:	return 37;
	case group_name::C18 			:	return 38;
	case group_name::GDih9 			:	return 39;
	case group_name::Dih3xC3 		:	return 40;
	case group_name::C5__C4 		:	return 41;
	case group_name::C7__C3 		:	return 42;
	default 						:	return 0;
	}
}


std::string to_string(group_name arg)
{
	switch(arg) {
		case group_name::T				: return "T";
		case group_name::C				: return "C";
		case group_name::PD				: return "PD";
		case group_name::PD_Cyc			: return "PD_Cyc";
		case group_name::C2_2			: return "C2_2";
		case group_name::Dih			: return "Dih";
		case group_name::C2_3			: return "C2_3";
		case group_name::C4xC2			: return "C4xC2";
		case group_name::Q				: return "Q";
		case group_name::Dic			: return "Dic";
		case group_name::C3_2			: return "C3_2";
		case group_name::C6xC2			: return "C6xC2";
		case group_name::C3__C4			: return "C3__C4";
		case group_name::C3__C2_2		: return "C3__C2_2";
		case group_name::Dih6			: return "Dih6";
		case group_name::Dih3xC2		: return "Dih3xC2";
		case group_name::C6__C2			: return "C6__C2";
		case group_name::Dic3			: return "Dic3";
		case group_name::C2_2__C3		: return "C2_2__C3";
		case group_name::A4				: return "A4";
		case group_name::C2_4			: return "C2_4";
		case group_name::C4xC2_2		: return "C4xC2_2";
		case group_name::C4_2			: return "C4_2";
		case group_name::C8xC2			: return "C8xC2";
		case group_name::C16			: return "C16";
		case group_name::M16			: return "M16";
		case group_name::Dih8			: return "Dih8";
		case group_name::Dic4			: return "Dic4";
		case group_name::SDih8			: return "SDih8";
		case group_name::C4__C4			: return "C4__C4";
		case group_name::Dih4xC2		: return "Dih4xC2";
		case group_name::Q8xC2			: return "Q8xC2";
		case group_name::Q16			: return "Q16";
		case group_name::Dih4_c_C2		: return "Dih4_c_C2";
		case group_name::GDih			: return "GDih";
		case group_name::C4xC2__C2		: return "C4xC2__C2";
		case group_name::C6xC3			: return "C6xC3";
		case group_name::C18			: return "C18";
		case group_name::GDih9			: return "GDih9";
		case group_name::Dih3xC3		: return "Dih3xC3";
		case group_name::C5__C4			: return "C5__C4";
		case group_name::C7__C3			: return "C7__C3";
		default							: return "";
	}
}

inline constexpr
bool operator<(group_name a,group_name b) {
	return(to_ullint(a) < to_ullint(b));
}

inline constexpr
bool operator<=(group_name a,group_name b) {
	return(to_ullint(a) <= to_ullint(b));
}

inline constexpr
bool operator>(group_name a,group_name b) {
	return(to_ullint(a) > to_ullint(b));
}

inline constexpr
bool operator>=(group_name a,group_name b) {
	return(to_ullint(a) >= to_ullint(b));
}

}
#endif // BASIC_TYPES_HPP_INCLUDED
