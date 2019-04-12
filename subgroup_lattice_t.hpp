/*
 * subgroup_lattice_t.hpp
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

#ifndef LATTICE_SUBGROUP_HPP_INCLUDED
#define LATTICE_SUBGROUP_HPP_INCLUDED


#include <iostream>
#include <fstream>
#include <list>
#include <tuple>
#include <map>

#include "subset_of_magma_t.hpp"

namespace tfg{
	
	template<typename UIntType,UIntType N_n,UIntType ... N_nm1>
	using elem_t = modint_cartprod_t<UIntType,N_n,N_nm1...>;
	
	template<group_name gn,typename UIntType,UIntType N_n,UIntType ... N_nm1>
	using elem_gr_t = magma_t<gn,UIntType,N_n,N_nm1...>;
	
	template<group_name gn,typename UIntType,UIntType N_n,UIntType ... N_nm1>
	using gr_t = subset_of_magma_t<gn,UIntType,N_n,N_nm1...>;
	
	template<group_name gn,typename UIntType,UIntType N_n,UIntType ... N_nm1>
	using set_lattice_t =
		typename std::set<gr_t<gn,UIntType,N_n,N_nm1...>>;

	template<group_name gn,typename UIntType,UIntType N_n, UIntType ... N_nm1>
	using lattice_const_iterator =
		typename set_lattice_t<gn,UIntType,N_n,N_nm1...>::const_iterator;

	template<group_name gn,typename UIntType,UIntType Nn, UIntType ... Nnm1>
	using const_lattice_const_iterator =
		const lattice_const_iterator<gn,UIntType,Nn,Nnm1...>;

	template<group_name gn,typename UIntType,UIntType Nn,UIntType ... Nnm1>
	using insert_result_type =
		typename std::pair<
			lattice_const_iterator<gn,UIntType,Nn,Nnm1...>,
			bool
		>;

	template<typename UIntType,UIntType Nn,UIntType ... Nnm1>
	constexpr UIntType max_N =
		elem_t<UIntType,Nn,Nnm1...>::max_elem();

	template<typename UIntType,UIntType Nn,UIntType ... Nnm1>
	constexpr UIntType max_dim =
		elem_t<UIntType,Nn,Nnm1...>::dim();

	template<typename UIntType,UIntType Nn,UIntType ... Nnm1>
	static constexpr UIntType order =
		elem_t<UIntType,Nn,Nnm1...>::card();

	template<group_name gn,typename UIntType,UIntType Nn,UIntType ... Nnm1 >
	constexpr
	insert_result_type<gn,UIntType,Nn,Nnm1...> insert(
			set_lattice_t<gn,UIntType,Nn,Nnm1...> & container,
			const subset_of_magma_t<gn,UIntType,Nn,Nnm1...> & element
	)	{
		return container.insert(element);
	}

	template<group_name gn,typename UIntType,UIntType Nn,UIntType ... Nnm1>
	constexpr
	auto erase(
		set_lattice_t<gn,UIntType,Nn,Nnm1...> & container,
		lattice_const_iterator<gn,UIntType,Nn,Nnm1...> it
	) {
		return container.erase(it);
	}

	template<group_name gn,typename UIntType,UIntType Nn,UIntType ... Nnm1>
	constexpr
	void fill_the_subgroups_from_1_generator_of_lattice(
		set_lattice_t<gn,UIntType,Nn,Nnm1...> & L
	)	{
		using gr_t = subset_of_magma_t<gn,UIntType,Nn,Nnm1...>;
		gr_t G{init_default_ways::maximal};
		const typename gr_t::base_t& G_Set{G.setdata};
		for(auto x : G_Set) {
			gr_t H{};
			H.span_group(x);
			if (H.is_subgroup())
				L.insert(H);
		}
	}
	
	template<group_name gn,typename UIntType,UIntType Nn,UIntType ... Nnm1>
	constexpr
	void
	fill_the_subgroups_from_2_generators_of_lattice(
		set_lattice_t<gn,UIntType,Nn,Nnm1...>& L
	)	{
		using gr_t = subset_of_magma_t<gn,UIntType,Nn,Nnm1...>;
		using gr_set_t = subset_of_underliying_magma_t<gn,UIntType,Nn,Nnm1...>;
		// Se van a insertar los subgrupos ciclicos
		fill_the_subgroups_from_1_generator_of_lattice(L);
		// Se van a insertar los subgrupo generados por 2 elementos
		gr_t K(init_default_ways::maximal);
		const gr_set_t & K_Set(K.setdata);
		gr_t J(init_default_ways::maximal);
		const gr_set_t & J_Set(J.setdata);
		for(auto t : K_Set){
			for(auto r : J_Set){
				gr_t H{};
				H.span_group(t,r);
				if (H.is_subgroup())
					L.insert(H);
			}
		}
		//Se han insertado los subgrupos generados
		//estrictamente por 2 elementos
	}
	
	template<group_name gn,typename UIntType,UIntType Nn,UIntType ... Nnm1>
	constexpr
	void 
	fill_the_subgroups_from_3_generators_of_lattice(
		set_lattice_t<gn,UIntType,Nn,Nnm1...>& L
	)	{
		using gr_t = subset_of_magma_t<gn,UIntType,Nn,Nnm1...>;
		using gr_set_t = subset_of_underliying_magma_t<gn,UIntType,Nn,Nnm1...>;
		// Se van a insertar los subgrupos ciclicos
		// incluidos en los generados por 2 generadores
		// Tambien se van a insertar los subgrupos generados
		// por 2 generadores.
		fill_the_subgroups_from_2_generators_of_lattice(L);
		const gr_t N(init_default_ways::maximal);
		const gr_set_t& N_Set{N.setdata};
		const gr_t G(init_default_ways::maximal);
		const gr_set_t& G_Set{G.setdata};
		const gr_t S(init_default_ways::maximal);
		const gr_set_t& S_Set{S.setdata};
		
		// Se han insertado los subgrupos ciclicos
		// Se van a insertar los subgrupos
		// generados por 3 elementos
		for( auto u : G_Set ) {
			for( auto v : N_Set ) {
				for( auto w : S_Set ) {
					gr_t H{};
					H.span_group(u,v,w);
					if(H.is_subgroup())
						L.insert(H);
				}
			}
		}
		// Se han insertado los subgrupos generados
		// estrictamente por 3, 2 y 1 elementos (la
		// identidad se integra en 1 elemento, aunque 
		// formalmente no sea correcto)
	}
	
	template<group_name gn,typename UIntType,UIntType Nn,UIntType ... Nnm1>
	constexpr
	void 
	fill_the_subgroups_from_4_generators_of_lattice(
		set_lattice_t<gn,UIntType,Nn,Nnm1...>& L
	)	{
		using elem_gr_t = magma_t<gn,UIntType,Nn,Nnm1...>;
		using gr_t = subset_of_magma_t<gn,UIntType,Nn,Nnm1...>;
		//using gr_set_t = subset_of_underliying_magma_t<gn,UIntType,Nn,Nnm1...>;
		
		// Se van a insertar los subgrupos generados
		// por 3 generadores o menos.
		fill_the_subgroups_from_3_generators_of_lattice(L);
		const gr_t N(init_default_ways::maximal);
		const gr_t G(init_default_ways::maximal);
		const gr_t S(init_default_ways::maximal);
		const gr_t T(init_default_ways::maximal);
		
		for(elem_gr_t n : N) {
			for(elem_gr_t g : G) {
				for(elem_gr_t s : S) {
					for(elem_gr_t t : T) {
						gr_t generadores{init_default_ways::minimal};
						generadores.insert(n);
						generadores.insert(g);
						generadores.insert(s);
						generadores.insert(t);
						gr_t H{init_default_ways::minimal};
						H.span_group(generadores);
						if (H.is_subgroup())
							L.insert(H);
					}
				}
			}
		}
	}
	
	template<group_name gn,typename UIntType,UIntType Nn,UIntType ... Nnm1>
	constexpr
	void generate_right_equivalence_classes(
		set_lattice_t<gn,UIntType,Nn,Nnm1...>&	L,
		const subset_of_magma_t<gn,UIntType,Nn,Nnm1...>&	G,
		const subset_of_magma_t<gn,UIntType,Nn,Nnm1...>&	H
	)	{
		using gr_t = subset_of_magma_t<gn,UIntType,Nn,Nnm1...>;
		L.clear();
		const subset_of_underliying_magma_t<gn,UIntType,Nn,Nnm1...>& G_Set{G.setdata};
		const subset_of_underliying_magma_t<gn,UIntType,Nn,Nnm1...>& H_Set{H.setdata};
		for(auto g : G_Set) {
			gr_t equiv_class{};
			equiv_class.do_empty();
			equiv_class.insert(g);
			for(auto h : H_Set) {
				equiv_class.insert(gr_t::gr_bop(g,h));
			}
			L.insert(equiv_class);
		}
	}

	template<group_name gn,typename UIntType,UIntType Nn,UIntType ... Nnm1>
	constexpr
	void generate_left_equivalence_classes(
		set_lattice_t<gn,UIntType,Nn,Nnm1...>&	L,
		const subset_of_magma_t<gn,UIntType,Nn,Nnm1...>&	G,
		const subset_of_magma_t<gn,UIntType,Nn,Nnm1...>&	H
	)	{
		using gr_t = subset_of_magma_t<gn,UIntType,Nn,Nnm1...>;
		L.clear();
		const subset_of_underliying_magma_t<gn,UIntType,Nn,Nnm1...>& G_Set{G.setdata};
		const subset_of_underliying_magma_t<gn,UIntType,Nn,Nnm1...>& H_Set{H.setdata};
		for(auto g : G_Set) {
			gr_t equiv_class{};
			equiv_class.do_empty();
			equiv_class.insert(g);
			for(auto h : H_Set) {
				equiv_class.insert(gr_t::bop(g,h));
			}
			L.insert(equiv_class);
		}
	}

	template<group_name gn,typename UIntType,UIntType Nn,UIntType ... Nnm1>
	std::string to_string(
		std::string& result,
		const set_lattice_t<gn,UIntType,Nn,Nnm1...>& container,
		const std::string & abecedario
	)	{
		using gr_t = subset_of_magma_t<gn,UIntType,Nn,Nnm1...>;
		result="";
		result += "\\left\\lbrace\\right.{\n";
		const_lattice_const_iterator<gn,UIntType,Nn,Nnm1...>
			itend=container.cend();
		lattice_const_iterator<gn,UIntType,Nn,Nnm1...>
			it=container.begin();
		for(; it != itend ; ++it ) {
			gr_t gr{*it};
			result += (gr.to_string(abecedario));
			if (std::next(it) != itend)
				result += " , \n";
		}
		result += "\n}\\left.\\right\\rbrace";
		return result;
	}

}

#endif // LATTICE_SUBGROUP_HPP_INCLUDED
