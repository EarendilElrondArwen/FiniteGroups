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

#include "binop_t.hpp"
#include <array>

// binop_t<group_name gn, uint Ns_head, uint ... Ns_tail>
// modint_cartprod_t<uint Ns_head,uint ...Ns_tail>
namespace tfg {
using std::size_t;
template<group_name gn,typename UIntType,UIntType N_n,UIntType ...N_nm1>
struct magma_t :
	public modint_cartprod_t<UIntType,N_n,N_nm1...>,public binop_t<gn,UIntType,N_n,N_nm1...>
{
public:
	static_assert(N_n>1);
	
	using elem_t		=		modint_cartprod_t< UIntType, N_n , N_nm1... >;
	// This instances of modint_carprod are the elements of the underliying set of magma 
	using base_t		=		elem_t;
	// elem_t or, better, modint_cartprod, id the base class of magma
	using op_t			=		binop_t< gn , UIntType , N_n , N_nm1... >;
	// This type, an operation, is already in the present class as static, belong the class
	using elem_mgm_t	=		magma_t;
	// As instance of the class magma_t, we call this instance as element of the magma
	
	/////////////////////////////////////////////////////
	///		CONVERSION TO BASE CLASS ELEMENT_OF_SET	  ///
	/////////////////////////////////////////////////////

	constexpr
	elem_t get_elem_t() const {
		return (this->get_base_elem());
	}
	
	elem_t & get_elem_t() {
		return (this->get_base_elem());
	}
	
	///////////////////////////////////////////////////////////////
	///	OPERATIONS FROM OP_T OVER ELEMS FROM MODINT_CARTPROD	///
	///////////////////////////////////////////////////////////////
	
	static constexpr
	elem_mgm_t bop(const elem_mgm_t & a,const elem_mgm_t & b) {
		return elem_mgm_t{elem_t(op_t::gr_bop(a.get_elem_t(),b.get_elem_t()))};
	}
	
	elem_mgm_t operator*(const elem_mgm_t & rhs) const {
		elem_mgm_t lhs{*this};
		lhs = bop(lhs,rhs);
		return lhs;
	}
	
	const elem_mgm_t & operator*=(const elem_mgm_t & rhs) const {
		elem_mgm_t& lhs{*this};
		lhs = bop(lhs,rhs);
		return (lhs);
	}
	
	elem_mgm_t operator/(const elem_mgm_t & rhs) const {
		elem_mgm_t lhs{*this};
		lhs *= rhs.mgm_inv();
		return lhs;
	}
	
	const elem_mgm_t & operator/=(const elem_mgm_t & rhs) const {
		elem_mgm_t& lhs{*this};
		lhs*=rhs.mgm_inv();
		return (lhs);
	}
	
	elem_mgm_t operator|(const elem_mgm_t & rhs) const {
		elem_mgm_t lhs{*this};
		lhs.mgm_inv_ass();
		lhs*=rhs;
		return lhs;
	}
	
	const elem_mgm_t & operator|=(const elem_mgm_t & rhs) const {
		elem_mgm_t& lhs{*this};
		lhs.mgm_inv_ass();
		lhs *= rhs;
		return (lhs);
	}
	
	static constexpr
	elem_mgm_t left_bop(const elem_mgm_t & a,const elem_mgm_t & b,const elem_mgm_t & c) {
		return bop(bop(a,b),c);
	}
	
	static constexpr
	elem_mgm_t right_bop(const elem_mgm_t & a,const elem_mgm_t & b,const elem_mgm_t & c) {
		return bop(a,bop(b,c));
	}
	
	static constexpr
	elem_mgm_t left_left_bop(const elem_mgm_t & a,const elem_mgm_t & b,const elem_mgm_t & c,const elem_mgm_t & d) {
		return bop(bop(bop(a,b),c),d);
	}
	
	static constexpr
	elem_mgm_t left_right_bop(const elem_mgm_t & a,const elem_mgm_t & b,const elem_mgm_t & c,const elem_mgm_t & d) {
		return bop(a,bop(bop(b,c),d));
	}
	
	static constexpr
	elem_mgm_t right_right_bop(const elem_mgm_t & a,const elem_mgm_t & b,const elem_mgm_t & c,const elem_mgm_t & d) {
		return bop(a,bop(b,bop(c,d)));
	}
	
	static constexpr
	elem_mgm_t right_left_bop(const elem_mgm_t & a,const elem_mgm_t & b,const elem_mgm_t & c,const elem_mgm_t & d) {
		return bop(bop(a,bop(b,c),d));
	}
	
	static constexpr
	elem_mgm_t central_central_bop(const elem_mgm_t & a,const elem_mgm_t & b,const elem_mgm_t & c,const elem_mgm_t & d) {
		return bop(bop(a,b),bop(c,d));
	}
	
	static constexpr UIntType	max_mod()	{return elem_t::max_mod();}
	static constexpr UIntType	min_mod()	{return elem_t::min_mod();}
	static constexpr UIntType	dim()		{return elem_t::dim();}
	static constexpr size_t		card()  	{return elem_t::card();}
	static constexpr elem_mgm_t max_elem()  {return elem_mgm_t{elem_t(elem_t::max_elem())};}
	static constexpr elem_mgm_t unit_elem()  {return elem_mgm_t{elem_t(elem_t::unit_elem())};}
	static constexpr elem_mgm_t zero_elem()  {return elem_mgm_t{elem_t(elem_t::zero_elem())};}
	
	//////////////////////////////////////
	//			CONSTRUCTORS			//
	//////////////////////////////////////
	
	
public:

	constexpr
	magma_t()=default;

	explicit constexpr
	magma_t(const elem_t & elem_arg) :
		elem_t(elem_arg) {}
	
	explicit constexpr
	magma_t(elem_t && elem_arg) :
		elem_t(elem_arg) {}

	constexpr
	magma_t(const elem_mgm_t &)=default;

	constexpr
	magma_t(elem_mgm_t &&)=default;
	
	//////////////////////////////////////////////
	//				ASSIGNS						//
	//////////////////////////////////////////////
		
	constexpr
	elem_mgm_t & operator=(elem_mgm_t &)=default;
	
	constexpr
	const elem_mgm_t & operator=(const elem_mgm_t & arg) {
		if (this != &arg) {
			this->get_base_elem() = arg.get_base_elem();
		}
		return (*this);
	}

	constexpr
	elem_mgm_t & operator=(elem_mgm_t &&)=default;
	
	//////////////////////////////////////////////
	//			BASIC BOOLEAN RELATIONS			//
	//////////////////////////////////////////////
	
	constexpr
	bool operator != (const elem_mgm_t & b) const {
		return (get_elem_t() != b.get_elem_t());
	}

	constexpr
	bool operator == (const elem_mgm_t & b) const {
		return (get_elem_t() == b.get_elem_t());
	}

	constexpr
	bool operator < (const elem_mgm_t & b) const {
		return (get_elem_t() < b.get_elem_t());
	}

	constexpr
	bool operator > (const elem_mgm_t & b) const {
		return (get_elem_t() > b.get_elem_t());
	}

	constexpr
	bool operator <= (const elem_mgm_t & b) const {
		return (get_elem_t() <= b.get_elem_t());
	}

	constexpr
	bool operator >= (const elem_mgm_t & b) const {
		return (get_elem_t() >= b.get_elem_t());
	}

	//////////////////////////////////////////////////
	//			OUTPUT TO STRING					//
	//////////////////////////////////////////////////

	//		BY INHERITANCE

	//////////////////////////////////////////////////
	//			OPERATIONS AND GROUPS				//
	//////////////////////////////////////////////////

	constexpr
	bool is_directprod_unit() const {
		constexpr elem_mgm_t dp_unit{unit_elem()};
		if((*this)==dp_unit)
			return true;
		else
			return false;
	}

	static constexpr
	bool commute(const elem_mgm_t & lhs,const elem_mgm_t & rhs) {
		if (bop(lhs,rhs)==bop(rhs,lhs))
			return true;
		else
			return false;
	}
	
	constexpr
	UIntType elem_order() const {
		elem_mgm_t accumulate{*this};
		UIntType order{1};
		if ((*this) == bop(accumulate,(*this)))
			return order;
		while ((*this) != bop(accumulate,(*this)))  {
			accumulate = bop(accumulate,(*this));
			++order;
		}
		return order;
	}
	
	static constexpr
	elem_mgm_t left_pow(elem_mgm_t lhs,next_int_t<UIntType> i) {
		if (i==0) return elem_mgm_t{};
		if (i==1) return lhs;
		else {
			elem_mgm_t kp{lhs};
			for(UIntType k{1} ; k < i ; ++k){
				kp = bop(kp,lhs);
			}
			return kp;
		}
	}
	
	constexpr
	elem_mgm_t operator^(signed_for_unsigned_t<UIntType> rhs) const {
		if (rhs < -1) {
			elem_mgm_t result{mgm_inv()};
			return (left_pow(result,static_cast<next_int_t<UIntType>>(-rhs)));
		} else if (rhs == -1) {
			elem_mgm_t result{mgm_inv()};
			return result;
		} else if (rhs == 0) {
			return (get_the_identity());
		} else if (rhs == 1) {
			return (*this);
		} else {
			return (left_pow(*this,static_cast<next_int_t<UIntType>>(rhs)));
		}
	}
	
	
	constexpr
	const elem_mgm_t & operator^=(signed_for_unsigned_t<UIntType> rhs)  {
		elem_mgm_t & lhs{*this};
		if (rhs < -1) {
			lhs = lhs.mgm_inv();
			lhs = left_pow(lhs,static_cast<next_int_t<UIntType>>(-rhs+1));
			return (lhs);
		} else if (rhs == -1) {
			lhs = lhs.mgm_inv();
			return (lhs);
		} else if (rhs == 0) {
			lhs = get_the_identity();
		} else if (rhs == 1) {
			return (*this);
		} else {
			lhs = left_pow(lhs,static_cast<next_int_t<UIntType>>(rhs));
			return (lhs);
		}
	}
	
	
	static constexpr
	elem_mgm_t right_pow(elem_mgm_t lhs,UIntType i) {
		if (i==0) return elem_mgm_t{};
		else if (i==1) return lhs;
		else {
			elem_mgm_t kp{lhs};
			for(UIntType k{1} ; k < i ; ++k){
				kp = bop(lhs,kp);
			}
			return kp;
		}
	}
	
	static constexpr
	bool associate(const elem_mgm_t & lhs,const elem_mgm_t & chs,const elem_mgm_t & rhs) {
		const elem_mgm_t LHS{left_bop(lhs,chs,rhs)};
		const elem_mgm_t RHS{right_bop(lhs,chs,rhs)};
		const bool result{LHS==RHS};
		return result;
	}
	
	constexpr
	bool is_left_identity(const elem_mgm_t & rhs) const {
		const elem_mgm_t & lhs {*this};
		const elem_mgm_t term{lhs*rhs};
		const bool result{rhs==term};
		return result;
	}
	
	constexpr
	bool is_right_identity(const elem_mgm_t & lhs) const {
		const elem_mgm_t & rhs {*this};
		const auto term{lhs*rhs};
		const bool result{lhs==term};
		return result;
	}
	
	constexpr
	bool is_identity(const elem_mgm_t & rhs) const {
		const elem_mgm_t lhs{*this};
		const auto term_left{bop(lhs,rhs)};
		const auto term_right{bop(rhs,lhs)};
		const bool left_result{rhs==term_left};
		const bool right_result{rhs==term_right};
		const bool result{left_result && right_result};
		return result;
	}
	
	constexpr
	elem_mgm_t right_commutator(const elem_mgm_t & b) const {
		const elem_mgm_t & a{*this};
		const elem_mgm_t& result_1{a*b};
		const elem_mgm_t& result_2{a.mgm_inv()*b.mgm_inv()};
		const elem_mgm_t  result{result_1*result_2};
		return result;
	}
	
	constexpr
	elem_mgm_t left_commutator(const elem_mgm_t & b) const {
		const elem_mgm_t & a{*this};
		const elem_mgm_t result_1{a*b};
		const elem_mgm_t result_2{(a.mgm_inv())*(b.mgm_inv())};
		const elem_mgm_t result{result_2*result_1};
		return result;
	}

	constexpr
	elem_mgm_t left_conjugate(const elem_mgm_t & h) const {
		const elem_mgm_t & a{*this};
		const elem_mgm_t result{(h*a)*h.mgm_inv()};
		return result;
	}
	
	constexpr
	elem_mgm_t right_conjugate(const elem_mgm_t & h) const {
		const elem_mgm_t & a{*this};
		const elem_mgm_t result{h.mgm_inv()*(a*h)};
		return result;
	}
	
	constexpr
	elem_mgm_t cartprod_inv() const {
		return elem_mgm_t{(-get_elem_t())};
	}
	
public :

	static constexpr bool is_abelian() {
		elem_mgm_t lhs{};
		for(size_t il{0} ; il < card() ; ++il) {
			elem_mgm_t rhs{};
			for(size_t jl{0} ; jl < card() ; ++jl) {
				const elem_mgm_t rophs {lhs*rhs};
				const elem_mgm_t lpohs {rhs*lhs};
				if (rophs!=lpohs)
					return false;
				rhs.m_next();
			}
			lhs.m_next();
		}
		return true;
	}

public :
	constexpr bool commute_with_all() const {
		elem_mgm_t cthis{*this};
		elem_mgm_t var_elem{};
		for( size_t i{0} ; i < card() ; ++i ) {
			if (!(commute(cthis,var_elem)))
				return false;
			var_elem.m_next();
		}
		return true;
	}
	
public :
 
	static constexpr bool is_associative() {
		elem_mgm_t lhs{};
		for( size_t i{0} ; i < card() ; ++i ) {
			elem_mgm_t chs{};
			for( size_t j{0} ; j < card() ; ++j ) {
				elem_mgm_t rhs{};
				for( size_t k{0} ; k < card() ; ++k ) {
					if (!associate(lhs,chs,rhs)) {
						return false;
					}
					rhs.m_next();
				}
				chs.m_next();
			}
			lhs.m_next();
		}
		return true;
	}
	
public :

	constexpr bool associate_with_all_as_lhs() const {
		const elem_mgm_t & lhs{*this};
		for(elem_mgm_t chs{} ; chs< max_elem() ; chs.m_next() ) {
			for(elem_mgm_t rhs{} ; rhs< max_elem() ; rhs.m_next() ) {
				if (!(associate(lhs,chs,rhs)))
					return false;
			}
		}
		for(elem_mgm_t rhs{} ; rhs< max_elem ; rhs.m_next() ) {
			if (!(associate(lhs,max_elem,rhs)))
				return false;
		}
		if (associate(lhs,max_elem,max_elem))
				return true;
		else
				return true;
	}
	
public :
	
	static constexpr bool exists_neutral_elem() {
		
		array<bool,card()> mark{};
		
		elem_mgm_t lhs{};
		for(size_t left_idx{0} ; left_idx != card() ; ++left_idx ) {
			elem_mgm_t rhs{};
			for(size_t right_idx{0} ; right_idx != card() ; ++right_idx ) {
				if (lhs.is_identity(rhs)) {
					mark[left_idx]=true;
					break;
				}
			}
		}
		
		bool exists_identity{true};
		for(bool exists_value : mark)
			exists_identity = exists_identity && exists_value;
		return exists_identity;
	}
	
	static constexpr 
	elem_mgm_t
	get_the_identity() { // in an group an element is idempotent iff is the identity 
		elem_mgm_t t{};
		for(size_t ix{0} ; ix < card() ; ++ix) {
			if ((t*t)==t)
				return t;
			t.m_next();
		}
		return elem_mgm_t{};
	}
	
	static constexpr
	elem_mgm_t
	get_gr_inv_for(elem_mgm_t lhs) {
		const elem_mgm_t id{get_the_identity()};
		if (lhs==id)
			return id;
		else {
			elem_mgm_t pos_inv{id.next()};
			for( ; pos_inv != id ; pos_inv.m_next() )
				if (bop(lhs,pos_inv)==id)
					return pos_inv;
			return lhs;
		}
	}
	
	constexpr
	elem_mgm_t mgm_inv() const {
		const elem_mgm_t id{get_the_identity()};
		const elem_mgm_t & lhs{*this};
		if (lhs==id)
			return id;
		else {
			elem_mgm_t pos_inv{id.next()};
			for( ; pos_inv != id ; pos_inv.m_next() )
				if ((lhs*pos_inv)==id)
					return pos_inv;
			return lhs;
		}
	}
	
	constexpr
	const elem_mgm_t & mgm_inv_assign() {
		elem_mgm_t & lhs{*this};
		const elem_mgm_t & lhs_inv{elem_t(mgm_inv())};
		lhs = lhs_inv;
		return (lhs);
	}
	
	constexpr
	bool
	exists_gr_inv_for() const {
		const elem_mgm_t id{get_the_identity()};
		const elem_mgm_t & lhs{*this};
		const elem_mgm_t lhs_inv{lhs.mgm_inv()};
		
		if (lhs==id) 
			return true;
		else {
			elem_mgm_t pos_inv{id.next()};
			for(  ; pos_inv != id ; pos_inv.m_next() )
				if (bop(lhs,pos_inv)==id) {
					return true;
					break;
				}
			return false;
		}
	}
	
	static constexpr bool
	exists_gr_inv_for_all() {
		const elem_mgm_t id{get_the_identity()};
		bool exists{true};
		
		elem_mgm_t lhs{id.next()};
		for( ; lhs != id ; lhs.m_next() )
			exists = exists && (lhs.exists_gr_inv_for());
		
		return exists;
	}
	
	static constexpr 
	bool is_group() {
		return (is_associative()&&exists_neutral_elem()&&exists_gr_inv_for_all());
	}
	
	static constexpr 
	bool is_abelian_group() {
		return (is_group() && is_abelian());
	}
	
	static constexpr
	ullint order_of_one_past_zero() {
		const bool exists_the_neutral_element{exists_neutral_elem()};
		const bool is_an_associative_bop{is_associative()};
		ullint orden_de_it{1};
		if (exists_the_neutral_element && is_an_associative_bop) {
			const elem_mgm_t id{get_the_identity()};
			const elem_mgm_t it{id.next()};
			elem_mgm_t accumulate{it};
			while(accumulate!=id) {
				accumulate = accumulate*it;
				++orden_de_it;
			}
		}
		return orden_de_it;
	}
	
	static constexpr
	bool is_left_cancellative() {
		elem_mgm_t a{};
		array<bool,card()*card()> mark{}; 
		for(size_t i{0} ; i < card() ; ++i ) {
			elem_mgm_t b{};
			for(size_t j{0} ; j < card() ; ++j ) {
				elem_mgm_t x{};
				for(size_t k{0} ; k < card() ; ++k ) {
					if((x*a)==b) {
						mark[i*card()+j] = true;
						break;
					}
					x.m_next();
				}
				b.m_next();
			}
			a.m_next();
		}
		
		bool result{true};
		for(auto value : mark) {
			result = result && value;
		}
		return result;
	}
	
	static constexpr
	bool is_right_cancellative() {
		elem_mgm_t a{};
		array<bool,card()*card()> mark{}; 
		for(size_t i{0} ; i < card() ; ++i ) {
			elem_mgm_t b{};
			for(size_t j{0} ; j < card() ; ++j ) {
				elem_mgm_t x{};
				for(size_t k{0} ; k < card() ; ++k ) {
					if((a*x)==b) {
						mark[i*card()+j] = true;
						break;
					}
					x.m_next();
				}
				b.m_next();
			}
			a.m_next();
		}
		
		bool result{true};
		for(auto value : mark) {
			result = result && value;
		}
		return result;
	}
	
	static constexpr
	bool is_cancellative() {
		
		array<bool,card()*card()> left_mark{};
		array<bool,card()*card()> right_mark{};
		elem_mgm_t lhs{};
		for(size_t i{0} ; i < card() ; ++i ) {
			elem_mgm_t rhs{};
			for(size_t j{0} ; j < card() ; ++j ) {
				elem_mgm_t x{};
				for(size_t k{0} ; k < card() ; ++k ) {
					if((x*lhs)==rhs) {
						left_mark[i*card()+j] = true;
						if (right_mark[i*card()+j])
							break;
					}
					if((lhs*x)==rhs) {
						right_mark[i*card()+j] = true;
						if (left_mark[i*card()+j])
							break;
					}
					x.m_next();
				}
				rhs.m_next();
			}
			lhs.m_next();
		}
		
		for(auto value : left_mark) {
			if (! value) return false;
		}
		for(auto value : right_mark) {
			if (! value) return false;
		}
		return true;
	}
	
};

}
#endif // ELEMENT_OF_GROUP_T_HPP_INCLUDED
