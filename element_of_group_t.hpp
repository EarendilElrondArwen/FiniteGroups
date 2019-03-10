/*
 * elem_of_group_t.hpp
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

#ifndef ELEMENT_OF_GROUP_T_HPP_INCLUDED
#define ELEMENT_OF_GROUP_T_HPP_INCLUDED

#include <set>
#include "group_binop_t.hpp"
//#include "element_of_set_t.hpp"

// GROUP_BINOP_T<group_name gn, uint Ns_head, uint ... Ns_tail>
// ELEMENT_OF_SET_T<uint Ns_head,uint ...Ns_tail>
namespace tfg {

template<group_name gn,uint N_n,uint ...N_nm1>
struct element_of_group_t :
	public element_of_set_t<N_n,N_nm1...>
{
	static_assert(N_n>1);
	using elem_t	=
		element_of_set_t< N_n , N_nm1... >;
	using op_t		=
		group_binop_t< gn , N_n , N_nm1... >;
	using elem_gr_t	=
		element_of_group_t;

	static constexpr uint max_N 				=
		elem_t::max_N;
	static constexpr uint max_dim 				=
		elem_t::max_dim;
	static constexpr uint Order_Of_This_Group 	=
		elem_t::Order_Of_This_Group;

	//////////////////////////////////////////////
	//			CONSTRUCTORS					//
	//////////////////////////////////////////////

	constexpr
	element_of_group_t()=default;

	constexpr
	element_of_group_t(	const elem_t & elem_arg) :
		elem_t(elem_arg) {}

	constexpr
	element_of_group_t(const elem_gr_t &)=default;

	constexpr
	element_of_group_t(elem_gr_t &&)=default;

	//////////////////////////////////////////////
	//				ASSIGNS						//
	//////////////////////////////////////////////

	constexpr
	elem_gr_t & operator=(elem_t & arg){
		(*this) = arg;
		return (*this);
	}

	constexpr
	elem_gr_t & operator=(elem_gr_t &)=default;

	constexpr
	elem_gr_t & operator=(elem_gr_t &&)=default;

	//////////////////////////////////////////////
	//			BASIC BOOLEAN RELATIONS			//
	//////////////////////////////////////////////

	constexpr
	bool operator != (const elem_gr_t & b) const {
		return this->elem_t::operator!=(b);
	}

	constexpr
	bool operator == (const elem_gr_t & b) const {
		return this->elem_t::operator==(b);
	}

	constexpr
	bool operator < (const elem_gr_t & b) const {
		return this->elem_t::operator<(b);
	}

	constexpr
	bool operator > (const elem_gr_t & b) const {
		return this->elem_t::operator>(b);
	}

	constexpr
	bool operator <= (const elem_gr_t & b) const {
		return this->elem_t::operator<=(b);
	}

	constexpr
	bool operator >= (const elem_gr_t & b) const {
		return this->elem_t::operator>=(b);
	}

	//////////////////////////////////////////////////
	//			OUTPUT TO STRING					//
	//////////////////////////////////////////////////

	//		BY INHERITANCE

	//////////////////////////////////////////////////
	//		CONVERSION TO BASE CLASS ELEMENT_OF_SET	//
	//////////////////////////////////////////////////

	explicit constexpr
	operator elem_t() {
		return (*(static_cast<elem_t*>(this)));
	}

	//////////////////////////////////////////////////
	//			OPERATIONS AND GROUPS				//
	//////////////////////////////////////////////////

	constexpr
	bool is_the_gr_unit() const {
		constexpr elem_gr_t gr_unit{};
		if((*this)==gr_unit)
			return true;
		else
			return false;
	}

	constexpr
	bool commute(const elem_gr_t & b) const {
		if (
			op_t::gr_bop(*this,b)
					==
			op_t::gr_bop(b,*this)
		)
			return true;
		else
			return false;
	}

	constexpr
	elem_gr_t inv() const {
		const elem_gr_t unit{};
		elem_gr_t b{*this};
		if(b==unit)
			return unit;
		elem_gr_t temp{unit};
		temp.m_next();
		while(temp != unit){
			temp = op_t::gr_bop(*this,b);
			if (temp==unit) {
				return b;
			}
			b.m_next();
		}
		return unit.m_prev();
	}

	constexpr
	uint elem_order() const {
		const elem_gr_t unit{};
		elem_gr_t b{*this};
		uint result{1};
		while(b != unit){
			b = op_t::gr_bop(*this,b);
			++result;
		}
		return result;
	}

	constexpr
	elem_gr_t pow(uint i) const {
		if (i==0)	return elem_gr_t();
		else {
			elem_gr_t kp{*this};
			for(uint k{1} ; k < i ; ++k){
				kp = op_t::gr_bop(kp,*this);
			}
			return kp;
		}
	}

	constexpr
	elem_gr_t commutator(
		const elem_gr_t & b
	) const {
		const elem_gr_t& a{*this};
		const elem_gr_t& result_1
			{op_t::gr_bop(a,b)};
		const elem_gr_t& result_2
			{op_t::gr_bop(a.inv(),b.inv())};
		const elem_gr_t  result
			{op_t::gr_bop(result_1,result_2)};
		return result;
	}

	constexpr
	elem_gr_t conjugate(
		const elem_gr_t & h
	) const {
		const elem_gr_t a{*this};
		const elem_gr_t result{op_t::gr_bop(h,a)};
		result = elem_gr_t(op_t::gr_bop(result,h.inv()));
		return result;
	}
};

}
#endif // ELEMENT_OF_GROUP_T_HPP_INCLUDED
