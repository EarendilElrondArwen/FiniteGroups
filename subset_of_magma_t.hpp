/*
 * subset_of_magma_t.hpp
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

#ifndef subset_of_magma_t_HPP_INCLUDED
#define subset_of_magma_t_HPP_INCLUDED

#include "args_traits_ugly_style.hpp"
#include <cstdlib>
#include <algorithm>
#include <set>

namespace tfg {
	
using std::set;
using std::size_t;
using std::pair;
using std::array;
using std::sort;
using std::next_permutation;
	
template<	group_name 	gn	,
			typename UIntType,
			UIntType 		N_n	,
			UIntType ...	N_nm1	>
using subset_of_underliying_magma_t =
	set<
		magma_t<gn,UIntType,N_n,N_nm1...>
	>;

template<	group_name 	gn	 ,
			typename UIntType,
			uint 		N_n	 ,
			uint ...	N_nm1	>
using subset_const_iterator =
	typename	subset_of_underliying_magma_t<
					gn,UIntType,N_n,N_nm1...
				>::const_iterator;

template<	group_name 		gn	,
			typename UIntType,
			UIntType 			N_n	,
			UIntType ...		N_nm1
		>

using const_subset_const_iterator =
	const subset_const_iterator<gn,UIntType,N_n,N_nm1...>;

enum class init_default_ways {empty,minimal,maximal};
///////////////////////////////////////////////////////////////////
////			producto cartesiano generico (casi) vacio		///
///////////////////////////////////////////////////////////////////
template<	group_name 		gn		,
			typename UIntType   	,
			UIntType			N_n	,
			UIntType ...		N_nm1
		>
struct subset_of_magma_t {
public:
	template<size_t I>
	using exact					=	exactly<I,magma_t,gn,UIntType,N_n,N_nm1...>;
	using mgm_t					=	magma_t<gn,UIntType,N_n,N_nm1...>;
	using elem_mgm_t			=	mgm_t;
	using elem_t 				=	modint_cartprod_t<UIntType,N_n,N_nm1...>;
	using mgm_elem_set_t		=	set< elem_mgm_t >;
	using base_t				=	mgm_elem_set_t;
	using const_iterator		=	typename mgm_elem_set_t::const_iterator;
	using insert_result_type	=	pair<const_iterator,bool>;
	static constexpr UIntType	max_mod()	{return elem_mgm_t::max_mod();}
	static constexpr UIntType	min_mod()	{return elem_mgm_t::min_mod();}
	static constexpr UIntType	dim()		{return elem_mgm_t::dim();}
	static constexpr size_t		card()		{return elem_mgm_t::card();}
	
	static constexpr 
	elem_mgm_t mgm_op(
		const elem_mgm_t & lhs,
		const elem_mgm_t & rhs
	) {
		return elem_mgm_t{lhs*rhs};
	}
	
	/// El nombre tiene sentido solo si la operacion es asociativa 
	static constexpr 
	elem_mgm_t mgm_op(
		const elem_mgm_t & lhs,
		const elem_mgm_t & chs,
		const elem_mgm_t & rhs
	) {
		const elem_mgm_t result{elem_mgm_t::left_bop(lhs,chs,rhs)};
		return result;
	}
	
	/// El nombre tiene sentido solo si la operacion es 4-asociativa 
	static constexpr 
	elem_mgm_t mgm_op(
		const elem_mgm_t & lhs,
		const elem_mgm_t & clhs,
		const elem_mgm_t & crhs,
		const elem_mgm_t & rhs
	) {
		const elem_mgm_t result{
			elem_mgm_t::central_central_bop(lhs,clhs,crhs,rhs)
		};
		return result;
	}
	
	/// El nombre tiene sentido solo si la operacion es 5-asociativa 
	static constexpr 
	elem_mgm_t mgm_op(
		const elem_mgm_t & A,
		const elem_mgm_t & B,
		const elem_mgm_t & C,
		const elem_mgm_t & D,
		const elem_mgm_t & E
	) {
		const elem_mgm_t result{
			elem_mgm_t::bop(
				elem_mgm_t::central_central_bop(
					A,B,C,D
				),E
			)
		};
		return result;
	}
	
	/// El nombre tiene sentido solo si la operacion es 6-asociativa 
	static constexpr 
	elem_mgm_t mgm_op(
		const elem_mgm_t & A,
		const elem_mgm_t & B,
		const elem_mgm_t & C,
		const elem_mgm_t & D,
		const elem_mgm_t & E,
		const elem_mgm_t & F
	) {
		const elem_mgm_t AB{elem_mgm_t::bop(A,B)};
		const elem_mgm_t CD{elem_mgm_t::bop(C,D)};
		const elem_mgm_t ABCD{elem_mgm_t::bop(AB,CD)};
		const elem_mgm_t EF{elem_mgm_t::bop(E,F)};
		const elem_mgm_t result{elem_mgm_t::bop(ABCD,EF)};
		return result;
	}
	
	static constexpr 
	elem_mgm_t exists_neutral_elem () {
		return elem_mgm_t{
			elem_mgm_t::exists_neutral_elem()
		};
	}
	
	static constexpr 
	bool is_associative() {
		return elem_mgm_t::is_associative();
	}
	
	static constexpr 
	bool commute(elem_mgm_t a,elem_mgm_t b) {
		return elem_mgm_t::commute(a,b);
	}
	
	static constexpr 
	size_t elem_order(elem_mgm_t a) {
		size_t result{
			static_cast<size_t>(a.elem_order())
		};
		return result;
	}
	
	static constexpr 
	elem_mgm_t gr_inv(const elem_mgm_t & a) {
		const auto result{a.mgm_inv()};
		return result;
	}
	
	static constexpr bool is_abelian() {
		return elem_mgm_t::is_abelian();
	}
	
	static constexpr bool is_abelian_group() {
		return elem_mgm_t::is_abelian_group();
	}
	
	static constexpr bool is_group() {
		return elem_mgm_t::is_group();
	}
	
	static constexpr 
	bool exists_mgm_inv() {
		return elem_mgm_t::exists_mgm_inv_for_all();
	}
	
	static constexpr 
	elem_mgm_t mgm_id() {
		return elem_mgm_t{elem_mgm_t::get_the_identity()};
	}
	
	static constexpr 
	elem_mgm_t left_commutator(
		const elem_mgm_t & a,
		const elem_mgm_t & b
	) {
		return elem_mgm_t{
			elem_mgm_t::left_commutator(a,b)
		};
	}
	
	static constexpr 
	elem_mgm_t right_commutator(
		const elem_mgm_t & a,
		const elem_mgm_t & b
	) {
		return elem_mgm_t{
			elem_mgm_t::right_commutator(a,b)
		};
	}
	
	static constexpr 
	elem_mgm_t left_conjugate(
		const elem_mgm_t & a,
		const elem_mgm_t & b
	) {
		return elem_mgm_t{
			elem_mgm_t::left_conjugate(a,b)
		};
	}
	
	static constexpr 
	elem_mgm_t right_conjugate(
		const elem_mgm_t & a,
		const elem_mgm_t & b
	) {
		return elem_mgm_t{
			elem_mgm_t::right_conjugate(a,b)
		};
	}
	
	static constexpr 
	elem_mgm_t pow(const elem_mgm_t & a,UIntType i) {
		return elem_mgm_t{elem_mgm_t::left_pow(a,i)};
	}

	/// BEGIN : DATA MEMBER ///
	mgm_elem_set_t setdata{};
	/// END : DATA MEMBER	///

	constexpr
	auto do_empty() {
		return this->setdata.clear();
	}

	constexpr
	size_t size() const {
		return this->setdata.size();
	}

	constexpr
	size_t count(const elem_mgm_t & a) const {
		return this->setdata.count(a);
	}

	constexpr
	const_iterator begin() const {
		return this->setdata.begin();
	}

	constexpr
	const_iterator end() const {
		return  this->setdata.end();
	}

	constexpr
	const const_iterator cbegin() const {
		return  this->setdata.cbegin();
	}

	constexpr
	const const_iterator cend() const {
		return  this->setdata.cend();
	}

	constexpr
	insert_result_type insert(const elem_mgm_t & elem) {
		return this->setdata.insert(elem);
	}
	
	constexpr
	insert_result_type insert_op(
		const elem_mgm_t & a,
		const elem_mgm_t & b
	) {
		return this->setdata.insert(mgm_op(a,b));
	}
	
	constexpr
	insert_result_type insert_op(
		const elem_mgm_t & a,
		const elem_mgm_t & b,
		const elem_mgm_t & c
	) {
		return this->setdata.insert(mgm_op(a,b,c));
	}
	
	constexpr
	insert_result_type insert_op(
		const elem_mgm_t & a,
		const elem_mgm_t & b,
		const elem_mgm_t & c,
		const elem_mgm_t & d
	) {
		return this->setdata.insert(mgm_op(a,b,c,d));
	}
	
	constexpr
	insert_result_type insert_op(
		const elem_mgm_t & a,
		const elem_mgm_t & b,
		const elem_mgm_t & c,
		const elem_mgm_t & d,
		const elem_mgm_t & e
	) {
		return this->setdata.insert(mgm_op(a,b,c,d,e));
	}
	
	constexpr
	insert_result_type insert_op(
		const elem_mgm_t & a,
		const elem_mgm_t & b,
		const elem_mgm_t & c,
		const elem_mgm_t & d,
		const elem_mgm_t & e,
		const elem_mgm_t & f
	) {
		return this->setdata.insert(mgm_op(a,b,c,d,e,f));
	}
	
	static constexpr base_t complete_mgm() {
		base_t H{};
		elem_mgm_t it{mgm_id().next()};
		for(size_t ix{0} ; ix < card() ; ++ix) {
			H.insert(it);
			it.m_next();
		}
		return H;
	}
	
	static constexpr base_t trivial() {
		base_t H{};
		H.clear();
		const elem_mgm_t id{mgm_id()};
		H.insert(id);
		return H;
	}
	
	static constexpr base_t none() {
		base_t H{};
		H.clear();
		return H;
	}
	
	constexpr
	subset_of_magma_t(init_default_ways way=init_default_ways::empty) : 
	setdata{
		(way==init_default_ways::maximal)		?
		(complete_mgm())						:
		(
			(way==init_default_ways::minimal)	?
			(trivial())							:
			(none())
		)
	} {}
	
	constexpr
	subset_of_magma_t(const subset_of_magma_t &)=default;
	
	constexpr
	subset_of_magma_t(subset_of_magma_t &&)=default;
	
	constexpr
	subset_of_magma_t(
		const elem_mgm_t & A
	) : subset_of_magma_t(span_group(A)) {}
	
	constexpr
	subset_of_magma_t(
		const elem_mgm_t & A,
		const elem_mgm_t & B
	) : subset_of_magma_t(span_group(A,B)) {}
	
	constexpr
	subset_of_magma_t(
		const elem_mgm_t & A,
		const elem_mgm_t & B,
		const elem_mgm_t & C
	) : subset_of_magma_t(span_group(A,B,C)) {}
	
	constexpr
	subset_of_magma_t(
		const elem_mgm_t & A,
		const elem_mgm_t & B,
		const elem_mgm_t & C,
		const elem_mgm_t & D
	) : subset_of_magma_t(span_group(A,B,C,D)) {}
	
	constexpr
	subset_of_magma_t(
		const elem_mgm_t & A,
		const elem_mgm_t & B,
		const elem_mgm_t & C,
		const elem_mgm_t & D,
		const elem_mgm_t & E
	) : subset_of_magma_t(span_group(A,B,C,D,E)) {}
	
	constexpr
	subset_of_magma_t(
		const elem_mgm_t & A,
		const elem_mgm_t & B,
		const elem_mgm_t & C,
		const elem_mgm_t & D,
		const elem_mgm_t & E,
		const elem_mgm_t & F
	) : subset_of_magma_t(span_group(A,B,C,D,E,F)) {}
	
	constexpr
	subset_of_magma_t& operator=(subset_of_magma_t&)=default;
	
	constexpr
	const subset_of_magma_t& operator=(const subset_of_magma_t& arg) {
		if (this != &arg) {
			this->setdata.clear();
			for(auto a : arg.setdata) {
				this->setdata.insert(a);
			}
		}
		return (*this);
	}

	constexpr
	subset_of_magma_t& operator=(subset_of_magma_t&&)=default;
		
	constexpr
	void fill_the_group(){
		const elem_mgm_t zero{};
		elem_mgm_t x{zero.next()};
		while(x != zero) {
			insert(x);
			x.m_next();
		}
		insert(zero);
	}

	constexpr
	bool operator != (const subset_of_magma_t & B) const {
		return(
			(!(this->is_subgroup_of(B)))
						||
			(!(B.is_subgroup_of(*this)))
		);
	}
	
	constexpr
	bool operator == (const subset_of_magma_t & B) const {
		return(
			(this->is_subgroup_of(B))
				&&
			(B.is_subgroup_of(*this))
		);
	}
	
	constexpr
	bool operator < (const subset_of_magma_t & B) const {
		if (this->is_proper_subgroup_of(B)) return true;
		else if (B.is_subgroup_of(*this)) return false;
		else {
			if (this->size() < B.size()) return true;
			else if (this->size() > B.size()) return false;
			else {
				const_iterator itcthis{begin()};
				const_iterator itB{B.begin()};
				const const_iterator itendcthis{cend()};
				const const_iterator itendB{B.cend()};
				for(							;
					(itcthis	!=	itendcthis)
								&&
					(itB		!=	itendB)		;
					++itcthis,++itB             )
				{
					if ((*itcthis)<(*itB))
						return true;
					else if ((*itcthis)>(*itB))
						return false;
				}
				return false;
			}
		}
	}
	
	constexpr
	bool operator <= (const subset_of_magma_t & B) const {
		if (this->is_subgroup_of(B))
			return true;
		else if (B.is_proper_subgroup_of(*this))
			return false;
		else {
			if (this->size() < B.size())
				return true;
			else if (this->size() > B.size())
				return false;
			else {
				const_iterator itcthis{this->begin()};
				const_iterator itB{B.begin()};
				const const_iterator itendcthis{this->cend()};
				const const_iterator itendB{B.cend()};
				for(								;
						(itcthis	!=	itendcthis)
									&&
						(itB		!=	itendB)		;
						++itcthis	,	++itB		)
				{
					if ( (*itcthis) < (*itB) )
						return true;
					else if ( (*itcthis) > (*itB) )
						return false;
				}
				return true;
			}
		}
	}
	
	constexpr
	bool operator > (const subset_of_magma_t & B) const {
		if (B.is_proper_subgroup_of(*this))
			return true;
		else if (this->is_subgroup_of(B))
			return false;
		else {
			if (this->size() > B.size())
				return true;
			else if (this->size() < B.size())
				return false;
			else {
				const_iterator itcthis{this->begin()};
				const_iterator itB{B.begin()};
				const const_iterator itendcthis{this->cend()};
				const const_iterator itendB{B.cend()};
				for(								;
						(itcthis	!=	itendcthis)
									&&
						(itB		!=	itendB)		;
						++itcthis	,	++itB		)
				{
					if ((*itcthis)>(*itB))
						return true;
					else if ((*itcthis)<(*itB))
						return false;
				}
				return false;
			}
		}
	}
	
	constexpr
	bool operator >= (const subset_of_magma_t & B) const {
		if (B.is_subgroup_of(*this))
			return true;
		else if (this->is_subgroup_of(B))
			return false;
		else {
			if (this->size() > B.size())
				return true;
			else if (this->size() < B.size())
				return false;
			else {
				const_iterator itcthis{this->begin()};
				const_iterator itB{B.begin()};
				const const_iterator itendcthis{this->cend()};
				const const_iterator itendB{B.cend()};
				for(								;
						(itcthis	!=	itendcthis)
									&&
						(itB		!=	itendB)		;
						++itcthis	,	++itB		)
				{
					if ((*itcthis)>(*itB))
						return true;
					else if ((*itcthis)<(*itB))
						return false;
				}
				return true;
			}
		}
	}
	
	constexpr
	bool is_empty() const {
		if (this->size()==0)
			return true;
		else
			return false;
	}
	
	constexpr
	bool is_unitary() const {
		if (this->size()==1)
			return true;
		else
			return false;
	}
	
	constexpr
	bool has_got_elem(const elem_mgm_t & a) const {
		if (this->size()==0)
			return false;
		else {
			if (this->count(a)!=0)
				return true;
			else
				return false;
		}
	}
	
	constexpr
	bool is_subgroup_of(const subset_of_magma_t & B) const {
		if (this->is_empty())
			return true;
		else if (this->size()>B.size())
			return false;
		else {
			for( auto a : *this ) {
				if (B.count(a)==0)
					return false;
			}
			return true;
		}
	}
	
	constexpr
	bool is_proper_subgroup_of(const subset_of_magma_t & B) const {
		if ((this->is_empty())&&(!B.is_empty()))
			return true;
		else if (this->size()>=B.size())
			return false;
		else {
			for(auto a : *this){
				if (B.count(a)==0)
					return false;
			}
			return true;
		}
	}
	
	subset_of_magma_t centralizer(const subset_of_magma_t & H) const {
		subset_of_magma_t the_centralizer{};
		the_centralizer.do_empty();
		for(auto g : *this) {
			bool commute_with_H = true;
			for(auto h : H) {
				if (!commute(h,g)) {
					commute_with_H = false;
					break;
				}
			}
			if (commute_with_H) {
				the_centralizer.insert(g);
			}
		}
		return the_centralizer;
	}
	
	constexpr
	subset_of_magma_t centre() const {
		subset_of_magma_t the_centre{};
		for(auto g : *this) {
			unsigned t{0};
			for(auto h : *this) {
				if (mgm_t::commute(g,h)) {
					++t;
				}
			}
			if (t == card()) {
				the_centre.insert(g);
			}
		}
		return the_centre;
	}
	
	constexpr
	bool is_inner_binary_operation() const {
		for(auto x : *this) {
			for (auto y : *this) {
				if (!(this->has_got_elem(mgm_op(x,y)))) {
					return false;
				}
			}
		}
		return true;
	}
	
	constexpr
	bool is_abelian_subset() const {
		for(auto x : *this) {
			for (auto y : *this) {
				if ((x*y)!=(y*x)) {
					return false;
				}
			}
		}
		return true;
	}
	
	constexpr
	bool is_inner_inverter() const {
		for(auto x: *this) {
			if(!(this->has_got_elem(gr_inv(x)))) {
				return false;
			}
		}
		return true;
	}
	
	constexpr
	bool
	is_subgroup() const {
		const bool is_close_under_binary_op{is_inner_binary_operation()};
		const bool is_close_under_inversion{is_inner_inverter()};
		const bool is_subgroup_of_the_universe_group{is_close_under_binary_op && is_close_under_inversion};
		return is_subgroup_of_the_universe_group;
	}
	
	pair<elem_mgm_t,bool> give_me_the_first_resbop_notin() const {
		pair<elem_mgm_t,bool> result;
		for(auto x : *this) {
			for (auto y : *this) {
				elem_mgm_t z{mgm_op(x,y)};
				if (!this->has_got_elem(z)) {
					result.first	= z;
					result.second	= true;
					return result;
				}
			}
		}
		result.second = false;
		return result;
	}
	
	pair<elem_mgm_t,bool>
	give_me_the_first_resinv_notin() const {
		pair<elem_mgm_t,bool> result;
		for (auto x : *this) {
			elem_mgm_t z{x.inv()};
			if (!this->has_got_elem(z)) {
				result.first	= z;
				result.second	= true;
				return result;
			}
		}
		result.second = false;
		return result;
	}
	
	///////////////////////////////////////////////////////////////////
	///		PARTIAL_SPAN											///
	///////////////////////////////////////////////////////////////////
	
	inline static void
	partial_span_group(
		subset_of_magma_t & H,
		const elem_mgm_t & a
	) {
		const elem_mgm_t id{mgm_id()};
		H.insert(id);
		if(a != id) {
			const size_t a_order{elem_order(a)};
			elem_mgm_t lhs{a};
			for(UIntType i{0} ; i < a_order ; ++i) {
				H.insert(lhs);
				lhs = mgm_op(lhs,a);
				if (lhs == id) 
					break;
			}
		}
	}
	
	subset_of_magma_t	span_group(const elem_mgm_t & a) {
		partial_span_group(*this,a);
		return (*this);
	}
	
	inline static void
	partial_span_group(
		subset_of_magma_t & H,
		const elem_mgm_t & a,
		const elem_mgm_t & b
	) {
		const elem_mgm_t id{mgm_id()};
		H.insert(id);
		if ((a==id)&&(b==id)) {
			H.insert(id);
			return;
		} else if ((a!=id)&&(b==id)) {
			if (H.count(a)==0) {
				partial_span_group(H,a);
			}
			return;
		} else if ((b!=id)&&(a==id)) {
			if (H.count(b)==0) {
				partial_span_group(H,b);
			}
			return;
		} else if (a==b) {
			if (H.count(a)==0) {
				partial_span_group(H,a);
			}
			return;
		} else {
			const size_t a_order{elem_order(a)};
			const size_t b_order{elem_order(b)};
			
			elem_mgm_t lhs{a};
			for(size_t i{0} ; i < a_order ; ++i) {
				elem_mgm_t rhs{b};
				for(size_t j{0} ; j < b_order ; ++j) {
					if ((lhs!=rhs)&&(lhs!=id)&&(rhs!=id)) {
						H.insert_op(lhs,rhs);
						H.insert_op(rhs,lhs);
					}
					rhs = mgm_op(rhs,b);
				}
				if (H==subset_of_magma_t{init_default_ways::maximal}) {
					return;
				}
				lhs = mgm_op(lhs,a);
			}
		}
		return;
	}
	
	
	inline static void
	partial_span_group(
		subset_of_magma_t & H,
		const elem_mgm_t & a,
		const elem_mgm_t & b,
		const elem_mgm_t & c
	) {
		const elem_mgm_t id{mgm_id()};
		
		if (exact<2>::funct(a,b,c)) {
			H.span_group(a,b);
			return;
		} else if (exact<2>::funct(a,c,b)) {
			H.span_group(a,c);
			return;
		} else if (exact<2>::funct(b,c,a)) {
			H.span_group(b,c);
			return;
		} else {
			const size_t a_order{elem_order(a)};
			const size_t b_order{elem_order(b)};
			const size_t c_order{elem_order(c)};
			
			elem_mgm_t lhs{a};
			for(size_t i{0} ; i < a_order ; ++i) {
				elem_mgm_t chs{b};
				for(size_t j{0} ; j < b_order ; ++j) {
					elem_mgm_t rhs{c};
					for(size_t k{0} ; k < c_order ; ++k) {
						if (exact<3>::funct(a,b,c)) {
							array<elem_mgm_t,3> arg{a,b,c};
							sort(arg.begin(),arg.end());
							while(! next_permutation(arg.begin(),arg.end())) {
								H.insert_op(arg[0],arg[1],arg[2]);
							};
						}
						rhs = mgm_op(rhs,c);
					}
					chs = mgm_op(chs,b);
				}
				if (H==subset_of_magma_t{init_default_ways::maximal}) {
					return;
				}
				lhs = mgm_op(lhs,a);
			}
		 }
		return;
	}
	
	inline static void
	partial_span_group(
		subset_of_magma_t & H,
		const elem_mgm_t & a,
		const elem_mgm_t & b,
		const elem_mgm_t & c,
		const elem_mgm_t & d
	) {
		if ( exact<3>::funct(a,b,c,d) ) {
			span_group(a,b,c);return;
		} else if ( exact<3>::funct(a,b,d,c) ) {
			span_group(a,b,d);return;
		} else if ( exact<3>::funct(a,c,d,b) ) {
			span_group(a,c,d);return;
		} else if ( exact<3>::funct(b,c,d,a) ) {
			span_group(b,c,d);return;
		} else {
			const size_t a_order{elem_order(a)};
			const size_t b_order{elem_order(b)};
			const size_t c_order{elem_order(c)};
			const size_t d_order{elem_order(d)};
			
			elem_mgm_t A{a};
			for(size_t i{0} ; i < a_order ; ++i) {
				elem_mgm_t B{b};
				for(size_t j{0} ; j < b_order ; ++j) {
					elem_mgm_t C{c};
					for(size_t k{0} ; k < c_order ; ++k) {
						elem_mgm_t D{d};
						for(size_t l{0} ; l < d_order ; ++l) {
							if (exact<4>::funct(a,b,c,d)) {
								array<elem_mgm_t,4> arg{a,b,c,d};
								sort(arg.begin(),arg.end());
								while(! next_permutation(arg.begin(),arg.end())) {
									H.insert_op(arg[0],arg[1],arg[2],arg[3]);
								}
							}
							D = mgm_op(D,d);
						}
						C = mgm_op(C,c);
					}
					B = mgm_op(B,b);
				}
				if (H==subset_of_magma_t{init_default_ways::maximal}) {
					return;
				}
				A = mgm_op(A,a);
			}
			return;
		}
	}
	
	inline static void
	partial_span_group(
		subset_of_magma_t & H,
		const elem_mgm_t & a,
		const elem_mgm_t & b,
		const elem_mgm_t & c,
		const elem_mgm_t & d,
		const elem_mgm_t & e
	) {
		if (exact<4>::funct(a,b,c,d,e)) {
			H.span_group(a,b,c,d);return;
		} else if (exact<4>::funct(a,b,c,e,d)) {
			H.span_group(a,b,c,e);return;
		} else if (exact<4>::funct(a,b,d,e,c)) {
			H.span_group(a,b,d,e);return;
		} else if (exact<4>::funct(a,c,d,e,b)) {
			H.span_group(a,c,d,e);return;
		} else if (exact<4>::funct(b,c,d,e,a)) {
			H.span_group(b,c,d,e);return;
		} else {
			const size_t a_order{elem_order(a)};
			const size_t b_order{elem_order(b)};
			const size_t c_order{elem_order(c)};
			const size_t d_order{elem_order(d)};
			const size_t e_order{elem_order(e)};
			
			elem_mgm_t A{a};
			for(size_t i{0} ; i < a_order ; ++i) {
				elem_mgm_t B{b};
				for(size_t j{0} ; j < b_order ; ++j) {
					elem_mgm_t C{c};
					for(size_t k{0} ; k < c_order ; ++k) {
						elem_mgm_t D{d};
						for(size_t l{0} ; l < d_order ; ++l) {
							elem_mgm_t E{e};
							for(size_t m{0} ; m < e_order ; ++m) {
								if (exact<5>::funct(A,B,C,D,E)) {
									array<elem_mgm_t,5> arg{A,B,C,D,E};
									sort(arg.begin(),arg.end());
									while(! std::next_permutation(arg.begin(),arg.end())) {
										insert_op(arg[0],arg[1],arg[2],arg[3],arg[4]);
									}
								}
								E = mgm_op(E,e);
							}
							D = mgm_op(D,d);
						}
						C = mgm_op(C,c);
					}
					B = mgm_op(B,b);
				}
				if (H==subset_of_magma_t{init_default_ways::maximal}) {
					return;
				}
				A = mgm_op(A,a);
			}
			return;
		}
	}
	
	inline static void
	partial_span_group(
		subset_of_magma_t & H,
		const elem_mgm_t & a,
		const elem_mgm_t & b,
		const elem_mgm_t & c,
		const elem_mgm_t & d,
		const elem_mgm_t & e,
		const elem_mgm_t & f
	) {
		if (exact<5>::funct(a,b,c,d,e,f)) {
			H.span_group(a,b,c,d,e);return;
		} else if (exact<5>::funct(a,b,c,d,f,e)) {
			H.span_group(a,b,c,d,f);return;
		} else if (exact<5>::funct(a,b,c,e,f,d)) {
			H.span_group(a,b,c,e,f);return;
		} else if (exact<5>::funct(a,b,d,e,f,c)) {
			H.span_group(a,b,d,e,f);return;
		} else if (exact<5>::funct(a,c,d,e,f,b)) {
			H.span_group(a,c,d,e,f);return;
		} else if (exact<5>::funct(b,c,d,e,f,a)) {
			H.span_group(b,c,d,e,f);return;
		} else {
			const size_t a_order{elem_order(a)};
			const size_t b_order{elem_order(b)};
			const size_t c_order{elem_order(c)};
			const size_t d_order{elem_order(d)};
			const size_t e_order{elem_order(e)};
			const size_t f_order{elem_order(f)};
			
			elem_mgm_t A{a};
			for(size_t i{0} ; i < a_order ; ++i) {
				elem_mgm_t B{b};
				for(size_t j{0} ; j < b_order ; ++j) {
					elem_mgm_t C{c};
					for(size_t k{0} ; k < c_order ; ++k) {
						elem_mgm_t D{d};
						for(size_t l{0} ; l < d_order ; ++l) {
							elem_mgm_t E{e};
							for(size_t m{0} ; m < e_order ; ++m) {
								elem_mgm_t F{f};
								for(size_t n{0} ; n < f_order ; ++n) {
									if (exact<6>::funct(A,B,C,D,E,F)) {
										array<const elem_mgm_t,6> arg{A,B,C,D,E,F};
										sort(arg.begin(),arg.end());
										while(! next_permutation(arg.begin(),arg.end())) {
											insert_op(arg[0],arg[1],arg[2],arg[3],arg[4],arg[5]);
										}
									}
									F = mgm_op(F,f);
								}
								E = mgm_op(E,e);
							}
							D = mgm_op(D,d);
						}
						C = mgm_op(C,c);
					}
					B = mgm_op(B,b);
				}
				if (H==subset_of_magma_t{init_default_ways::maximal}) {
					return;
				}
				A = mgm_op(A,a);
			}
			return;
		}
	}
	
	inline static void
	partial_span_group(subset_of_magma_t & H,const subset_of_magma_t & generadores) {
		const elem_mgm_t id{mgm_id()};
		for(elem_mgm_t i : generadores) {
			partial_span_group(H,i);
		}
		if (H==subset_of_magma_t{init_default_ways::maximal})
				return;
		const subset_of_magma_t control{H};
		for(elem_mgm_t i : generadores) {
			if (i != id) {
				for(elem_mgm_t j : generadores) {
					if ((j != id)&&(i != j)) {
						partial_span_group(H,i,j);
					}
				}
			}
			if (H==subset_of_magma_t{init_default_ways::maximal})
				return;
		}
		return;
	}
	
	const subset_of_magma_t &
	span_group(const subset_of_magma_t & generadores) {
		const subset_of_magma_t universe_group{init_default_ways::maximal};
		while((*this)!=universe_group) {
			subset_of_magma_t control{*this};
			partial_span_group(*this,generadores);
			if ((*this)==control)
				return (*this);
		}
		return (*this);
	}
	
	const subset_of_magma_t &
	span_group(const elem_mgm_t & a ,const elem_mgm_t & b) {
		span_group(a);
		span_group(b);
		partial_span_group(*this,a,b);
		span_group();
		return (*this);
	}
	
	const subset_of_magma_t &
	span_group(
		const elem_mgm_t & a,
		const elem_mgm_t & b,
		const elem_mgm_t & c
	) {
		span_group(a,b);
		span_group(a,c);
		span_group(b,c);
		partial_span_group(*this,a,b,c);
		span_group();
		return (*this);
	}
	
	const subset_of_magma_t &
	span_group(
		const elem_mgm_t & a,
		const elem_mgm_t & b,
		const elem_mgm_t & c,
		const elem_mgm_t & d
	) {
		span_group(a,b,c);
		span_group(a,b,d);
		span_group(a,c,d);
		span_group(b,c,d);
		partial_span_group(*this,a,b,c,d);
		span_group();
		return (*this);
	}
	
	const subset_of_magma_t &
	span_group(
		const elem_mgm_t & a,
		const elem_mgm_t & b,
		const elem_mgm_t & c,
		const elem_mgm_t & d,
		const elem_mgm_t & e
	) {
		span_group(a,b,c,d);
		span_group(a,b,c,e);
		span_group(a,b,d,e);
		span_group(a,c,d,e);
		span_group(b,c,d,e);
		partial_span_group(*this,a,b,c,d,e);
		span_group();
		return (*this);
	}
	
	const subset_of_magma_t &
	span_group(
		const elem_mgm_t & a,
		const elem_mgm_t & b,
		const elem_mgm_t & c,
		const elem_mgm_t & d,
		const elem_mgm_t & e,
		const elem_mgm_t & f
	) {
		span_group(a,b,c,d,e);
		span_group(a,b,c,d,f);
		span_group(a,b,c,e,f);
		span_group(a,b,d,e,f);
		span_group(a,c,d,e,f);
		span_group(b,c,d,e,f);
		partial_span_group(*this,a,b,c,d,e,f);
		span_group();
		return (*this);
	}
	
	const subset_of_magma_t &
	span_group() {
		for (size_t k{} ; k < card() ; ++k ) {
			const subset_of_magma_t generadores{*this};
			partial_span_group(*this,generadores);
			if ((*this) == generadores)
				return (*this);
		}
		return (*this);
	}
	
	subset_of_magma_t normalizer(const subset_of_magma_t & H) const {
		subset_of_magma_t the_normalizer{};
		for(auto h : H) {
			the_normalizer.setdata.insert(h);
		}
		subset_of_magma_t C{centralizer(H)};
		for (auto c : C) {
			the_normalizer.insert(c);
		}
		subset_of_magma_t joindiff{C};
		for(auto h : H) {
			joindiff.insert(h);
		}
		subset_of_magma_t cthis(*this);
		for (auto q : joindiff){
			cthis.setdata.erase(q);
		}

		for(auto g : cthis) {
			bool el_conjugado_esta_en_cthis{true};
			for(auto h : H) {
				const elem_mgm_t gh{mgm_op(g,h)};
				const elem_mgm_t g_inv{g.mgm_inv()};
				const elem_mgm_t x{mgm_op(gh,g_inv)};
				if(H.count(x)==0){
					el_conjugado_esta_en_cthis = false;
					break;
				}
			}
			if (el_conjugado_esta_en_cthis){
				the_normalizer.insert(g);
			}
		}
		partial_span_group(the_normalizer,H);
		the_normalizer.span_group();
		return the_normalizer;
	}

	static subset_of_magma_t commutator_group(const subset_of_magma_t & K,const subset_of_magma_t & H) {
		subset_of_magma_t the_commutator{};

		for(auto h : H) {
			for(auto k : K) {
				const elem_mgm_t Ck_hC{left_commutator(h,k)};
				the_commutator.insert(Ck_hC);
			}
		}
		span_group(the_commutator);
		return the_commutator;
	}
	
	static void generate_commutator_elements(
			subset_of_magma_t & the_commutator,
			const subset_of_magma_t & K,
			const subset_of_magma_t & H,
			bool first_time
		){
		if (first_time) {
			the_commutator.do_empty();
		}

		for(auto h : H) {
			for(auto k : K) {
				const elem_mgm_t l{k.left_commutator(h)};
				the_commutator.insert(l);
				the_commutator.insert(gr_inv(l));
			}
		}
	}

	inline static subset_of_magma_t 
	generate_commutator(const subset_of_magma_t & K,const subset_of_magma_t & H) {
		subset_of_magma_t the_commutator{};
		generate_commutator_elements(the_commutator,K,H,true);
		the_commutator.span_group();
		return the_commutator;
	}

	subset_of_magma_t commutator(const subset_of_magma_t & H) const {
		subset_of_magma_t result{generate_commutator(*this,H)};
		return result;
	}
	
	bool exists_gr_identity() const {
		elem_mgm_t id{mgm_id()};
		if (count(id)==0)
			return false;
		else
			return true;
	}
	
	bool exists_all_inverses() const{
		const elem_mgm_t id{mgm_id()};
		for(auto a : *this) {
			if (count(gr_inv(a))==0)
				return false;
		}
		return true;
	}
	
	subset_of_magma_t derived(UIntType N) const {
		subset_of_magma_t K{*this};
		if (N!=0) {
			for(UIntType n{0} ; n < N ; ++n){
				K = K.commutator(K);
			}
			return K;
		}
		else
			return K;
	}

	subset_of_magma_t L_derived(UIntType N) const {
		subset_of_magma_t K{*this};
		const subset_of_magma_t & L{*this};
		if ((N)!=0) {
			for(UIntType n{0} ; n < N ; ++n){
				K = K.commutator(L);
			}
			return K;
		}
		else
			return K;
	}
	
	bool is_nilpotent() const {
		subset_of_magma_t DG{this->derived(1)};
		subset_of_magma_t UNIT(init_default_ways::minimal);
		for(UIntType i{0} ; i < card() ; ++i){
			DG = DG.commutator(*this);
		}
		if (DG == UNIT) return true;
		else return false;
	}
	
	bool is_solvable() const {
		subset_of_magma_t DG{this->derived(1)};
		subset_of_magma_t UNIT(init_default_ways::minimal);
		
		for(UIntType i{0} ; i < card() ; ++i){
			DG = DG.commutator(DG);
		}
		if (DG == UNIT) return true;
		else return false;
	}
	
	bool is_normalized_for(const subset_of_magma_t & H) {
		subset_of_magma_t NH{normalizer(H)};
		if (NH == (*this))	return true;
		else				return false;
	}
	
	std::string to_string(const std::string & X) const {
		std::string result{"{\\left\\lbrace{"};
		const auto 	itend{this->cend()};
		auto	it{this->cbegin()};
		for(; it != itend  ; ++it ) {
			result = result + (it->to_string(X));
			if (std::next(it)!=itend)
				result += ",";
		}
		result = result + "}\\right\\rbrace}";
		return result;
	}

};

}
#endif //subset_of_magma_t_HPP_INCLUDED
