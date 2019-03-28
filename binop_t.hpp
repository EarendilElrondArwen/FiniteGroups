/*
 * binop_t.hpp
 *
 * Copyright 2018 Julian Calderon Almendros
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

#ifndef ACTION_OF_A_GROUP_OVER_OTHER_GROUP_HPP_INCLUDED
#define ACTION_OF_A_GROUP_OVER_OTHER_GROUP_HPP_INCLUDED

#include "modint_cartprod_t.hpp"
#include <utility>
#include <tuple>

namespace tfg {
using std::get;
using std::pair;
template<typename T>
using Ints_pair = pair<T,T>;

template<group_name gn,typename UIntType,UIntType Ns_head,UIntType ... Ns_tail>
struct binop_t{
	using type = void;
	using SIntType = signed_for_unsigned_t<UIntType>;
	using LUIntType = next_int_t<unsigned_for_signed_t<SIntType>>;
	using UIntType_pair = Ints_pair<UIntType>;
	using modint_cartprod_t = modint_cartprod_t<UIntType,Ns_head,Ns_tail...>;///!!!
	using base_t = typename modint_cartprod_t::base_t;
	template<UIntType k>
	using modint_mod = modint_t<UIntType,k>;
	template<size_t K>
	using modint_idx = modint_t<UIntType,get<K>(modint_cartprod_t::mod_tup())>;
	inline static constexpr UIntType max_mod() {return modint_cartprod_t::max_mod();}
	inline static constexpr UIntType min_mod() {return modint_cartprod_t::min_mod();}
	inline static constexpr UIntType dim() {return modint_cartprod_t::dim();}
	inline static constexpr LUIntType card() {return modint_cartprod_t::card();}
	
};

template<typename UIntType,UIntType N>
struct binop_t<group_name::C,UIntType,N>{
	using type = binop_t;
	using SIntType = signed_for_unsigned_t<UIntType>;
	using LUIntType = next_int_t<unsigned_for_signed_t<SIntType>>;
	using UIntType_pair = Ints_pair<UIntType>;
	using modint_cartprod_t = modint_cartprod_t<UIntType,N>;///!!!
	using base_t = typename modint_cartprod_t::base_t;
	template<UIntType k>
	using modint_mod = modint_t<UIntType,k>;
	template<size_t K>
	using modint_idx = modint_t<UIntType,get<K>(modint_cartprod_t::mod_tup())>;
	inline static constexpr UIntType max_mod() {return N;}
	inline static constexpr UIntType min_mod() {return N;}
	inline static constexpr UIntType dim() {return 1;}
	inline static constexpr LUIntType card() {return N;}
	
	static constexpr
		modint_cartprod_t direct_product(
			modint_cartprod_t a,
			modint_cartprod_t b
		)  {
		const modint_cartprod_t result{a+b};
		return result;
	}
	
	static constexpr
		modint_cartprod_t semi_direct_product(
			modint_cartprod_t a,
			modint_cartprod_t b
		)  {
		return direct_product(a,b);
	}

	static constexpr
		modint_cartprod_t gr_bop(
			modint_cartprod_t a,
			modint_cartprod_t b
		)  {
		return direct_product(a,b);
	}
};

template<typename UIntType,UIntType N2,UIntType N1>
struct binop_t<group_name::PD_Cyc,UIntType,N2,N1>{
	using type = binop_t;
	using SIntType = signed_for_unsigned_t<UIntType>;
	using LUIntType = next_int_t<unsigned_for_signed_t<SIntType>>;
	using UIntType_pair = Ints_pair<UIntType>;
	using modint_cartprod_t = modint_cartprod_t<UIntType,N2,N1>;///!!!
	using base_t = typename modint_cartprod_t::base_t;
	template<UIntType k>
	using modint_mod = modint_t<UIntType,k>;
	template<size_t K>
	using modint_idx = modint_t<UIntType,get<K>(modint_cartprod_t::mod_tup())>;
	inline static constexpr UIntType max_mod() {return modint_cartprod_t::max_mod();}
	inline static constexpr UIntType min_mod() {return modint_cartprod_t::min_mod();}
	inline static constexpr UIntType dim() {return modint_cartprod_t::dim();}
	inline static constexpr LUIntType card() {return modint_cartprod_t::card();}
	
	static constexpr
		modint_cartprod_t direct_product(
			modint_cartprod_t a,
			modint_cartprod_t b
		) {
		const modint_cartprod_t result{a+b};
		return result;
	}
	
	static constexpr
		modint_cartprod_t semi_direct_product(
			modint_cartprod_t a,
			modint_cartprod_t b
		)  {
		return direct_product(a,b);
	}
	
	static constexpr
		modint_cartprod_t gr_bop(
			modint_cartprod_t a,
			modint_cartprod_t b
		) {
		return direct_product(a,b);
	}
};

template<>
struct binop_t<group_name::Q,uint,2_u8,4_u8>{
	using type = binop_t;
	using UIntType = uint;
	using SIntType = signed_for_unsigned_t<uint>;
	using LUIntType = next_int_t<unsigned_for_signed_t<SIntType>>;
	using UIntType_pair = Ints_pair<UIntType>;;
	using modint_cartprod_t = modint_cartprod_t<UIntType,2_u8,4_u8>;///!!!
	using base_t = typename modint_cartprod_t::base_t;
	template<UIntType k>
	using modint_mod = modint_t<UIntType,k>;
	template<size_t K>
	using modint_idx = modint_t<UIntType,get<K>(modint_cartprod_t::mod_tup())>;
	inline static constexpr UIntType max_mod() {return modint_cartprod_t::max_mod();}
	inline static constexpr UIntType min_mod() {return modint_cartprod_t::min_mod();}
	inline static constexpr UIntType dim() {return modint_cartprod_t::dim();}
	inline static constexpr LUIntType card() {return modint_cartprod_t::card();}

	static constexpr
		modint_cartprod_t Q_product(
			modint_cartprod_t IK,
			modint_cartprod_t JL
		) {
		UIntType i{IK.get_int<0>()};
		UIntType k{IK.get_int<1>()};
		UIntType j{JL.get_int<0>()};
		UIntType l{JL.get_int<1>()};
		
		if (((i%2)==0)and((j%2)==0)){
			return modint_cartprod_t{
				(i+j)%2 , (k+l)%4
			};
		}
		else if (((i%2)==0)and((j%2)==1)) {
			return modint_cartprod_t{
				(i+j)%2 , (3*k+l)%4
			};
		}
		else if (((i%2)==1)and((j%2)==0)) {
			return modint_cartprod_t{
				(i+j)%2 , (k+l)%4
			};
		}
		else {
			return modint_cartprod_t{
				(i+j)%2 , (3*k+l+2)%4
			};
		}
	}
	
	inline static constexpr
	modint_cartprod_t 
	direct_product(
		modint_cartprod_t a, modint_cartprod_t b
	) 
	{
		const modint_cartprod_t result{a+b};
		return result;
	}
	
	inline static constexpr
	modint_cartprod_t gr_bop(
		modint_cartprod_t a,
		modint_cartprod_t b
		) {
		return Q_product(a,b);
	}

	inline static constexpr
	modint_cartprod_t 
	semi_direct_product(
		modint_cartprod_t a,
		modint_cartprod_t b
		)  {
		return direct_product(a,b);
	}
};

template<>
struct binop_t<group_name::C3__C4,uint,4_u8,3_u8> {
	using type = binop_t;
	using UIntType = uint;
	using SIntType = signed_for_unsigned_t<UIntType>;
	using LUIntType = next_int_t<unsigned_for_signed_t<SIntType>>;
	using UIntType_pair = Ints_pair<UIntType>;
	using modint_cartprod_t = modint_cartprod_t<UIntType,3_u8,4_u8>;
	using base_t = typename modint_cartprod_t::base_t;
	template<UIntType k>
	using modint_mod = modint_t<UIntType,k>;
	template<size_t K>
	using modint_idx = modint_t<UIntType,get<K>(modint_cartprod_t::mod_tup())>;
	inline static constexpr UIntType max_mod() {return modint_cartprod_t::max_mod();}
	inline static constexpr UIntType min_mod() {return modint_cartprod_t::min_mod();}
	inline static constexpr UIntType dim() {return modint_cartprod_t::dim();}
	inline static constexpr LUIntType card() {return modint_cartprod_t::card();}


	static constexpr
		modint_cartprod_t C3__C4_product(
			modint_cartprod_t IJ,
			modint_cartprod_t KM
		) {
		UIntType k{KM.get_int<0>()};
		UIntType j{IJ.get_int<1>()};
		modint_cartprod_t resultado{IJ+KM};
		if ((k%4==1)||(k%4==3)){
			resultado.get_modint<1>()+=modint_idx<1>(j);
		}
		return resultado;
	}
	
	inline static constexpr 
	modint_cartprod_t 
	direct_product(
		modint_cartprod_t a, modint_cartprod_t b
	)	{
		const modint_cartprod_t result{a+b};
		return result;
	}

	static constexpr
		modint_cartprod_t semi_direct_product(
			modint_cartprod_t a,
			modint_cartprod_t b
		)  {
		return direct_product(a,b);
	}
		
	static constexpr
		modint_cartprod_t gr_bop(
			modint_cartprod_t a,
			modint_cartprod_t b
		) {
		return C3__C4_product(a,b);
	}
};

template<uint N3,uint N2,uint N1>
struct binop_t<group_name::PD_Cyc,uint,N3,N2,N1>{
	using type = binop_t;
	using UIntType = uint;
	using SIntType = signed_for_unsigned_t<UIntType>;
	using LUIntType = next_int_t<unsigned_for_signed_t<SIntType>>;
	using UIntType_pair = Ints_pair<UIntType>;
	using modint_cartprod_t = modint_cartprod_t<UIntType,N3,N2,N1>;
	using base_t = typename modint_cartprod_t::base_t;
	template<UIntType k>
	using modint_mod = modint_t<UIntType,k>;
	template<size_t K>
	using modint_idx = modint_t<UIntType,get<K>(modint_cartprod_t::mod_tup())>;
	inline static constexpr UIntType max_mod() {return modint_cartprod_t::max_mod();}
	inline static constexpr UIntType min_mod() {return modint_cartprod_t::min_mod();}
	inline static constexpr UIntType dim() {return modint_cartprod_t::dim();}
	inline static constexpr LUIntType card() {return modint_cartprod_t::card();}
	
	static constexpr
		modint_cartprod_t direct_product(
			modint_cartprod_t a,
			modint_cartprod_t b
		) {
		const modint_cartprod_t result{a+b};
		return result;
	}
	
	static constexpr
		modint_cartprod_t semi_direct_product(
			modint_cartprod_t a,
			modint_cartprod_t b
		) {
		return direct_product(a,b);
	}
	
	static constexpr
		modint_cartprod_t gr_bop(
			modint_cartprod_t a,
			modint_cartprod_t b
		) {
		return direct_product(a,b);
	}
};

template<>
struct binop_t<group_name::C3__C2_2,uint,2_u8,2_u8,3_u8> {
	using type = binop_t;
	using UIntType = uint;
	using SIntType = signed_for_unsigned_t<UIntType>;
	using LUIntType = next_int_t<unsigned_for_signed_t<SIntType>>;
	using UIntType_pair = Ints_pair<UIntType>;
	using modint_cartprod_t = modint_cartprod_t<UIntType,2_u8,2_u8,3_u8>;
	using base_t = typename modint_cartprod_t::base_t;
	template<UIntType k>
	using modint_mod = modint_t<UIntType,k>;
	template<size_t K>
	using modint_idx = modint_t<UIntType,get<K>(modint_cartprod_t::mod_tup())>;
	inline static constexpr UIntType max_mod() {return modint_cartprod_t::max_mod();}
	inline static constexpr UIntType min_mod() {return modint_cartprod_t::min_mod();}
	inline static constexpr UIntType dim() {return modint_cartprod_t::dim();}
	inline static constexpr LUIntType card() {return modint_cartprod_t::card();}
	
	static constexpr
		modint_cartprod_t C3__C2_2_product(
			modint_cartprod_t IJK,
			modint_cartprod_t LMN
		) {
		UIntType i{IJK.get_int<0>()};
		UIntType j{IJK.get_int<1>()};
		UIntType k{IJK.get_int<2>()};
		UIntType l{LMN.get_int<0>()};
		UIntType m{LMN.get_int<1>()};
		UIntType n{LMN.get_int<2>()};
		
		if ((l%2)==(m%2)){
			return modint_cartprod_t{
				(i+l)%2 , (j+m)%2 , (k+n)%3
			};
		}
		else {
			return modint_cartprod_t{
				(i+l)%2 , (j+m)%2 ,  (3-k+n)%3
			};
		}
	}

	static constexpr
	modint_cartprod_t direct_product(
		modint_cartprod_t a,
		modint_cartprod_t b	
	)  {
		const modint_cartprod_t result{a+b};
		return result;
	}

	static constexpr
	modint_cartprod_t semi_direct_product(
						modint_cartprod_t a,
						modint_cartprod_t b) {
		return direct_product(a,b);
	}

	static constexpr
		modint_cartprod_t gr_bop(
			modint_cartprod_t a,
			modint_cartprod_t b
		) {
		return C3__C2_2_product(a,b);
	}
};


template<>
struct binop_t<group_name::C2_2__C3,uint,2_u8,2_u8,3_u8> {
	using type = binop_t;
	using UIntType = uint;
	using SIntType = signed_for_unsigned_t<UIntType>;
	using LUIntType = next_int_t<unsigned_for_signed_t<SIntType>>;
	using UIntType_pair = Ints_pair<UIntType>;
	using modint_cartprod_t = modint_cartprod_t<UIntType,2_u8,2_u8,3_u8>;
	using base_t = typename modint_cartprod_t::base_t;
	template<UIntType k>
	using modint_mod = modint_t<UIntType,k>;
	template<size_t K>
	using modint_idx = modint_t<UIntType,get<K>(modint_cartprod_t::mod_tup())>;
	inline static constexpr UIntType max_mod() {return modint_cartprod_t::max_mod();}
	inline static constexpr UIntType min_mod() {return modint_cartprod_t::min_mod();}
	inline static constexpr UIntType dim() {return modint_cartprod_t::dim();}
	inline static constexpr LUIntType card() {return modint_cartprod_t::card();}
	
	static constexpr
	modint_cartprod_t 
	phi_action(
		modint_cartprod_t IJK,modint_cartprod_t LMN
	) {
		const UIntType k{IJK.get_int<2>()};
		const UIntType l{LMN.get_int<0>()};
		const UIntType m{LMN.get_int<1>()};
		const UIntType n{LMN.get_int<2>()};
		
		if (k%3==0) {
			const modint_cartprod_t R{
				l,m,n
			};
			return R;
		}
		else if (k%3==1){
			const modint_cartprod_t R{
				l+m , l , n
			};
			return R;
		}
		else {
			const modint_cartprod_t R{
				m , l+m , n
			};
			return R;
		}
	}

	static constexpr
	modint_cartprod_t zeta_action(
		modint_cartprod_t IJK,modint_cartprod_t LMN
	) {
		const UIntType i{IJK.get_int<0>()};
		const UIntType j{IJK.get_int<1>()};
		const UIntType k{IJK.get_int<2>()};
		
		const UIntType l{LMN.get_int<0>()};
		const UIntType m{LMN.get_int<1>()};
		
		if ((l%2==0)&&(m%2==0)) {
			const modint_cartprod_t R{
				i , j , k
			};
			return R;
		}
		else if ((l%2==0)&&(m%2==1)) {
			const modint_cartprod_t R{
				i , j+1 , k
			};
			return R;
		}
		else if ((l%2==1)&&(m%2==0)) {
			const modint_cartprod_t R{
				i+1 , j , k
			};
			return R;
		}
		else {
			const modint_cartprod_t R{
				i+1 , j+1 , k
			};
			return R;
		}
	}

	static constexpr
	modint_cartprod_t C2_2__C3_product(
		modint_cartprod_t IJK,modint_cartprod_t LMN
	) {
		const UIntType k{IJK.get_int<2>()};
		
		const UIntType l{LMN.get_int<0>()};
		const UIntType m{LMN.get_int<1>()};
		
		if(((l%2==0)&&(m%2==0))||(k%3==0))
			return (IJK+LMN);

		const modint_cartprod_t
			LMN_por_zeta{zeta_action(IJK,LMN)};
		const modint_cartprod_t
			IJK_por_phi{phi_action(IJK,LMN)};
		return (IJK_por_phi+LMN_por_zeta);
	}

	static constexpr
	modint_cartprod_t direct_product(
		modint_cartprod_t a,modint_cartprod_t b
	) {
		const modint_cartprod_t result {a+b};
		return result;
	}
	
	static constexpr
	modint_cartprod_t semi_direct_product(
		modint_cartprod_t a,modint_cartprod_t b
	) {
		return direct_product(a,b);
	}

	static constexpr
	modint_cartprod_t gr_bop(
		modint_cartprod_t a,
		modint_cartprod_t b
	) {
		return C2_2__C3_product(a,b);
	}
};

template<uint N>
struct binop_t<group_name::Dih,uint,2_u8,N> {
	using type = binop_t;
	using UIntType = uint;
	using SIntType = signed_for_unsigned_t<UIntType>;
	using LUIntType = next_int_t<unsigned_for_signed_t<SIntType>>;
	using UIntType_pair = Ints_pair<UIntType>;
	using modint_cartprod_t = modint_cartprod_t<UIntType,2_u8,N>;
	using base_t = typename modint_cartprod_t::base_t;
	template<UIntType k>
	using modint_mod = modint_t<UIntType,k>;
	template<size_t K>
	using modint_idx = modint_t<UIntType,get<K>(modint_cartprod_t::mod_tup())>;
	inline static constexpr UIntType max_mod() {return modint_cartprod_t::max_mod();}
	inline static constexpr UIntType min_mod() {return modint_cartprod_t::min_mod();}
	inline static constexpr UIntType dim() {return modint_cartprod_t::dim();}
	inline static constexpr LUIntType card() {return modint_cartprod_t::card();}
	
	
	static constexpr
	modint_cartprod_t Dih_product (modint_cartprod_t a,modint_cartprod_t b) 
	{
		
		UIntType i = a.get_int<0>();/// Module 2
		const UIntType k {a.get_int<1>()};/// Module N
		
		auto j {b.get_int<0>()};/// Module 2
		const auto m {b.get_int<1>()};/// Module N

		if (j%2_u8==0) {
			const modint_cartprod_t R{i+j,m+k};
			return R;
		} else {
			const modint_cartprod_t R{i+j,m+(N-k)};
			return R;
		}
	}

	static constexpr
	modint_cartprod_t direct_product(
		modint_cartprod_t a,
		modint_cartprod_t b
	) {
		const modint_cartprod_t result{a+b};
		return result;
	}

	static constexpr
	modint_cartprod_t gr_bop (
		modint_cartprod_t a,
		modint_cartprod_t b
	) {
		return Dih_product(a,b);
	}
};


template<uint N>
struct binop_t<group_name::Dic,uint,2_u8,N>
{
	using type = binop_t;
	using UIntType = uint;
	using SIntType = signed_for_unsigned_t<UIntType>;
	using LUIntType = next_int_t<unsigned_for_signed_t<SIntType>>;

	using UIntType_pair =
		typename std::pair<UIntType,UIntType>;
	using modint_cartprod_t =
		modint_cartprod_t<UIntType,2,2,3>;
	
	inline static constexpr UIntType max_mod() {return modint_cartprod_t::max_mod();}
	inline static constexpr UIntType dim() {return modint_cartprod_t::dim();}
	inline static constexpr LUIntType card() {return modint_cartprod_t::card();}

	static_assert(N%2==0);

	static constexpr
	modint_cartprod_t Dic_product(
		modint_cartprod_t a,
		modint_cartprod_t b
	) {
		const UIntType i{a.get_int<0>()};
		const UIntType j{b.get_int<0>()};
		modint_cartprod_t sr{
			binop_t<group_name::Dih,UIntType,2,N>::gr_bop(a,b)
		};
		if((i%2 != 0)||(j%2 != 0)) {
			if ((i%2 ==1)&&( j%2==1)) {
				sr.get_modint<1>() += (N/2);
			}
		}
		return sr;
	}

	static constexpr
	modint_cartprod_t direct_product(
		modint_cartprod_t a,
		modint_cartprod_t b
	) {
		const modint_cartprod_t result{a+b};
		return result;
	}

	static constexpr
	modint_cartprod_t gr_bop(
		modint_cartprod_t a,
		modint_cartprod_t b
	) {
		return Dic_product(a,b);
	}
};

template<typename UIntType,UIntType p,UIntType q>
struct binop_t<group_name::GDih,UIntType,p,q>
{
	using type = binop_t;
	using SIntType = signed_for_unsigned_t<UIntType>;
	using LUIntType = next_int_t<unsigned_for_signed_t<SIntType>>;

	using UIntType_pair =
		typename std::pair<UIntType,UIntType>;
	using modint_cartprod_t =
		modint_cartprod_t<UIntType,p,q>;
	
	inline static constexpr UIntType max_mod() {return modint_cartprod_t::max_mod();}
	inline static constexpr UIntType dim() {return modint_cartprod_t::dim();}
	inline static constexpr LUIntType card() {return modint_cartprod_t::card();}

	static_assert(p>1);
	static_assert(q>1);
	static_assert(p<q);
	static_assert(is_prime(p));
	static_assert(is_prime(q));
	static_assert((q-1)%p==0);
	static constexpr UIntType r = (q-1)/p;
	static_assert(q==r*p+1);
	static constexpr
	UIntType r_(UIntType k) {
		return UIntType(r^(UIntType(k)));
	}

	static constexpr
	modint_cartprod_t GDih_action(
		modint_cartprod_t a,
		modint_cartprod_t b
	) {
		const UIntType i{a.get_int<0>()};
		const UIntType j{a.get_int<1>()};
		
		const UIntType k{b.get_int<0>()};
		const modint_cartprod_t resultado{
			i, r_(k)*j
		};
		return resultado;
	}

	static constexpr
	modint_cartprod_t GDih_product(
		modint_cartprod_t a,
		modint_cartprod_t b
	) {
		const modint_cartprod_t
			a_new{GDih_action(a,b)};
		const modint_cartprod_t
			resultado{a_new+b};
		return resultado;
	}

	static constexpr
	modint_cartprod_t direct_product(
		modint_cartprod_t a,
		modint_cartprod_t b
	) {
		const modint_cartprod_t result{a+b};
		return result;
	}

	static constexpr
	modint_cartprod_t gr_bop(
		modint_cartprod_t a,
		modint_cartprod_t b
	) {
		const modint_cartprod_t
			resultado{GDih_product(a,b)};
		return resultado;
	}
};

template<
	typename UIntType,
	UIntType N4,
	UIntType N3,
	UIntType N2,
	UIntType N1	>
struct binop_t<group_name::PD_Cyc,UIntType,N4,N3,N2,N1> {
	using type = binop_t;
	using SIntType = signed_for_unsigned_t<UIntType>;
	using LUIntType = next_int_t<unsigned_for_signed_t<SIntType>>;

	using UIntType_pair =
		typename std::pair<UIntType,UIntType>;
	using modint_cartprod_t =
		modint_cartprod_t<UIntType,N4,N3,N2,N1>;
	
	inline static constexpr UIntType max_mod() {return modint_cartprod_t::max_mod();}
	inline static constexpr UIntType dim() {return modint_cartprod_t::dim();}
	inline static constexpr LUIntType card() {return modint_cartprod_t::card();}


	static_assert(N4>1);
	static_assert(N3>1);
	static_assert(N2>1);
	static_assert(N1>1);
	
	static constexpr
	modint_cartprod_t direct_product(
		modint_cartprod_t a,
		modint_cartprod_t b
	) {
		const modint_cartprod_t result{a+b};
		return result;
	}

	static constexpr
	modint_cartprod_t gr_bop(
		modint_cartprod_t a,
		modint_cartprod_t b
	) {
		return direct_product(a,b);
	}
};

template<
	group_name gn,
	typename UIntType,
	UIntType N5,
	UIntType N4,
	UIntType N3,
	UIntType N2,
	UIntType N1
>
struct binop_t<gn,UIntType,N5,N4,N3,N2,N1>	{
	using type = binop_t;
	using SIntType = signed_for_unsigned_t<UIntType>;
	using LUIntType = next_int_t<unsigned_for_signed_t<SIntType>>;

	using UIntType_pair =
		typename std::pair<UIntType,UIntType>;
	using modint_cartprod_t =
		modint_cartprod_t<UIntType,N5,N4,N3,N2,N1>;
	
	inline static constexpr UIntType max_mod() {return modint_cartprod_t::max_mod();}
	inline static constexpr UIntType dim() {return modint_cartprod_t::dim();}
	inline static constexpr LUIntType card() {return modint_cartprod_t::card();}

	static_assert(N5>1);
	static_assert(N4>1);
	static_assert(N3>1);
	static_assert(N2>1);
	static_assert(N1>1);
	
	static_assert(gn==group_name::PD_Cyc);
	
	static constexpr
	modint_cartprod_t direct_product(
		modint_cartprod_t a,
		modint_cartprod_t b
	)  {
		const modint_cartprod_t result{a+b};
		return result;
	}

	static constexpr
	modint_cartprod_t semi_direct_product(
		modint_cartprod_t a,
		modint_cartprod_t b
	) {
		return direct_product(a,b);
	}

	static constexpr
	modint_cartprod_t gr_bop(
		modint_cartprod_t a,
		modint_cartprod_t b
	) {
		return direct_product(a,b);
	}
};


template<
	group_name gn,
	typename UIntType
	UIntType N6,
	UIntType N5,
	UIntType N4,
	UIntType N3,
	UIntType N2,
	UIntType N1			>
struct binop_t<gn,UIntType,N6,N5,N4,N3,N2,N1> {
	using type = binop_t;
	using SIntType = signed_for_unsigned_t<UIntType>;
	using LUIntType = next_int_t<unsigned_for_signed_t<SIntType>>;

	using UIntType_pair =
		typename std::pair<UIntType,UIntType>;
	using modint_cartprod_t =
		modint_cartprod_t<UIntType,N6,N5,N4,N3,N2,N1>;
	
	inline static constexpr UIntType max_mod() {return modint_cartprod_t::max_mod();}
	inline static constexpr UIntType dim() {return modint_cartprod_t::dim();}
	inline static constexpr LUIntType card() {return modint_cartprod_t::card();}

	static_assert(N6>1);
	static_assert(N5>1);
	static_assert(N4>1);
	static_assert(N3>1);
	static_assert(N2>1);
	static_assert(N1>1);
	static_assert(gn==group_name::PD_Cyc);
	
	static constexpr
	modint_cartprod_t direct_product(
		modint_cartprod_t a,
		modint_cartprod_t b
	)  {
		const modint_cartprod_t{a+b};
		return result;
	}

	static constexpr
	modint_cartprod_t semi_direct_product(
		modint_cartprod_t a,
		modint_cartprod_t b
	) {
		return direct_product(a,b);
	}

	static constexpr
	modint_cartprod_t gr_bop(
		modint_cartprod_t a,
		modint_cartprod_t b
	) {
		return direct_product(a,b);
	}
};

}
#endif //ACTION_OF_A_GROUP_OVER_OTHER_GROUP_HPP_INCLUDED
