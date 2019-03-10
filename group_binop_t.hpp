/*
 * group_binop_t.hpp
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

#include "element_of_set_t.hpp"

namespace tfg {

template<group_name gn,uint Ns_head, uint ... Ns_tail>
struct group_binop_t{
	static constexpr bool defined = false;
	static_assert(defined);
};

template<uint N>
struct group_binop_t<group_name::C,N>{
	static constexpr bool defined = true;
	static_assert(defined);

	static_assert(
		N > 1,
		"No trabajmos sobre palotes o sobre la nada"
	);
	using element_of_set_t = element_of_set_t<N>;
	static constexpr uint max_N = N;
	static constexpr uint max_dim = 1;
	static constexpr uint Order_Of_This_Group = N;

	static constexpr
		element_of_set_t semi_direct_product(
			element_of_set_t a,
			element_of_set_t b
		)  {
		return a+b;
	}

	static constexpr
		element_of_set_t direct_product(
			element_of_set_t a,
			element_of_set_t b
		)  {
		return a+b;
	}

	static constexpr
		element_of_set_t gr_bop(
			element_of_set_t a,
			element_of_set_t b
		)  {
		return direct_product(a,b);
	}
};

template<uint N2,uint N1>
struct group_binop_t<group_name::PD_Cyc,N2,N1>{
	static constexpr bool defined = true;
	static_assert(defined);

	static_assert(N2 > 1);
	static_assert(N1 > 1);
	//static_assert(N2 <= N1);
	using element_of_set_t = element_of_set_t<N2,N1>;
	static constexpr uint max_N   = std::max(N2,N1);
	static constexpr uint max_dim = 2;
	static constexpr uint Order_Of_This_Group = N2*N1;

	static constexpr
		element_of_set_t semi_direct_product(
			element_of_set_t a,
			element_of_set_t b
		)  {
		return element_of_set_t(a+b);
	}

	static constexpr
		element_of_set_t direct_product(
			element_of_set_t a,
			element_of_set_t b
		) {
		return a+b;
	}
	static constexpr
		element_of_set_t gr_bop(
			element_of_set_t a,
			element_of_set_t b
		) {
		return direct_product(a,b);
	}
};

template<>
struct group_binop_t<group_name::Q,2,4>{
	static constexpr bool defined = true;
	static_assert(defined);

	using uint_pair = typename std::pair<uint,uint>;
	using element_of_set_t = element_of_set_t<2,4>;
	static constexpr uint max_N = 4;
	static constexpr uint max_dim = element_of_set_t::max_dim;
	static constexpr uint Order_Of_This_Group = 2*4;

	static constexpr
		element_of_set_t Q_product(
			element_of_set_t IK,
			element_of_set_t JL
		) {
		uint i{IK.dm.m_i};
		uint k{IK.edm.dm.m_i};
		uint j{JL.dm.m_i};
		uint l{JL.edm.dm.m_i};
		element_of_set_t R;
		if (((i%2)==0)and((j%2)==0)){
			R=element_of_set_t{
				uint((i+j)%2),
				{uint((k+l)%4)}
			};
		}
		else if (((i%2)==0)and((j%2)==1)) {
			R=element_of_set_t{
				uint((i+j)%2),
				{uint((3*k+l)%4)}
			};
		}
		else if (((i%2)==1)and((j%2)==0)) {
			R=element_of_set_t{
				uint((i+j)%2),
				{uint((k+l)%4)}
			};
		}
		else {
			R=element_of_set_t{
				uint((i+j)%2),
				uint((3*k+l+2)%4)
			};
		}
		return R;
	}

	static constexpr
		element_of_set_t semi_direct_product(
			element_of_set_t a,
			element_of_set_t b
		)  {
		return element_of_set_t(a+b);
	}

	static constexpr
		element_of_set_t direct_product(
			element_of_set_t a,
			element_of_set_t b
		) {
		return a+b;
	}
	static constexpr
		element_of_set_t gr_bop(
			element_of_set_t a,
			element_of_set_t b
		) {
		return Q_product(a,b);
	}
};

template<>
struct group_binop_t<group_name::C3__C4,4,3>
{
	static constexpr bool defined = true;
	static_assert(defined);

	using uint_pair = typename std::pair<uint,uint>;
	using element_of_set_t = element_of_set_t<4,3>;
	static constexpr uint max_N = 4;
	static constexpr uint max_dim = 2;
	static constexpr uint Order_Of_This_Group = 3*4;

	static constexpr
		element_of_set_t C3__C4_product(
			element_of_set_t IJ,
			element_of_set_t KM
		) {
		uint k{KM.dm.m_i};
		uint j{IJ.edm.dm.m_i};
		element_of_set_t resultado{IJ+KM};
		if ((k%4==1)||(k%4==3)){
			resultado.edm.dm+=j;
		}
		return resultado;
	}

	static constexpr
		element_of_set_t semi_direct_product(
			element_of_set_t a,
			element_of_set_t b
		)  {
		return element_of_set_t(a+b);
	}

	static constexpr
		element_of_set_t direct_product(
			element_of_set_t a,
			element_of_set_t b
		) {
		return a+b;
	}
	static constexpr
		element_of_set_t gr_bop(
			element_of_set_t a,
			element_of_set_t b
		) {
		return C3__C4_product(a,b);
	}
};

template<uint N3,uint N2,uint N1>
struct group_binop_t<group_name::PD_Cyc,N3,N2,N1>{
	static constexpr bool defined = true;
	static_assert(defined);

	static_assert(N3 > 1);
	static_assert(N2 > 1);
	static_assert(N1 > 1);
	using element_of_set_t = element_of_set_t<N3,N2,N1>;
	static constexpr uint max_N = std::max(N3,N2,N1);
	static constexpr uint max_dim = 3;
	static constexpr uint Order_Of_This_Group = N3*N2*N1;

	static constexpr
		element_of_set_t semi_direct_product(
			element_of_set_t a,
			element_of_set_t b
		) {
		return a+b;
	}

	static constexpr
		element_of_set_t direct_product(
			element_of_set_t a,
			element_of_set_t b
		) {
		return a+b;
	}

	static constexpr
		element_of_set_t gr_bop(
			element_of_set_t a,
			element_of_set_t b
		) {
		return direct_product(a,b);
	}
};

template<>
struct group_binop_t<group_name::C3__C2_2,2,2,3>
{
	static constexpr bool defined = true;
	static_assert(defined);

	using uint_pair =
		typename std::pair<uint,uint>;
	using element_of_set_t =
		element_of_set_t<2,2,3>;
	static constexpr uint max_N = 3;
	static constexpr uint max_dim = 3;
	static constexpr
		uint Order_Of_This_Group = 2*2*3;

	static constexpr
		element_of_set_t C3__C2_2_product(
			element_of_set_t IJK,
			element_of_set_t LMN
		) {
		uint i{IJK.dm.m_i};
		uint j{IJK.edm.dm.m_i};
		uint k{IJK.edm.edm.dm.m_i};
		uint l{LMN.dm.m_i};
		uint m{LMN.edm.dm.m_i};
		uint n{LMN.edm.edm.dm.m_i};
		element_of_set_t R;
		if ((l%2)==(m%2)){
			R=element_of_set_t{
				uint((i+l)%2),
				{uint((j+m)%2),
				 {uint((k+n)%3)}
				}
			};
		}
		else {
			R=element_of_set_t{
				uint((i+l)%2),
				{uint((j+m)%2),
				 {uint((3-k+n)%3)}
				}
			};
		}
		return R;
	}

	static constexpr
	element_of_set_t semi_direct_product(
		element_of_set_t a,
		element_of_set_t b	)  {
		return element_of_set_t(a+b);
	}

	static element_of_set_t direct_product(
						element_of_set_t a,
						element_of_set_t b) {
		return a+b;
	}

	static constexpr
		element_of_set_t gr_bop(
			element_of_set_t a,
			element_of_set_t b
		) {
		return C3__C2_2_product(a,b);
	}
};


template<>
struct group_binop_t<group_name::C2_2__C3,2,2,3>
{
	static constexpr bool defined = true;
	static_assert(defined);

	using uint_pair = typename std::pair<uint,uint>;
	using element_of_set_t = element_of_set_t<2,2,3>;
	static constexpr uint max_N = 3;
	static constexpr uint max_dim = 3;
	static constexpr uint Order_Of_This_Group = 2*2*3;

	static constexpr
		element_of_set_t phi_action(
			element_of_set_t IJK,
			element_of_set_t LMN
		){
		const uint k{IJK.edm.edm.dm.m_i};
		const uint l{LMN.dm.m_i};
		const uint m{LMN.edm.dm.m_i};
		const uint n{LMN.edm.edm.dm.m_i};
		element_of_set_t R;
		if (k%3==0) {
			R.dm.m_i = l;
			R.edm.dm.m_i =m;
			R.edm.edm.dm.m_i=n;
			return R;
		}
		else if (k%3==1){
			R.dm.m_i = (l+m);
			R.edm.dm.m_i =l;
			R.edm.edm.dm.m_i=n;
			return R;
		}
		else {
			R.dm = m;
			R.edm.dm =(l+m);
			R.edm.edm.dm=n;
			return R;
		}
	}

	static constexpr
		element_of_set_t zeta_action(
			element_of_set_t IJK,
			element_of_set_t LMN
		){
		const uint i{IJK.dm.m_i};
		const uint j{IJK.edm.dm.m_i};
		const uint k{IJK.edm.edm.dm.m_i};
		const uint l{LMN.dm.m_i};
		const uint m{LMN.edm.dm.m_i};
		element_of_set_t R;
		if ((l%2==0)&&(m%2==0)) {
			R.dm = i;
			R.edm.dm = j;
			R.edm.edm.dm = k;
			return R;
		}
		else if ((l%2==0)&&(m%2==1)) {
			R.dm = i;
			R.edm.dm = (j+1);
			R.edm.edm.dm = k;
			return R;
		}
		else if ((l%2==1)&&(m%2==0)) {
			R.dm = (i+1);
			R.edm.dm = j;
			R.edm.edm.dm = k;
			return R;
		}
		else {
			R.dm = (i+1);
			R.edm.dm = (j+1);
			R.edm.edm.dm = k;
			return R;
		}
	}

	static constexpr
	element_of_set_t C2_2__C3_product(
		element_of_set_t IJK,
		element_of_set_t LMN
	) {
		const uint l{LMN.dm.m_i};
		const uint m{LMN.edm.dm.m_i};
		const uint k{IJK.edm.edm.dm.m_i};
		if(((l%2==0)&&(m%2==0))||(k%3==0))
			return IJK+LMN;

		const element_of_set_t
			LMN_por_zeta{zeta_action(IJK,LMN)};
		const element_of_set_t
			IJK_por_phi{phi_action(IJK,LMN)};
		return (IJK_por_phi+LMN_por_zeta);
	}

	static constexpr
	element_of_set_t direct_product(
		element_of_set_t a,
		element_of_set_t b
	) {
		return a+b;
	}

	static constexpr
	element_of_set_t gr_bop(
		element_of_set_t a,
		element_of_set_t b
	) {
		return C2_2__C3_product(a,b);
	}
};

template<uint N>
struct group_binop_t<group_name::Dih,2,N>
{
	static constexpr bool defined = true;
	static_assert(defined);

	static_assert( N>2 );
	using uint_pair = typename std::pair<uint,uint>;
	using element_of_set_t = element_of_set_t<2,N>;
	static constexpr uint max_N = N;
	static constexpr uint max_dim = 2;
	static constexpr uint Order_Of_This_Group = 2*N;

	static constexpr
	element_of_set_t Dih_product(
		element_of_set_t a,
		element_of_set_t b
	) {
		const uint i{a.dm.m_i};
		const uint k{a.edm.dm.m_i};
		const uint j{b.dm.m_i};
		const uint m{b.edm.dm.m_i};

		element_of_set_t R;
		R.dm = (i+j);
		R.edm.dm = m;
		if (j%2==0)
			R.edm.dm +=k;
		else
			R.edm.dm +=(N-k);
		return R;
	}

	static constexpr
	element_of_set_t direct_product(
		element_of_set_t a,
		element_of_set_t b
	) {
		return a+b;
	}

	static constexpr
	element_of_set_t gr_bop(
		element_of_set_t a,
		element_of_set_t b
	) {
		return Dih_product(a,b);
	}
};


template<uint N>
struct group_binop_t<group_name::Dic,2,N>
{
	static constexpr bool defined = true;
	static_assert(defined);

	static_assert(N%2==0);
	using uint_pair = typename std::pair<uint,uint>;
	using element_of_set_t = element_of_set_t<2,N>;
	static constexpr uint max_N = N;
	static constexpr uint max_dim = 2;
	static constexpr uint Order_Of_This_Group = 2*N;

	static constexpr
	element_of_set_t Dic_product(
		element_of_set_t a,
		element_of_set_t b
	) {
		const uint i{a.dm.m_i};
		const uint j{b.dm.m_i};
		element_of_set_t sr{
			group_binop_t<group_name::Dih,2,N>::gr_bop(a,b)
		};
		if((i%2 != 0)or(j%2 != 0)) {
			if ((i%2 ==1)&&( j%2==1)) {
				sr.edm.dm += (N/2);
			}
		}
		return sr;
	}

	static constexpr
	element_of_set_t direct_product(
		element_of_set_t a,
		element_of_set_t b
	) {
		return a+b;
	}

	static constexpr
	element_of_set_t gr_bop(
		element_of_set_t a,
		element_of_set_t b
	) {
		return Dic_product(a,b);
	}
};

template<uint p,uint q>
struct group_binop_t<group_name::GDih,p,q>
{
	static constexpr bool defined = true;
	static_assert(defined);

	static_assert(p>1);
	static_assert(q>1);
	static_assert(p<q);
	static_assert(is_prime(p));
	static_assert(is_prime(q));
	static_assert((q-1)%p==0);
	static constexpr uint r = (q-1)/p;
	static_assert(q==r*p+1);
	static constexpr
	uint r_(uint k) {
		return std::pow(uint(r),uint(k));
	}
	//static_assert(rep>q);
	using uint_pair = typename std::pair<uint,uint>;
	using element_of_set_t = element_of_set_t<p,q>;
	static constexpr uint max_N = q;
	static constexpr uint max_dim = 2;
	static constexpr uint Order_Of_This_Group = p*q;

	static constexpr
	element_of_set_t GDih_action(
		element_of_set_t a,
		element_of_set_t b
	) {
		const uint i{a.dm.m_i};
		const uint j{a.edm.dm.m_i};
		const uint k{b.dm.m_i};
		const element_of_set_t resultado{
			i,static_cast<uint>(r_(k)*j)
		};
		return resultado;
	}

	static constexpr
	element_of_set_t GDih_product(
		element_of_set_t a,
		element_of_set_t b
	) {
		const element_of_set_t
			a_new{GDih_action(a,b)};
		const element_of_set_t
			resultado{a_new+b};
		return resultado;
	}

	static constexpr
	element_of_set_t direct_product(
		element_of_set_t a,
		element_of_set_t b
	) {
		return a+b;
	}

	static constexpr
	element_of_set_t gr_bop(
		element_of_set_t a,
		element_of_set_t b
	) {
		const element_of_set_t
			resultado{GDih_product(a,b)};
		return resultado;
	}
};

template<
	uint N4,
	uint N3,
	uint N2,
	uint N1	>
struct group_binop_t<group_name::PD_Cyc,N4,N3,N2,N1> {
	static constexpr bool defined = true;
	static_assert(defined);

	static_assert(N4>1);
	static_assert(N3>1);
	static_assert(N2>1);
	static_assert(N1>1);
	using element_of_set_t =
		element_of_set_t<N4,N3,N2,N1>;
	static constexpr
		uint max_N =
			std::max(N4,
				std::max(N3,
					std::max(N2,N1)
				)
			);
	static constexpr uint max_dim = 4;
	static constexpr uint
		Order_Of_This_Group = N4*N3*N2*N1;

	static constexpr
	element_of_set_t direct_product(
		element_of_set_t a,
		element_of_set_t b
	) {
		return a+b;
	}

	static constexpr
	element_of_set_t gr_bop(
		element_of_set_t a,
		element_of_set_t b
	) {
		return direct_product(a,b);
	}
};

template<
	group_name gn,
	uint N5,
	uint N4,
	uint N3,
	uint N2,
	uint N1			>
struct group_binop_t<gn,N5,N4,N3,N2,N1>	{
	static constexpr bool defined = true;
	static_assert(defined);

	static_assert(N5>1);
	static_assert(N4>1);
	static_assert(N3>1);
	static_assert(N2>1);
	static_assert(N1>1);
	static_assert(gn==group_name::PD_Cyc);
	using element_of_set_t =
		element_of_set_t<N5,N4,N3,N2,N1>;
	static constexpr uint max_N =
		std::max(N5,
			std::max(N4,
				std::max(N3,
					std::max(N2,N1)
				)
			)
		);
	static constexpr uint max_dim = 5;
	static constexpr uint Order_Of_This_Group =
		N5*N4*N3*N2*N1;

	static constexpr
	element_of_set_t semi_direct_product(
		element_of_set_t a,
		element_of_set_t b
	)  {
		return a+b;
	}

	static constexpr
	element_of_set_t direct_product(
		element_of_set_t a,
		element_of_set_t b
	) {
		return a+b;
	}

	static constexpr
	element_of_set_t gr_bop(
		element_of_set_t a,
		element_of_set_t b
	) {
		return direct_product(a,b);
	}
};


template<
	group_name gn,
	uint N6,
	uint N5,
	uint N4,
	uint N3,
	uint N2,
	uint N1			>
struct group_binop_t<gn,N6,N5,N4,N3,N2,N1> {
	static constexpr bool defined = true;
	static_assert(defined);

	static_assert(N6>1);
	static_assert(N5>1);
	static_assert(N4>1);
	static_assert(N3>1);
	static_assert(N2>1);
	static_assert(N1>1);
	static_assert(gn==group_name::PD_Cyc);
	using element_of_set_t =
		element_of_set_t<N6,N5,N4,N3,N2,N1>;
	static constexpr uint max_N =
		std::max(N6,
			std::max(N5,
				std::max(N4,
					std::max(N3,
						std::max(N2,N1)
					)
				)
			)
		);
	static constexpr uint max_dim = 6;
	static constexpr uint Order_Of_This_Group =
		N6*N5*N4*N3*N2*N1;

	static constexpr
	element_of_set_t semi_direct_product(
		element_of_set_t a,
		element_of_set_t b
	)  {
		return a+b;
	}

	static constexpr
	element_of_set_t direct_product(
		element_of_set_t a,
		element_of_set_t b
	) {
		return a+b;
	}

	static constexpr
	element_of_set_t gr_bop(
		element_of_set_t a,
		element_of_set_t b
	) {
		return direct_product(a,b);
	}
};

}
#endif //ACTION_OF_A_GROUP_OVER_OTHER_GROUP_HPP_INCLUDED
