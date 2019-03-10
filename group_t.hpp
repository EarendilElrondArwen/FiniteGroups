/*
 * group_t.hpp
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

#ifndef GROUP_T_HPP_INCLUDED
#define GROUP_T_HPP_INCLUDED

#include "element_of_group_t.hpp"
#include <cstdlib>
#include <algorithm>
#include <set>

namespace tfg {

template<	group_name 	gn	,
			uint 		N_n	,
			uint ...	N_nm1
		>
using group_set_t =
	typename std::set<
		element_of_group_t<gn,N_n,N_nm1...>
	>;

template<	group_name 	gn	,
			uint 		N_n	,
			uint ...	N_nm1
		>
using group_const_iterator =
	typename	group_set_t<
					gn,N_n,N_nm1...
				>::const_iterator;

template<	group_name 		gn	,
			uint 			N_n	,
			uint ...		N_nm1
		>
using const_group_const_iterator =
	const group_const_iterator<gn,N_n,N_nm1...>;

///////////////////////////////////////////////////////////////////
//				producto cartesiano generico (casi) vacio		 //
///////////////////////////////////////////////////////////////////
template<	group_name 		gn	,
			uint 			N_n	,
			uint ...		N_nm1
		>
struct group_t {
public:
	using op_t 		=
		group_binop_t		<gn,N_n,N_nm1...>;
	using elem_gr_t =
		element_of_group_t<gn,N_n,N_nm1...>;
	using elem_t 	=
		element_of_set_t	<   N_n,N_nm1...>;
	using set_of_gr_elem_t =
		typename std::set< elem_gr_t >;
	using const_iterator =
		typename set_of_gr_elem_t::const_iterator;
	using insert_result_type =
		typename std::pair<const_iterator,bool>;
	static constexpr uint max_N = elem_t::max_N;
	static constexpr uint max_dim = elem_t::max_dim;

	static constexpr uint
		Order_Of_This_Group = elem_t::Order_Of_This_Group;

	/// BEGIN : DATA MEMBER ///
	set_of_gr_elem_t setdata;
	/// END : DATA MEMBER	///

	constexpr
	auto do_empty() {
		return this->setdata.clear();
	}

	constexpr
	std::size_t cardinal() const {
		return this->setdata.size();
	}

	constexpr
	std::size_t count(
		const elem_gr_t & a
	) const {
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
	insert_result_type insert(
		const elem_gr_t & elem
	) {
		return this->setdata.insert(elem);
	}

	constexpr
	group_t() : setdata{set_of_gr_elem_t()} {}

	constexpr
	group_t(const group_t &)=default;

	constexpr
	group_t(group_t &&)=default;

	constexpr
	group_t& operator=(
		const group_t& arg
	) {
		this->setdata.clear();
		for(auto a : arg.setdata) {
			this->setdata.insert(a);
		}
		return (*this);
	}

	constexpr
	group_t& operator=(group_t&&)=default;

	constexpr
	uint direct_product_card() const {
		elem_gr_t x;
		const elem_gr_t unit{x};
		x.m_next();
		uint num{1};
		while(x != unit) {
			x.m_next();
			++num;
		}
		return num;
	}

	void fill_the_group(){
		this->do_empty();
		elem_gr_t x;
		const elem_gr_t unit{x};
		this->group_t::insert(x);
		x.m_next();

		while(x != unit) {
			this->group_t::insert(x);
			x.m_next();
		}

		this->group_t::insert(elem_gr_t());
	}

	bool operator != (const group_t & B) const {
		return(
			(!(this->is_subgroup_of(B)))
						||
			(!(B.is_subgroup_of(*this)))
		);
	}

	bool operator == (const group_t & B) const {
		return(
			(this->is_subgroup_of(B))
				&&
			(B.is_subgroup_of(*this))
		);
	}

	bool operator < (const group_t & B) const {
		if (this->is_proper_subgroup_of(B)) return true;
		else if (B.is_subgroup_of(*this)) return false;
		else {
			if (this->cardinal() < B.cardinal()) return true;
			else if (this->cardinal() > B.cardinal()) return false;
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

	bool operator <= (const group_t & B) const
	{
		if (this->is_subgroup_of(B))
			return true;
		else if (B.is_proper_subgroup_of(*this))
			return false;
		else {
			if (this->cardinal() < B.cardinal())
				return true;
			else if (this->cardinal() > B.cardinal())
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

	bool operator > (const group_t & B) const
	{
		if (B.is_proper_subgroup_of(*this))
			return true;
		else if (this->is_subgroup_of(B))
			return false;
		else {
			if (this->cardinal() > B.cardinal())
				return true;
			else if (this->cardinal() < B.cardinal())
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

	bool operator >= (const group_t & B) const {
		if (B.is_subgroup_of(*this))
			return true;
		else if (this->is_subgroup_of(B))
			return false;
		else {
			if (this->cardinal() > B.cardinal())
				return true;
			else if (this->cardinal() < B.cardinal())
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

	bool is_empty() const {
		if (this->setdata.size()==0)
			return true;
		else
			return false;
	}

	bool is_unitary() const {
		if (this->setdata.size()==1)
			return true;
		else
			return false;
	}

	bool has_got_elem(const elem_gr_t & a) const {
		if (this->setdata.size()==0)
			return false;
		else {
			if (this->setdata.count(a)!=0)
				return true;
			else
				return false;
		}
	}

	bool is_subgroup_of(const group_t & B) const
	{
		if (this->cardinal()>B.cardinal())
			return false;
		else {
			for( auto a : *this ) {
				if (B.setdata.count(a)==0)
					return false;
			}
			return true;
		}
	}

	bool is_proper_subgroup_of(const group_t & B)const
	{
		if (this->cardinal()>=B.cardinal())
			return false;
		else {
			for(auto a : *this){
				if (B.count(a)==0)
					return false;
			}
			return true;
		}
	}

	static elem_gr_t bop(elem_gr_t a,elem_gr_t b)
	{
		return op_t::gr_bop(a,b);
	}

	group_t centralizer(const group_t & H) const
	{
		group_t the_centralizer{};
		the_centralizer.do_empty();
		for(auto g : this->setdata) {
			bool commute_with_H = true;
			for(auto h : H.setdata) {
				if (!(h.commute(g))){
					commute_with_H = false;
					break;
				}
			}
			if (commute_with_H) {
				the_centralizer.setdata.insert(g);
			}
		}
		return the_centralizer;
	}

	group_t centre() const {
		group_t the_centre{};
		the_centre.do_empty();
		for(auto g : *this) {
			uint t{0};
			for(auto h : *this) {
				if (g.commute(h)) {
					++t;
				}
			}
			if (t == Order_Of_This_Group) {
				the_centre.insert(g);
			}
		}
		return the_centre;
	}
set_of_gr_elem_t
	bool is_inner_binary_operation() const {
		for(auto x : setdata) {
			for (auto y : setdata) {
				if (!(this->has_got_elem(bop(x,y)))) {
					return false;
				}
			}
		}
		return true;
	}

	bool is_inner_inverter() const {
		for(auto x: thid->setdata) {
			if(!(this->has_got_elem(x.inv()))) {
				return false;
			}
		}
		return true;
	}

	std::pair<elem_gr_t,bool> give_me_the_first_resbop_notin() const {
		std::pair<elem_gr_t,bool> result;
		for(auto x : setdata) {
			for (auto y : setdata) {
				elem_gr_t z{bop(x,y)};
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

	std::pair<elem_gr_t,bool>
	give_me_the_first_resinv_notin() const
	{
		std::pair<elem_gr_t,bool> result;
		for (auto x : this->setdata) {
			elem_gr_t z{x.inv()};
			if (!this->has_got_elem(z)) {
				result.first	= z;
				result.second	= true;
				return result;
			}
		}
		result.second = false;
		return result;
	}

	static void span_subgroup(
					group_t		& H ,
			const	group_t 	& cH,
			const	elem_gr_t 	& a ,
			const	elem_gr_t 	& b
		){
		elem_gr_t rebop{bop(a,b)};
		if (!(cH.has_got_elem(rebop))) {
			H.insert(rebop);
		}
		rebop = bop(a.inv(),b);
		if (!(cH.has_got_elem(rebop))) {
			H.insert(rebop);
		}
		rebop = bop(a.inv(),b.inv());
		if (!(cH.has_got_elem(rebop))) {
			H.insert(rebop);
		}
		rebop = bop(a,b.inv());
		if (!(cH.has_got_elem(rebop))) {
			H.insert(rebop);
		}
		rebop = bop(b,a);
		if (!(cH.has_got_elem(rebop))) {
			H.insert(rebop);
		}
		rebop = bop(b,a.inv());
		if (!(cH.has_got_elem(rebop))) {
			H.insert(rebop);
		}
		rebop = bop(b.inv(),a.inv());
		if (!(cH.has_got_elem(rebop))) {
			H.insert(rebop);
		}
		rebop = bop(b.inv(),a);
		if (!(cH.has_got_elem(rebop))) {
			H.insert(rebop);
		}
	}

	static void span_subgroup(
		group_t & H,
			const group_t & cH
		) {
		while(true) {
			group_t dH{H};
			while(true){
				group_t cH2{H};
				for(auto ch : cH.setdata) {
					const elem_gr_t notch{ch.inv()};
					if (!(cH.has_got_elem(notch))) {
						H.insert(notch);
					}
				}
				if (cH2 == H) break;
			}
			while(true){
				group_t cH3{H};
				for(auto ch : cH.setdata) {
					for(auto c2h : cH.setdata) {
						span_subgroup(H,cH3,ch,c2h);
					}
				}
				if (cH3 == H) break;
			}
			if (dH == H) break;
		}
	}

	group_t normalizer(const group_t & H) const {
		group_t the_normalizer{};
		the_normalizer.do_empty();
		for(auto h : H.setdata) {
			the_normalizer.setdata.insert(h);
		}
		group_t C{this->centralizer(H)};
		for (auto c : C.setdata) {
			the_normalizer.setdata.insert(c);
		}
		group_t joindiff{C};
		for(auto h : H.setdata) {
			joindiff.setdata.insert(h);
		}
		group_t cthis(*this);
		for (auto q : joindiff.setdata){
			cthis.setdata.erase(q);
		}

		for(auto g : cthis.setdata) {
			bool el_conjugado_esta_en_cthis{true};
			for(auto h : H.setdata) {
				const elem_gr_t gh{bop(g,h)};
				const elem_gr_t g_inv(g.inv());
				const elem_gr_t x{bop(gh,g_inv)};
				if(H.setdata.count(x)==0){
					el_conjugado_esta_en_cthis = false;
					break;
				}
			}
			if (el_conjugado_esta_en_cthis){
				the_normalizer.setdata.insert(g);
			}
		}
		span_subgroup(the_normalizer,H);
		return the_normalizer;
	}

	static group_t commutator_group(
			const group_t & K,
			const group_t & H
		) {
		group_t the_commutator{};
		the_commutator.do_empty();

		for(auto h : H.setdata) {
			for(auto k : K.setdata) {
				const elem_gr_t kh{bop(k,h)};
				const elem_gr_t kinv{k.inv()};
				const elem_gr_t hinv{h.inv()};
				const elem_gr_t kinvhinv{bop(kinv,hinv)};
				const elem_gr_t Ck_hC{bop(kh,kinvhinv)};
				the_commutator.insert(Ck_hC);
			}
		}
		group_t c_commutator{the_commutator};
		span_subgroup(the_commutator,c_commutator);
		return the_commutator;
	}

	bool has_the_trusthed_unity() const {
		for(auto e : setdata){
			bool found{true};// suposicion e es el neutro
			for(auto b : setdata){
				if (bop(e,b)==b){
					if (bop(b,e)==b) {
						continue;
					}
					else {
						found = false;
						break;
					}
				}
				else {
					found = false;
					break;
				}
			}
			if (found) return true;
		}
		return false;
	}

	std::pair<elem_gr_t,bool> get_the_trusthed_unity() const {
		std::pair<elem_gr_t,bool> result;
		bool found{true};
		elem_gr_t neutro{};
		for(auto e : setdata){
			found = true;// suposicion e es el neutro
			neutro = e;
			for(auto b : setdata){
				if (bop(e,b)==b){
					if (bop(b,e)==b) {
						return std::make_pair(neutro,true);
					}
					else {
						found = false;
						continue;
					}
				}
				else {
					found = false;
					continue;
				}
			}
			if (found){
				result.first = neutro;
				result.second = true;
				return result;
			}
		}
		if(found) {
			result.first = neutro;
			result.second = true;
			return result;
		}
		else {
			result.first = elem_gr_t();
			result.second = false;
			return result;
		}
	}

	static void generate_commutator_elements(
			group_t & the_commutator,
			const group_t & K,
			const group_t & H,
			bool first
		){
		if (first) {
			the_commutator.do_empty();
		}

		for(auto h : H) {
			for(auto k : K) {
				const elem_gr_t kh{bop(k,h)};
				const elem_gr_t kinv{k.inv()};
				const elem_gr_t hinv{h.inv()};
				const elem_gr_t kinvhinv{bop(kinv,hinv)};
				const elem_gr_t Ck_hC{bop(kh,kinvhinv)};
				the_commutator.insert(Ck_hC);
				the_commutator.insert(Ck_hC.inv());
			}
		}
	}

	static group_t generate_group_from_set(group_t & G) {
		const group_t G_initial_reference{G};
		for(auto h :  G_initial_reference.setdata){
			for(auto k :  G_initial_reference.setdata){
				const elem_gr_t hi{h};
				const elem_gr_t kj{k};
				const elem_gr_t inv_hi{h.inv()};
				const elem_gr_t inv_kj{k.inv()};
				G.insert(bop(kj,hi));
				G.insert(bop(hi,kj));
				G.insert(bop(inv_kj,hi));
				G.insert(bop(inv_kj,inv_hi));
				G.insert(bop(kj,inv_hi));
				G.insert(bop(inv_hi,kj));
				G.insert(bop(inv_hi,inv_kj));
				G.insert(bop(hi,inv_kj));

				G.insert(bop(kj,hi).inv());
				G.insert(bop(hi,kj).inv());
				G.insert(bop(inv_kj,hi).inv());
				G.insert(bop(inv_kj,inv_hi).inv());
				G.insert(bop(kj,inv_hi).inv());
				G.insert(bop(inv_hi,kj).inv());
				G.insert(bop(inv_hi,inv_kj).inv());
				G.insert(bop(hi,inv_kj).inv());
			}
		}
		const group_t cG{G};
		span_subgroup(G,cG);
		return G;
	}


	static group_t generate_commutator(
			const group_t & K,
			const group_t & H
		) {
		group_t the_commutator{};
		the_commutator.setdata.clear();
		generate_commutator_elements(the_commutator,K,H,true);
		while(true) {
			const group_t the_old_commutator{the_commutator};
			generate_group_from_set(the_commutator);
			if (the_commutator == the_old_commutator) break;
		}
		return the_commutator;
	}

	group_t commutator(const group_t & H) const {
		group_t result{group_t::generate_commutator(*this,H)};
		return result;
	}

	bool dp_unit_equal_gr_unit() const {
		auto result{this->get_the_trusthed_unity()};
		if (result.second) {
			auto defecto{elem_gr_t()};
			return (defecto == result.first);
		}
		else {
			return false;
		}
	}

	elem_gr_t inv(const elem_gr_t & a) const {
		auto result{this->get_the_trusthed_unity()};
		elem_gr_t unity{elem_gr_t()};
		if (result.second)
			unity = result.first;
		for(auto b : setdata) {
			if ((bop(a,b)==unity)and(bop(b,a)==unity)) {
				return b;
			}
		}
		return elem_gr_t();
	}

	bool exists_inverse_for_every_element() const{
		const elem_gr_t unity{(this->get_the_trusthed_unity()).first};
		for(auto a : setdata) {
			elem_gr_t inva{this->group_t::inv(a)};
			if (	(bop(a,inva)!=unity) ||
					(bop(inva,a)!=unity) 	)
			{
				return false;
			}
		}
		return true;
	}

	bool is_associative() const {
		const elem_gr_t unity{(this->get_the_trusthed_unity()).first};
		for(auto a : setdata){
			for(auto b : setdata){
				for(auto c : setdata){
					if((a!=unity)&&(b!=unity)&&(c!=unity)){
						if ((bop(a,bop(b,c)))
							!=
							bop((bop(a,b)),c))
						return false;
					}
				}
			}
		}
		return true;
	}

	bool is_abelian() const {
		const elem_gr_t unity{(this->get_the_trusthed_unity()).first};
		for(auto a : setdata)
			for(auto b : setdata)
				if((a!=unity)&&(b!=unity))
					if (bop(a,b)
						!=
						(bop(b,a)))
						return false;
		return true;
	}

	group_t derived(uint N) const {
		group_t K{*this};
		if ((N)!=0) {
			for(uint n{0} ; n < N ; ++n){
				K = K.commutator(K);
			}
			return K;
		}
		else
			return K;
	}

	group_t L_derived(uint N) const {
		group_t K{*this};
		const group_t & L{*this};
		if ((N)!=0) {
			for(uint n{0} ; n < N ; ++n){
				K = K.commutator(L);
			}
			return K;
		}
		else
			return K;
	}


	bool is_nilpotent() const {
		group_t DG{this->derived(1)};
		group_t UNIT{};
		UNIT.do_empty();
		UNIT.insert(elem_gr_t());
		for(uint i{0} ; i < max_N ; ++i){
			DG = DG.commutator(*this);
		}
		if (DG == UNIT) return true;
		else return false;
	}

	bool is_solvable() const {
		group_t DG{this->derived(1)};
		group_t UNIT{};
		if (UNIT.is_empty()) {
			UNIT.insert(elem_gr_t());
		}
		for(uint i{0} ; i < max_N ; ++i){
			DG = DG.commutator(DG);
		}
		if (DG == UNIT) return true;
		else return false;
	}

	bool is_normalized_for(const group_t & H){
		group_t NH{normalizer(H)};
		if (NH == (*this))	return true;
		else				return false;
	}


	std::string to_string(const std::string & X) {
		std::string result{"{\\left\\lbrace{"};
		const auto 	itend{this->group_t::cend()};
		auto	it{this->group_t::begin()};
		for(; it != itend  ; ++it ) {
			result = result + (it->to_string(X));
			if (std::next(it)!=itend)
				result += ",";
		}
		result = result + "}\\right\\rbrace}";
		return result;
	}

};


///////////////////////////////////////////////////////////////////
//				producto cartesiano 1							 //
///////////////////////////////////////////////////////////////////

template<group_name gn,uint N1>
struct group_t<gn,N1>
{
public:
	static_assert(N1>1);
	using op_t = group_binop_t<gn,N1>;
	using elem_gr_t = element_of_group_t<gn,N1>;
	using elem_t = element_of_set_t<N1>;
	using own_base_type = std::set< elem_gr_t >;
	using const_iterator = typename own_base_type::const_iterator;
	using insert_result_type = std::pair<const_iterator,bool>;
	static constexpr uint max_N = N1-1;
	static constexpr uint max_dim = 1;
	//const uint max_num_elems{this->direct_product_card()};
	static constexpr uint Order_Of_This_Group = N1;
	own_base_type setdata;

	//uint order() const;
	//uint cardinal() const;
	//const_iterator begin() const;
	//const_iterator end() const;
	//const const_iterator cbegin() const;
	//const const_iterator cend() const;
	//bool is_empty() const;
	//bool is_unitary() const;
	//bool exists_inverse_for_every_element() const;
	//bool has_the_trusthed_unity() const;
	//bool is_associative() const;
	//bool exists_inverse_for_every_element() const;
	//bool is_nilpotent() const;
	//bool is_solvable() const;
	//bool is_abelian() const;

	auto do_empty() {
		return this->setdata.clear();
	}

	uint order() const {
		return this->setdata.size();
	}

	uint count(const elem_gr_t & a) const {
		return this->setdata.count(a);
	}

	const_iterator begin() const {
		return this->setdata.begin();
	}

	const_iterator end() const {
		return  this->setdata.end();
	}

	const const_iterator cbegin() const {
		return  this->setdata.cbegin();
	}

	const const_iterator cend() const {
		return  this->setdata.cend();
	}

	auto insert(const elem_gr_t & el) {
		return this->setdata.insert(el);
	}

	group_t(const group_t &)=default;
	group_t(group_t &&)=default;
	group_t(): setdata{} {}
	group_t& operator=(group_t &)=default;
	group_t& operator=(group_t &&)=default;
	const group_t& operator=(const group_t & arg) {
		setdata=arg.setdata;
		return (*this);
	}
	void fill_the_group(){
		do_empty();
		for( uint u=0 ; u < N1 ; ++u ) {
			this->setdata.insert(elem_t(u));
		}
	}

	bool is_empty() const {
		if (this->setdata.size()==0) return true;
		else return false;
	}

	bool is_unitary() const {
		if (this->setdata.size()==1) return true;
		else return false;
	}


	bool is_subgroup_of(const group_t & B) const{
		if (this->cardinal()>B.cardinal()) return false;
		else {
			for( auto a : *this ) {
				if (B.count(a)==0) return false;
			}
			return true;
		}
	}

	bool is_proper_subgroup_of(const group_t & B)const {
		if (this->cardinal()>=B.cardinal()) return false;
		else {
			for(auto a : *this){
				if (B.count(a)==0) return false;
			}
			return true;
		}
	}

	bool operator != (const group_t & B) const {
		return ((!(is_subgroup_of(B)))||(!(B.is_subgroup_of(*this))));
	}

	bool operator == (const group_t & B) const {
		return ((is_subgroup_of(B))&&(B.is_subgroup_of(*this)));
	}

	bool operator < (const group_t & B) const {
		if (is_proper_subgroup_of(B)) return true;
		else if (B.is_subgroup_of(*this)) return false;
		else {
			if (this->cardinal() < B.cardinal()) return true;
			else if (this->cardinal() > B.cardinal()) return false;
			else {
				const_iterator itcthis{begin()};
				const_iterator itB{B.begin()};
				const const_iterator itendcthis{cend()};
				const const_iterator itendB{B.cend()};
				for(;(itcthis != itendcthis)     &&      itB != itendB;
					++itcthis                    ,              ++itB)
				{
					if ((*itcthis)<(*itB)) return true;
					else if ((*itcthis)>(*itB)) return false;
				}
				return false;
			}
		}
	}

	bool operator <= (const group_t & B) const {
		if (is_subgroup_of(B)) return true;
		else if (B.is_proper_subgroup_of(*this)) return false;
		else {
			if (this->cardinal() < B.cardinal()) return true;
			else if (this->cardinal() > B.cardinal()) return false;
			else {
				const_iterator itcthis{begin()};
				const_iterator itB{B.begin()};
				const const_iterator itendcthis{cend()};
				const const_iterator itendB{B.cend()};
				for(;(itcthis != itendcthis)     &&      itB != itendB;
						++itcthis                    ,              ++itB)
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

	bool operator > (const group_t & B) const {
		if (B.is_proper_subgroup_of(*this)) return true;
		else if (is_subgroup_of(B)) return false;
		else {
			if (this->cardinal() > B.cardinal()) return true;
			else if (this->cardinal() < B.cardinal()) return false;
			else {
				const_iterator itcthis{begin()};
				const_iterator itB{B.begin()};
				const const_iterator itendcthis{cend()};
				const const_iterator itendB{B.cend()};
				for(;(itcthis != itendcthis)     &&      itB != itendB;
					++itcthis                    ,              ++itB)
				{
					if ((*itcthis)>(*itB)) return true;
					else if ((*itcthis)<(*itB)) return false;
				}
				return false;
			}
		}
	}

	bool operator >= (const group_t & B) const {
		if (B.is_subgroup_of(*this)) return true;
		else if (is_subgroup_of(B)) return false;
		else {
			if (this->cardinal() > B.cardinal()) return true;
			else if (this->cardinal() < B.cardinal()) return false;
			else {
				const_iterator itcthis{begin()};
				const_iterator itB{B.begin()};
				const const_iterator itendcthis{cend()};
				const const_iterator itendB{B.cend()};
				for(;(itcthis != itendcthis)     &&      (itB != itendB);
					++itcthis                    ,              ++itB)
				{
					if ((*itcthis)>(*itB)) return true;
					else if ((*itcthis)<(*itB)) return false;
				}
				return true;
			}
		}
	}

	static elem_gr_t bop(elem_gr_t a, elem_gr_t b) {
		return op_t::gr_bop(a,b);
	}

	bool dp_unit_equal_gr_unit() const {
		auto result{this->get_the_trusthed_unity()};
		if (result.second) {
			auto defecto{elem_gr_t()};
			return (defecto == result.first);
		}
		else {
			return false;
		}
	}

	group_t centralizer(const group_t & H) const {
		group_t the_centralizer{};
		for(auto g : *this) {
			bool centraliza_H{true};
			for(auto h : H) {
				if (!(h.commute(g))){
					centraliza_H = false;
					break;
				}
			}
			if (centraliza_H) {
				the_centralizer.insert(g);
			}
		}
		return the_centralizer;
	}

	group_t centre() const {
		group_t the_centre{};
		the_centre.do_empty();
		for(auto g : *this) {
			uint t{0};
			for(auto h : *this) {
				if (g.commute(h)) {
					++t;
				}
			}
			if (t == N1) {
				the_centre.insert(g);
			}
		}
		return the_centre;
	}

	bool has_got_elem(const elem_gr_t & a) const {
		if (is_empty()) return false;
		else {
				if (count(a)!=0) return true;
				else return false;
		}
	}

	bool is_inner_binary_operation() const {
		for(auto x : setdata) {
			for (auto y : setdata) {
				if (!(has_got_elem(bop(x,y)))) {
					return false;
				}
			}
		}
		return true;
	}

	bool is_inner_inverter() const {
		for(auto x: setdata) {
			if(!(has_got_elem(x.inv()))) {
				return false;
			}
		}
		return true;
	}

	std::pair<elem_gr_t,bool> give_me_the_first_resbop_notin() const {
		std::pair<elem_gr_t,bool> result;
		for(auto x : setdata) {
			for (auto y : setdata) {
				elem_gr_t z{bop(x,y)};
				if (!has_got_elem(z)) {
					result.first = z;
					result.second =true;
					return result;
				}
			}
		}
		result.second = false;
		return result;
	}

	std::pair<elem_gr_t,bool>
	give_me_the_first_resinv_notin() const
	{
		std::pair<elem_gr_t,bool> result;
		for (auto x : this->setdata) {
			elem_gr_t z{x.inv()};
			if (!this->has_got_elem(z)) {
				result.first = z;
				result.second =true;
				return result;
			}
		}
		result.second = false;
		return result;
	}

	static void span_subgroup(
				group_t		& H,
		const	group_t		& cH,
		const	elem_gr_t	& ch,
		const	elem_gr_t	& c2h
	) {
		elem_gr_t rebop{bop(ch,c2h)};
		if (!(cH.has_got_elem(rebop))) {
			H.insert(rebop);
		}
		rebop = bop(c2h,ch);
		if (!(cH.has_got_elem(rebop))) {
			H.insert(rebop);
		}
		rebop = bop(ch.inv(),c2h);
		if (!(cH.has_got_elem(rebop))) {
			H.insert(rebop);
		}
		rebop = bop(ch.inv(),c2h.inv());
		if (!(cH.has_got_elem(rebop))) {
			H.insert(rebop);
		}
		rebop = bop(ch,c2h.inv());
		if (!(cH.has_got_elem(rebop))) {
			H.insert(rebop);
		}
		rebop = bop(c2h,ch);
		if (!(cH.has_got_elem(rebop))) {
			H.insert(rebop);
		}
		rebop = bop(c2h,ch.inv());
		if (!(cH.has_got_elem(rebop))) {
			H.insert(rebop);
		}
		rebop = bop(c2h.inv(),ch.inv());
		if (!(cH.has_got_elem(rebop))) {
			H.insert(rebop);
		}
		rebop = bop(c2h.inv(),ch);
		if (!(cH.has_got_elem(rebop))) {
			H.insert(rebop);
		}
	}

	static void span_subgroup(
		group_t& H,
		const group_t & cH,
		const elem_gr_t & a,
		const elem_gr_t & b,
		const uint & i,
		const uint & j
	) {
		elem_gr_t ch{a.pow(i)};
		elem_gr_t c2h{b.pow(j)};
		elem_gr_t rebop{bop(ch,c2h)};
		if (!(cH.has_got_elem(rebop))) {
			H.insert(rebop);
		}
		rebop = bop(c2h,ch);
		if (!(cH.has_got_elem(rebop))) {
			H.insert(rebop);
		}
		rebop = bop(ch.inv(),c2h);
		if (!(cH.has_got_elem(rebop))) {
			H.insert(rebop);
		}
		rebop = bop(ch.inv(),c2h.inv());
		if (!(cH.has_got_elem(rebop))) {
			H.insert(rebop);
		}
		rebop = bop(ch,c2h.inv());
		if (!(cH.has_got_elem(rebop))) {
			H.insert(rebop);
		}
		rebop = bop(c2h,ch);
		if (!(cH.has_got_elem(rebop))) {
			H.insert(rebop);
		}
		rebop = bop(c2h,ch.inv());
		if (!(cH.has_got_elem(rebop))) {
			H.insert(rebop);
		}
		rebop = bop(c2h.inv(),ch.inv());
		if (!(cH.has_got_elem(rebop))) {
			H.insert(rebop);
		}
		rebop = bop(c2h.inv(),ch);
		if (!(cH.has_got_elem(rebop))) {
			H.insert(rebop);
		}
	}

	static
	void span_subgroup(
			group_t & H	,
			const group_t & cH
		){
		while(true){
			group_t dH(H);
			while(true){
				dH = H;
				for(auto ch : cH.setdata){
					const elem_gr_t notch{ch.inv()};
					if (!(cH.has_got_elem(notch))){
						H.insert(notch);
					}
				}
				if (cH == H) break;
			}
			while(true) {
				dH  = H;
				for(auto ch : cH.setdata){
					for(auto c2h : cH.setdata){
						span_subgroup(H,cH,ch,c2h);
					}
				}
				if (cH == H) break;
			}
			if (cH == H) break;
		}
	}

	group_t normalizer(const group_t & H) const
	{
		group_t the_normalizer{};
		the_normalizer.do_empty();
		for(auto h : H.setdata) {
			the_normalizer.insert(h);
		}
		group_t C{centralizer(H)};
		for (auto c : C.setdata) {
			the_normalizer.insert(c);
		}
		/*
		std::set<elem_gr_t> join{};
		join.clear();
		std::set_union(C.begin(),C.end(),H.begin(),H.end(),
                 std::inserter(join));
		std::set<elem_gr_t> cthis(this->setdata);
		std::set<elem_gr_t> diff{};
		diff.clear();
		*/
		group_t diff{*this};
		/*
		std::set_difference(cthis.begin(),cthis.end(),join.begin().join.end(),
				std::inserter(diff.setdata));
		*/
		for(auto g : diff) {
			bool el_conjugado_esta_en_diff{true};
			for(auto h : H) {
				const elem_gr_t gh{bop(g,h)};
				const elem_gr_t g_inv(g.inv());
				const elem_gr_t x{bop(gh,g_inv)};
				if(H.count(x)==0){
					el_conjugado_esta_en_diff = false;
					break;
				}
			}
			if (el_conjugado_esta_en_diff){
				the_normalizer.insert(g);
			}
		}
		group_t c_normalizer{the_normalizer};
		span_subgroup(the_normalizer,c_normalizer);
		return the_normalizer;
	}

	static
	void generate_commutator_elements(
			group_t & the_commutator,
			const group_t & K,
			const group_t & H,
			bool first
		){
		if (first) {
			the_commutator.do_empty();
		}

		for(auto h : H) {
			for(auto k : K) {
				const elem_gr_t kh{bop(k,h)};
				const elem_gr_t kinv{k.inv()};
				const elem_gr_t hinv{h.inv()};
				const elem_gr_t kinvhinv{bop(kinv,hinv)};
				const elem_gr_t Ck_hC{bop(kh,kinvhinv)};
				the_commutator.insert(Ck_hC);
				the_commutator.insert(Ck_hC.inv());
			}
		}
	}

	static
	group_t generate_group_from_set(group_t & G)
	{
		const group_t G_initial_reference{G};
		for(auto h :  G_initial_reference.setdata){
			for(auto k :  G_initial_reference.setdata){
				const elem_gr_t hi{h};
				const elem_gr_t kj{k};
				const elem_gr_t inv_hi{h.inv()};
				const elem_gr_t inv_kj{k.inv()};
				G.insert(bop(kj,hi));
				G.insert(bop(hi,kj));
				G.insert(bop(inv_kj,hi));
				G.insert(bop(inv_kj,inv_hi));
				G.insert(bop(kj,inv_hi));
				G.insert(bop(inv_hi,kj));
				G.insert(bop(inv_hi,inv_kj));
				G.insert(bop(hi,inv_kj));

				G.insert(bop(kj,hi).inv());
				G.insert(bop(hi,kj).inv());
				G.insert(bop(inv_kj,hi).inv());
				G.insert(bop(inv_kj,inv_hi).inv());
				G.insert(bop(kj,inv_hi).inv());
				G.insert(bop(inv_hi,kj).inv());
				G.insert(bop(inv_hi,inv_kj).inv());
				G.insert(bop(hi,inv_kj).inv());
			}
		}
		const group_t cG{G};
		span_subgroup(G,cG);
		return G;
	}

	static
	group_t generate_commutator(
			const group_t & K,
			const group_t & H
		) {
		group_t the_commutator{};
		the_commutator.setdata.clear();
		generate_commutator_elements(the_commutator,K,H,true);
		while(true) {
			const group_t the_old_commutator{the_commutator};
			generate_group_from_set(the_commutator);
			if (the_commutator == the_old_commutator) break;
		}
		return the_commutator;
	}

	group_t commutator(const group_t & H) const
	{
		const group_t result{
			group_t::generate_commutator(*this,H)
		};
		return result;
	}

	static
	group_t commutator_group(
			const group_t & K,
			const group_t & H
		) {
		group_t the_commutator{};
		the_commutator.do_empty();

		for(auto h : H.setdata) {
			for(auto k : K.setdata) {
				const elem_gr_t kh{bop(k,h)};
				const elem_gr_t kinv{k.inv()};
				const elem_gr_t hinv{h.inv()};
				const elem_gr_t kinvhinv{bop(kinv,hinv)};
				const elem_gr_t Ck_hC{bop(kh,kinvhinv)};
				the_commutator.insert(Ck_hC);
			}
		}
		group_t c_commutator{the_commutator};
		span_subgroup(the_commutator,c_commutator);
		return the_commutator;
	}

	bool has_the_trusthed_unity() const {
		for(auto e : setdata){
			bool found{true};// suposicion e es el neutro
			for(auto b : setdata){
				if (bop(e,b)==b){
					if (bop(b,e)==b) {
						continue;
					}
					else {
						found = false;
						break;
					}
				}
				else {
					found = false;
					break;
				}
			}
			if (found) return true;
		}
		return false;
	}

	std::pair<elem_gr_t,bool> get_the_trusthed_unity() const
	{
		bool encontrado = false;
		std::pair<elem_gr_t,bool> result;
		for(auto e : setdata){
			bool found{true};// suposicion e es el neutro
			for(auto b : *this){
				if (bop(e,b)==b){
					if (bop(b,e)==b) {
						continue;
					}
					else {
						found = false;
						break;
					}
				}
				else {
					found = false;
					break;
				}
			}
			if (found){
				encontrado = true;
				result.first = e;
				result.second = true;
			}
		}
		if (!(encontrado)) {
			result.first = elem_gr_t();
			result.second = false;
		}
		return result;
	}

	bool exists_inverse_for_every_element() const{
		const elem_gr_t unity{};
		for(auto a : setdata) {
			elem_gr_t inva{a.inv()};
			elem_gr_t a_inv_a{bop(a,inva)};
			elem_gr_t inv_a_a{bop(inva,a)};
			if (	(a_inv_a!=unity) ||
					(inv_a_a!=unity) 	)
			{
				return false;
			}
		}
		return true;
	}

	bool is_associative() const {
		const elem_gr_t unity{};
		for(auto a : setdata)
			for(auto b : setdata)
				for(auto c : setdata)
					if((a!=unity)&&(b!=unity)&&(c!=unity))
						if ((bop(a,bop(b,c)))
							!=
							bop((bop(a,b)),c))
						return false;
		return true;
	}

	bool is_abelian() const {
		const auto unity{this->get_the_trusthed_unity()};
		for(auto a : setdata)
			for(auto b : setdata)
				if((a!=unity.first)&&(b!=unity.first))
					if (bop(a,b)
						!=
						(bop(b,a)))
						return false;
		return true;
	}

	group_t derived(uint N) const {
		if ((N%N1)!=0) {
			group_t K(*this);
			for(uint n{0} ; n < N%N1 ; ++n){
				K = K.commutator(K);
			}
			return K;
		}
		else return(*this);
	}

	group_t L_derived(uint N) const {
		if ((N%N1)!=0) {
			group_t K(*this);
			for(uint n{0} ; n < N%N1 ; ++n){
				K = K.commutator(*this);
			}
			return K;
		}
		else return(*this);
	}

	bool is_nilpotent() const {
		group_t DG{this->derived(1)};
		group_t UNIT{};
		UNIT.do_empty();
		UNIT.insert(elem_gr_t());
		for(uint i{0} ; i < max_N ; ++i){
			DG = DG.commutator(*this);
		}
		if (DG == UNIT) return true;
		else return false;
	}

	bool is_solvable() const {
		group_t DG{this->derived(1)};
		group_t UNIT{};
		UNIT.setdata.insert(elem_gr_t());
		for(uint i{0} ; i < N1 ; ++i){
			DG = DG.commutator(DG);
		}
		if (DG == UNIT) return true;
		else return false;
	}

	bool is_normalized_for(const group_t & H){
		group_t NH{normalizer(H)};
		if (NH == (*this))	return true;
		else				return false;
	}

	std::size_t cardinal() const {
		return setdata.size();
	}

	std::string to_string(const std::string & abecedario)
	{
		std::string result{"{\\left\\lbrace{"};
		auto 	itend{this->group_t::cend()};
		auto	it{this->group_t::begin()};
		for(; it != itend  ; ++it ) {
			result = result + (it->to_string(abecedario));
			if (std::next(it)!=itend)
				result += ",";
		}
		result = result + "}\\right\\rbrace}";
		return result;
	}
};

}
#endif //GROUP_T_HPP_INCLUDED
