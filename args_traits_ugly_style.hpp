/*
 * args_traits_old_style.hpp
 *
 * Copyright 2018 Julian Calderon Almendros
 *	<julian.calderon.almendros@gmail.com>
 *
 * This program is free software; you can redistribute it and/or
 * modify
 * it under the terms of the GNU General Public License as published
 * by
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

#ifndef ARGS_TRAITS_OLD_STYLE_HPP_INCLUDED
#define ARGS_TRAITS_OLD_STYLE_HPP_INCLUDED

#include "magma_t.hpp"
#include <cstdlib>
#include <algorithm>
#include <set>

namespace tfg{
	
/// Esta implementacion claramente se puede hacer con Metaprogramacion de 
/// Templates usando variadic parameter packs, a traves del paso del paso
/// template<template class TT,group_name gn,typename UIntType,UIntType N0,UIntType Ns...,sizet_t ...Is>
/// Ademas mantendríamos las 6 sobrecargas del operator(), para que no hubiese problemas con la deduccion
/// de las funciones llamadas pr falta de deduccion de argumentos de template de una template funcion.
/// Aplicacion de std::apply y a veces de std::get y de std::tuple.
	
namespace details {
template<size_t I,template<group_name,typename K,K,K...> class TT,group_name gn,typename UIntType,UIntType N0,UIntType ... Ns>
struct exists_eq_id;
template<group_name gn,typename UIntType,UIntType N0,UIntType ... Ns>
struct exists_eq_id<0,magma_t,gn,UIntType,N0,Ns...> {
	using el_t = magma_t<gn,UIntType,N0,Ns...>;
	
	static constexpr bool funct(const el_t & t0) {
		return (t0==(el_t::get_the_identity()));
	}
	static constexpr bool funct(const el_t& t0,const el_t& t1) {
		return (t0==(el_t::get_the_identity()));
	}
	static constexpr bool funct(const el_t& t0,const el_t& t1,const el_t& t2) {
		return (t0==(el_t::get_the_identity()));
	}
	static constexpr bool funct(const el_t& t0,const el_t& t1,const el_t& t2,const el_t& t3) {
		return (t0==(el_t::get_the_identity()));
	}
	static constexpr bool funct(const el_t& t0,const el_t& t1,const el_t& t2,const el_t& t3,const el_t& t4) {
		return (t0==(el_t::get_the_identity()));
	}
	static constexpr bool funct(const el_t& t0,const el_t& t1,const el_t& t2,const el_t& t3,const el_t& t4,const el_t& t5) {
		return (t0==(el_t::get_the_identity()));
	}
	static constexpr bool funct(const el_t& t0,const el_t& t1,const el_t& t2,const el_t& t3,const el_t& t4,const el_t& t5,const el_t& t6) {
		return (t0==(el_t::get_the_identity()));
	}
};
template<group_name gn,typename UIntType,UIntType N0,UIntType ... Ns>
struct exists_eq_id<1,magma_t,gn,UIntType,N0,Ns...> {
	using el_t = magma_t<gn,UIntType,N0,Ns...>;
	
	static constexpr bool funct(const el_t& t0) {
		return (t0==(el_t::get_the_identity()));
	}
	static constexpr bool funct(const el_t& t0,const el_t& t1) {
		return ((t0==(el_t::get_the_identity()))||(t1==(el_t::get_the_identity())));
	}
	static constexpr bool funct(const el_t& t0,const el_t& t1,const el_t& t2) {
		return ((t0==(el_t::get_the_identity()))||(t1==(el_t::get_the_identity())));
	}
	static constexpr bool funct(const el_t& t0,const el_t& t1,const el_t& t2,const el_t& t3) {
		return ((t0==(el_t::get_the_identity()))||(t1==(el_t::get_the_identity())));
	}
	static constexpr bool funct(const el_t& t0,const el_t& t1,const el_t& t2,const el_t& t3,const el_t& t4) {
		return ((t0==(el_t::get_the_identity()))||(t1==(el_t::get_the_identity())));
	}
	static constexpr bool funct(const el_t& t0,const el_t& t1,const el_t& t2,const el_t& t3,const el_t& t4,const el_t& t5) {
		return ((t0==(el_t::get_the_identity()))||(t1==(el_t::get_the_identity())));
	}
	static constexpr bool funct(const el_t& t0,const el_t& t1,const el_t& t2,const el_t& t3,const el_t& t4,const el_t& t5,const el_t& t6) {
		return ((t0==(el_t::get_the_identity()))||(t1==(el_t::get_the_identity())));
	}
};
template<group_name gn,typename UIntType,UIntType N0,UIntType ... Ns>
struct exists_eq_id<2,magma_t,gn,UIntType,N0,Ns...> {
	using el_t = magma_t<gn,UIntType,N0,Ns...>;
	
	static constexpr bool funct(const el_t& t0) {
		return (t0==(el_t::get_the_identity()));
	}
	static constexpr bool funct(const el_t& t0,const el_t& t1) {
		return ((t0==(el_t::get_the_identity()))||(t1==(el_t::get_the_identity())));
	}
	static constexpr bool funct(const el_t& t0,const el_t& t1,const el_t& t2) {
		return ((t0==(el_t::get_the_identity()))||(t1==(el_t::get_the_identity()))||(t2==(el_t::get_the_identity())));
	}
	static constexpr bool funct(const el_t& t0,const el_t& t1,const el_t& t2,const el_t& t3) {
		return ((t0==(el_t::get_the_identity()))||(t1==(el_t::get_the_identity()))||(t2==(el_t::get_the_identity())));
	}
	static constexpr bool funct(const el_t& t0,const el_t& t1,const el_t& t2,const el_t& t3,const el_t& t4) {
		return ((t0==(el_t::get_the_identity()))||(t1==(el_t::get_the_identity()))||(t2==(el_t::get_the_identity())));
	}
	static constexpr bool funct(const el_t& t0,const el_t& t1,const el_t& t2,const el_t& t3,const el_t& t4,const el_t& t5) {
		return ((t0==(el_t::get_the_identity()))||(t1==(el_t::get_the_identity()))||(t2==(el_t::get_the_identity())));
	}
	static constexpr bool funct(const el_t& t0,const el_t& t1,const el_t& t2,const el_t& t3,const el_t& t4,const el_t& t5,const el_t& t6) {
		return ((t0==(el_t::get_the_identity()))||(t1==(el_t::get_the_identity()))||(t2==(el_t::get_the_identity())));
	}
};
template<group_name gn,typename UIntType,UIntType N0,UIntType ... Ns>
struct exists_eq_id<3,magma_t,gn,UIntType,N0,Ns...> {
	using el_t = magma_t<gn,UIntType,N0,Ns...>;
	
	static constexpr bool funct(const el_t& t0) {
		return (t0==(el_t::get_the_identity()));
	}
	static constexpr bool funct(const el_t& t0,const el_t& t1) {
		return ((t0==(el_t::get_the_identity()))||(t1==(el_t::get_the_identity())));
	}
	static constexpr bool funct(const el_t& t0,const el_t& t1,const el_t& t2) {
		return ((t0==(el_t::get_the_identity()))||(t1==(el_t::get_the_identity()))||(t2==(el_t::get_the_identity())));
	}
	static constexpr bool funct(const el_t& t0,const el_t& t1,const el_t& t2,const el_t& t3) {
		return ((t0==(el_t::get_the_identity()))||(t1==(el_t::get_the_identity()))||(t2==(el_t::get_the_identity()))||(t3==(el_t::get_the_identity())));
	}
	static constexpr bool funct(const el_t& t0,const el_t& t1,const el_t& t2,const el_t& t3,const el_t& t4) {
		return ((t0==(el_t::get_the_identity()))||(t1==(el_t::get_the_identity()))||(t2==(el_t::get_the_identity()))||(t3==(el_t::get_the_identity())));
	}
	static constexpr bool funct(const el_t& t0,const el_t& t1,const el_t& t2,const el_t& t3,const el_t& t4,const el_t& t5) {
		return ((t0==(el_t::get_the_identity()))||(t1==(el_t::get_the_identity()))||(t2==(el_t::get_the_identity()))||(t3==(el_t::get_the_identity())));
	}
	static constexpr bool funct(const el_t& t0,const el_t& t1,const el_t& t2,const el_t& t3,const el_t& t4,const el_t& t5,const el_t& t6) {
		return ((t0==(el_t::get_the_identity()))||(t1==(el_t::get_the_identity()))||(t2==(el_t::get_the_identity()))||(t3==(el_t::get_the_identity())));
	}
};
template<group_name gn,typename UIntType,UIntType N0,UIntType ... Ns>
struct exists_eq_id<4,magma_t,gn,UIntType,N0,Ns...> {
	using el_t = magma_t<gn,UIntType,N0,Ns...>;
	
	static constexpr bool funct(const el_t& t0) {
		return (t0==(el_t::get_the_identity()));
	}
	static constexpr bool funct(const el_t& t0,const el_t& t1) {
		return ((t0==(el_t::get_the_identity()))||(t1==(el_t::get_the_identity())));
	}
	static constexpr bool funct(const el_t& t0,const el_t& t1,const el_t& t2) {
		return ((t0==(el_t::get_the_identity()))||(t1==(el_t::get_the_identity()))||(t2==(el_t::get_the_identity())));
	}
	static constexpr bool funct(const el_t& t0,const el_t& t1,const el_t& t2,const el_t& t3) {
		return ((t0==(el_t::get_the_identity()))||(t1==(el_t::get_the_identity()))||(t2==(el_t::get_the_identity()))||(t3==(el_t::get_the_identity())));
	}
	static constexpr bool funct(const el_t& t0,const el_t& t1,const el_t& t2,const el_t& t3,const el_t& t4) {
		return ((t0==(el_t::get_the_identity()))||(t1==(el_t::get_the_identity()))||(t2==(el_t::get_the_identity()))||(t3==(el_t::get_the_identity()))||(t4==(el_t::get_the_identity())));
	}
	static constexpr bool funct(const el_t& t0,const el_t& t1,const el_t& t2,const el_t& t3,const el_t& t4,const el_t& t5) {
		return ((t0==(el_t::get_the_identity()))||(t1==(el_t::get_the_identity()))||(t2==(el_t::get_the_identity()))||(t3==(el_t::get_the_identity()))||(t4==(el_t::get_the_identity())));
	}
	static constexpr bool funct(const el_t& t0,const el_t& t1,const el_t& t2,const el_t& t3,const el_t& t4,const el_t& t5,const el_t& t6) {
		return ((t0==(el_t::get_the_identity()))||(t1==(el_t::get_the_identity()))||(t2==(el_t::get_the_identity()))||(t3==(el_t::get_the_identity()))||(t4==(el_t::get_the_identity())));
	}
};
template<group_name gn,typename UIntType,UIntType N0,UIntType ... Ns>
struct exists_eq_id<5,magma_t,gn,UIntType,N0,Ns...> {
	using el_t = magma_t<gn,UIntType,N0,Ns...>;
	
	static constexpr bool funct(const el_t& t0) {
		return (t0==(el_t::get_the_identity()));
	}
	static constexpr bool funct(const el_t& t0,const el_t& t1) {
		return ((t0==(el_t::get_the_identity()))||(t1==(el_t::get_the_identity())));
	}
	static constexpr bool funct(const el_t& t0,const el_t& t1,const el_t& t2) {
		return ((t0==(el_t::get_the_identity()))||(t1==(el_t::get_the_identity()))||(t2==(el_t::get_the_identity())));
	}
	static constexpr bool funct(const el_t& t0,const el_t& t1,const el_t& t2,const el_t& t3) {
		return ((t0==(el_t::get_the_identity()))||(t1==(el_t::get_the_identity()))||(t2==(el_t::get_the_identity()))||(t3==(el_t::get_the_identity())));
	}
	static constexpr bool funct(const el_t& t0,const el_t& t1,const el_t& t2,const el_t& t3,const el_t& t4) {
		return ((t0==(el_t::get_the_identity()))||(t1==(el_t::get_the_identity()))||(t2==(el_t::get_the_identity()))||(t3==(el_t::get_the_identity()))||(t4==(el_t::get_the_identity())));
	}
	static constexpr bool funct(const el_t& t0,const el_t& t1,const el_t& t2,const el_t& t3,const el_t& t4,const el_t& t5) {
		return ((t0==(el_t::get_the_identity()))||(t1==(el_t::get_the_identity()))||(t2==(el_t::get_the_identity()))||(t3==(el_t::get_the_identity()))||(t4==(el_t::get_the_identity()))||(t5==(el_t::get_the_identity())));
	}
	static constexpr bool funct(const el_t& t0,const el_t& t1,const el_t& t2,const el_t& t3,const el_t& t4,const el_t& t5,const el_t& t6) {
		return ((t0==(el_t::get_the_identity()))||(t1==(el_t::get_the_identity()))||(t2==(el_t::get_the_identity()))||(t3==(el_t::get_the_identity()))||(t4==(el_t::get_the_identity()))||(t5==(el_t::get_the_identity())));
	}
};
template<group_name gn,typename UIntType,UIntType N0,UIntType ... Ns>
struct exists_eq_id<6,magma_t,gn,UIntType,N0,Ns...> {
	using el_t = magma_t<gn,UIntType,N0,Ns...>;
	
	static constexpr bool funct(const el_t& t0) {
		return (t0==(el_t::get_the_identity()));
	}
	static constexpr bool funct(const el_t& t0,const el_t& t1) {
		return ((t0==(el_t::get_the_identity()))||(t1==(el_t::get_the_identity())));
	}
	static constexpr bool funct(const el_t& t0,const el_t& t1,const el_t& t2) {
		return ((t0==(el_t::get_the_identity()))||(t1==(el_t::get_the_identity()))||(t2==(el_t::get_the_identity())));
	}
	static constexpr bool funct(const el_t& t0,const el_t& t1,const el_t& t2,const el_t& t3) {
		return ((t0==(el_t::get_the_identity()))||(t1==(el_t::get_the_identity()))||(t2==(el_t::get_the_identity()))||(t3==(el_t::get_the_identity())));
	}
	static constexpr bool funct(const el_t& t0,const el_t& t1,const el_t& t2,const el_t& t3,const el_t& t4) {
		return ((t0==(el_t::get_the_identity()))||(t1==(el_t::get_the_identity()))||(t2==(el_t::get_the_identity()))||(t3==(el_t::get_the_identity()))||(t4==(el_t::get_the_identity())));
	}
	static constexpr bool funct(const el_t& t0,const el_t& t1,const el_t& t2,const el_t& t3,const el_t& t4,const el_t& t5) {
		return ((t0==(el_t::get_the_identity()))||(t1==(el_t::get_the_identity()))||(t2==(el_t::get_the_identity()))||(t3==(el_t::get_the_identity()))||(t4==(el_t::get_the_identity()))||(t5==(el_t::get_the_identity())));
	}
	static constexpr bool funct(const el_t& t0,const el_t& t1,const el_t& t2,const el_t& t3,const el_t& t4,const el_t& t5,const el_t& t6) {
		return ((t0==(el_t::get_the_identity()))||(t1==(el_t::get_the_identity()))||(t2==(el_t::get_the_identity()))||(t3==(el_t::get_the_identity()))||(t4==(el_t::get_the_identity()))||(t5==(el_t::get_the_identity()))||(t6==(el_t::get_the_identity())));
	}
};
}
namespace details {
template<size_t I,template<group_name,typename K_t,K_t,K_t...> class TT,group_name gn,typename UIntType,UIntType N0,UIntType ... Ns>
struct arg_Ix_eq_id;
template<group_name gn,typename UIntType,UIntType N0,UIntType ... Ns>
struct arg_Ix_eq_id<0,magma_t,gn,UIntType,N0,Ns...> {
	using el_t = magma_t<gn,UIntType,N0,Ns...>;
	
	static constexpr bool funct(const el_t& t0) {
		return (t0==(el_t::get_the_identity()));
	}
	static constexpr bool funct(const el_t& t0,const el_t& t1) {
		return (t0==(el_t::get_the_identity()));
	}
	static constexpr bool funct(const el_t& t0,const el_t& t1,const el_t& t2) {
		return (t0==(el_t::get_the_identity()));
	}
	static constexpr bool funct(const el_t& t0,const el_t& t1,const el_t& t2,const el_t& t3) {
		return (t0==(el_t::get_the_identity()));
	}
	static constexpr bool funct(const el_t& t0,const el_t& t1,const el_t& t2,const el_t& t3,const el_t& t4) {
		return (t0==(el_t::get_the_identity()));
	}
	static constexpr bool funct(const el_t& t0,const el_t& t1,const el_t& t2,const el_t& t3,const el_t& t4,const el_t& t5) {
		return (t0==(el_t::get_the_identity()));
	}
	static constexpr bool funct(const el_t& t0,const el_t& t1,const el_t& t2,const el_t& t3,const el_t& t4,const el_t& t5,const el_t& t6) {
		return (t0==(el_t::get_the_identity()));
	}
};
template<group_name gn,typename UIntType,UIntType N0,UIntType ... Ns>
struct arg_Ix_eq_id<1,magma_t,gn,UIntType,N0,Ns...> {
	using el_t = magma_t<gn,UIntType,N0,Ns...>;
	
	static constexpr bool funct(const el_t& t0) {
		return false;
	}
	static constexpr bool funct(const el_t& t0,const el_t& t1) {
		return (t1==(el_t::get_the_identity()));
	}
	static constexpr bool funct(const el_t& t0,const el_t& t1,const el_t& t2) {
		return (t1==(el_t::get_the_identity()));
	}
	static constexpr bool funct(const el_t& t0,const el_t& t1,const el_t& t2,const el_t& t3) {
		return (t1==(el_t::get_the_identity()));
	}
	static constexpr bool funct(const el_t& t0,const el_t& t1,const el_t& t2,const el_t& t3,const el_t& t4) {
		return (t1==(el_t::get_the_identity()));
	}
	static constexpr bool funct(const el_t& t0,const el_t& t1,const el_t& t2,const el_t& t3,const el_t& t4,const el_t& t5) {
		return (t1==(el_t::get_the_identity()));
	}
	static constexpr bool funct(const el_t& t0,const el_t& t1,const el_t& t2,const el_t& t3,const el_t& t4,const el_t& t5,const el_t& t6) {
		return (t1==(el_t::get_the_identity()));
	}
};
template<group_name gn,typename UIntType,UIntType N0,UIntType ... Ns>
struct arg_Ix_eq_id<2,magma_t,gn,UIntType,N0,Ns...> {
	using el_t = magma_t<gn,UIntType,N0,Ns...>;
	
	static constexpr bool funct(const el_t& t0) {
		return false;
	}
	static constexpr bool funct(const el_t& t0,const el_t& t1) {
		return false;
	}
	static constexpr bool funct(const el_t& t0,const el_t& t1,const el_t& t2) {
		return (t2==(el_t::get_the_identity()));
	}
	static constexpr bool funct(const el_t& t0,const el_t& t1,const el_t& t2,const el_t& t3) {
		return (t2==(el_t::get_the_identity()));
	}
	static constexpr bool funct(const el_t& t0,const el_t& t1,const el_t& t2,const el_t& t3,const el_t& t4) {
		return (t2==(el_t::get_the_identity()));
	}
	static constexpr bool funct(const el_t& t0,const el_t& t1,const el_t& t2,const el_t& t3,const el_t& t4,const el_t& t5) {
		return (t2==(el_t::get_the_identity()));
	}
	static constexpr bool funct(const el_t& t0,const el_t& t1,const el_t& t2,const el_t& t3,const el_t& t4,const el_t& t5,const el_t& t6) {
		return (t2==(el_t::get_the_identity()));
	}
};
template<group_name gn,typename UIntType,UIntType N0,UIntType ... Ns>
struct arg_Ix_eq_id<3,magma_t,gn,UIntType,N0,Ns...> {
	using el_t = magma_t<gn,UIntType,N0,Ns...>;
	
	static constexpr bool funct(const el_t& t0) {
		return false;
	}
	static constexpr bool funct(const el_t& t0,const el_t& t1) {
		return false;
	}
	static constexpr bool funct(const el_t& t0,const el_t& t1,const el_t& t2) {
		return false;
	}
	static constexpr bool funct(const el_t& t0,const el_t& t1,const el_t& t2,const el_t& t3) {
		return (t3==(el_t::get_the_identity()));
	}
	static constexpr bool funct(const el_t& t0,const el_t& t1,const el_t& t2,const el_t& t3,const el_t& t4) {
		return (t3==(el_t::get_the_identity()));
	}
	static constexpr bool funct(const el_t& t0,const el_t& t1,const el_t& t2,const el_t& t3,const el_t& t4,const el_t& t5) {
		return (t3==(el_t::get_the_identity()));
	}
	static constexpr bool funct(const el_t& t0,const el_t& t1,const el_t& t2,const el_t& t3,const el_t& t4,const el_t& t5,const el_t& t6) {
		return (t3==(el_t::get_the_identity()));
	}
};
template<group_name gn,typename UIntType,UIntType N0,UIntType ... Ns>
struct arg_Ix_eq_id<4,magma_t,gn,UIntType,N0,Ns...> {
	using el_t = magma_t<gn,UIntType,N0,Ns...>;
	
	static constexpr bool funct(const el_t& t0) {
		return false;
	}
	static constexpr bool funct(const el_t& t0,const el_t& t1) {
		return false;
	}
	static constexpr bool funct(const el_t& t0,const el_t& t1,const el_t& t2) {
		return false;
	}
	static constexpr bool funct(const el_t& t0,const el_t& t1,const el_t& t2,const el_t& t3) {
		return false;
	}
	static constexpr bool funct(const el_t& t0,const el_t& t1,const el_t& t2,const el_t& t3,const el_t& t4) {
		return (t4==(el_t::get_the_identity()));
	}
	static constexpr bool funct(const el_t& t0,const el_t& t1,const el_t& t2,const el_t& t3,const el_t& t4,const el_t& t5) {
		return (t4==(el_t::get_the_identity()));
	}
	static constexpr bool funct(const el_t& t0,const el_t& t1,const el_t& t2,const el_t& t3,const el_t& t4,const el_t& t5,const el_t& t6) {
		return (t4==(el_t::get_the_identity()));
	}
};
template<group_name gn,typename UIntType,UIntType N0,UIntType ... Ns>
struct arg_Ix_eq_id<5,magma_t,gn,UIntType,N0,Ns...> {
	using el_t = magma_t<gn,UIntType,N0,Ns...>;
	
	static constexpr bool funct(const el_t & t0) {
		return false;
	}
	static constexpr bool funct(const el_t & t0,const el_t & t1) {
		return false;
	}
	static constexpr bool funct(const el_t & t0,const el_t & t1,const el_t & t2) {
		return false;
	}
	static constexpr bool funct(const el_t & t0,const el_t & t1,const el_t & t2,const el_t & t3) {
		return false;
	}
	static constexpr bool funct(const el_t & t0,const el_t & t1,const el_t & t2,const el_t & t3,const el_t & t4) {
		return false;
	}
	static constexpr bool funct(const el_t & t0,const el_t & t1,const el_t & t2,const el_t & t3,const el_t & t4,const el_t & t5) {
		return (t5==(el_t::get_the_identity()));
	}
	static constexpr bool funct(const el_t & t0,const el_t & t1,const el_t & t2,const el_t & t3,const el_t & t4,const el_t & t5,const el_t & t6) {
		return (t5==(el_t::get_the_identity()));
	}
};
template<group_name gn,typename UIntType,UIntType N0,UIntType ... Ns>
struct arg_Ix_eq_id<6,magma_t,gn,UIntType,N0,Ns...> {
	using el_t = magma_t<gn,UIntType,N0,Ns...>;
	
	static constexpr bool funct(const el_t & t0) {
		return false;
	}
	static constexpr bool funct(const el_t & t0,const el_t & t1) {
		return false;
	}
	static constexpr bool funct(const el_t & t0,const el_t & t1,const el_t & t2) {
		return false;
	}
	static constexpr bool funct(const el_t & t0,const el_t & t1,const el_t & t2,const el_t & t3) {
		return false;
	}
	static constexpr bool funct(const el_t & t0,const el_t & t1,const el_t & t2,const el_t & t3,const el_t & t4) {
		return false;
	}
	static constexpr bool funct(const el_t & t0,const el_t & t1,const el_t & t2,const el_t & t3,const el_t & t4,const el_t & t5) {
		return false;
	}
	static constexpr bool funct(const el_t & t0,const el_t & t1,const el_t & t2,const el_t & t3,const el_t & t4,const el_t & t5,const el_t & t6) {
		return (t6==(el_t::get_the_identity()));
	}
};
}
namespace details {
template<size_t I,size_t J,template<group_name,typename K_t,K_t,K_t...> class TT,group_name gn,typename UIntType,UIntType N0,UIntType ... Ns>
struct arg_I_eq_arg_J;
template<group_name gn,typename UIntType,UIntType N0,UIntType ... Ns>
struct arg_I_eq_arg_J<0,1,magma_t,gn,UIntType,N0,Ns...> {
	using el_t = magma_t<gn,UIntType,N0,Ns...>;
	static constexpr bool funct(const el_t & t0) {
		return false;
	}
	static constexpr bool funct(const el_t & t0,const el_t & t1) {
		return (t0==t1);
	}
	static constexpr bool funct(const el_t & t0,const el_t & t1,const el_t & t2) {
		return (t0==t1);
	}
	static constexpr bool funct(const el_t & t0,const el_t & t1,const el_t & t2,const el_t & t3) {
		return (t0==t1);
	}
	static constexpr bool funct(const el_t & t0,const el_t & t1,const el_t & t2,const el_t & t3,const el_t & t4) {
		return (t0==t1);
	}
	static constexpr bool funct(const el_t & t0,const el_t & t1,const el_t & t2,const el_t & t3,const el_t & t4,const el_t & t5) {
		return (t0==t1);
	}
	static constexpr bool funct(const el_t & t0,const el_t & t1,const el_t & t2,const el_t & t3,const el_t & t4,const el_t & t5,const el_t & t6) {
		return (t0==t1);
	}
};
template<group_name gn,typename UIntType,UIntType N0,UIntType ... Ns>
struct arg_I_eq_arg_J<0,2,magma_t,gn,UIntType,N0,Ns...> {
	using el_t = magma_t<gn,UIntType,N0,Ns...>;
	static constexpr bool funct(const el_t & t0) {
		return false;
	}
	static constexpr bool funct(const el_t & t0,const el_t & t1) {
		return false;
	}
	static constexpr bool funct(const el_t & t0,const el_t & t1,const el_t & t2) {
		return (t0==t2);
	}
	static constexpr bool funct(const el_t & t0,const el_t & t1,const el_t & t2,const el_t & t3) {
		return (t0==t2);
	}
	static constexpr bool funct(const el_t & t0,const el_t & t1,const el_t & t2,const el_t & t3,const el_t & t4) {
		return (t0==t2);
	}
	static constexpr bool funct(const el_t & t0,const el_t & t1,const el_t & t2,const el_t & t3,const el_t & t4,const el_t & t5) {
		return (t0==t2);
	}
	static constexpr bool funct(const el_t & t0,const el_t & t1,const el_t & t2,const el_t & t3,const el_t & t4,const el_t & t5,const el_t & t6) {
		return (t0==t2);
	}
};
template<group_name gn,typename UIntType,UIntType N0,UIntType ... Ns>
struct arg_I_eq_arg_J<0,3,magma_t,gn,UIntType,N0,Ns...> {
	using el_t = magma_t<gn,UIntType,N0,Ns...>;
	static constexpr bool funct(const el_t & t0) {
		return false;
	}
	static constexpr bool funct(const el_t & t0,const el_t & t1) {
		return false;
	}
	static constexpr bool funct(const el_t & t0,const el_t & t1,const el_t & t2) {
		return false;
	}
	static constexpr bool funct(const el_t & t0,const el_t & t1,const el_t & t2,const el_t & t3) {
		return (t0==t3);
	}
	static constexpr bool funct(const el_t & t0,const el_t & t1,const el_t & t2,const el_t & t3,const el_t & t4) {
		return (t0==t3);
	}
	static constexpr bool funct(const el_t & t0,const el_t & t1,const el_t & t2,const el_t & t3,const el_t & t4,const el_t & t5) {
		return (t0==t3);
	}
	static constexpr bool funct(const el_t & t0,const el_t & t1,const el_t & t2,const el_t & t3,const el_t & t4,const el_t & t5,const el_t & t6) {
		return (t0==t3);
	}
};
template<group_name gn,typename UIntType,UIntType N0,UIntType ... Ns>
struct arg_I_eq_arg_J<0,4,magma_t,gn,UIntType,N0,Ns...> {
	using el_t = magma_t<gn,UIntType,N0,Ns...>;
	static constexpr bool funct(const el_t & t0) {
		return false;
	}
	static constexpr bool funct(const el_t & t0,const el_t & t1) {
		return false;
	}
	static constexpr bool funct(const el_t & t0,const el_t & t1,const el_t & t2) {
		return false;
	}
	static constexpr bool funct(const el_t & t0,const el_t & t1,const el_t & t2,const el_t & t3) {
		return false;
	}
	static constexpr bool funct(const el_t & t0,const el_t & t1,const el_t & t2,const el_t & t3,const el_t & t4) {
		return (t0==t4);
	}
	static constexpr bool funct(const el_t & t0,const el_t & t1,const el_t & t2,const el_t & t3,const el_t & t4,const el_t & t5) {
		return (t0==t4);
	}
	static constexpr bool funct(const el_t & t0,const el_t & t1,const el_t & t2,const el_t & t3,const el_t & t4,const el_t & t5,const el_t & t6) {
		return (t0==t4);
	}
};
template<group_name gn,typename UIntType,UIntType N0,UIntType ... Ns>
struct arg_I_eq_arg_J<0,5,magma_t,gn,UIntType,N0,Ns...> {
	using el_t = magma_t<gn,UIntType,N0,Ns...>;
	static constexpr bool funct(const el_t & t0) {
		return false;
	}
	static constexpr bool funct(const el_t & t0,const el_t & t1) {
		return false;
	}
	static constexpr bool funct(const el_t & t0,const el_t & t1,const el_t & t2) {
		return false;
	}
	static constexpr bool funct(const el_t & t0,const el_t & t1,const el_t & t2,const el_t & t3) {
		return false;
	}
	static constexpr bool funct(const el_t & t0,const el_t & t1,const el_t & t2,const el_t & t3,const el_t & t4) {
		return false;
	}
	static constexpr bool funct(const el_t & t0,const el_t & t1,const el_t & t2,const el_t & t3,const el_t & t4,const el_t & t5) {
		return (t0==t5);
	}
	static constexpr bool funct(const el_t & t0,const el_t & t1,const el_t & t2,const el_t & t3,const el_t & t4,const el_t & t5,const el_t & t6) {
		return (t0==t5);
	}
};
template<group_name gn,typename UIntType,UIntType N0,UIntType ... Ns>
struct arg_I_eq_arg_J<0,6,magma_t,gn,UIntType,N0,Ns...> {
	using el_t = magma_t<gn,UIntType,N0,Ns...>;
	static constexpr bool funct(const el_t & t0) {
		return false;
	}
	static constexpr bool funct(const el_t & t0,const el_t & t1) {
		return false;
	}
	static constexpr bool funct(const el_t & t0,const el_t & t1,const el_t & t2) {
		return false;
	}
	static constexpr bool funct(const el_t & t0,const el_t & t1,const el_t & t2,const el_t & t3) {
		return false;
	}
	static constexpr bool funct(const el_t & t0,const el_t & t1,const el_t & t2,const el_t & t3,const el_t & t4) {
		return false;
	}
	static constexpr bool funct(const el_t & t0,const el_t & t1,const el_t & t2,const el_t & t3,const el_t & t4,const el_t & t5) {
		return false;
	}
	static constexpr bool funct(const el_t & t0,const el_t & t1,const el_t & t2,const el_t & t3,const el_t & t4,const el_t & t5,const el_t & t6) {
		return (t0==t6);
	}
};
template<group_name gn,typename UIntType,UIntType N0,UIntType ... Ns>
struct arg_I_eq_arg_J<1,2,magma_t,gn,UIntType,N0,Ns...> {
	using el_t = magma_t<gn,UIntType,N0,Ns...>;
	static constexpr bool funct(const el_t & t0) {
		return false;
	}
	static constexpr bool funct(const el_t & t0,const el_t & t1) {
		return false;
	}
	static constexpr bool funct(const el_t & t0,const el_t & t1,const el_t & t2) {
		return (t1==t2);
	}
	static constexpr bool funct(const el_t & t0,const el_t & t1,const el_t & t2,const el_t & t3) {
		return (t1==t2);
	}
	static constexpr bool funct(const el_t & t0,const el_t & t1,const el_t & t2,const el_t & t3,const el_t & t4) {
		return (t1==t2);
	}
	static constexpr bool funct(const el_t & t0,const el_t & t1,const el_t & t2,const el_t & t3,const el_t & t4,const el_t & t5) {
		return (t1==t2);
	}
	static constexpr bool funct(const el_t & t0,const el_t & t1,const el_t & t2,const el_t & t3,const el_t & t4,const el_t & t5,const el_t & t6) {
		return (t1==t2);
	}
};
template<group_name gn,typename UIntType,UIntType N0,UIntType ... Ns>
struct arg_I_eq_arg_J<1,3,magma_t,gn,UIntType,N0,Ns...> {
	using el_t = magma_t<gn,UIntType,N0,Ns...>;
	static constexpr bool funct(const el_t & t0) {
		return false;
	}
	static constexpr bool funct(const el_t & t0,const el_t & t1) {
		return false;
	}
	static constexpr bool funct(const el_t & t0,const el_t & t1,const el_t & t2) {
		return false;
	}
	static constexpr bool funct(const el_t & t0,const el_t & t1,const el_t & t2,const el_t & t3) {
		return (t1==t3);
	}
	static constexpr bool funct(const el_t & t0,const el_t & t1,const el_t & t2,const el_t & t3,const el_t & t4) {
		return (t1==t3);
	}
	static constexpr bool funct(const el_t & t0,const el_t & t1,const el_t & t2,const el_t & t3,const el_t & t4,const el_t & t5) {
		return (t1==t3);
	}
	static constexpr bool funct(const el_t & t0,const el_t & t1,const el_t & t2,const el_t & t3,const el_t & t4,const el_t & t5,const el_t & t6) {
		return (t1==t3);
	}
};
template<group_name gn,typename UIntType,UIntType N0,UIntType ... Ns>
struct arg_I_eq_arg_J<1,4,magma_t,gn,UIntType,N0,Ns...> {
	using el_t = magma_t<gn,UIntType,N0,Ns...>;
	static constexpr bool funct(const el_t & t0) {
		return false;
	}
	static constexpr bool funct(const el_t & t0,const el_t & t1) {
		return false;
	}
	static constexpr bool funct(const el_t & t0,const el_t & t1,const el_t & t2) {
		return false;
	}
	static constexpr bool funct(const el_t & t0,const el_t & t1,const el_t & t2,const el_t & t3) {
		return false;
	}
	static constexpr bool funct(const el_t & t0,const el_t & t1,const el_t & t2,const el_t & t3,const el_t & t4) {
		return (t1==t4);
	}
	static constexpr bool funct(const el_t & t0,const el_t & t1,const el_t & t2,const el_t & t3,const el_t & t4,const el_t & t5) {
		return (t1==t4);
	}
	static constexpr bool funct(const el_t & t0,const el_t & t1,const el_t & t2,const el_t & t3,const el_t & t4,const el_t & t5,const el_t & t6) {
		return (t1==t4);
	}
};
template<group_name gn,typename UIntType,UIntType N0,UIntType ... Ns>
struct arg_I_eq_arg_J<1,5,magma_t,gn,UIntType,N0,Ns...> {
	using el_t = magma_t<gn,UIntType,N0,Ns...>;
	static constexpr bool funct(const el_t & t0) {
		return false;
	}
	static constexpr bool funct(const el_t & t0,const el_t & t1) {
		return false;
	}
	static constexpr bool funct(const el_t & t0,const el_t & t1,const el_t & t2) {
		return false;
	}
	static constexpr bool funct(const el_t & t0,const el_t & t1,const el_t & t2,const el_t & t3) {
		return false;
	}
	static constexpr bool funct(const el_t & t0,const el_t & t1,const el_t & t2,const el_t & t3,const el_t & t4) {
		return false;
	}
	static constexpr bool funct(const el_t & t0,const el_t & t1,const el_t & t2,const el_t & t3,const el_t & t4,const el_t & t5) {
		return (t1==t5);
	}
	static constexpr bool funct(const el_t & t0,const el_t & t1,const el_t & t2,const el_t & t3,const el_t & t4,const el_t & t5,const el_t & t6) {
		return (t1==t5);
	}
};
template<group_name gn,typename UIntType,UIntType N0,UIntType ... Ns>
struct arg_I_eq_arg_J<1,6,magma_t,gn,UIntType,N0,Ns...> {
	using el_t = magma_t<gn,UIntType,N0,Ns...>;
	static constexpr bool funct(const el_t & t0) {
		return false;
	}
	static constexpr bool funct(const el_t & t0,const el_t & t1) {
		return false;
	}
	static constexpr bool funct(const el_t & t0,const el_t & t1,const el_t & t2) {
		return false;
	}
	static constexpr bool funct(const el_t & t0,const el_t & t1,const el_t & t2,const el_t & t3) {
		return false;
	}
	static constexpr bool funct(const el_t & t0,const el_t & t1,const el_t & t2,const el_t & t3,const el_t & t4) {
		return false;
	}
	static constexpr bool funct(const el_t & t0,const el_t & t1,const el_t & t2,const el_t & t3,const el_t & t4,const el_t & t5) {
		return false;
	}
	static constexpr bool funct(const el_t & t0,const el_t & t1,const el_t & t2,const el_t & t3,const el_t & t4,const el_t & t5,const el_t & t6) {
		return (t1==t6);
	}
};
template<group_name gn,typename UIntType,UIntType N0,UIntType ... Ns>
struct arg_I_eq_arg_J<2,3,magma_t,gn,UIntType,N0,Ns...> {
	using el_t = magma_t<gn,UIntType,N0,Ns...>;
	static constexpr bool funct(const el_t & t0) {
		return false;
	}
	static constexpr bool funct(const el_t & t0,const el_t & t1) {
		return false;
	}
	static constexpr bool funct(const el_t & t0,const el_t & t1,const el_t & t2) {
		return false;
	}
	static constexpr bool funct(const el_t & t0,const el_t & t1,const el_t & t2,const el_t & t3) {
		return (t2==t3);
	}
	static constexpr bool funct(const el_t & t0,const el_t & t1,const el_t & t2,const el_t & t3,const el_t & t4) {
		return (t2==t3);
	}
	static constexpr bool funct(const el_t & t0,const el_t & t1,const el_t & t2,const el_t & t3,const el_t & t4,const el_t & t5) {
		return (t2==t3);
	}
	static constexpr bool funct(const el_t & t0,const el_t & t1,const el_t & t2,const el_t & t3,const el_t & t4,const el_t & t5,const el_t & t6) {
		return (t2==t3);
	}
};
template<group_name gn,typename UIntType,UIntType N0,UIntType ... Ns>
struct arg_I_eq_arg_J<2,4,magma_t,gn,UIntType,N0,Ns...> {
	using el_t = magma_t<gn,UIntType,N0,Ns...>;
	static constexpr bool funct(const el_t & t0) {
		return false;
	}
	static constexpr bool funct(const el_t & t0,const el_t & t1) {
		return false;
	}
	static constexpr bool funct(const el_t & t0,const el_t & t1,const el_t & t2) {
		return false;
	}
	static constexpr bool funct(const el_t & t0,const el_t & t1,const el_t & t2,const el_t & t3) {
		return false;
	}
	static constexpr bool funct(const el_t & t0,const el_t & t1,const el_t & t2,const el_t & t3,const el_t & t4) {
		return (t2==t4);
	}
	static constexpr bool funct(const el_t & t0,const el_t & t1,const el_t & t2,const el_t & t3,const el_t & t4,const el_t & t5) {
		return (t2==t4);
	}
	static constexpr bool funct(const el_t & t0,const el_t & t1,const el_t & t2,const el_t & t3,const el_t & t4,const el_t & t5,const el_t & t6) {
		return (t2==t4);
	}
};
template<group_name gn,typename UIntType,UIntType N0,UIntType ... Ns>
struct arg_I_eq_arg_J<2,5,magma_t,gn,UIntType,N0,Ns...> {
	using el_t = magma_t<gn,UIntType,N0,Ns...>;
	static constexpr bool funct(const el_t & t0) {
		return false;
	}
	static constexpr bool funct(const el_t & t0,const el_t & t1) {
		return false;
	}
	static constexpr bool funct(const el_t & t0,const el_t & t1,const el_t & t2) {
		return false;
	}
	static constexpr bool funct(const el_t & t0,const el_t & t1,const el_t & t2,const el_t & t3) {
		return false;
	}
	static constexpr bool funct(const el_t & t0,const el_t & t1,const el_t & t2,const el_t & t3,const el_t & t4) {
		return false;
	}
	static constexpr bool funct(const el_t & t0,const el_t & t1,const el_t & t2,const el_t & t3,const el_t & t4,const el_t & t5) {
		return (t2==t5);
	}
	static constexpr bool funct(const el_t & t0,const el_t & t1,const el_t & t2,const el_t & t3,const el_t & t4,const el_t & t5,const el_t & t6) {
		return (t2==t5);
	}
};
template<group_name gn,typename UIntType,UIntType N0,UIntType ... Ns>
struct arg_I_eq_arg_J<2,6,magma_t,gn,UIntType,N0,Ns...> {
	using el_t = magma_t<gn,UIntType,N0,Ns...>;
	static constexpr bool funct(const el_t & t0) {
		return false;
	}
	static constexpr bool funct(const el_t & t0,const el_t & t1) {
		return false;
	}
	static constexpr bool funct(const el_t & t0,const el_t & t1,const el_t & t2) {
		return false;
	}
	static constexpr bool funct(const el_t & t0,const el_t & t1,const el_t & t2,const el_t & t3) {
		return false;
	}
	static constexpr bool funct(const el_t & t0,const el_t & t1,const el_t & t2,const el_t & t3,const el_t & t4) {
		return false;
	}
	static constexpr bool funct(const el_t & t0,const el_t & t1,const el_t & t2,const el_t & t3,const el_t & t4,const el_t & t5) {
		return false;
	}
	static constexpr bool funct(const el_t & t0,const el_t & t1,const el_t & t2,const el_t & t3,const el_t & t4,const el_t & t5,const el_t & t6) {
		return (t2==t6);
	}
};
template<group_name gn,typename UIntType,UIntType N0,UIntType ... Ns>
struct arg_I_eq_arg_J<3,4,magma_t,gn,UIntType,N0,Ns...> {
	using el_t = magma_t<gn,UIntType,N0,Ns...>;
	static constexpr bool funct(const el_t & t0) {
		return false;
	}
	static constexpr bool funct(const el_t & t0,const el_t & t1) {
		return false;
	}
	static constexpr bool funct(const el_t & t0,const el_t & t1,const el_t & t2) {
		return false;
	}
	static constexpr bool funct(const el_t & t0,const el_t & t1,const el_t & t2,const el_t & t3) {
		return false;
	}
	static constexpr bool funct(const el_t & t0,const el_t & t1,const el_t & t2,const el_t & t3,const el_t & t4) {
		return (t3==t4);
	}
	static constexpr bool funct(const el_t & t0,const el_t & t1,const el_t & t2,const el_t & t3,const el_t & t4,const el_t & t5) {
		return (t3==t4);
	}
	static constexpr bool funct(const el_t & t0,const el_t & t1,const el_t & t2,const el_t & t3,const el_t & t4,const el_t & t5,const el_t & t6) {
		return (t3==t4);
	}
};
template<group_name gn,typename UIntType,UIntType N0,UIntType ... Ns>
struct arg_I_eq_arg_J<3,5,magma_t,gn,UIntType,N0,Ns...> {
	using el_t = magma_t<gn,UIntType,N0,Ns...>;
	static constexpr bool funct(const el_t & t0) {
		return false;
	}
	static constexpr bool funct(const el_t & t0,const el_t & t1) {
		return false;
	}
	static constexpr bool funct(const el_t & t0,const el_t & t1,const el_t & t2) {
		return false;
	}
	static constexpr bool funct(const el_t & t0,const el_t & t1,const el_t & t2,const el_t & t3) {
		return false;
	}
	static constexpr bool funct(const el_t & t0,const el_t & t1,const el_t & t2,const el_t & t3,const el_t & t4) {
		return false;
	}
	static constexpr bool funct(const el_t & t0,const el_t & t1,const el_t & t2,const el_t & t3,const el_t & t4,const el_t & t5) {
		return (t3==t5);
	}
	static constexpr bool funct(const el_t & t0,const el_t & t1,const el_t & t2,const el_t & t3,const el_t & t4,const el_t & t5,const el_t & t6) {
		return (t3==t5);
	}
};
template<group_name gn,typename UIntType,UIntType N0,UIntType ... Ns>
struct arg_I_eq_arg_J<3,6,magma_t,gn,UIntType,N0,Ns...> {
	using el_t = magma_t<gn,UIntType,N0,Ns...>;
	static constexpr bool funct(const el_t & t0) {
		return false;
	}
	static constexpr bool funct(const el_t & t0,const el_t & t1) {
		return false;
	}
	static constexpr bool funct(const el_t & t0,const el_t & t1,const el_t & t2) {
		return false;
	}
	static constexpr bool funct(const el_t & t0,const el_t & t1,const el_t & t2,const el_t & t3) {
		return false;
	}
	static constexpr bool funct(const el_t & t0,const el_t & t1,const el_t & t2,const el_t & t3,const el_t & t4) {
		return false;
	}
	static constexpr bool funct(const el_t & t0,const el_t & t1,const el_t & t2,const el_t & t3,const el_t & t4,const el_t & t5) {
		return false;
	}
	static constexpr bool funct(const el_t & t0,const el_t & t1,const el_t & t2,const el_t & t3,const el_t & t4,const el_t & t5,const el_t & t6) {
		return (t3==t6);
	}
};
template<group_name gn,typename UIntType,UIntType N0,UIntType ... Ns>
struct arg_I_eq_arg_J<4,5,magma_t,gn,UIntType,N0,Ns...> {
	using el_t = magma_t<gn,UIntType,N0,Ns...>;
	static constexpr bool funct(const el_t & t0) {
		return false;
	}
	static constexpr bool funct(const el_t & t0,const el_t & t1) {
		return false;
	}
	static constexpr bool funct(const el_t & t0,const el_t & t1,const el_t & t2) {
		return false;
	}
	static constexpr bool funct(const el_t & t0,const el_t & t1,const el_t & t2,const el_t & t3) {
		return false;
	}
	static constexpr bool funct(const el_t & t0,const el_t & t1,const el_t & t2,const el_t & t3,const el_t & t4) {
		return false;
	}
	static constexpr bool funct(const el_t & t0,const el_t & t1,const el_t & t2,const el_t & t3,const el_t & t4,const el_t & t5) {
		return (t4==t5);
	}
	static constexpr bool funct(const el_t & t0,const el_t & t1,const el_t & t2,const el_t & t3,const el_t & t4,const el_t & t5,const el_t & t6) {
		return (t4==t5);
	}
};
template<group_name gn,typename UIntType,UIntType N0,UIntType ... Ns>
struct arg_I_eq_arg_J<4,6,magma_t,gn,UIntType,N0,Ns...> {
	using el_t = magma_t<gn,UIntType,N0,Ns...>;
	static constexpr bool funct(const el_t & t0) {
		return false;
	}
	static constexpr bool funct(const el_t & t0,const el_t & t1) {
		return false;
	}
	static constexpr bool funct(const el_t & t0,const el_t & t1,const el_t & t2) {
		return false;
	}
	static constexpr bool funct(const el_t & t0,const el_t & t1,const el_t & t2,const el_t & t3) {
		return false;
	}
	static constexpr bool funct(const el_t & t0,const el_t & t1,const el_t & t2,const el_t & t3,const el_t & t4) {
		return false;
	}
	static constexpr bool funct(const el_t & t0,const el_t & t1,const el_t & t2,const el_t & t3,const el_t & t4,const el_t & t5) {
		return false;
	}
	static constexpr bool funct(const el_t & t0,const el_t & t1,const el_t & t2,const el_t & t3,const el_t & t4,const el_t & t5,const el_t & t6) {
		return (t4==t6);
	}
};
template<group_name gn,typename UIntType,UIntType N0,UIntType ... Ns>
struct arg_I_eq_arg_J<5,6,magma_t,gn,UIntType,N0,Ns...> {
	using el_t = magma_t<gn,UIntType,N0,Ns...>;
	static constexpr bool funct(const el_t & t0) {
		return false;
	}
	static constexpr bool funct(const el_t & t0,const el_t & t1) {
		return false;
	}
	static constexpr bool funct(const el_t & t0,const el_t & t1,const el_t & t2) {
		return false;
	}
	static constexpr bool funct(const el_t & t0,const el_t & t1,const el_t & t2,const el_t & t3) {
		return false;
	}
	static constexpr bool funct(const el_t & t0,const el_t & t1,const el_t & t2,const el_t & t3,const el_t & t4) {
		return false;
	}
	static constexpr bool funct(const el_t & t0,const el_t & t1,const el_t & t2,const el_t & t3,const el_t & t4,const el_t & t5) {
		return false;
	}
	static constexpr bool funct(const el_t & t0,const el_t & t1,const el_t & t2,const el_t & t3,const el_t & t4,const el_t & t5,const el_t & t6) {
		return (t5==t6);
	}
};
}
namespace details {
template<size_t I,size_t J,template<group_name,typename K_t,K_t,K_t...> class TT,group_name gn,typename UIntType,UIntType N0,UIntType ... Ns>
struct arg_I_eq_some_prev_or_eq_id; 
template<group_name gn,typename UIntType,UIntType N0,UIntType ... Ns>
struct arg_I_eq_some_prev_or_eq_id<6,0,magma_t,gn,UIntType,N0,Ns...> {
	using el_t = magma_t<gn,UIntType,N0,Ns...>;
	
	static constexpr bool funct(const el_t & t0) {
		return false;
	}
	static constexpr bool funct(const el_t & t0,const el_t & t1) {
		return false;
	}
	static constexpr bool funct(const el_t & t0,const el_t & t1,const el_t & t2) {
		return false;
	}
	static constexpr bool funct(const el_t & t0,const el_t & t1,const el_t & t2,const el_t & t3) {
		return false;
	}
	static constexpr bool funct(const el_t & t0,const el_t & t1,const el_t & t2,const el_t & t3,const el_t & t4) {
		return false;
	}
	static constexpr bool funct(const el_t & t0,const el_t & t1,const el_t & t2,const el_t & t3,const el_t & t4,const el_t & t5) {
		return false;
	}
	static constexpr bool funct(const el_t & t0,const el_t & t1,const el_t & t2,const el_t & t3,const el_t & t4,const el_t & t5,const el_t & t6) {
		return ((t0==t6)||(t6==(el_t::get_the_identity())));
	}
};
template<group_name gn,typename UIntType,UIntType N0,UIntType ... Ns>
struct arg_I_eq_some_prev_or_eq_id<6,1,magma_t,gn,UIntType,N0,Ns...> {
	using el_t = magma_t<gn,UIntType,N0,Ns...>;
	
	static constexpr bool funct(const el_t & t0) {
		return false;
	}
	static constexpr bool funct(const el_t & t0,const el_t & t1) {
		return false;
	}
	static constexpr bool funct(const el_t & t0,const el_t & t1,const el_t & t2) {
		return false;
	}
	static constexpr bool funct(const el_t & t0,const el_t & t1,const el_t & t2,const el_t & t3) {
		return false;
	}
	static constexpr bool funct(const el_t & t0,const el_t & t1,const el_t & t2,const el_t & t3,const el_t & t4) {
		return false;
	}
	static constexpr bool funct(const el_t & t0,const el_t & t1,const el_t & t2,const el_t & t3,const el_t & t4,const el_t & t5) {
		return false;
	}
	static constexpr bool funct(const el_t & t0,const el_t & t1,const el_t & t2,const el_t & t3,const el_t & t4,const el_t & t5,const el_t & t6) {
		return ((t0==t6)||(t1==t6)||(t6==(el_t::get_the_identity())));
	}
};
template<group_name gn,typename UIntType,UIntType N0,UIntType ... Ns>
struct arg_I_eq_some_prev_or_eq_id<6,2,magma_t,gn,UIntType,N0,Ns...> {
	using el_t = magma_t<gn,UIntType,N0,Ns...>;
	
	static constexpr bool funct(const el_t & t0) {
		return false;
	}
	static constexpr bool funct(const el_t & t0,const el_t & t1) {
		return false;
	}
	static constexpr bool funct(const el_t & t0,const el_t & t1,const el_t & t2) {
		return false;
	}
	static constexpr bool funct(const el_t & t0,const el_t & t1,const el_t & t2,const el_t & t3) {
		return false;
	}
	static constexpr bool funct(const el_t & t0,const el_t & t1,const el_t & t2,const el_t & t3,const el_t & t4) {
		return false;
	}
	static constexpr bool funct(const el_t & t0,const el_t & t1,const el_t & t2,const el_t & t3,const el_t & t4,const el_t & t5) {
		return false;
	}
	static constexpr bool funct(const el_t & t0,const el_t & t1,const el_t & t2,const el_t & t3,const el_t & t4,const el_t & t5,const el_t & t6) {
		return ((t0==t6)||(t1==t6)||(t2==t6)||(t6==(el_t::get_the_identity())));
	}
};
template<group_name gn,typename UIntType,UIntType N0,UIntType ... Ns>
struct arg_I_eq_some_prev_or_eq_id<6,3,magma_t,gn,UIntType,N0,Ns...> {
	using el_t = magma_t<gn,UIntType,N0,Ns...>;
	
	static constexpr bool funct(const el_t & t0) {
		return false;
	}
	static constexpr bool funct(const el_t & t0,const el_t & t1) {
		return false;
	}
	static constexpr bool funct(const el_t & t0,const el_t & t1,const el_t & t2) {
		return false;
	}
	static constexpr bool funct(const el_t & t0,const el_t & t1,const el_t & t2,const el_t & t3) {
		return false;
	}
	static constexpr bool funct(const el_t & t0,const el_t & t1,const el_t & t2,const el_t & t3,const el_t & t4) {
		return false;
	}
	static constexpr bool funct(const el_t & t0,const el_t & t1,const el_t & t2,const el_t & t3,const el_t & t4,const el_t & t5) {
		return false;
	}
	static constexpr bool funct(const el_t & t0,const el_t & t1,const el_t & t2,const el_t & t3,const el_t & t4,const el_t & t5,const el_t & t6) {
		return ((t0==t6)||(t1==t6)||(t2==t6)||(t3==t6)||(t6==(el_t::get_the_identity())));
	}
};
template<group_name gn,typename UIntType,UIntType N0,UIntType ... Ns>
struct arg_I_eq_some_prev_or_eq_id<6,4,magma_t,gn,UIntType,N0,Ns...> {
	using el_t = magma_t<gn,UIntType,N0,Ns...>;
	
	static constexpr bool funct(const el_t & t0) {
		return false;
	}
	static constexpr bool funct(const el_t & t0,const el_t & t1) {
		return false;
	}
	static constexpr bool funct(const el_t & t0,const el_t & t1,const el_t & t2) {
		return false;
	}
	static constexpr bool funct(const el_t & t0,const el_t & t1,const el_t & t2,const el_t & t3) {
		return false;
	}
	static constexpr bool funct(const el_t & t0,const el_t & t1,const el_t & t2,const el_t & t3,const el_t & t4) {
		return false;
	}
	static constexpr bool funct(const el_t & t0,const el_t & t1,const el_t & t2,const el_t & t3,const el_t & t4,const el_t & t5) {
		return false;
	}
	static constexpr bool funct(const el_t & t0,const el_t & t1,const el_t & t2,const el_t & t3,const el_t & t4,const el_t & t5,const el_t & t6) {
		return ((t0==t6)||(t1==t6)||(t2==t6)||(t3==t6)||(t4==t6)||(t6==(el_t::get_the_identity())));
	}
};
template<group_name gn,typename UIntType,UIntType N0,UIntType ... Ns>
struct arg_I_eq_some_prev_or_eq_id<6,5,magma_t,gn,UIntType,N0,Ns...> {
	using el_t = magma_t<gn,UIntType,N0,Ns...>;
	
	static constexpr bool funct(const el_t & t0) {
		return false;
	}
	static constexpr bool funct(const el_t & t0,const el_t & t1) {
		return false;
	}
	static constexpr bool funct(const el_t & t0,const el_t & t1,const el_t & t2) {
		return false;
	}
	static constexpr bool funct(const el_t & t0,const el_t & t1,const el_t & t2,const el_t & t3) {
		return false;
	}
	static constexpr bool funct(const el_t & t0,const el_t & t1,const el_t & t2,const el_t & t3,const el_t & t4) {
		return false;
	}
	static constexpr bool funct(const el_t & t0,const el_t & t1,const el_t & t2,const el_t & t3,const el_t & t4,const el_t & t5) {
		return false;
	}
	static constexpr bool funct(const el_t & t0,const el_t & t1,const el_t & t2,const el_t & t3,const el_t & t4,const el_t & t5,const el_t & t6) {
		return ((t0==t6)||(t1==t6)||(t2==t6)||(t3==t6)||(t4==t6)||(t5==t6)||(t6==(el_t::get_the_identity())));
	}
};
template<group_name gn,typename UIntType,UIntType N0,UIntType ... Ns>
struct arg_I_eq_some_prev_or_eq_id<5,0,magma_t,gn,UIntType,N0,Ns...> {
	using el_t = magma_t<gn,UIntType,N0,Ns...>;
	
	static constexpr bool funct(const el_t & t0) {
		return false;
	}
	static constexpr bool funct(const el_t & t0,const el_t & t1) {
		return false;
	}
	static constexpr bool funct(const el_t & t0,const el_t & t1,const el_t & t2) {
		return false;
	}
	static constexpr bool funct(const el_t & t0,const el_t & t1,const el_t & t2,const el_t & t3) {
		return false;
	}
	static constexpr bool funct(const el_t & t0,const el_t & t1,const el_t & t2,const el_t & t3,const el_t & t4) {
		return false;
	}
	static constexpr bool funct(const el_t & t0,const el_t & t1,const el_t & t2,const el_t & t3,const el_t & t4,const el_t & t5) {
		return ((t0==t5)||(t5==(el_t::get_the_identity())));
	}
	static constexpr bool funct(const el_t & t0,const el_t & t1,const el_t & t2,const el_t & t3,const el_t & t4,const el_t & t5,const el_t & t6) {
		return ((t0==t5)||(t5==(el_t::get_the_identity())));
	}
};
template<group_name gn,typename UIntType,UIntType N0,UIntType ... Ns>
struct arg_I_eq_some_prev_or_eq_id<5,1,magma_t,gn,UIntType,N0,Ns...> {
	using el_t = magma_t<gn,UIntType,N0,Ns...>;
	
	static constexpr bool funct(const el_t & t0) {
		return false;
	}
	static constexpr bool funct(const el_t & t0,const el_t & t1) {
		return false;
	}
	static constexpr bool funct(const el_t & t0,const el_t & t1,const el_t & t2) {
		return false;
	}
	static constexpr bool funct(const el_t & t0,const el_t & t1,const el_t & t2,const el_t & t3) {
		return false;
	}
	static constexpr bool funct(const el_t & t0,const el_t & t1,const el_t & t2,const el_t & t3,const el_t & t4) {
		return false;
	}
	static constexpr bool funct(const el_t & t0,const el_t & t1,const el_t & t2,const el_t & t3,const el_t & t4,const el_t & t5) {
		return ((t0==t5)||(t1==t5)||(t5==(el_t::get_the_identity())));
	}
	static constexpr bool funct(const el_t & t0,const el_t & t1,const el_t & t2,const el_t & t3,const el_t & t4,const el_t & t5,const el_t & t6) {
		return ((t0==t5)||(t1==t5)||(t5==(el_t::get_the_identity())));
	}
};
template<group_name gn,typename UIntType,UIntType N0,UIntType ... Ns>
struct arg_I_eq_some_prev_or_eq_id<5,2,magma_t,gn,UIntType,N0,Ns...> {
	using el_t = magma_t<gn,UIntType,N0,Ns...>;
	
	static constexpr bool funct(const el_t & t0) {
		return false;
	}
	static constexpr bool funct(const el_t & t0,const el_t & t1) {
		return false;
	}
	static constexpr bool funct(const el_t & t0,const el_t & t1,const el_t & t2) {
		return false;
	}
	static constexpr bool funct(const el_t & t0,const el_t & t1,const el_t & t2,const el_t & t3) {
		return false;
	}
	static constexpr bool funct(const el_t & t0,const el_t & t1,const el_t & t2,const el_t & t3,const el_t & t4) {
		return false;
	}
	static constexpr bool funct(const el_t & t0,const el_t & t1,const el_t & t2,const el_t & t3,const el_t & t4,const el_t & t5) {
		return ((t0==t5)||(t1==t5)||(t2==t5)||(t5==(el_t::get_the_identity())));
	}
	static constexpr bool funct(const el_t & t0,const el_t & t1,const el_t & t2,const el_t & t3,const el_t & t4,const el_t & t5,const el_t & t6) {
		return ((t0==t5)||(t1==t5)||(t2==t5)||(t5==(el_t::get_the_identity())));
	}
};
template<group_name gn,typename UIntType,UIntType N0,UIntType ... Ns>
struct arg_I_eq_some_prev_or_eq_id<5,3,magma_t,gn,UIntType,N0,Ns...> {
	using el_t = magma_t<gn,UIntType,N0,Ns...>;
	
	static constexpr bool funct(const el_t & t0) {
		return false;
	}
	static constexpr bool funct(const el_t & t0,const el_t & t1) {
		return false;
	}
	static constexpr bool funct(const el_t & t0,const el_t & t1,const el_t & t2) {
		return false;
	}
	static constexpr bool funct(const el_t & t0,const el_t & t1,const el_t & t2,const el_t & t3) {
		return false;
	}
	static constexpr bool funct(const el_t & t0,const el_t & t1,const el_t & t2,const el_t & t3,const el_t & t4) {
		return false;
	}
	static constexpr bool funct(const el_t & t0,const el_t & t1,const el_t & t2,const el_t & t3,const el_t & t4,const el_t & t5) {
		return ((t0==t5)||(t1==t5)||(t2==t5)||(t3==t5)||(t5==(el_t::get_the_identity())));
	}
	static constexpr bool funct(const el_t & t0,const el_t & t1,const el_t & t2,const el_t & t3,const el_t & t4,const el_t & t5,const el_t & t6) {
		return ((t0==t5)||(t1==t5)||(t2==t5)||(t3==t5)||(t5==(el_t::get_the_identity())));
	}
};
template<group_name gn,typename UIntType,UIntType N0,UIntType ... Ns>
struct arg_I_eq_some_prev_or_eq_id<5,4,magma_t,gn,UIntType,N0,Ns...> {
	using el_t = magma_t<gn,UIntType,N0,Ns...>;
	
	static constexpr bool funct(const el_t & t0) {
		return false;
	}
	static constexpr bool funct(const el_t & t0,const el_t & t1) {
		return false;
	}
	static constexpr bool funct(const el_t & t0,const el_t & t1,const el_t & t2) {
		return false;
	}
	static constexpr bool funct(const el_t & t0,const el_t & t1,const el_t & t2,const el_t & t3) {
		return false;
	}
	static constexpr bool funct(const el_t & t0,const el_t & t1,const el_t & t2,const el_t & t3,const el_t & t4) {
		return false;
	}
	static constexpr bool funct(const el_t & t0,const el_t & t1,const el_t & t2,const el_t & t3,const el_t & t4,const el_t & t5) {
		return ((t0==t5)||(t1==t5)||(t2==t5)||(t3==t5)||(t4==t5)||(t5==(el_t::get_the_identity())));
	}
	static constexpr bool funct(const el_t & t0,const el_t & t1,const el_t & t2,const el_t & t3,const el_t & t4,const el_t & t5,const el_t & t6) {
		return ((t0==t5)||(t1==t5)||(t2==t5)||(t3==t5)||(t4==t5)||(t5==(el_t::get_the_identity())));
	}
};
template<group_name gn,typename UIntType,UIntType N0,UIntType ... Ns>
struct arg_I_eq_some_prev_or_eq_id<4,0,magma_t,gn,UIntType,N0,Ns...> {
	using el_t = magma_t<gn,UIntType,N0,Ns...>;
	
	static constexpr bool funct(const el_t & t0) {
		return false;
	}
	static constexpr bool funct(const el_t & t0,const el_t & t1) {
		return false;
	}
	static constexpr bool funct(const el_t & t0,const el_t & t1,const el_t & t2) {
		return false;
	}
	static constexpr bool funct(const el_t & t0,const el_t & t1,const el_t & t2,const el_t & t3) {
		return false;
	}
	static constexpr bool funct(const el_t & t0,const el_t & t1,const el_t & t2,const el_t & t3,const el_t & t4) {
		return ((t0==t4)||(t4==(el_t::get_the_identity())));
	}
	static constexpr bool funct(const el_t & t0,const el_t & t1,const el_t & t2,const el_t & t3,const el_t & t4,const el_t & t5) {
		return ((t0==t4)||(t4==(el_t::get_the_identity())));
	}
	static constexpr bool funct(const el_t & t0,const el_t & t1,const el_t & t2,const el_t & t3,const el_t & t4,const el_t & t5,const el_t & t6) {
		return ((t0==t4)||(t4==(el_t::get_the_identity())));
	}
};
template<group_name gn,typename UIntType,UIntType N0,UIntType ... Ns>
struct arg_I_eq_some_prev_or_eq_id<4,1,magma_t,gn,UIntType,N0,Ns...> {
	using el_t = magma_t<gn,UIntType,N0,Ns...>;
	
	static constexpr bool funct(const el_t & t0) {
		return false;
	}
	static constexpr bool funct(const el_t & t0,const el_t & t1) {
		return false;
	}
	static constexpr bool funct(const el_t & t0,const el_t & t1,const el_t & t2) {
		return false;
	}
	static constexpr bool funct(const el_t & t0,const el_t & t1,const el_t & t2,const el_t & t3) {
		return false;
	}
	static constexpr bool funct(const el_t & t0,const el_t & t1,const el_t & t2,const el_t & t3,const el_t & t4) {
		return ((t0==t4)||(t1==t4)||(t4==(el_t::get_the_identity())));
	}
	static constexpr bool funct(const el_t & t0,const el_t & t1,const el_t & t2,const el_t & t3,const el_t & t4,const el_t & t5) {
		return ((t0==t4)||(t1==t4)||(t4==(el_t::get_the_identity())));
	}
	static constexpr bool funct(const el_t & t0,const el_t & t1,const el_t & t2,const el_t & t3,const el_t & t4,const el_t & t5,const el_t & t6) {
		return ((t0==t4)||(t1==t4)||(t4==(el_t::get_the_identity())));
	}
};
template<group_name gn,typename UIntType,UIntType N0,UIntType ... Ns>
struct arg_I_eq_some_prev_or_eq_id<4,2,magma_t,gn,UIntType,N0,Ns...> {
	using el_t = magma_t<gn,UIntType,N0,Ns...>;
	
	static constexpr bool funct(const el_t & t0) {
		return false;
	}
	static constexpr bool funct(const el_t & t0,const el_t & t1) {
		return false;
	}
	static constexpr bool funct(const el_t & t0,const el_t & t1,const el_t & t2) {
		return false;
	}
	static constexpr bool funct(const el_t & t0,const el_t & t1,const el_t & t2,const el_t & t3) {
		return false;
	}
	static constexpr bool funct(const el_t & t0,const el_t & t1,const el_t & t2,const el_t & t3,const el_t & t4) {
		return ((t0==t4)||(t1==t4)||(t2==t4)||(t4==(el_t::get_the_identity())));
	}
	static constexpr bool funct(const el_t & t0,const el_t & t1,const el_t & t2,const el_t & t3,const el_t & t4,const el_t & t5) {
		return ((t0==t4)||(t1==t4)||(t2==t4)||(t4==(el_t::get_the_identity())));
	}
	static constexpr bool funct(const el_t & t0,const el_t & t1,const el_t & t2,const el_t & t3,const el_t & t4,const el_t & t5,const el_t & t6) {
		return ((t0==t4)||(t1==t4)||(t2==t4)||(t4==(el_t::get_the_identity())));
	}
};
template<group_name gn,typename UIntType,UIntType N0,UIntType ... Ns>
struct arg_I_eq_some_prev_or_eq_id<4,3,magma_t,gn,UIntType,N0,Ns...> {
	using el_t = magma_t<gn,UIntType,N0,Ns...>;
	
	static constexpr bool funct(const el_t & t0) {
		return false;
	}
	static constexpr bool funct(const el_t & t0,const el_t & t1) {
		return false;
	}
	static constexpr bool funct(const el_t & t0,const el_t & t1,const el_t & t2) {
		return false;
	}
	static constexpr bool funct(const el_t & t0,const el_t & t1,const el_t & t2,const el_t & t3) {
		return false;
	}
	static constexpr bool funct(const el_t & t0,const el_t & t1,const el_t & t2,const el_t & t3,const el_t & t4) {
		return ((t0==t4)||(t1==t4)||(t2==t4)||(t3==t4)||(t4==(el_t::get_the_identity())));
	}
	static constexpr bool funct(const el_t & t0,const el_t & t1,const el_t & t2,const el_t & t3,const el_t & t4,const el_t & t5) {
		return ((t0==t4)||(t1==t4)||(t2==t4)||(t3==t4)||(t4==(el_t::get_the_identity())));
	}
	static constexpr bool funct(const el_t & t0,const el_t & t1,const el_t & t2,const el_t & t3,const el_t & t4,const el_t & t5,const el_t & t6) {
		return ((t0==t4)||(t1==t4)||(t2==t4)||(t3==t4)||(t4==(el_t::get_the_identity())));
	}
};
template<group_name gn,typename UIntType,UIntType N0,UIntType ... Ns>
struct arg_I_eq_some_prev_or_eq_id<3,0,magma_t,gn,UIntType,N0,Ns...> {
	using el_t = magma_t<gn,UIntType,N0,Ns...>;
	
	static constexpr bool funct(const el_t & t0) {
		return false;
	}
	static constexpr bool funct(const el_t & t0,const el_t & t1) {
		return false;
	}
	static constexpr bool funct(const el_t & t0,const el_t & t1,const el_t & t2) {
		return false;
	}
	static constexpr bool funct(const el_t & t0,const el_t & t1,const el_t & t2,const el_t & t3) {
		return ((t0==t3)||(t3==(el_t::get_the_identity())));
	}
	static constexpr bool funct(const el_t & t0,const el_t & t1,const el_t & t2,const el_t & t3,const el_t & t4) {
		return ((t0==t3)||(t3==(el_t::get_the_identity())));
	}
	static constexpr bool funct(const el_t & t0,const el_t & t1,const el_t & t2,const el_t & t3,const el_t & t4,const el_t & t5) {
		return ((t0==t3)||(t3==(el_t::get_the_identity())));
	}
	static constexpr bool funct(const el_t & t0,const el_t & t1,const el_t & t2,const el_t & t3,const el_t & t4,const el_t & t5,const el_t & t6) {
		return ((t0==t3)||(t3==(el_t::get_the_identity())));
	}
};
template<group_name gn,typename UIntType,UIntType N0,UIntType ... Ns>
struct arg_I_eq_some_prev_or_eq_id<3,1,magma_t,gn,UIntType,N0,Ns...> {
	using el_t = magma_t<gn,UIntType,N0,Ns...>;
	
	static constexpr bool funct(const el_t & t0) {
		return false;
	}
	static constexpr bool funct(const el_t & t0,const el_t & t1) {
		return false;
	}
	static constexpr bool funct(const el_t & t0,const el_t & t1,const el_t & t2) {
		return false;
	}
	static constexpr bool funct(const el_t & t0,const el_t & t1,const el_t & t2,const el_t & t3) {
		return ((t0==t3)||(t1==t3)||(t3==(el_t::get_the_identity())));
	}
	static constexpr bool funct(const el_t & t0,const el_t & t1,const el_t & t2,const el_t & t3,const el_t & t4) {
		return ((t0==t3)||(t1==t3)||(t3==(el_t::get_the_identity())));
	}
	static constexpr bool funct(const el_t & t0,const el_t & t1,const el_t & t2,const el_t & t3,const el_t & t4,const el_t & t5) {
		return ((t0==t3)||(t1==t3)||(t3==(el_t::get_the_identity())));
	}
	static constexpr bool funct(const el_t & t0,const el_t & t1,const el_t & t2,const el_t & t3,const el_t & t4,const el_t & t5,const el_t & t6) {
		return ((t0==t3)||(t1==t3)||(t3==(el_t::get_the_identity())));
	}
};
template<group_name gn,typename UIntType,UIntType N0,UIntType ... Ns>
struct arg_I_eq_some_prev_or_eq_id<3,2,magma_t,gn,UIntType,N0,Ns...> {
	using el_t = magma_t<gn,UIntType,N0,Ns...>;
	
	static constexpr bool funct(const el_t & t0) {
		return false;
	}
	static constexpr bool funct(const el_t & t0,const el_t & t1) {
		return false;
	}
	static constexpr bool funct(const el_t & t0,const el_t & t1,const el_t & t2) {
		return false;
	}
	static constexpr bool funct(const el_t & t0,const el_t & t1,const el_t & t2,const el_t & t3) {
		return ((t0==t3)||(t1==t3)||(t2==t3)||(t3==(el_t::get_the_identity())));
	}
	static constexpr bool funct(const el_t & t0,const el_t & t1,const el_t & t2,const el_t & t3,const el_t & t4) {
		return ((t0==t3)||(t1==t3)||(t2==t3)||(t3==(el_t::get_the_identity())));
	}
	static constexpr bool funct(const el_t & t0,const el_t & t1,const el_t & t2,const el_t & t3,const el_t & t4,const el_t & t5) {
		return ((t0==t3)||(t1==t3)||(t2==t3)||(t3==(el_t::get_the_identity())));
	}
	static constexpr bool funct(const el_t & t0,const el_t & t1,const el_t & t2,const el_t & t3,const el_t & t4,const el_t & t5,const el_t & t6) {
		return ((t0==t3)||(t1==t3)||(t2==t3)||(t3==(el_t::get_the_identity())));
	}
};
template<group_name gn,typename UIntType,UIntType N0,UIntType ... Ns>
struct arg_I_eq_some_prev_or_eq_id<2,0,magma_t,gn,UIntType,N0,Ns...> {
	using el_t = magma_t<gn,UIntType,N0,Ns...>;
	
	static constexpr bool funct(const el_t & t0) {
		return false;
	}
	static constexpr bool funct(const el_t & t0,const el_t & t1) {
		return false;
	}
	static constexpr bool funct(const el_t & t0,const el_t & t1,const el_t & t2) {
		return ((t0==t2)||(t2==(el_t::get_the_identity())));
	}
	static constexpr bool funct(const el_t & t0,const el_t & t1,const el_t & t2,const el_t & t3) {
		return ((t0==t2)||(t2==(el_t::get_the_identity())));
	}
	static constexpr bool funct(const el_t & t0,const el_t & t1,const el_t & t2,const el_t & t3,const el_t & t4) {
		return ((t0==t2)||(t2==(el_t::get_the_identity())));
	}
	static constexpr bool funct(const el_t & t0,const el_t & t1,const el_t & t2,const el_t & t3,const el_t & t4,const el_t & t5) {
		return ((t0==t2)||(t2==(el_t::get_the_identity())));
	}
	static constexpr bool funct(const el_t & t0,const el_t & t1,const el_t & t2,const el_t & t3,const el_t & t4,const el_t & t5,const el_t & t6) {
		return ((t0==t2)||(t2==(el_t::get_the_identity())));
	}
};
template<group_name gn,typename UIntType,UIntType N0,UIntType ... Ns>
struct arg_I_eq_some_prev_or_eq_id<2,1,magma_t,gn,UIntType,N0,Ns...> {
	using el_t = magma_t<gn,UIntType,N0,Ns...>;
	
	static constexpr bool funct(const el_t & t0) {
		return false;
	}
	static constexpr bool funct(const el_t & t0,const el_t & t1) {
		return false;
	}
	static constexpr bool funct(const el_t & t0,const el_t & t1,const el_t & t2) {
		return ((t0==t2)||(t1==t2)||(t2==(el_t::get_the_identity())));
	}
	static constexpr bool funct(const el_t & t0,const el_t & t1,const el_t & t2,const el_t & t3) {
		return ((t0==t2)||(t1==t2)||(t2==(el_t::get_the_identity())));
	}
	static constexpr bool funct(const el_t & t0,const el_t & t1,const el_t & t2,const el_t & t3,const el_t & t4) {
		return ((t0==t2)||(t1==t2)||(t2==(el_t::get_the_identity())));
	}
	static constexpr bool funct(const el_t & t0,const el_t & t1,const el_t & t2,const el_t & t3,const el_t & t4,const el_t & t5) {
		return ((t0==t2)||(t1==t2)||(t2==(el_t::get_the_identity())));
	}
	static constexpr bool funct(const el_t & t0,const el_t & t1,const el_t & t2,const el_t & t3,const el_t & t4,const el_t & t5,const el_t & t6) {
		return ((t0==t2)||(t1==t2)||(t2==(el_t::get_the_identity())));
	}
};
template<group_name gn,typename UIntType,UIntType N0,UIntType ... Ns>
struct arg_I_eq_some_prev_or_eq_id<1,0,magma_t,gn,UIntType,N0,Ns...> {
	using el_t = magma_t<gn,UIntType,N0,Ns...>;
	
	static constexpr bool funct(const el_t & t0) {
		return false;
	}
	static constexpr bool funct(const el_t & t0,const el_t & t1) {
		return ((t0==t1)||(t1==(el_t::get_the_identity())));
	}
	static constexpr bool funct(const el_t & t0,const el_t & t1,const el_t & t2) {
		return ((t0==t1)||(t1==(el_t::get_the_identity())));
	}
	static constexpr bool funct(const el_t & t0,const el_t & t1,const el_t & t2,const el_t & t3) {
		return ((t0==t1)||(t1==(el_t::get_the_identity())));
	}
	static constexpr bool funct(const el_t & t0,const el_t & t1,const el_t & t2,const el_t & t3,const el_t & t4) {
		return ((t0==t1)||(t1==(el_t::get_the_identity())));
	}
	static constexpr bool funct(const el_t & t0,const el_t & t1,const el_t & t2,const el_t & t3,const el_t & t4,const el_t & t5) {
		return ((t0==t1)||(t1==(el_t::get_the_identity())));
	}
	static constexpr bool funct(const el_t & t0,const el_t & t1,const el_t & t2,const el_t & t3,const el_t & t4,const el_t & t5,const el_t & t6) {
		return ((t0==t1)||(t1==(el_t::get_the_identity())));
	}
};
}
namespace details {
template<size_t I,template<group_name,typename K_t,K_t,K_t...> class TT,group_name gn,typename UIntType,UIntType N0,UIntType ... Ns>
struct invalid_the_latters;
template<group_name gn,typename UIntType,UIntType N0,UIntType ... Ns>
struct invalid_the_latters<5,magma_t,gn,UIntType,N0,Ns...> {
	
	using not_valid_6 = arg_I_eq_some_prev_or_eq_id<6,5,magma_t,gn,UIntType,N0,Ns...>;
	using el_t = magma_t<gn,UIntType,N0,Ns...>;
	
	static constexpr bool funct(const el_t & t0) {
		return not_valid_6::funct(t0);
	}
	static constexpr bool funct(const el_t & t0,const el_t & t1) {
		return not_valid_6::funct(t0,t1);
	}
	static constexpr bool funct(const el_t & t0,const el_t & t1,const el_t & t2) {
		return not_valid_6::funct(t0,t1,t2);
	}
	static constexpr bool funct(const el_t & t0,const el_t & t1,const el_t & t2,const el_t & t3) {
		return not_valid_6::funct(t0,t1,t2,t3);
	}
	static constexpr bool funct(const el_t & t0,const el_t & t1,const el_t & t2,const el_t & t3,const el_t & t4) {
		return not_valid_6::funct(t0,t1,t2,t3,t4);
	}
	static constexpr bool funct(const el_t & t0,const el_t & t1,const el_t & t2,const el_t & t3,const el_t & t4,const el_t & t5) {
		return not_valid_6::funct(t0,t1,t2,t3,t4,t5);
	}
	static constexpr bool funct(const el_t & t0,const el_t & t1,const el_t & t2,const el_t & t3,const el_t & t4,const el_t & t5,const el_t & t6) {
		return not_valid_6::funct(t0,t1,t2,t3,t4,t5,t6);
	}
};
template<group_name gn,typename UIntType,UIntType N0,UIntType ... Ns>
struct invalid_the_latters<4,magma_t,gn,UIntType,N0,Ns...> {
	
	using not_valid_6 = arg_I_eq_some_prev_or_eq_id<6,4,magma_t,gn,UIntType,N0,Ns...>;
	using not_valid_5 = arg_I_eq_some_prev_or_eq_id<5,4,magma_t,gn,UIntType,N0,Ns...>;
	using el_t = magma_t<gn,UIntType,N0,Ns...>;
	
	static constexpr bool funct(const el_t & t0) {
		return (not_valid_6::funct(t0)&&not_valid_5::funct(t0));
	}
	static constexpr bool funct(const el_t & t0,const el_t & t1) {
		return (not_valid_6::funct(t0,t1)&&not_valid_5::funct(t0,t1));
	}
	static constexpr bool funct(const el_t & t0,const el_t & t1,const el_t & t2) {
		return (not_valid_6::funct(t0,t1,t2)&&not_valid_5::funct(t0,t1,t2));
	}
	static constexpr bool funct(const el_t & t0,const el_t & t1,const el_t & t2,const el_t & t3) {
		return (not_valid_6::funct(t0,t1,t2,t3)&&not_valid_5::funct(t0,t1,t2,t3));
	}
	static constexpr bool funct(const el_t & t0,const el_t & t1,const el_t & t2,const el_t & t3,const el_t & t4) {
		return (not_valid_6::funct(t0,t1,t2,t3,t4)&&not_valid_5::funct(t0,t1,t2,t3,t4));
	}
	static constexpr bool funct(const el_t & t0,const el_t & t1,const el_t & t2,const el_t & t3,const el_t & t4,const el_t & t5) {
		return (not_valid_6::funct(t0,t1,t2,t3,t4,t5)&&not_valid_5::funct(t0,t1,t2,t3,t4,t5));
	}
	static constexpr bool funct(const el_t & t0,const el_t & t1,const el_t & t2,const el_t & t3,const el_t & t4,const el_t & t5,const el_t & t6) {
		return (not_valid_6::funct(t0,t1,t2,t3,t4,t5,t6)&&not_valid_5::funct(t0,t1,t2,t3,t4,t5,t6));
	}
};
template<group_name gn,typename UIntType,UIntType N0,UIntType ... Ns>
struct invalid_the_latters<3,magma_t,gn,UIntType,N0,Ns...> {
	
	using not_valid_6 = arg_I_eq_some_prev_or_eq_id<6,3,magma_t,gn,UIntType,N0,Ns...>;
	using not_valid_5 = arg_I_eq_some_prev_or_eq_id<5,3,magma_t,gn,UIntType,N0,Ns...>;
	using not_valid_4 = arg_I_eq_some_prev_or_eq_id<4,3,magma_t,gn,UIntType,N0,Ns...>;
	using el_t = magma_t<gn,UIntType,N0,Ns...>;
	
	static constexpr bool funct(const el_t & t0) {
		return (not_valid_6::funct(t0)&&not_valid_5::funct(t0)&&not_valid_4::funct(t0));
	}
	static constexpr bool funct(const el_t & t0,const el_t & t1) {
		return (not_valid_6::funct(t0,t1)&&not_valid_5::funct(t0,t1)&&not_valid_4::funct(t0,t1));
	}
	static constexpr bool funct(const el_t & t0,const el_t & t1,const el_t & t2) {
		return (not_valid_6::funct(t0,t1,t2)&&not_valid_5::funct(t0,t1,t2)&&not_valid_4::funct(t0,t1,t2));
	}
	static constexpr bool funct(const el_t & t0,const el_t & t1,const el_t & t2,const el_t & t3) {
		return (not_valid_6::funct(t0,t1,t2,t3)&&not_valid_5::funct(t0,t1,t2,t3)&&not_valid_4::funct(t0,t1,t2,t3));
	}
	static constexpr bool funct(const el_t & t0,const el_t & t1,const el_t & t2,const el_t & t3,const el_t & t4) {
		return (not_valid_6::funct(t0,t1,t2,t3,t4)&&not_valid_5::funct(t0,t1,t2,t3,t4)&&not_valid_4::funct(t0,t1,t2,t3,t4));
	}
	static constexpr bool funct(const el_t & t0,const el_t & t1,const el_t & t2,const el_t & t3,const el_t & t4,const el_t & t5) {
		return (not_valid_6::funct(t0,t1,t2,t3,t4,t5)&&not_valid_5::funct(t0,t1,t2,t3,t4,t5)&&not_valid_4::funct(t0,t1,t2,t3,t4,t5));
	}
	static constexpr bool funct(const el_t & t0,const el_t & t1,const el_t & t2,const el_t & t3,const el_t & t4,const el_t & t5,const el_t & t6) {
		return (not_valid_6::funct(t0,t1,t2,t3,t4,t5,t6)&&not_valid_5::funct(t0,t1,t2,t3,t4,t5,t6)&&not_valid_4::funct(t0,t1,t2,t3,t4,t5,t6));
	}
};
template<group_name gn,typename UIntType,UIntType N0,UIntType ... Ns>
struct invalid_the_latters<2,magma_t,gn,UIntType,N0,Ns...> {
	
	using not_valid_6 = arg_I_eq_some_prev_or_eq_id<6,2,magma_t,gn,UIntType,N0,Ns...>;
	using not_valid_5 = arg_I_eq_some_prev_or_eq_id<5,2,magma_t,gn,UIntType,N0,Ns...>;
	using not_valid_4 = arg_I_eq_some_prev_or_eq_id<4,2,magma_t,gn,UIntType,N0,Ns...>;
	using not_valid_3 = arg_I_eq_some_prev_or_eq_id<3,2,magma_t,gn,UIntType,N0,Ns...>;
	
	using el_t = magma_t<gn,UIntType,N0,Ns...>;
	static constexpr bool funct(const el_t & t0) {
		return (not_valid_6::funct(t0)&&not_valid_5::funct(t0)&&not_valid_4::funct(t0)&&not_valid_3::funct(t0));
	}
	static constexpr bool funct(const el_t & t0,const el_t & t1) {
		return (not_valid_6::funct(t0,t1)&&not_valid_5::funct(t0,t1)&&not_valid_4::funct(t0,t1)&&not_valid_3::funct(t0,t1));
	}
	static constexpr bool funct(const el_t & t0,const el_t & t1,const el_t & t2) {
		return (not_valid_6::funct(t0,t1,t2)&&not_valid_5::funct(t0,t1,t2)&&not_valid_4::funct(t0,t1,t2)&&not_valid_3::funct(t0,t1,t2));
	}
	static constexpr bool funct(const el_t & t0,const el_t & t1,const el_t & t2,const el_t & t3) {
		return (not_valid_6::funct(t0,t1,t2,t3)&&not_valid_5::funct(t0,t1,t2,t3)&&not_valid_4::funct(t0,t1,t2,t3)&&not_valid_3::funct(t0,t1,t2,t3));
	}
	static constexpr bool funct(const el_t & t0,const el_t & t1,const el_t & t2,const el_t & t3,const el_t & t4) {
		return (not_valid_6::funct(t0,t1,t2,t3,t4)&&not_valid_5::funct(t0,t1,t2,t3,t4)&&not_valid_4::funct(t0,t1,t2,t3,t4)&&not_valid_3::funct(t0,t1,t2,t3,t4));
	}
	static constexpr bool funct(const el_t & t0,const el_t & t1,const el_t & t2,const el_t & t3,const el_t & t4,const el_t & t5) {
		return (not_valid_6::funct(t0,t1,t2,t3,t4,t5)&&not_valid_5::funct(t0,t1,t2,t3,t4,t5)&&not_valid_4::funct(t0,t1,t2,t3,t4,t5)&&not_valid_3::funct(t0,t1,t2,t3,t4,t5));
	}
	static constexpr bool funct(const el_t & t0,const el_t & t1,const el_t & t2,const el_t & t3,const el_t & t4,const el_t & t5,const el_t & t6) {
		return (not_valid_6::funct(t0,t1,t2,t3,t4,t5,t6)&&not_valid_5::funct(t0,t1,t2,t3,t4,t5,t6)&&not_valid_4::funct(t0,t1,t2,t3,t4,t5,t6)&&not_valid_3::funct(t0,t1,t2,t3,t4,t5,t6));
	}
};
template<group_name gn,typename UIntType,UIntType N0,UIntType ... Ns>
struct invalid_the_latters<1,magma_t,gn,UIntType,N0,Ns...> {
	
	using not_valid_6 = arg_I_eq_some_prev_or_eq_id<6,1,magma_t,gn,UIntType,N0,Ns...>;
	using not_valid_5 = arg_I_eq_some_prev_or_eq_id<5,1,magma_t,gn,UIntType,N0,Ns...>;
	using not_valid_4 = arg_I_eq_some_prev_or_eq_id<4,1,magma_t,gn,UIntType,N0,Ns...>;
	using not_valid_3 = arg_I_eq_some_prev_or_eq_id<3,1,magma_t,gn,UIntType,N0,Ns...>;
	using not_valid_2 = arg_I_eq_some_prev_or_eq_id<2,1,magma_t,gn,UIntType,N0,Ns...>;
	
	using el_t = magma_t<gn,UIntType,N0,Ns...>;
	static constexpr bool funct(const el_t & t0) {
		return (not_valid_6::funct(t0)&&not_valid_5::funct(t0)&&not_valid_4::funct(t0)&&not_valid_3::funct(t0)&&not_valid_2::funct(t0));
	}
	static constexpr bool funct(const el_t & t0,const el_t & t1) {
		return (not_valid_6::funct(t0,t1)&&not_valid_5::funct(t0,t1)&&not_valid_4::funct(t0,t1)&&not_valid_3::funct(t0,t1)&&not_valid_2::funct(t0,t1));
	}
	static constexpr bool funct(const el_t & t0,const el_t & t1,const el_t & t2) {
		return (not_valid_6::funct(t0,t1,t2)&&not_valid_5::funct(t0,t1,t2)&&not_valid_4::funct(t0,t1,t2)&&not_valid_3::funct(t0,t1,t2)&&not_valid_2::funct(t0,t1,t2));
	}
	static constexpr bool funct(const el_t & t0,const el_t & t1,const el_t & t2,const el_t & t3) {
		return (not_valid_6::funct(t0,t1,t2,t3)&&not_valid_5::funct(t0,t1,t2,t3)&&not_valid_4::funct(t0,t1,t2,t3)&&not_valid_3::funct(t0,t1,t2,t3)&&not_valid_2::funct(t0,t1,t2,t3));
	}
	static constexpr bool funct(const el_t & t0,const el_t & t1,const el_t & t2,const el_t & t3,const el_t & t4) {
		return (not_valid_6::funct(t0,t1,t2,t3,t4)&&not_valid_5::funct(t0,t1,t2,t3,t4)&&not_valid_4::funct(t0,t1,t2,t3,t4)&&not_valid_3::funct(t0,t1,t2,t3,t4)&&not_valid_2::funct(t0,t1,t2,t3,t4));
	}
	static constexpr bool funct(const el_t & t0,const el_t & t1,const el_t & t2,const el_t & t3,const el_t & t4,const el_t & t5) {
		return (not_valid_6::funct(t0,t1,t2,t3,t4,t5)&&not_valid_5::funct(t0,t1,t2,t3,t4,t5)&&not_valid_4::funct(t0,t1,t2,t3,t4,t5)&&not_valid_3::funct(t0,t1,t2,t3,t4,t5)&&not_valid_2::funct(t0,t1,t2,t3,t4,t5));
	}
	static constexpr bool funct(const el_t & t0,const el_t & t1,const el_t & t2,const el_t & t3,const el_t & t4,const el_t & t5,const el_t & t6) {
		return (not_valid_6::funct(t0,t1,t2,t3,t4,t5,t6)&&not_valid_5::funct(t0,t1,t2,t3,t4,t5,t6)&&not_valid_4::funct(t0,t1,t2,t3,t4,t5,t6)&&not_valid_3::funct(t0,t1,t2,t3,t4,t5,t6)&&not_valid_2::funct(t0,t1,t2,t3,t4,t5,t6));
	}
};
template<group_name gn,typename UIntType,UIntType N0,UIntType ... Ns>
struct invalid_the_latters<0,magma_t,gn,UIntType,N0,Ns...> {
	
	using not_valid_6 = arg_I_eq_some_prev_or_eq_id<6,0,magma_t,gn,UIntType,N0,Ns...>;
	using not_valid_5 = arg_I_eq_some_prev_or_eq_id<5,0,magma_t,gn,UIntType,N0,Ns...>;
	using not_valid_4 = arg_I_eq_some_prev_or_eq_id<4,0,magma_t,gn,UIntType,N0,Ns...>;
	using not_valid_3 = arg_I_eq_some_prev_or_eq_id<3,0,magma_t,gn,UIntType,N0,Ns...>;
	using not_valid_2 = arg_I_eq_some_prev_or_eq_id<2,0,magma_t,gn,UIntType,N0,Ns...>;
	using not_valid_1 = arg_I_eq_some_prev_or_eq_id<1,0,magma_t,gn,UIntType,N0,Ns...>;
	using not_valid_0 = exists_eq_id<0,magma_t,gn,UIntType,N0,Ns...>;
	
	using el_t = magma_t<gn,UIntType,N0,Ns...>;
	static constexpr bool funct(const el_t & t0) {
		return (not_valid_6::funct(t0)&&not_valid_5::funct(t0)&&not_valid_4::funct(t0)&&not_valid_3::funct(t0)&&not_valid_2::funct(t0)&&not_valid_1::funct(t0)&&not_valid_0::funct(t0));
	}
	static constexpr bool funct(const el_t & t0,const el_t & t1) {
		return (not_valid_6::funct(t0,t1)&&not_valid_5::funct(t0,t1)&&not_valid_4::funct(t0,t1)&&not_valid_3::funct(t0,t1)&&not_valid_2::funct(t0,t1)&&not_valid_1::funct(t0,t1)&&not_valid_0::funct(t0,t1));
	}
	static constexpr bool funct(const el_t & t0,const el_t & t1,const el_t & t2) {
		return (not_valid_6::funct(t0,t1,t2)&&not_valid_5::funct(t0,t1,t2)&&not_valid_4::funct(t0,t1,t2)&&not_valid_3::funct(t0,t1,t2)&&not_valid_2::funct(t0,t1,t2)&&not_valid_1::funct(t0,t1,t2)&&not_valid_0::funct(t0,t1,t2));
	}
	static constexpr bool funct(const el_t & t0,const el_t & t1,const el_t & t2,const el_t & t3) {
		return (not_valid_6::funct(t0,t1,t2,t3)&&not_valid_5::funct(t0,t1,t2,t3)&&not_valid_4::funct(t0,t1,t2,t3)&&not_valid_3::funct(t0,t1,t2,t3)&&not_valid_2::funct(t0,t1,t2,t3)&&not_valid_1::funct(t0,t1,t2,t3)&&not_valid_0::funct(t0,t1,t2,t3));
	}
	static constexpr bool funct(const el_t & t0,const el_t & t1,const el_t & t2,const el_t & t3,const el_t & t4) {
		return (not_valid_6::funct(t0,t1,t2,t3,t4)&&not_valid_5::funct(t0,t1,t2,t3,t4)&&not_valid_4::funct(t0,t1,t2,t3,t4)&&not_valid_3::funct(t0,t1,t2,t3,t4)&&not_valid_2::funct(t0,t1,t2,t3,t4)&&not_valid_1::funct(t0,t1,t2,t3,t4)&&not_valid_0::funct(t0,t1,t2,t3,t4));
	}
	static constexpr bool funct(const el_t & t0,const el_t & t1,const el_t & t2,const el_t & t3,const el_t & t4,const el_t & t5) {
		return (not_valid_6::funct(t0,t1,t2,t3,t4,t5)&&not_valid_5::funct(t0,t1,t2,t3,t4,t5)&&not_valid_4::funct(t0,t1,t2,t3,t4,t5)&&not_valid_3::funct(t0,t1,t2,t3,t4,t5)&&not_valid_2::funct(t0,t1,t2,t3,t4,t5)&&not_valid_1::funct(t0,t1,t2,t3,t4,t5)&&not_valid_0::funct(t0,t1,t2,t3,t4,t5));
	}
	static constexpr bool funct(const el_t & t0,const el_t & t1,const el_t & t2,const el_t & t3,const el_t & t4,const el_t & t5,const el_t & t6) {
		return (not_valid_6::funct(t0,t1,t2,t3,t4,t5,t6)&&not_valid_5::funct(t0,t1,t2,t3,t4,t5,t6)&&not_valid_4::funct(t0,t1,t2,t3,t4,t5,t6)&&not_valid_3::funct(t0,t1,t2,t3,t4,t5,t6)&&not_valid_2::funct(t0,t1,t2,t3,t4,t5,t6)&&not_valid_1::funct(t0,t1,t2,t3,t4,t5,t6)&&not_valid_0::funct(t0,t1,t2,t3,t4,t5,t6));
	}
};
}
namespace details {
template<size_t I,template<group_name,typename K_t,K_t,K_t...> class TT,group_name gn,typename UIntType,UIntType N0,UIntType ... Ns>
struct all_firsts_neq_id;
template<group_name gn,typename UIntType,UIntType N0,UIntType ... Ns>
struct all_firsts_neq_id<0,magma_t,gn,UIntType,N0,Ns...> {
	using el_t = magma_t<gn,UIntType,N0,Ns...>;
	
	static constexpr bool funct(const el_t & t0) {
		return (t0!=(el_t::get_the_identity()));
	}
	static constexpr bool funct(const el_t & t0,const el_t & t1) {
		return (t0!=(el_t::get_the_identity()));
	}
	static constexpr bool funct(const el_t & t0,const el_t & t1,const el_t & t2) {
		return (t0!=(el_t::get_the_identity()));
	}
	static constexpr bool funct(const el_t & t0,const el_t & t1,const el_t & t2,const el_t & t3) {
		return (t0!=(el_t::get_the_identity()));
	}
	static constexpr bool funct(const el_t & t0,const el_t & t1,const el_t & t2,const el_t & t3,const el_t & t4) {
		return (t0!=(el_t::get_the_identity()));
	}
	static constexpr bool funct(const el_t & t0,const el_t & t1,const el_t & t2,const el_t & t3,const el_t & t4,const el_t & t5) {
		return (t0!=(el_t::get_the_identity()));
	}
	static constexpr bool funct(const el_t & t0,const el_t & t1,const el_t & t2,const el_t & t3,const el_t & t4,const el_t & t5,const el_t & t6) {
		return (t0!=(el_t::get_the_identity()));
	}
};
template<group_name gn,typename UIntType,UIntType N0,UIntType ... Ns>
struct all_firsts_neq_id<1,magma_t,gn,UIntType,N0,Ns...> {
	using el_t = magma_t<gn,UIntType,N0,Ns...>;
	
	static constexpr bool funct(const el_t & t0) {
		return (t0!=(el_t::get_the_identity()));
	}
	static constexpr bool funct(const el_t & t0,const el_t & t1) {
		return ((t0!=(el_t::get_the_identity()))&&(t1!=(el_t::get_the_identity())));
	}
	static constexpr bool funct(const el_t & t0,const el_t & t1,const el_t & t2) {
		return ((t0!=(el_t::get_the_identity()))&&(t1!=(el_t::get_the_identity())));
	}
	static constexpr bool funct(const el_t & t0,const el_t & t1,const el_t & t2,const el_t & t3) {
		return ((t0!=(el_t::get_the_identity()))&&(t1!=(el_t::get_the_identity())));
	}
	static constexpr bool funct(const el_t & t0,const el_t & t1,const el_t & t2,const el_t & t3,const el_t & t4) {
		return ((t0!=(el_t::get_the_identity()))&&(t1!=(el_t::get_the_identity())));
	}
	static constexpr bool funct(const el_t & t0,const el_t & t1,const el_t & t2,const el_t & t3,const el_t & t4,const el_t & t5) {
		return ((t0!=(el_t::get_the_identity()))&&(t1!=(el_t::get_the_identity())));
	}
	static constexpr bool funct(const el_t & t0,const el_t & t1,const el_t & t2,const el_t & t3,const el_t & t4,const el_t & t5,const el_t & t6) {
		return ((t0!=(el_t::get_the_identity()))&&(t1!=(el_t::get_the_identity())));
	}
};
template<group_name gn,typename UIntType,UIntType N0,UIntType ... Ns>
struct all_firsts_neq_id<2,magma_t,gn,UIntType,N0,Ns...> {
	using el_t = magma_t<gn,UIntType,N0,Ns...>;
	
	static constexpr bool funct(const el_t & t0) {
		return (t0!=(el_t::get_the_identity()));
	}
	static constexpr bool funct(const el_t & t0,const el_t & t1) {
		return ((t0!=(el_t::get_the_identity()))&&(t1!=(el_t::get_the_identity())));
	}
	static constexpr bool funct(const el_t & t0,const el_t & t1,const el_t & t2) {
		return ((t0!=(el_t::get_the_identity()))&&(t1!=(el_t::get_the_identity()))&&(t2!=(el_t::get_the_identity())));
	}
	static constexpr bool funct(const el_t & t0,const el_t & t1,const el_t & t2,const el_t & t3) {
		return ((t0!=(el_t::get_the_identity()))&&(t1!=(el_t::get_the_identity()))&&(t2!=(el_t::get_the_identity())));
	}
	static constexpr bool funct(const el_t & t0,const el_t & t1,const el_t & t2,const el_t & t3,const el_t & t4) {
		return ((t0!=(el_t::get_the_identity()))&&(t1!=(el_t::get_the_identity()))&&(t2!=(el_t::get_the_identity())));
	}
	static constexpr bool funct(const el_t & t0,const el_t & t1,const el_t & t2,const el_t & t3,const el_t & t4,const el_t & t5) {
		return ((t0!=(el_t::get_the_identity()))&&(t1!=(el_t::get_the_identity()))&&(t2!=(el_t::get_the_identity())));
	}
	static constexpr bool funct(const el_t & t0,const el_t & t1,const el_t & t2,const el_t & t3,const el_t & t4,const el_t & t5,const el_t & t6) {
		return ((t0!=(el_t::get_the_identity()))&&(t1!=(el_t::get_the_identity()))&&(t2!=(el_t::get_the_identity())));
	}
};
template<group_name gn,typename UIntType,UIntType N0,UIntType ... Ns>
struct all_firsts_neq_id<3,magma_t,gn,UIntType,N0,Ns...> {
	using el_t = magma_t<gn,UIntType,N0,Ns...>;
	
	static constexpr bool funct(const el_t & t0) {
		return (t0!=(el_t::get_the_identity()));
	}
	static constexpr bool funct(const el_t & t0,const el_t & t1) {
		return ((t0!=(el_t::get_the_identity()))&&(t1!=(el_t::get_the_identity())));
	}
	static constexpr bool funct(const el_t & t0,const el_t & t1,const el_t & t2) {
		return ((t0!=(el_t::get_the_identity()))&&(t1!=(el_t::get_the_identity()))&&(t2!=(el_t::get_the_identity())));
	}
	static constexpr bool funct(const el_t & t0,const el_t & t1,const el_t & t2,const el_t & t3) {
		return ((t0!=(el_t::get_the_identity()))&&(t1!=(el_t::get_the_identity()))&&(t2!=(el_t::get_the_identity()))&&(t3!=(el_t::get_the_identity())));
	}
	static constexpr bool funct(const el_t & t0,const el_t & t1,const el_t & t2,const el_t & t3,const el_t & t4) {
		return ((t0!=(el_t::get_the_identity()))&&(t1!=(el_t::get_the_identity()))&&(t2!=(el_t::get_the_identity()))&&(t3!=(el_t::get_the_identity())));
	}
	static constexpr bool funct(const el_t & t0,const el_t & t1,const el_t & t2,const el_t & t3,const el_t & t4,const el_t & t5) {
		return ((t0!=(el_t::get_the_identity()))&&(t1!=(el_t::get_the_identity()))&&(t2!=(el_t::get_the_identity()))&&(t3!=(el_t::get_the_identity())));
	}
	static constexpr bool funct(const el_t & t0,const el_t & t1,const el_t & t2,const el_t & t3,const el_t & t4,const el_t & t5,const el_t & t6) {
		return ((t0!=(el_t::get_the_identity()))&&(t1!=(el_t::get_the_identity()))&&(t2!=(el_t::get_the_identity()))&&(t3!=(el_t::get_the_identity())));
	}
};
template<group_name gn,typename UIntType,UIntType N0,UIntType ... Ns>
struct all_firsts_neq_id<4,magma_t,gn,UIntType,N0,Ns...> {
	using el_t = magma_t<gn,UIntType,N0,Ns...>;
	
	static constexpr bool funct(const el_t & t0) {
		return (t0!=(el_t::get_the_identity()));
	}
	static constexpr bool funct(const el_t & t0,const el_t & t1) {
		return ((t0!=(el_t::get_the_identity()))&&(t1!=(el_t::get_the_identity())));
	}
	static constexpr bool funct(const el_t & t0,const el_t & t1,const el_t & t2) {
		return ((t0!=(el_t::get_the_identity()))&&(t1!=(el_t::get_the_identity()))&&(t2!=(el_t::get_the_identity())));
	}
	static constexpr bool funct(const el_t & t0,const el_t & t1,const el_t & t2,const el_t & t3) {
		return ((t0!=(el_t::get_the_identity()))&&(t1!=(el_t::get_the_identity()))&&(t2!=(el_t::get_the_identity()))&&(t3!=(el_t::get_the_identity())));
	}
	static constexpr bool funct(const el_t & t0,const el_t & t1,const el_t & t2,const el_t & t3,const el_t & t4) {
		return ((t0!=(el_t::get_the_identity()))&&(t1!=(el_t::get_the_identity()))&&(t2!=(el_t::get_the_identity()))&&(t3!=(el_t::get_the_identity()))&&(t4!=(el_t::get_the_identity())));
	}
	static constexpr bool funct(const el_t & t0,const el_t & t1,const el_t & t2,const el_t & t3,const el_t & t4,const el_t & t5) {
		return ((t0!=(el_t::get_the_identity()))&&(t1!=(el_t::get_the_identity()))&&(t2!=(el_t::get_the_identity()))&&(t3!=(el_t::get_the_identity()))&&(t4!=(el_t::get_the_identity())));
	}
	static constexpr bool funct(const el_t & t0,const el_t & t1,const el_t & t2,const el_t & t3,const el_t & t4,const el_t & t5,const el_t & t6) {
		return ((t0!=(el_t::get_the_identity()))&&(t1!=(el_t::get_the_identity()))&&(t2!=(el_t::get_the_identity()))&&(t3!=(el_t::get_the_identity()))&&(t4!=(el_t::get_the_identity())));
	}
};
template<group_name gn,typename UIntType,UIntType N0,UIntType ... Ns>
struct all_firsts_neq_id<5,magma_t,gn,UIntType,N0,Ns...> {
	using el_t = magma_t<gn,UIntType,N0,Ns...>;
	
	static constexpr bool funct(const el_t & t0) {
		return (t0!=(el_t::get_the_identity()));
	}
	static constexpr bool funct(const el_t & t0,const el_t & t1) {
		return ((t0!=(el_t::get_the_identity()))&&(t1!=(el_t::get_the_identity())));
	}
	static constexpr bool funct(const el_t & t0,const el_t & t1,const el_t & t2) {
		return ((t0!=(el_t::get_the_identity()))&&(t1!=(el_t::get_the_identity()))&&(t2!=(el_t::get_the_identity())));
	}
	static constexpr bool funct(const el_t & t0,const el_t & t1,const el_t & t2,const el_t & t3) {
		return ((t0!=(el_t::get_the_identity()))&&(t1!=(el_t::get_the_identity()))&&(t2!=(el_t::get_the_identity()))&&(t3!=(el_t::get_the_identity())));
	}
	static constexpr bool funct(const el_t & t0,const el_t & t1,const el_t & t2,const el_t & t3,const el_t & t4) {
		return ((t0!=(el_t::get_the_identity()))&&(t1!=(el_t::get_the_identity()))&&(t2!=(el_t::get_the_identity()))&&(t3!=(el_t::get_the_identity()))&&(t4!=(el_t::get_the_identity())));
	}
	static constexpr bool funct(const el_t & t0,const el_t & t1,const el_t & t2,const el_t & t3,const el_t & t4,const el_t & t5) {
		return ((t0!=(el_t::get_the_identity()))&&(t1!=(el_t::get_the_identity()))&&(t2!=(el_t::get_the_identity()))&&(t3!=(el_t::get_the_identity()))&&(t4!=(el_t::get_the_identity()))&&(t5!=(el_t::get_the_identity())));
	}
	static constexpr bool funct(const el_t & t0,const el_t & t1,const el_t & t2,const el_t & t3,const el_t & t4,const el_t & t5,const el_t & t6) {
		return ((t0!=(el_t::get_the_identity()))&&(t1!=(el_t::get_the_identity()))&&(t2!=(el_t::get_the_identity()))&&(t3!=(el_t::get_the_identity()))&&(t4!=(el_t::get_the_identity()))&&(t5!=(el_t::get_the_identity())));
	}
};
template<group_name gn,typename UIntType,UIntType N0,UIntType ... Ns>
struct all_firsts_neq_id<6,magma_t,gn,UIntType,N0,Ns...> {
	using el_t = magma_t<gn,UIntType,N0,Ns...>;
	
	static constexpr bool funct(const el_t & t0) {
		return (t0!=(el_t::get_the_identity()));
	}
	static constexpr bool funct(const el_t & t0,const el_t & t1) {
		return ((t0!=(el_t::get_the_identity()))&&(t1!=(el_t::get_the_identity())));
	}
	static constexpr bool funct(const el_t & t0,const el_t & t1,const el_t & t2) {
		return ((t0!=(el_t::get_the_identity()))&&(t1!=(el_t::get_the_identity()))&&(t2!=(el_t::get_the_identity())));
	}
	static constexpr bool funct(const el_t & t0,const el_t & t1,const el_t & t2,const el_t & t3) {
		return ((t0!=(el_t::get_the_identity()))&&(t1!=(el_t::get_the_identity()))&&(t2!=(el_t::get_the_identity()))&&(t3!=(el_t::get_the_identity())));
	}
	static constexpr bool funct(const el_t & t0,const el_t & t1,const el_t & t2,const el_t & t3,const el_t & t4) {
		return ((t0!=(el_t::get_the_identity()))&&(t1!=(el_t::get_the_identity()))&&(t2!=(el_t::get_the_identity()))&&(t3!=(el_t::get_the_identity()))&&(t4!=(el_t::get_the_identity())));
	}
	static constexpr bool funct(const el_t & t0,const el_t & t1,const el_t & t2,const el_t & t3,const el_t & t4,const el_t & t5) {
		return ((t0!=(el_t::get_the_identity()))&&(t1!=(el_t::get_the_identity()))&&(t2!=(el_t::get_the_identity()))&&(t3!=(el_t::get_the_identity()))&&(t4!=(el_t::get_the_identity()))&&(t5!=(el_t::get_the_identity())));
	}
	static constexpr bool funct(const el_t & t0,const el_t & t1,const el_t & t2,const el_t & t3,const el_t & t4,const el_t & t5,const el_t & t6) {
		return ((t0!=(el_t::get_the_identity()))&&(t1!=(el_t::get_the_identity()))&&(t2!=(el_t::get_the_identity()))&&(t3!=(el_t::get_the_identity()))&&(t4!=(el_t::get_the_identity()))&&(t5!=(el_t::get_the_identity()))&&(t6!=(el_t::get_the_identity())));
	}
};

template<size_t I,size_t J,template<group_name,typename K_t,K_t,K_t...> class TT,group_name gn,typename UIntType,UIntType N0,UIntType ... Ns>
struct all_firsts_N_different_from_I;
template<group_name gn,typename UIntType,UIntType N0,UIntType ... Ns>
struct all_firsts_N_different_from_I<0,1,magma_t,gn,UIntType,N0,Ns...> {
	using el_t = magma_t<gn,UIntType,N0,Ns...>;
	
	static constexpr bool funct(const el_t & t0) {
		return true;
	}
	static constexpr bool funct(const el_t & t0,const el_t & t1) {
		return (t0!=t1);
	}
	static constexpr bool funct(const el_t & t0,const el_t & t1,const el_t & t2) {
		return (t0!=t1);
	}
	static constexpr bool funct(const el_t & t0,const el_t & t1,const el_t & t2,const el_t & t3) {
		return (t0!=t1);
	}
	static constexpr bool funct(const el_t & t0,const el_t & t1,const el_t & t2,const el_t & t3,const el_t & t4) {
		return (t0!=t1);
	}
	static constexpr bool funct(const el_t & t0,const el_t & t1,const el_t & t2,const el_t & t3,const el_t & t4,const el_t & t5) {
		return (t0!=t1);
	}
	static constexpr bool funct(const el_t & t0,const el_t & t1,const el_t & t2,const el_t & t3,const el_t & t4,const el_t & t5,const el_t & t6) {
		return (t0!=t1);
	}
};
template<group_name gn,typename UIntType,UIntType N0,UIntType ... Ns>
struct all_firsts_N_different_from_I<0,2,magma_t,gn,UIntType,N0,Ns...> {
	using el_t = magma_t<gn,UIntType,N0,Ns...>;
	
	static constexpr bool funct(const el_t & t0) {
		return true;
	}
	static constexpr bool funct(const el_t & t0,const el_t & t1) {
		return (t0!=t1);
	}
	static constexpr bool funct(const el_t & t0,const el_t & t1,const el_t & t2) {
		return ((t0!=t1)&&(t0!=t2));
	}
	static constexpr bool funct(const el_t & t0,const el_t & t1,const el_t & t2,const el_t & t3) {
		const all_firsts_neq_id<2,magma_t,gn,UIntType,N0,Ns...> no_id{};
		return ((t0!=t1)&&(t0!=t2));
	}
	static constexpr bool funct(const el_t & t0,const el_t & t1,const el_t & t2,const el_t & t3,const el_t & t4) {
		const all_firsts_neq_id<2,magma_t,gn,UIntType,N0,Ns...> no_id{};
		return ((t0!=t1)&&(t0!=t2));
	}
	static constexpr bool funct(const el_t & t0,const el_t & t1,const el_t & t2,const el_t & t3,const el_t & t4,const el_t & t5) {
		const all_firsts_neq_id<2,magma_t,gn,UIntType,N0,Ns...> no_id{};
		return ((t0!=t1)&&(t0!=t2));
	}
	static constexpr bool funct(const el_t & t0,const el_t & t1,const el_t & t2,const el_t & t3,const el_t & t4,const el_t & t5,const el_t & t6) {
		const all_firsts_neq_id<2,magma_t,gn,UIntType,N0,Ns...> no_id{};
		return ((t0!=t1)&&(t0!=t2));
	}
};
template<group_name gn,typename UIntType,UIntType N0,UIntType ... Ns>
struct all_firsts_N_different_from_I<0,3,magma_t,gn,UIntType,N0,Ns...> {
	using el_t = magma_t<gn,UIntType,N0,Ns...>;
	
	static constexpr bool funct(const el_t & t0) {
		return true;
	}
	static constexpr bool funct(const el_t & t0,const el_t & t1) {
		return (t0!=t1);
	}
	static constexpr bool funct(const el_t & t0,const el_t & t1,const el_t & t2) {
		return ((t0!=t1)&&(t0!=t2));
	}
	static constexpr bool funct(const el_t & t0,const el_t & t1,const el_t & t2,const el_t & t3) {
		return ((t0!=t1)&&(t0!=t2)&&(t0!=t3));
	}
	static constexpr bool funct(const el_t & t0,const el_t & t1,const el_t & t2,const el_t & t3,const el_t & t4) {
		return ((t0!=t1)&&(t0!=t2)&&(t0!=t3));
	}
	static constexpr bool funct(const el_t & t0,const el_t & t1,const el_t & t2,const el_t & t3,const el_t & t4,const el_t & t5) {
		return ((t0!=t1)&&(t0!=t2)&&(t0!=t3));
	}
	static constexpr bool funct(const el_t & t0,const el_t & t1,const el_t & t2,const el_t & t3,const el_t & t4,const el_t & t5,const el_t & t6) {
		const all_firsts_neq_id<3,magma_t,gn,UIntType,N0,Ns...> no_id{};
		return ((t0!=t1)&&(t0!=t2)&&(t0!=t3));
	}
};
template<group_name gn,typename UIntType,UIntType N0,UIntType ... Ns>
struct all_firsts_N_different_from_I<0,4,magma_t,gn,UIntType,N0,Ns...> {
	using el_t = magma_t<gn,UIntType,N0,Ns...>;
	
	static constexpr bool funct(const el_t & t0) {
		return true;
	}
	static constexpr bool funct(const el_t & t0,const el_t & t1) {
		return (t0!=t1);
	}
	static constexpr bool funct(const el_t & t0,const el_t & t1,const el_t & t2) {
		return ((t0!=t1)&&(t0!=t2));
	}
	static constexpr bool funct(const el_t & t0,const el_t & t1,const el_t & t2,const el_t & t3) {
		return ((t0!=t1)&&(t0!=t2)&&(t0!=t3));
	}
	static constexpr bool funct(const el_t & t0,const el_t & t1,const el_t & t2,const el_t & t3,const el_t & t4) {
		return ((t0!=t1)&&(t0!=t2)&&(t0!=t3)&&(t0!=t4));
	}
	static constexpr bool funct(const el_t & t0,const el_t & t1,const el_t & t2,const el_t & t3,const el_t & t4,const el_t & t5) {
		return ((t0!=t1)&&(t0!=t2)&&(t0!=t3)&&(t0!=t4));
	}
	static constexpr bool funct(const el_t & t0,const el_t & t1,const el_t & t2,const el_t & t3,const el_t & t4,const el_t & t5,const el_t & t6) {
		return ((t0!=t1)&&(t0!=t2)&&(t0!=t3)&&(t0!=t4));
	}
};
template<group_name gn,typename UIntType,UIntType N0,UIntType ... Ns>
struct all_firsts_N_different_from_I<0,5,magma_t,gn,UIntType,N0,Ns...> {
	using el_t = magma_t<gn,UIntType,N0,Ns...>;
	
	static constexpr bool funct(const el_t & t0) {
		return true;
	}
	static constexpr bool funct(const el_t & t0,const el_t & t1) {
		return (t0!=t1);
	}
	static constexpr bool funct(const el_t & t0,const el_t & t1,const el_t & t2) {
		return ((t0!=t1)&&(t0!=t2));
	}
	static constexpr bool funct(const el_t & t0,const el_t & t1,const el_t & t2,const el_t & t3) {
		return ((t0!=t1)&&(t0!=t2)&&(t0!=t3));
	}
	static constexpr bool funct(const el_t & t0,const el_t & t1,const el_t & t2,const el_t & t3,const el_t & t4) {
		return ((t0!=t1)&&(t0!=t2)&&(t0!=t3)&&(t0!=t4));
	}
	static constexpr bool funct(const el_t & t0,const el_t & t1,const el_t & t2,const el_t & t3,const el_t & t4,const el_t & t5) {
		return ((t0!=t1)&&(t0!=t2)&&(t0!=t3)&&(t0!=t4)&&(t0!=t5));
	}
	static constexpr bool funct(const el_t & t0,const el_t & t1,const el_t & t2,const el_t & t3,const el_t & t4,const el_t & t5,const el_t & t6) {
		return ((t0!=t1)&&(t0!=t2)&&(t0!=t3)&&(t0!=t4)&&(t0!=t5));
	}
};
template<group_name gn,typename UIntType,UIntType N0,UIntType ... Ns>
struct all_firsts_N_different_from_I<0,6,magma_t,gn,UIntType,N0,Ns...> {
	using el_t = magma_t<gn,UIntType,N0,Ns...>;
	
	static constexpr bool funct(const el_t & t0) {
		return true;
	}
	static constexpr bool funct(const el_t & t0,const el_t & t1) {
		return (t0!=t1);
	}
	static constexpr bool funct(const el_t & t0,const el_t & t1,const el_t & t2) {
		return ((t0!=t1)&&(t0!=t2));
	}
	static constexpr bool funct(const el_t & t0,const el_t & t1,const el_t & t2,const el_t & t3) {
		return ((t0!=t1)&&(t0!=t2)&&(t0!=t3));
	}
	static constexpr bool funct(const el_t & t0,const el_t & t1,const el_t & t2,const el_t & t3,const el_t & t4) {
		return ((t0!=t1)&&(t0!=t2)&&(t0!=t3)&&(t0!=t4));
	}
	static constexpr bool funct(const el_t & t0,const el_t & t1,const el_t & t2,const el_t & t3,const el_t & t4,const el_t & t5) {
		return ((t0!=t1)&&(t0!=t2)&&(t0!=t3)&&(t0!=t4)&&(t0!=t5));
	}
	static constexpr bool funct(const el_t & t0,const el_t & t1,const el_t & t2,const el_t & t3,const el_t & t4,const el_t & t5,const el_t & t6) {
		return ((t0!=t1)&&(t0!=t2)&&(t0!=t3)&&(t0!=t4)&&(t0!=t5)&&(t0!=t6));
	}
};
template<group_name gn,typename UIntType,UIntType N0,UIntType ... Ns>
struct all_firsts_N_different_from_I<1,2,magma_t,gn,UIntType,N0,Ns...> {
	using el_t = magma_t<gn,UIntType,N0,Ns...>;
	
	static constexpr bool funct(const el_t & t0) {
		return true;
	}
	static constexpr bool funct(const el_t & t0,const el_t & t1) {
		return true;
	}
	static constexpr bool funct(const el_t & t0,const el_t & t1,const el_t & t2) {
		return (t1!=t2);
	}
	static constexpr bool funct(const el_t & t0,const el_t & t1,const el_t & t2,const el_t & t3) {
		return (t1!=t2);
	}
	static constexpr bool funct(const el_t & t0,const el_t & t1,const el_t & t2,const el_t & t3,const el_t & t4) {
		return (t1!=t2);
	}
	static constexpr bool funct(const el_t & t0,const el_t & t1,const el_t & t2,const el_t & t3,const el_t & t4,const el_t & t5) {
		return (t1!=t2);
	}
	static constexpr bool funct(const el_t & t0,const el_t & t1,const el_t & t2,const el_t & t3,const el_t & t4,const el_t & t5,const el_t & t6) {
		return (t1!=t2);
	}
};
template<group_name gn,typename UIntType,UIntType N0,UIntType ... Ns>
struct all_firsts_N_different_from_I<1,3,magma_t,gn,UIntType,N0,Ns...> {
	using el_t = magma_t<gn,UIntType,N0,Ns...>;
	
	static constexpr bool funct(const el_t & t0) {
		return true;
	}
	static constexpr bool funct(const el_t & t0,const el_t & t1) {
		return true;
	}
	static constexpr bool funct(const el_t & t0,const el_t & t1,const el_t & t2) {
		return (t1!=t2);
	}
	static constexpr bool funct(const el_t & t0,const el_t & t1,const el_t & t2,const el_t & t3) {
		return ((t1!=t2)&&(t1!=t3));
	}
	static constexpr bool funct(const el_t & t0,const el_t & t1,const el_t & t2,const el_t & t3,const el_t & t4) {
		return ((t1!=t2)&&(t1!=t3));
	}
	static constexpr bool funct(const el_t & t0,const el_t & t1,const el_t & t2,const el_t & t3,const el_t & t4,const el_t & t5) {
		return ((t1!=t2)&&(t1!=t3));
	}
	static constexpr bool funct(const el_t & t0,const el_t & t1,const el_t & t2,const el_t & t3,const el_t & t4,const el_t & t5,const el_t & t6) {
		return ((t1!=t2)&&(t1!=t3));
	}
};
template<group_name gn,typename UIntType,UIntType N0,UIntType ... Ns>
struct all_firsts_N_different_from_I<1,4,magma_t,gn,UIntType,N0,Ns...> {
	using el_t = magma_t<gn,UIntType,N0,Ns...>;
	
	static constexpr bool funct(const el_t & t0) {
		return true;
	}
	static constexpr bool funct(const el_t & t0,const el_t & t1) {
		return true;
	}
	static constexpr bool funct(const el_t & t0,const el_t & t1,const el_t & t2) {
		return (t1!=t2);
	}
	static constexpr bool funct(const el_t & t0,const el_t & t1,const el_t & t2,const el_t & t3) {
		return ((t1!=t2)&&(t1!=t3));
	}
	static constexpr bool funct(const el_t & t0,const el_t & t1,const el_t & t2,const el_t & t3,const el_t & t4) {
		return ((t1!=t2)&&(t1!=t3)&&(t1!=t4));
	}
	static constexpr bool funct(const el_t & t0,const el_t & t1,const el_t & t2,const el_t & t3,const el_t & t4,const el_t & t5) {
		return ((t1!=t2)&&(t1!=t3)&&(t1!=t4));
	}
	static constexpr bool funct(const el_t & t0,const el_t & t1,const el_t & t2,const el_t & t3,const el_t & t4,const el_t & t5,const el_t & t6) {
		return ((t1!=t2)&&(t1!=t3)&&(t1!=t4));
	}
};
template<group_name gn,typename UIntType,UIntType N0,UIntType ... Ns>
struct all_firsts_N_different_from_I<1,5,magma_t,gn,UIntType,N0,Ns...> {
	using el_t = magma_t<gn,UIntType,N0,Ns...>;
	
	static constexpr bool funct(const el_t & t0) {
		return true;
	}
	static constexpr bool funct(const el_t & t0,const el_t & t1) {
		return true;
	}
	static constexpr bool funct(const el_t & t0,const el_t & t1,const el_t & t2) {
		return (t1!=t2);
	}
	static constexpr bool funct(const el_t & t0,const el_t & t1,const el_t & t2,const el_t & t3) {
		return ((t1!=t2)&&(t1!=t3));
	}
	static constexpr bool funct(const el_t & t0,const el_t & t1,const el_t & t2,const el_t & t3,const el_t & t4) {
		return ((t1!=t2)&&(t1!=t3)&&(t1!=t4));
	}
	static constexpr bool funct(const el_t & t0,const el_t & t1,const el_t & t2,const el_t & t3,const el_t & t4,const el_t & t5) {
		return ((t1!=t2)&&(t1!=t3)&&(t1!=t4)&&(t1!=t5));
	}
	static constexpr bool funct(const el_t & t0,const el_t & t1,const el_t & t2,const el_t & t3,const el_t & t4,const el_t & t5,const el_t & t6) {
		return ((t1!=t2)&&(t1!=t3)&&(t1!=t4)&&(t1!=t5));
	}
};
template<group_name gn,typename UIntType,UIntType N0,UIntType ... Ns>
struct all_firsts_N_different_from_I<1,6,magma_t,gn,UIntType,N0,Ns...> {
	using el_t = magma_t<gn,UIntType,N0,Ns...>;
	
	static constexpr bool funct(const el_t & t0) {
		return true;
	}
	static constexpr bool funct(const el_t & t0,const el_t & t1) {
		return true;
	}
	static constexpr bool funct(const el_t & t0,const el_t & t1,const el_t & t2) {
		return (t1!=t2);
	}
	static constexpr bool funct(const el_t & t0,const el_t & t1,const el_t & t2,const el_t & t3) {
		return ((t1!=t2)&&(t1!=t3));
	}
	static constexpr bool funct(const el_t & t0,const el_t & t1,const el_t & t2,const el_t & t3,const el_t & t4) {
		return ((t1!=t2)&&(t1!=t3)&&(t1!=t4));
	}
	static constexpr bool funct(const el_t & t0,const el_t & t1,const el_t & t2,const el_t & t3,const el_t & t4,const el_t & t5) {
		return ((t1!=t2)&&(t1!=t3)&&(t1!=t4)&&(t1!=t5));
	}
	static constexpr bool funct(const el_t & t0,const el_t & t1,const el_t & t2,const el_t & t3,const el_t & t4,const el_t & t5,const el_t & t6) {
		return ((t1!=t2)&&(t1!=t3)&&(t1!=t4)&&(t1!=t5)&&(t1!=t6));
	}
};
template<group_name gn,typename UIntType,UIntType N0,UIntType ... Ns>
struct all_firsts_N_different_from_I<2,3,magma_t,gn,UIntType,N0,Ns...> {
	using el_t = magma_t<gn,UIntType,N0,Ns...>;
	
	static constexpr bool funct(const el_t & t0) {
		return true;
	}
	static constexpr bool funct(const el_t & t0,const el_t & t1) {
		return true;
	}
	static constexpr bool funct(const el_t & t0,const el_t & t1,const el_t & t2) {
		return true;
	}
	static constexpr bool funct(const el_t & t0,const el_t & t1,const el_t & t2,const el_t & t3) {
		return (t2!=t3);
	}
	static constexpr bool funct(const el_t & t0,const el_t & t1,const el_t & t2,const el_t & t3,const el_t & t4) {
		return (t2!=t3);
	}
	static constexpr bool funct(const el_t & t0,const el_t & t1,const el_t & t2,const el_t & t3,const el_t & t4,const el_t & t5) {
		return (t2!=t3);
	}
	static constexpr bool funct(const el_t & t0,const el_t & t1,const el_t & t2,const el_t & t3,const el_t & t4,const el_t & t5,const el_t & t6) {
		return (t2!=t3);
	}
};
template<group_name gn,typename UIntType,UIntType N0,UIntType ... Ns>
struct all_firsts_N_different_from_I<2,4,magma_t,gn,UIntType,N0,Ns...> {
	using el_t = magma_t<gn,UIntType,N0,Ns...>;
	
	static constexpr bool funct(const el_t & t0) {
		return true;
	}
	static constexpr bool funct(const el_t & t0,const el_t & t1) {
		return true;
	}
	static constexpr bool funct(const el_t & t0,const el_t & t1,const el_t & t2) {
		return true;
	}
	static constexpr bool funct(const el_t & t0,const el_t & t1,const el_t & t2,const el_t & t3) {
		return (t2!=t3);
	}
	static constexpr bool funct(const el_t & t0,const el_t & t1,const el_t & t2,const el_t & t3,const el_t & t4) {
		return ((t2!=t3)&&(t2!=t4));
	}
	static constexpr bool funct(const el_t & t0,const el_t & t1,const el_t & t2,const el_t & t3,const el_t & t4,const el_t & t5) {
		return ((t2!=t3)&&(t2!=t4));
	}
	static constexpr bool funct(const el_t & t0,const el_t & t1,const el_t & t2,const el_t & t3,const el_t & t4,const el_t & t5,const el_t & t6) {
		return ((t2!=t3)&&(t2!=t4));
	}
};
template<group_name gn,typename UIntType,UIntType N0,UIntType ... Ns>
struct all_firsts_N_different_from_I<2,5,magma_t,gn,UIntType,N0,Ns...> {
	using el_t = magma_t<gn,UIntType,N0,Ns...>;
	
	static constexpr bool funct(const el_t & t0) {
		return true;
	}
	static constexpr bool funct(const el_t & t0,const el_t & t1) {
		return true;
	}
	static constexpr bool funct(const el_t & t0,const el_t & t1,const el_t & t2) {
		return true;
	}
	static constexpr bool funct(const el_t & t0,const el_t & t1,const el_t & t2,const el_t & t3) {
		return (t2!=t3);
	}
	static constexpr bool funct(const el_t & t0,const el_t & t1,const el_t & t2,const el_t & t3,const el_t & t4) {
		return ((t2!=t3)&&(t2!=t4));
	}
	static constexpr bool funct(const el_t & t0,const el_t & t1,const el_t & t2,const el_t & t3,const el_t & t4,const el_t & t5) {
		return ((t2!=t3)&&(t2!=t4)&&(t2!=t5));
	}
	static constexpr bool funct(const el_t & t0,const el_t & t1,const el_t & t2,const el_t & t3,const el_t & t4,const el_t & t5,const el_t & t6) {
		return ((t2!=t3)&&(t2!=t4)&&(t2!=t5));
	}
};
template<group_name gn,typename UIntType,UIntType N0,UIntType ... Ns>
struct all_firsts_N_different_from_I<2,6,magma_t,gn,UIntType,N0,Ns...> {
	using el_t = magma_t<gn,UIntType,N0,Ns...>;
	
	static constexpr bool funct(const el_t & t0) {
		return true;
	}
	static constexpr bool funct(const el_t & t0,const el_t & t1) {
		return true;
	}
	static constexpr bool funct(const el_t & t0,const el_t & t1,const el_t & t2) {
		return true;
	}
	static constexpr bool funct(const el_t & t0,const el_t & t1,const el_t & t2,const el_t & t3) {
		return (t2!=t3);
	}
	static constexpr bool funct(const el_t & t0,const el_t & t1,const el_t & t2,const el_t & t3,const el_t & t4) {
		return ((t2!=t3)&&(t2!=t4));
	}
	static constexpr bool funct(const el_t & t0,const el_t & t1,const el_t & t2,const el_t & t3,const el_t & t4,const el_t & t5) {
		return ((t2!=t3)&&(t2!=t4)&&(t2!=t5));
	}
	static constexpr bool funct(const el_t & t0,const el_t & t1,const el_t & t2,const el_t & t3,const el_t & t4,const el_t & t5,const el_t & t6) {
		return ((t2!=t3)&&(t2!=t4)&&(t2!=t5)&&(t2!=t6));
	}
};
template<group_name gn,typename UIntType,UIntType N0,UIntType ... Ns>
struct all_firsts_N_different_from_I<3,4,magma_t,gn,UIntType,N0,Ns...> {
	using el_t = magma_t<gn,UIntType,N0,Ns...>;
	
	static constexpr bool funct(const el_t & t0) {
		return true;
	}
	static constexpr bool funct(const el_t & t0,const el_t & t1) {
		return true;
	}
	static constexpr bool funct(const el_t & t0,const el_t & t1,const el_t & t2) {
		return true;
	}
	static constexpr bool funct(const el_t & t0,const el_t & t1,const el_t & t2,const el_t & t3) {
		return true;
	}
	static constexpr bool funct(const el_t & t0,const el_t & t1,const el_t & t2,const el_t & t3,const el_t & t4) {
		return (t3!=t4);
	}
	static constexpr bool funct(const el_t & t0,const el_t & t1,const el_t & t2,const el_t & t3,const el_t & t4,const el_t & t5) {
		return (t3!=t4);
	}
	static constexpr bool funct(const el_t & t0,const el_t & t1,const el_t & t2,const el_t & t3,const el_t & t4,const el_t & t5,const el_t & t6) {
		return (t3!=t4);
	}
};
template<group_name gn,typename UIntType,UIntType N0,UIntType ... Ns>
struct all_firsts_N_different_from_I<3,5,magma_t,gn,UIntType,N0,Ns...> {
	using el_t = magma_t<gn,UIntType,N0,Ns...>;
	
	static constexpr bool funct(const el_t & t0) {
		return true;
	}
	static constexpr bool funct(const el_t & t0,const el_t & t1) {
		return true;
	}
	static constexpr bool funct(const el_t & t0,const el_t & t1,const el_t & t2) {
		return true;
	}
	static constexpr bool funct(const el_t & t0,const el_t & t1,const el_t & t2,const el_t & t3) {
		return true;
	}
	static constexpr bool funct(const el_t & t0,const el_t & t1,const el_t & t2,const el_t & t3,const el_t & t4) {
		return (t3!=t4);
	}
	static constexpr bool funct(const el_t & t0,const el_t & t1,const el_t & t2,const el_t & t3,const el_t & t4,const el_t & t5) {
		return ((t3!=t4)&&(t3!=t5));
	}
	static constexpr bool funct(const el_t & t0,const el_t & t1,const el_t & t2,const el_t & t3,const el_t & t4,const el_t & t5,const el_t & t6) {
		return ((t3!=t4)&&(t3!=t5));
	}
};
template<group_name gn,typename UIntType,UIntType N0,UIntType ... Ns>
struct all_firsts_N_different_from_I<3,6,magma_t,gn,UIntType,N0,Ns...> {
	using el_t = magma_t<gn,UIntType,N0,Ns...>;
	
	static constexpr bool funct(const el_t & t0) {
		return true;
	}
	static constexpr bool funct(const el_t & t0,const el_t & t1) {
		return true;
	}
	static constexpr bool funct(const el_t & t0,const el_t & t1,const el_t & t2) {
		return true;
	}
	static constexpr bool funct(const el_t & t0,const el_t & t1,const el_t & t2,const el_t & t3) {
		return true;
	}
	static constexpr bool funct(const el_t & t0,const el_t & t1,const el_t & t2,const el_t & t3,const el_t & t4) {
		return (t3!=t4);
	}
	static constexpr bool funct(const el_t & t0,const el_t & t1,const el_t & t2,const el_t & t3,const el_t & t4,const el_t & t5) {
		return ((t3!=t4)&&(t3!=t5));
	}
	static constexpr bool funct(const el_t & t0,const el_t & t1,const el_t & t2,const el_t & t3,const el_t & t4,const el_t & t5,const el_t & t6) {
		return ((t3!=t4)&&(t3!=t5)&&(t3!=t6));
	}
};
template<group_name gn,typename UIntType,UIntType N0,UIntType ... Ns>
struct all_firsts_N_different_from_I<4,5,magma_t,gn,UIntType,N0,Ns...> {
	using el_t = magma_t<gn,UIntType,N0,Ns...>;
	
	static constexpr bool funct(const el_t & t0) {
		return true;
	}
	static constexpr bool funct(const el_t & t0,const el_t & t1) {
		return true;
	}
	static constexpr bool funct(const el_t & t0,const el_t & t1,const el_t & t2) {
		return true;
	}
	static constexpr bool funct(const el_t & t0,const el_t & t1,const el_t & t2,const el_t & t3) {
		return true;
	}
	static constexpr bool funct(const el_t & t0,const el_t & t1,const el_t & t2,const el_t & t3,const el_t & t4) {
		return true;
	}
	static constexpr bool funct(const el_t & t0,const el_t & t1,const el_t & t2,const el_t & t3,const el_t & t4,const el_t & t5) {
		return (t4!=t5);
	}
	static constexpr bool funct(const el_t & t0,const el_t & t1,const el_t & t2,const el_t & t3,const el_t & t4,const el_t & t5,const el_t & t6) {
		return (t4!=t5);
	}
};
template<group_name gn,typename UIntType,UIntType N0,UIntType ... Ns>
struct all_firsts_N_different_from_I<4,6,magma_t,gn,UIntType,N0,Ns...> {
	using el_t = magma_t<gn,UIntType,N0,Ns...>;
	
	static constexpr bool funct(const el_t & t0) {
		return true;
	}
	static constexpr bool funct(const el_t & t0,const el_t & t1) {
		return true;
	}
	static constexpr bool funct(const el_t & t0,const el_t & t1,const el_t & t2) {
		return true;
	}
	static constexpr bool funct(const el_t & t0,const el_t & t1,const el_t & t2,const el_t & t3) {
		return true;
	}
	static constexpr bool funct(const el_t & t0,const el_t & t1,const el_t & t2,const el_t & t3,const el_t & t4) {
		return true;
	}
	static constexpr bool funct(const el_t & t0,const el_t & t1,const el_t & t2,const el_t & t3,const el_t & t4,const el_t & t5) {
		return (t4!=t5);
	}
	static constexpr bool funct(const el_t & t0,const el_t & t1,const el_t & t2,const el_t & t3,const el_t & t4,const el_t & t5,const el_t & t6) {
		return ((t4!=t5)&&(t4!=t6));
	}

};
template<group_name gn,typename UIntType,UIntType N0,UIntType ... Ns>
struct all_firsts_N_different_from_I<5,6,magma_t,gn,UIntType,N0,Ns...> {
	using el_t = magma_t<gn,UIntType,N0,Ns...>;
	
	static constexpr bool funct(const el_t & t0) {
		return true;
	}
	static constexpr bool funct(const el_t & t0,const el_t & t1) {
		return true;
	}
	static constexpr bool funct(const el_t & t0,const el_t & t1,const el_t & t2) {
		return true;
	}
	static constexpr bool funct(const el_t & t0,const el_t & t1,const el_t & t2,const el_t & t3) {
		return true;
	}
	static constexpr bool funct(const el_t & t0,const el_t & t1,const el_t & t2,const el_t & t3,const el_t & t4) {
		return true;
	}
	static constexpr bool funct(const el_t & t0,const el_t & t1,const el_t & t2,const el_t & t3,const el_t & t4,const el_t & t5) {
		return true;
	}
	static constexpr bool funct(const el_t & t0,const el_t & t1,const el_t & t2,const el_t & t3,const el_t & t4,const el_t & t5,const el_t & t6) {
		return (t5!=t6);
	}

};

template<size_t I,template<group_name,typename K_t,K_t,K_t...> class TT,group_name gn,typename UIntType,UIntType N0,UIntType ... Ns>
struct all_firsts_N_differents;
template<group_name gn,typename UIntType,UIntType N0,UIntType ... Ns>
struct all_firsts_N_differents<0,magma_t,gn,UIntType,N0,Ns...> {
	using el_t = magma_t<gn,UIntType,N0,Ns...>;
	static constexpr bool funct(const el_t & t0) {
		return true;
	}
	static constexpr bool funct(const el_t & t0,const el_t & t1) {
		return true;
	}
	static constexpr bool funct(const el_t & t0,const el_t & t1,const el_t & t2) {
		return true;
	}
	static constexpr bool funct(const el_t & t0,const el_t & t1,const el_t & t2,const el_t & t3) {
		return true;
	}
	static constexpr bool funct(const el_t & t0,const el_t & t1,const el_t & t2,const el_t & t3,const el_t & t4) {
		return true;
	}
	static constexpr bool funct(const el_t & t0,const el_t & t1,const el_t & t2,const el_t & t3,const el_t & t4,const el_t & t5) {
		return true;
	}
	static constexpr bool funct(const el_t & t0,const el_t & t1,const el_t & t2,const el_t & t3,const el_t & t4,const el_t & t5,const el_t & t6) {
		return true;
	}

};
template<group_name gn,typename UIntType,UIntType N0,UIntType ... Ns>
struct all_firsts_N_differents<1,magma_t,gn,UIntType,N0,Ns...> {
	using el_t = magma_t<gn,UIntType,N0,Ns...>;
	using fo = all_firsts_N_different_from_I<0,1,magma_t,gn,UIntType,N0,Ns...>;
	static constexpr bool funct(const el_t & t0) {
		return true;
	}
	static constexpr bool funct(const el_t & t0,const el_t & t1) {
		return fo::funct(t0,t1);
	}
	static constexpr bool funct(const el_t & t0,const el_t & t1,const el_t & t2) {
		return fo::funct(t0,t1);
	}
	static constexpr bool funct(const el_t & t0,const el_t & t1,const el_t & t2,const el_t & t3) {
		return fo::funct(t0,t1);
	}
	static constexpr bool funct(const el_t & t0,const el_t & t1,const el_t & t2,const el_t & t3,const el_t & t4) {
		return fo::funct(t0,t1);
	}
	static constexpr bool funct(const el_t & t0,const el_t & t1,const el_t & t2,const el_t & t3,const el_t & t4,const el_t & t5) {
		return fo::funct(t0,t1);
	}
	static constexpr bool funct(const el_t & t0,const el_t & t1,const el_t & t2,const el_t & t3,const el_t & t4,const el_t & t5,const el_t & t6) {
		return fo::funct(t0,t1);
	}

};
template<group_name gn,typename UIntType,UIntType N0,UIntType ... Ns>
struct all_firsts_N_differents<2,magma_t,gn,UIntType,N0,Ns...> {
	using el_t = magma_t<gn,UIntType,N0,Ns...>;
	
	using of_02 = all_firsts_N_different_from_I<0,2,magma_t,gn,UIntType,N0,Ns...>;
	using of_12 = all_firsts_N_different_from_I<1,2,magma_t,gn,UIntType,N0,Ns...>;
	
	static constexpr bool funct(const el_t & t0) {
		return true;
	}
	static constexpr bool funct(const el_t & t0,const el_t & t1) {
		return of_02::funct(t0,t1);
	}
	static constexpr bool funct(const el_t & t0,const el_t & t1,const el_t & t2) {
		return (of_02::funct(t0,t1)&&of_12::funct(t0,t1));
	}
	static constexpr bool funct(const el_t & t0,const el_t & t1,const el_t & t2,const el_t & t3) {
		return (of_02::funct(t0,t1)&&of_12::funct(t0,t1));
	}
	static constexpr bool funct(const el_t & t0,const el_t & t1,const el_t & t2,const el_t & t3,const el_t & t4) {
		return (of_02::funct(t0,t1)&&of_12::funct(t0,t1));
	}
	static constexpr bool funct(const el_t & t0,const el_t & t1,const el_t & t2,const el_t & t3,const el_t & t4,const el_t & t5) {
		return (of_02::funct(t0,t1)&&of_12::funct(t0,t1));
	}
	static constexpr bool funct(const el_t & t0,const el_t & t1,const el_t & t2,const el_t & t3,const el_t & t4,const el_t & t5,const el_t & t6) {
		return (of_02::funct(t0,t1)&&of_12::funct(t0,t1));
	}

};
template<group_name gn,typename UIntType,UIntType N0,UIntType ... Ns>
struct all_firsts_N_differents<3,magma_t,gn,UIntType,N0,Ns...> {
	using el_t = magma_t<gn,UIntType,N0,Ns...>;
	template<size_t P>
	using fo = all_firsts_N_different_from_I<P,3,magma_t,gn,UIntType,N0,Ns...>;
	static constexpr bool funct(const el_t & t0) {
		return true;
	}
	static constexpr bool funct(const el_t & t0,const el_t & t1) {
		return fo<0>::funct(t0,t1);
	}
	static constexpr bool funct(const el_t & t0,const el_t & t1,const el_t & t2) {
		return (fo<0>::funct(t0,t1,t2)&&fo<1>::funct(t0,t1,t2));
	}
	static constexpr bool funct(const el_t & t0,const el_t & t1,const el_t & t2,const el_t & t3) {
		return (fo<0>::funct(t0,t1,t2,t3)&&fo<1>::funct(t0,t1,t2,t3)&&fo<2>::funct(t0,t1,t2,t3));
	}
	static constexpr bool funct(const el_t & t0,const el_t & t1,const el_t & t2,const el_t & t3,const el_t & t4) {
		return (fo<0>::funct(t0,t1,t2,t3)&&fo<1>::funct(t0,t1,t2,t3)&&fo<2>::funct(t0,t1,t2,t3));
	}
	static constexpr bool funct(const el_t & t0,const el_t & t1,const el_t & t2,const el_t & t3,const el_t & t4,const el_t & t5) {
		return (fo<0>::funct(t0,t1,t2,t3)&&fo<1>::funct(t0,t1,t2,t3)&&fo<2>::funct(t0,t1,t2,t3));
	}
	static constexpr bool funct(const el_t & t0,const el_t & t1,const el_t & t2,const el_t & t3,const el_t & t4,const el_t & t5,const el_t & t6) {
		return (fo<0>::funct(t0,t1,t2,t3)&&fo<1>::funct(t0,t1,t2,t3)&&fo<2>::funct(t0,t1,t2,t3));
	}

};
template<group_name gn,typename UIntType,UIntType N0,UIntType ... Ns>
struct all_firsts_N_differents<4,magma_t,gn,UIntType,N0,Ns...> {
	using el_t = magma_t<gn,UIntType,N0,Ns...>;
	template<size_t P>
	using fo = all_firsts_N_different_from_I<P,4,magma_t,gn,UIntType,N0,Ns...>;
	static constexpr bool funct(const el_t & t0) {
		return true;
	}
	static constexpr bool funct(const el_t & t0,const el_t & t1) {
		return fo<0>::funct(t0,t1);
	}
	static constexpr bool funct(const el_t & t0,const el_t & t1,const el_t & t2) {
		return (fo<0>::funct(t0,t1,t2)&&fo<1>::funct(t0,t1,t2));
	}
	static constexpr bool funct(const el_t & t0,const el_t & t1,const el_t & t2,const el_t & t3) {
		return (fo<0>::funct(t0,t1,t2,t3)&&fo<1>::funct(t0,t1,t2,t3)&&fo<2>::funct(t0,t1,t2,t3));
	}
	static constexpr bool funct(const el_t & t0,const el_t & t1,const el_t & t2,const el_t & t3,const el_t & t4) {
		return (fo<0>::funct(t0,t1,t2,t3,t4)&&fo<1>::funct(t0,t1,t2,t3,t4)&&fo<2>::funct(t0,t1,t2,t3,t4)&&fo<3>::funct(t0,t1,t2,t3,t4));
	}
	static constexpr bool funct(const el_t & t0,const el_t & t1,const el_t & t2,const el_t & t3,const el_t & t4,const el_t & t5) {
		return (fo<0>::funct(t0,t1,t2,t3,t4)&&fo<1>::funct(t0,t1,t2,t3,t4)&&fo<2>::funct(t0,t1,t2,t3,t4)&&fo<3>::funct(t0,t1,t2,t3,t4));
	}
	static constexpr bool funct(const el_t & t0,const el_t & t1,const el_t & t2,const el_t & t3,const el_t & t4,const el_t & t5,const el_t & t6) {
		return (fo<0>::funct(t0,t1,t2,t3,t4)&&fo<1>::funct(t0,t1,t2,t3,t4)&&fo<2>::funct(t0,t1,t2,t3,t4)&&fo<3>::funct(t0,t1,t2,t3,t4));
	}

};
template<group_name gn,typename UIntType,UIntType N0,UIntType ... Ns>
struct all_firsts_N_differents<5,magma_t,gn,UIntType,N0,Ns...> {
	using el_t = magma_t<gn,UIntType,N0,Ns...>;
	template<size_t P>
	using fo = all_firsts_N_different_from_I<P,5,magma_t,gn,UIntType,N0,Ns...>;
	
	static constexpr bool funct(const el_t & t0) {
		return true;
	}
	static constexpr bool funct(const el_t & t0,const el_t & t1) {
		return fo<0>::funct(t0,t1);
	}
	static constexpr bool funct(const el_t & t0,const el_t & t1,const el_t & t2) {
		return (fo<0>::funct(t0,t1,t2)&&fo<1>::funct(t0,t1,t2));
	}
	static constexpr bool funct(const el_t & t0,const el_t & t1,const el_t & t2,const el_t & t3) {
		return (fo<0>::funct(t0,t1,t2,t3)&&fo<1>::funct(t0,t1,t2,t3)&&fo<2>::funct(t0,t1,t2,t3));
	}
	static constexpr bool funct(const el_t & t0,const el_t & t1,const el_t & t2,const el_t & t3,const el_t & t4) {
		return (fo<0>::funct(t0,t1,t2,t3,t4)&&fo<1>::funct(t0,t1,t2,t3,t4)&&fo<2>::funct(t0,t1,t2,t3,t4)&&fo<3>::funct(t0,t1,t2,t3,t4));
	}
	static constexpr bool funct(const el_t & t0,const el_t & t1,const el_t & t2,const el_t & t3,const el_t & t4,const el_t & t5) {
		return (fo<0>::funct(t0,t1,t2,t3,t4,t5)&&fo<1>::funct(t0,t1,t2,t3,t4,t5)&&fo<2>::funct(t0,t1,t2,t3,t4,t5)&&fo<3>::funct(t0,t1,t2,t3,t4,t5)&&fo<4>::funct(t0,t1,t2,t3,t4,t5));
	}
	static constexpr bool funct(const el_t & t0,const el_t & t1,const el_t & t2,const el_t & t3,const el_t & t4,const el_t & t5,const el_t & t6) {
		return (fo<0>::funct(t0,t1,t2,t3,t4,t5)&&fo<1>::funct(t0,t1,t2,t3,t4,t5)&&fo<2>::funct(t0,t1,t2,t3,t4,t5)&&fo<3>::funct(t0,t1,t2,t3,t4,t5)&&fo<4>::funct(t0,t1,t2,t3,t4,t5));
	}
};
template<group_name gn,typename UIntType,UIntType N0,UIntType ... Ns>
struct all_firsts_N_differents<6,magma_t,gn,UIntType,N0,Ns...> {
	using el_t = magma_t<gn,UIntType,N0,Ns...>;
	template<size_t P>
	using fo = all_firsts_N_different_from_I<P,5,magma_t,gn,UIntType,N0,Ns...>;
	
	static constexpr bool funct(const el_t & t0) {
		return true;
	}
	static constexpr bool funct(const el_t & t0,const el_t & t1) {
		return fo<0>::funct(t0,t1);
	}
	static constexpr bool funct(const el_t & t0,const el_t & t1,const el_t & t2) {
		return (fo<0>::funct(t0,t1,t2)&&fo<1>::funct(t0,t1,t2));
	}
	static constexpr bool funct(const el_t & t0,const el_t & t1,const el_t & t2,const el_t & t3) {
		return (fo<0>::funct(t0,t1,t2,t3)&&fo<1>::funct(t0,t1,t2,t3)&&fo<2>::funct(t0,t1,t2,t3));
	}
	static constexpr bool funct(const el_t & t0,const el_t & t1,const el_t & t2,const el_t & t3,const el_t & t4) {
		return (fo<0>::funct(t0,t1,t2,t3,t4)&&fo<1>::funct(t0,t1,t2,t3,t4)&&fo<2>::funct(t0,t1,t2,t3,t4)&&fo<3>::funct(t0,t1,t2,t3,t4));
	}
	static constexpr bool funct(const el_t & t0,const el_t & t1,const el_t & t2,const el_t & t3,const el_t & t4,const el_t & t5) {
		return (fo<0>::funct(t0,t1,t2,t3,t4,t5)&&fo<1>::funct(t0,t1,t2,t3,t4,t5)&&fo<2>::funct(t0,t1,t2,t3,t4,t5)&&fo<3>::funct(t0,t1,t2,t3,t4,t5)&&fo<4>::funct(t0,t1,t2,t3,t4,t5));
	}
	static constexpr bool funct(const el_t & t0,const el_t & t1,const el_t & t2,const el_t & t3,const el_t & t4,const el_t & t5,const el_t & t6) {
		return (fo<0>::funct(t0,t1,t2,t3,t4,t5,t6)&&fo<1>::funct(t0,t1,t2,t3,t4,t5,t6)&&fo<2>::funct(t0,t1,t2,t3,t4,t5,t6)&&fo<3>::funct(t0,t1,t2,t3,t4,t5,t6)&&fo<4>::funct(t0,t1,t2,t3,t4,t5,t6)&&fo<5>::funct(t0,t1,t2,t3,t4,t5,t6));
	}
};
}
namespace details {
template<size_t I,template<group_name,typename K_t,K_t,K_t...> class TT,group_name gn,typename UIntType,UIntType N0,UIntType ... Ns>
struct exactly_diffs_firsts;
template<group_name gn,typename UIntType,UIntType N0,UIntType ... Ns>
struct exactly_diffs_firsts<0,magma_t,gn,UIntType,N0,Ns...> {
	using el_t = magma_t<gn,UIntType,N0,Ns...>;
	using of = all_firsts_neq_id<0,magma_t,gn,UIntType,N0,Ns...>;
	
	static constexpr bool funct(const el_t & t0) {
		return of::funct(t0);
	}
	static constexpr bool funct(const el_t & t0,const el_t & t1) {
		return of::funct(t0);
	}
	static constexpr bool funct(const el_t & t0,const el_t & t1,const el_t & t2) {
		return of::funct(t0);
	}
	static constexpr bool funct(const el_t & t0,const el_t & t1,const el_t & t2,const el_t & t3) {
		return of::funct(t0);
	}
	static constexpr bool funct(const el_t & t0,const el_t & t1,const el_t & t2,const el_t & t3,const el_t & t4) {
		return of::funct(t0);
	}
	static constexpr bool funct(const el_t & t0,const el_t & t1,const el_t & t2,const el_t & t3,const el_t & t4,const el_t & t5) {
		return of::funct(t0);
	}
	static constexpr bool funct(const el_t & t0,const el_t & t1,const el_t & t2,const el_t & t3,const el_t & t4,const el_t & t5,const el_t & t6) {
		return of::funct(t0);
	}

};
template<group_name gn,typename UIntType,UIntType N0,UIntType ... Ns>
struct exactly_diffs_firsts<1,magma_t,gn,UIntType,N0,Ns...> {
	using el_t = magma_t<gn,UIntType,N0,Ns...>;
	using of = all_firsts_neq_id<1,magma_t,gn,UIntType,N0,Ns...>;
	
	static constexpr bool funct(const el_t & t0) {
		return of::funct(t0);
	}
	static constexpr bool funct(const el_t & t0,const el_t & t1) {
		return (all_firsts_N_different_from_I<0,1,magma_t,gn,UIntType,N0,Ns...>(t0,t1)&&of::funct(t0,t1));
	}
	static constexpr bool funct(const el_t & t0,const el_t & t1,const el_t & t2) {
		return (all_firsts_N_different_from_I<0,1,magma_t,gn,UIntType,gn,N0,Ns...>(t0,t1)&&of::funct(t0,t1));
	}
	static constexpr bool funct(const el_t & t0,const el_t & t1,const el_t & t2,const el_t & t3) {
		return (all_firsts_N_different_from_I<0,1,magma_t,gn,UIntType,N0,Ns...>(t0,t1)&&of::funct(t0,t1));
	}
	static constexpr bool funct(const el_t & t0,const el_t & t1,const el_t & t2,const el_t & t3,const el_t & t4) {
		return (all_firsts_N_different_from_I<0,1,magma_t,gn,UIntType,N0,Ns...>(t0,t1)&&of::funct(t0,t1));
	}
	static constexpr bool funct(const el_t & t0,const el_t & t1,const el_t & t2,const el_t & t3,const el_t & t4,const el_t & t5) {
		return (all_firsts_N_different_from_I<0,1,magma_t,gn,UIntType,N0,Ns...>(t0,t1)&&of::funct(t0,t1));
	}
	static constexpr bool funct(const el_t & t0,const el_t & t1,const el_t & t2,const el_t & t3,const el_t & t4,const el_t & t5,const el_t & t6) {
		return (all_firsts_N_different_from_I<0,1,magma_t,gn,UIntType,N0,Ns...>(t0,t1)&&of::funct(t0,t1));
	}

};
template<group_name gn,typename UIntType,UIntType N0,UIntType ... Ns>
struct exactly_diffs_firsts<2,magma_t,gn,UIntType,N0,Ns...> {
	using el_t = magma_t<gn,UIntType,N0,Ns...>;
	using all_firsts_neq_id = all_firsts_neq_id<2,magma_t,gn,UIntType,N0,Ns...>;
	using allfneqid_02 = all_firsts_N_different_from_I<0,2,magma_t,gn,UIntType,N0,Ns...>;
	using allfneqid_12 = all_firsts_N_different_from_I<1,2,magma_t,gn,UIntType,N0,Ns...>;
	
	static constexpr bool funct(const el_t & t0) {
		return all_firsts_neq_id::funct(t0);
	}
	static constexpr bool funct(const el_t & t0,const el_t & t1) {
		return (allfneqid_02::funct(t0,t1)&all_firsts_neq_id::funct(t0,t1));
	}
	static constexpr bool funct(const el_t & t0,const el_t & t1,const el_t & t2) {
		return (allfneqid_02::funct(t0,t1)&&allfneqid_12::funct(t0,t1)&&all_firsts_neq_id::funct(t0,t1,t2));
	}
	static constexpr bool funct(const el_t & t0,const el_t & t1,const el_t & t2,const el_t & t3) {
		return (allfneqid_02::funct(t0,t1)&&allfneqid_12::funct(t0,t1)&&all_firsts_neq_id::funct(t0,t1,t2));
	}
	static constexpr bool funct(const el_t & t0,const el_t & t1,const el_t & t2,const el_t & t3,const el_t & t4) {
		return (allfneqid_02::funct(t0,t1)&&allfneqid_12::funct(t0,t1)&&all_firsts_neq_id::funct(t0,t1,t2));
	}
	static constexpr bool funct(const el_t & t0,const el_t & t1,const el_t & t2,const el_t & t3,const el_t & t4,const el_t & t5) {
		return (allfneqid_02::funct(t0,t1)&&allfneqid_12::funct(t0,t1)&&all_firsts_neq_id::funct(t0,t1,t2));
	}
	static constexpr bool funct(const el_t & t0,const el_t & t1,const el_t & t2,const el_t & t3,const el_t & t4,const el_t & t5,const el_t & t6) {
		return (allfneqid_02::funct(t0,t1)&&allfneqid_12::funct(t0,t1)&&all_firsts_neq_id::funct(t0,t1,t2));
	}

};
template<group_name gn,typename UIntType,UIntType N0,UIntType ... Ns>
struct exactly_diffs_firsts<3,magma_t,gn,UIntType,N0,Ns...> {
	using el_t = magma_t<gn,UIntType,N0,Ns...>;
	using of = all_firsts_neq_id<3,magma_t,gn,UIntType,N0,Ns...>;
	using fo03 = all_firsts_N_different_from_I<0,3,magma_t,gn,UIntType,N0,Ns...>;
	using fo13 = all_firsts_N_different_from_I<1,3,magma_t,gn,UIntType,N0,Ns...>;
	using fo23 = all_firsts_N_different_from_I<2,3,magma_t,gn,UIntType,N0,Ns...>;
	
	static constexpr bool funct(const el_t & t0) {
		return of::funct(t0);
	}
	static constexpr bool funct(const el_t & t0,const el_t & t1) {
		return (fo03::funct(t0,t1)&&of::funct(t0,t1));
	}
	static constexpr bool funct(const el_t & t0,const el_t & t1,const el_t & t2) {
		return (fo03::funct(t0,t1,t2)&&fo13::funct(t0,t1,t2)&&of::funct(t0,t1,t2));
	}
	static constexpr bool funct(const el_t & t0,const el_t & t1,const el_t & t2,const el_t & t3) {
		return (fo03::funct(t0,t1,t2,t3)&&fo13::funct(t0,t1,t2,t3)&&fo23::funct(t0,t1,t2,t3)&&of::funct(t0,t1,t2,t3));
	}
	static constexpr bool funct(const el_t & t0,const el_t & t1,const el_t & t2,const el_t & t3,const el_t & t4) {
		return (fo03::funct(t0,t1,t2,t3)&&fo13::funct(t0,t1,t2,t3)&&fo23::funct(t0,t1,t2,t3)&&of::funct(t0,t1,t2,t3));
	}
	static constexpr bool funct(const el_t & t0,const el_t & t1,const el_t & t2,const el_t & t3,const el_t & t4,const el_t & t5) {
		return (fo03::funct(t0,t1,t2,t3)&&fo13::funct(t0,t1,t2,t3)&&fo23::funct(t0,t1,t2,t3)&&of::funct(t0,t1,t2,t3));
	}
	static constexpr bool funct(const el_t & t0,const el_t & t1,const el_t & t2,const el_t & t3,const el_t & t4,const el_t & t5,const el_t & t6) {
		return (fo03::funct(t0,t1,t2,t3)&&fo13::funct(t0,t1,t2,t3)&&fo23::funct(t0,t1,t2,t3)&&of::funct(t0,t1,t2,t3));
	}

};
template<group_name gn,typename UIntType,UIntType N0,UIntType ... Ns>
struct exactly_diffs_firsts<4,magma_t,gn,UIntType,N0,Ns...> {
	using el_t = magma_t<gn,UIntType,N0,Ns...>;
	using of = all_firsts_neq_id<4,magma_t,gn,UIntType,N0,Ns...>;
	
	using fo04 = all_firsts_N_different_from_I<0,4,magma_t,gn,UIntType,N0,Ns...>;
	using fo14 = all_firsts_N_different_from_I<1,4,magma_t,gn,UIntType,N0,Ns...>;
	using fo24 = all_firsts_N_different_from_I<2,4,magma_t,gn,UIntType,N0,Ns...>;
	using fo34 = all_firsts_N_different_from_I<3,4,magma_t,gn,UIntType,N0,Ns...>;
	
	static constexpr bool funct(const el_t & t0) {
		return of::funct(t0);
	}
	static constexpr bool funct(const el_t & t0,const el_t & t1) {
		return (fo04::funct(t0,t1)&&of::funct(t0,t1));
	}
	static constexpr bool funct(const el_t & t0,const el_t & t1,const el_t & t2) {
		return (fo04::funct(t0,t1,t2)&&fo14::funct(t0,t1,t2)&&of::funct(t0,t1,t2));
	}
	static constexpr bool funct(const el_t & t0,const el_t & t1,const el_t & t2,const el_t & t3) {
		return (fo04::funct(t0,t1,t2,t3)&&fo14::funct(t0,t1,t2,t3)&&fo24::funct(t0,t1,t2,t3)&&of::funct(t0,t1,t2,t3));
	}
	static constexpr bool funct(const el_t & t0,const el_t & t1,const el_t & t2,const el_t & t3,const el_t & t4) {
		return (fo04::funct(t0,t1,t2,t3,t4)&&fo14::funct(t0,t1,t2,t3,t4)&&fo24::funct(t0,t1,t2,t3,t4)&&fo34::funct(t0,t1,t2,t3,t4)&&of::funct(t0,t1,t2,t3,t4));
	}
	static constexpr bool funct(const el_t & t0,const el_t & t1,const el_t & t2,const el_t & t3,const el_t & t4,const el_t & t5) {
		return (fo04::funct(t0,t1,t2,t3,t4)&&fo14::funct(t0,t1,t2,t3,t4)&&fo24::funct(t0,t1,t2,t3,t4)&&fo34::funct(t0,t1,t2,t3,t4)&&of::funct(t0,t1,t2,t3,t4));
	}
	static constexpr bool funct(const el_t & t0,const el_t & t1,const el_t & t2,const el_t & t3,const el_t & t4,const el_t & t5,const el_t & t6) {
		return (fo04::funct(t0,t1,t2,t3,t4)&&fo14::funct(t0,t1,t2,t3,t4)&&fo24::funct(t0,t1,t2,t3,t4)&&fo34::funct(t0,t1,t2,t3,t4)&&of::funct(t0,t1,t2,t3,t4));
	}

};
template<group_name gn,typename UIntType,UIntType N0,UIntType ... Ns>
struct exactly_diffs_firsts<5,magma_t,gn,UIntType,N0,Ns...> {
	using el_t = magma_t<gn,UIntType,N0,Ns...>;
	using of = all_firsts_neq_id<5,magma_t,gn,UIntType,N0,Ns...>;
	
	using fo05 = all_firsts_N_different_from_I<0,5,magma_t,gn,UIntType,N0,Ns...>;
	using fo15 = all_firsts_N_different_from_I<1,5,magma_t,gn,UIntType,N0,Ns...>;
	using fo25 = all_firsts_N_different_from_I<2,5,magma_t,gn,UIntType,N0,Ns...>;
	using fo35 = all_firsts_N_different_from_I<3,5,magma_t,gn,UIntType,N0,Ns...>;
	using fo45 = all_firsts_N_different_from_I<4,5,magma_t,gn,UIntType,N0,Ns...>;
	
	static constexpr bool funct(const el_t & t0) {
		return of::funct(t0);
	}
	static constexpr bool funct(const el_t & t0,const el_t & t1) {
		return (fo05::funct(t0,t1)&&of::funct(t0,t1));
	}
	static constexpr bool funct(const el_t & t0,const el_t & t1,const el_t & t2) {
		return (fo05::funct(t0,t1,t2)&&fo15::funct(t0,t1,t2)&&of::funct(t0,t1,t2));
	}
	static constexpr bool funct(const el_t & t0,const el_t & t1,const el_t & t2,const el_t & t3) {
		return (fo05::funct(t0,t1,t2,t3)&&fo15::funct(t0,t1,t2,t3)&&fo25::funct(t0,t1,t2,t3)&&of::funct(t0,t1,t2,t3));
	}
	static constexpr bool funct(const el_t & t0,const el_t & t1,const el_t & t2,const el_t & t3,const el_t & t4) {
		return (fo05::funct(t0,t1,t2,t3,t4)&&fo15::funct(t0,t1,t2,t3,t4)&&fo25::funct(t0,t1,t2,t3,t4)&&fo35::funct(t0,t1,t2,t3,t4)&&of::funct(t0,t1,t2,t3,t4));
	}
	static constexpr bool funct(const el_t & t0,const el_t & t1,const el_t & t2,const el_t & t3,const el_t & t4,const el_t & t5) {
		return (fo05::funct(t0,t1,t2,t3,t4,t5)&&fo15::funct(t0,t1,t2,t3,t4,t5)&&fo25::funct(t0,t1,t2,t3,t4,t5)&&fo35::funct(t0,t1,t2,t3,t4,t5)&&fo45::funct(t0,t1,t2,t3,t4,t5)&&of::funct(t0,t1,t2,t3,t4,t5));
	}
	static constexpr bool funct(const el_t & t0,const el_t & t1,const el_t & t2,const el_t & t3,const el_t & t4,const el_t & t5,const el_t & t6) {
		return (fo05::funct(t0,t1,t2,t3,t4,t5)&&fo15::funct(t0,t1,t2,t3,t4,t5)&&fo25::funct(t0,t1,t2,t3,t4,t5)&&fo35::funct(t0,t1,t2,t3,t4,t5)&&fo45::funct(t0,t1,t2,t3,t4,t5)&&of::funct(t0,t1,t2,t3,t4,t5));
	}
};
template<group_name gn,typename UIntType,UIntType N0,UIntType ... Ns>
struct exactly_diffs_firsts<6,magma_t,gn,UIntType,N0,Ns...> {
	using el_t = magma_t<gn,UIntType,N0,Ns...>;
	
	using of = all_firsts_neq_id<6,magma_t,gn,UIntType,N0,Ns...>;
		
	using fo06 = all_firsts_N_different_from_I<0,6,magma_t,gn,UIntType,N0,Ns...>;
	using fo16 = all_firsts_N_different_from_I<1,6,magma_t,gn,UIntType,N0,Ns...>;
	using fo26 = all_firsts_N_different_from_I<2,6,magma_t,gn,UIntType,N0,Ns...>;
	using fo36 = all_firsts_N_different_from_I<3,6,magma_t,gn,UIntType,N0,Ns...>;
	using fo46 = all_firsts_N_different_from_I<4,6,magma_t,gn,UIntType,N0,Ns...>;
	using fo56 = all_firsts_N_different_from_I<5,6,magma_t,gn,UIntType,N0,Ns...>;
	
	static constexpr bool funct(const el_t & t0) {
		return of::funct(t0);
	}
	static constexpr bool funct(const el_t & t0,const el_t & t1) {
		return (fo06::funct(t0,t1)&&of::funct(t0,t1));
	}
	static constexpr bool funct(const el_t & t0,const el_t & t1,const el_t & t2) {
		return (fo06::funct(t0,t1,t2)&&fo16::funct(t0,t1,t2)&&of::funct(t0,t1,t2));
	}
	static constexpr bool funct(const el_t & t0,const el_t & t1,const el_t & t2,const el_t & t3) {
		return (fo06::funct(t0,t1,t2,t3)&&fo16::funct(t0,t1,t2,t3)&&fo26(t0,t1,t2,t3)&&of::funct(t0,t1,t2,t3));
	}
	static constexpr bool funct(const el_t & t0,const el_t & t1,const el_t & t2,const el_t & t3,const el_t & t4) {
		return (fo06::funct(t0,t1,t2,t3,t4)&&fo16::funct(t0,t1,t2,t3,t4)&&fo26(t0,t1,t2,t3,t4)&&fo36::funct(t0,t1,t2,t3,t4)&&of::funct(t0,t1,t2,t3,t4));
	}
	static constexpr bool funct(const el_t & t0,const el_t & t1,const el_t & t2,const el_t & t3,const el_t & t4,const el_t & t5) {
		return (fo06::funct(t0,t1,t2,t3,t4,t5)&&fo16::funct(t0,t1,t2,t3,t4,t5)&&fo26(t0,t1,t2,t3,t4,t5)&&fo36::funct(t0,t1,t2,t3,t4,t5)&&fo46::funct(t0,t1,t2,t3,t4,t5)&&of::funct(t0,t1,t2,t3,t4,t5));
	}
	static constexpr bool funct(const el_t & t0,const el_t & t1,const el_t & t2,const el_t & t3,const el_t & t4,const el_t & t5,const el_t & t6) {
		return (fo06::funct(t0,t1,t2,t3,t4,t5,t6)&&fo16::funct(t0,t1,t2,t3,t4,t5,t6)&&fo26(t0,t1,t2,t3,t4,t5,t6)&&fo36::funct(t0,t1,t2,t3,t4,t5,t6)&&fo46::funct(t0,t1,t2,t3,t4,t5,t6)&&fo56::funct(t0,t1,t2,t3,t4,t5,t6)&&of::funct(t0,t1,t2,t3,t4,t5,t6));
	}
};
}

template<size_t I,template<group_name,typename K_t,K_t,K_t...> class TT,group_name gn,typename UIntType,UIntType N0,UIntType ... Ns>
struct exactly;
template<group_name gn,typename UIntType,UIntType N0,UIntType ... Ns>
struct exactly<6,magma_t,gn,UIntType,N0,Ns...> {
	using el_t = magma_t<gn,UIntType,N0,Ns...>;
	using firsts = details::exactly_diffs_firsts<6,magma_t,gn,UIntType,N0,Ns...>;
	
	static constexpr bool funct(const el_t & t0) {
		return firsts::funct(t0);
	}
	static constexpr bool funct(const el_t & t0,const el_t & t1) {
		return firsts::funct(t0,t1);
	}
	static constexpr bool funct(const el_t & t0,const el_t & t1,const el_t & t2) {
		return firsts::funct(t0,t1,t2);
	}
	static constexpr bool funct(const el_t & t0,const el_t & t1,const el_t & t2,const el_t & t3) {
		return firsts::funct(t0,t1,t2,t3);
	}
	static constexpr bool funct(const el_t & t0,const el_t & t1,const el_t & t2,const el_t & t3,const el_t & t4) {
		return firsts::funct(t0,t1,t2,t3,t4);
	}
	static constexpr bool funct(const el_t & t0,const el_t & t1,const el_t & t2,const el_t & t3,const el_t & t4,const el_t & t5) {
		return firsts::funct(t0,t1,t2,t3,t4,t5);
	}
	static constexpr bool funct(const el_t & t0,const el_t & t1,const el_t & t2,const el_t & t3,const el_t & t4,const el_t & t5,const el_t & t6) {
		return firsts::funct(t0,t1,t2,t3,t4,t5,t6);
	}
};
template<group_name gn,typename UIntType,UIntType N0,UIntType ... Ns>
struct exactly<5,magma_t,gn,UIntType,N0,Ns...> {
	using el_t = magma_t<gn,UIntType,N0,Ns...>;
	using firsts = details::exactly_diffs_firsts<5,magma_t,gn,UIntType,N0,Ns...>;
	using latters = details::invalid_the_latters<5,magma_t,gn,UIntType,N0,Ns...>;
	
	static constexpr bool funct(const el_t & t0) {
		return (firsts::funct(t0)&&latters::funct(t0));
	}
	static constexpr bool funct(const el_t & t0,const el_t & t1) {
		return (firsts::funct(t0,t1)&&latters::funct(t0,t1));
	}
	static constexpr bool funct(const el_t & t0,const el_t & t1,const el_t & t2) {
		return (firsts::funct(t0,t1,t2)&&latters::funct(t0,t1,t2));
	}
	static constexpr bool funct(const el_t & t0,const el_t & t1,const el_t & t2,const el_t & t3) {
		return (firsts::funct(t0,t1,t2,t3)&&latters::funct(t0,t1,t2,t3));
	}
	static constexpr bool funct(const el_t & t0,const el_t & t1,const el_t & t2,const el_t & t3,const el_t & t4) {
		return (firsts::funct(t0,t1,t2,t3,t4)&&latters::funct(t0,t1,t2,t3,t4));
	}
	static constexpr bool funct(const el_t & t0,const el_t & t1,const el_t & t2,const el_t & t3,const el_t & t4,const el_t & t5) {
		return (firsts::funct(t0,t1,t2,t3,t4,t5)&&latters::funct(t0,t1,t2,t3,t4,t5));
	}
	static constexpr bool funct(const el_t & t0,const el_t & t1,const el_t & t2,const el_t & t3,const el_t & t4,const el_t & t5,const el_t & t6) {
		return (firsts::funct(t0,t1,t2,t3,t4,t5,t6)&&latters::funct(t0,t1,t2,t3,t4,t5,t6));
	}
};
template<group_name gn,typename UIntType,UIntType N0,UIntType ... Ns>
struct exactly<4,magma_t,gn,UIntType,N0,Ns...> {
	using el_t = magma_t<gn,uint8_t,N0,Ns...>;
	using firsts = details::exactly_diffs_firsts<4,magma_t,gn,UIntType,N0,Ns...>;
	using latters = details::invalid_the_latters<4,magma_t,gn,UIntType,N0,Ns...>;
	
	static constexpr bool funct(const el_t & t0) {
		return (firsts::funct(t0)&&latters::funct(t0));
	}
	static constexpr bool funct(const el_t & t0,const el_t & t1) {
		return (firsts::funct(t0,t1)&&latters::funct(t0,t1));
	}
	static constexpr bool funct(const el_t & t0,const el_t & t1,const el_t & t2) {
		return (firsts::funct(t0,t1,t2)&&latters::funct(t0,t1,t2));
	}
	static constexpr bool funct(const el_t & t0,const el_t & t1,const el_t & t2,const el_t & t3) {
		return (firsts::funct(t0,t1,t2,t3)&&latters::funct(t0,t1,t2,t3));
	}
	static constexpr bool funct(const el_t & t0,const el_t & t1,const el_t & t2,const el_t & t3,const el_t & t4) {
		return (firsts::funct(t0,t1,t2,t3,t4)&&latters::funct(t0,t1,t2,t3,t4));
	}
	static constexpr bool funct(const el_t & t0,const el_t & t1,const el_t & t2,const el_t & t3,const el_t & t4,const el_t & t5) {
		return (firsts::funct(t0,t1,t2,t3,t4,t5)&&latters::funct(t0,t1,t2,t3,t4,t5));
	}
	static constexpr bool funct(const el_t & t0,const el_t & t1,const el_t & t2,const el_t & t3,const el_t & t4,const el_t & t5,const el_t & t6) {
		return (firsts::funct(t0,t1,t2,t3,t4,t5,t6)&&latters::funct(t0,t1,t2,t3,t4,t5,t6));
	}
};
template<group_name gn,typename UIntType,UIntType N0,UIntType ... Ns>
struct exactly<3,magma_t,gn,UIntType,N0,Ns...> {
	using el_t = magma_t<gn,UIntType,N0,Ns...>;
	using firsts = details::exactly_diffs_firsts<3,magma_t,gn,UIntType,N0,Ns...>;
	using latters = details::invalid_the_latters<3,magma_t,gn,UIntType,N0,Ns...>;
	
	static constexpr bool funct(const el_t & t0) {
		return (firsts::funct(t0)&&latters::funct(t0));
	}
	static constexpr bool funct(const el_t & t0,const el_t & t1) {
		return (firsts::funct(t0,t1)&&latters::funct(t0,t1));
	}
	static constexpr bool funct(const el_t & t0,const el_t & t1,const el_t & t2) {
		return (firsts::funct(t0,t1,t2)&&latters::funct(t0,t1,t2));
	}
	static constexpr bool funct(const el_t & t0,const el_t & t1,const el_t & t2,const el_t & t3) {
		return (firsts::funct(t0,t1,t2,t3)&&latters::funct(t0,t1,t2,t3));
	}
	static constexpr bool funct(const el_t & t0,const el_t & t1,const el_t & t2,const el_t & t3,const el_t & t4) {
		return (firsts::funct(t0,t1,t2,t3,t4)&&latters::funct(t0,t1,t2,t3,t4));
	}
	static constexpr bool funct(const el_t & t0,const el_t & t1,const el_t & t2,const el_t & t3,const el_t & t4,const el_t & t5) {
		return (firsts::funct(t0,t1,t2,t3,t4,t5)&&latters::funct(t0,t1,t2,t3,t4,t5));
	}
	static constexpr bool funct(const el_t & t0,const el_t & t1,const el_t & t2,const el_t & t3,const el_t & t4,const el_t & t5,const el_t & t6) {
		return (firsts::funct(t0,t1,t2,t3,t4,t5,t6)&&latters::funct(t0,t1,t2,t3,t4,t5,t6));
	}
};
template<group_name gn,typename UIntType,UIntType N0,UIntType ... Ns>
struct exactly<2,magma_t,gn,UIntType,N0,Ns...> {
	using el_t = magma_t<gn,UIntType,N0,Ns...>;
	using firsts = details::exactly_diffs_firsts<2,magma_t,gn,UIntType,N0,Ns...>;
	using latters = details::invalid_the_latters<2,magma_t,gn,UIntType,N0,Ns...>;
	
	static constexpr bool funct(const el_t & t0) {
		return (firsts::funct(t0)&&latters::funct(t0));
	}
	static constexpr bool funct(const el_t & t0,const el_t & t1) {
		return (firsts::funct(t0,t1)&&latters::funct(t0,t1));
	}
	static constexpr bool funct(const el_t & t0,const el_t & t1,const el_t & t2) {
		return (firsts::funct(t0,t1,t2)&&latters::funct(t0,t1,t2));
	}
	static constexpr bool funct(const el_t & t0,const el_t & t1,const el_t & t2,const el_t & t3) {
		return (firsts::funct(t0,t1,t2,t3)&&latters::funct(t0,t1,t2,t3));
	}
	static constexpr bool funct(const el_t & t0,const el_t & t1,const el_t & t2,const el_t & t3,const el_t & t4) {
		return (firsts::funct(t0,t1,t2,t3,t4)&&latters::funct(t0,t1,t2,t3,t4));
	}
	static constexpr bool funct(const el_t & t0,const el_t & t1,const el_t & t2,const el_t & t3,const el_t & t4,const el_t & t5) {
		return (firsts::funct(t0,t1,t2,t3,t4,t5)&&latters::funct(t0,t1,t2,t3,t4,t5));
	}
	static constexpr bool funct(const el_t & t0,const el_t & t1,const el_t & t2,const el_t & t3,const el_t & t4,const el_t & t5,const el_t & t6) {
		return (firsts::funct(t0,t1,t2,t3,t4,t5,t6)&&latters::funct(t0,t1,t2,t3,t4,t5,t6));
	}
};
template<group_name gn,typename UIntType,UIntType N0,UIntType ... Ns>
struct exactly<1,magma_t,gn,UIntType,N0,Ns...> {
	using el_t = magma_t<gn,uint8_t,N0,Ns...>;
	using firsts = details::exactly_diffs_firsts<1,magma_t,gn,UIntType,N0,Ns...>;
	using latters = details::invalid_the_latters<1,magma_t,gn,UIntType,N0,Ns...>;
	
	static constexpr bool funct(const el_t & t0) {
		return (firsts::funct(t0)&&latters::funct(t0));
	}
	static constexpr bool funct(const el_t & t0,const el_t & t1) {
		return (firsts::funct(t0,t1)&&latters::funct(t0,t1));
	}
	static constexpr bool funct(const el_t & t0,const el_t & t1,const el_t & t2) {
		return (firsts::funct(t0,t1,t2)&&latters::funct(t0,t1,t2));
	}
	static constexpr bool funct(const el_t & t0,const el_t & t1,const el_t & t2,const el_t & t3) {
		return (firsts::funct(t0,t1,t2,t3)&&latters::funct(t0,t1,t2,t3));
	}
	static constexpr bool funct(const el_t & t0,const el_t & t1,const el_t & t2,const el_t & t3,const el_t & t4) {
		return (firsts::funct(t0,t1,t2,t3,t4)&&latters::funct(t0,t1,t2,t3,t4));
	}
	static constexpr bool funct(const el_t & t0,const el_t & t1,const el_t & t2,const el_t & t3,const el_t & t4,const el_t & t5) {
		return (firsts::funct(t0,t1,t2,t3,t4,t5)&&latters::funct(t0,t1,t2,t3,t4,t5));
	}
	static constexpr bool funct(const el_t & t0,const el_t & t1,const el_t & t2,const el_t & t3,const el_t & t4,const el_t & t5,const el_t & t6) {
		return (firsts::funct(t0,t1,t2,t3,t4,t5,t6)&&latters::funct(t0,t1,t2,t3,t4,t5,t6));
	}
};
template<group_name gn,typename UIntType,UIntType N0,UIntType ... Ns>
struct exactly<0,magma_t,gn,UIntType,N0,Ns...> {
	using el_t = magma_t<gn,uint8_t,N0,Ns...>;
	using firsts = details::exists_eq_id<0,magma_t,gn,UIntType,N0,Ns...>;
	using latters = details::invalid_the_latters<0,magma_t,gn,UIntType,N0,Ns...>;
	
	static constexpr bool funct(const el_t & t0) {
		return (firsts::funct(t0)&&latters::funct(t0));
	}
	static constexpr bool funct(const el_t & t0,const el_t & t1) {
		return (firsts::funct(t0,t1)&&latters::funct(t0,t1));
	}
	static constexpr bool funct(const el_t & t0,const el_t & t1,const el_t & t2) {
		return (firsts::funct(t0,t1,t2)&&latters::funct(t0,t1,t2));
	}
	static constexpr bool funct(const el_t & t0,const el_t & t1,const el_t & t2,const el_t & t3) {
		return (firsts::funct(t0,t1,t2,t3)&&latters::funct(t0,t1,t2,t3));
	}
	static constexpr bool funct(const el_t & t0,const el_t & t1,const el_t & t2,const el_t & t3,const el_t & t4) {
		return (firsts::funct(t0,t1,t2,t3,t4)&&latters::funct(t0,t1,t2,t3,t4));
	}
	static constexpr bool funct(const el_t & t0,const el_t & t1,const el_t & t2,const el_t & t3,const el_t & t4,const el_t & t5) {
		return (firsts::funct(t0,t1,t2,t3,t4,t5)&&latters::funct(t0,t1,t2,t3,t4,t5));
	}
	static constexpr bool funct(const el_t & t0,const el_t & t1,const el_t & t2,const el_t & t3,const el_t & t4,const el_t & t5,const el_t & t6) {
		return (firsts::funct(t0,t1,t2,t3,t4,t5,t6)&&latters::funct(t0,t1,t2,t3,t4,t5,t6));
	}
};
}






#endif // ARGS_TRAITS_OLD_STYLE_HPP_INCLUDED