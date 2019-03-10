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

#include "group_t.hpp"

namespace tfg{
	template<group_name gn,uint Nn, uint ... Nnm1>
	using set_lattice_t =
		typename std::set<group_t<gn,Nn,Nnm1...>>;

	template<group_name gn,uint Nn, uint ... Nnm1>
	using lattice_const_iterator =
		typename set_lattice_t<gn,Nn,Nnm1...>::const_iterator;

	template<group_name gn,uint Nn, uint ... Nnm1>
	using const_lattice_const_iterator =
		const lattice_const_iterator<gn,Nn,Nnm1...>;

	template<group_name gn,uint Nn, uint ... Nnm1>
	using insert_result_type =
		typename std::pair<
			lattice_const_iterator<gn,Nn,Nnm1...>,
			bool
		>;

	template<uint Nn,uint ... Nnm1>
	constexpr uint max_N =
		element_of_set_t<Nn,Nnm1...>::max_N;

	template<uint Nn,uint ... Nnm1>
	constexpr uint max_dim =
		element_of_set_t<Nn,Nnm1...>::max_dim;

	template<uint Nn,uint ... Nnm1>
	static constexpr uint Order_Of_This_Group =
		element_of_set_t<Nn,Nnm1...>::Order_Of_This_Group;

	template<group_name gn,uint Nn,uint ... Nnm1 >
	constexpr
	insert_result_type<gn,Nn,Nnm1...> insert(
			set_lattice_t<gn,Nn,Nnm1...> & container,
			const group_t<gn,Nn,Nnm1...> & element
	)	{
		return container.insert(element);
	}

	template<group_name gn,uint Nn,uint ... Nnm1>
	constexpr
	auto erase(
		set_lattice_t<gn,Nn,Nnm1...> & container,
		lattice_const_iterator<gn,Nn,Nnm1...> it
	) {
		return container.erase(it);
	}

	template<group_name gn,uint Nn,uint ... Nnm1>
	constexpr
	void fill_the_cyclic_subgroups_lattice(
		set_lattice_t<gn,Nn,Nnm1...> & L
	)	{
		using gr_t = group_t<gn,Nn,Nnm1...>;
		using elem_gr_t = element_of_group_t<gn,Nn,Nnm1...>;
		gr_t G{};
		G.fill_the_group();
		const typename gr_t::own_base_type& G_Set{G.setdata};
		for(auto x : G_Set) {
			gr_t H{};
			H.do_empty();
			elem_gr_t elem{x};
			for(
				uint i{0} ;
				i < gr_t::Order_Of_This_Group ;
				++i
			)	{
				H.insert(elem);
				H.insert(elem.inv());
				elem = gr_t::bop(elem,x);
			}
			const gr_t cH(H);
			gr_t::span_subgroup(H,cH);
			const gr_t cH2(H);
			gr_t::span_subgroup(H,cH2);
			const gr_t cH3(H);
			gr_t::span_subgroup(H,cH3);
			L.insert(H);
		}
	}

	template<group_name gn, uint Nn, uint ... Nnm1>
	constexpr
	void generate_a_group_from_2_elements(
		group_t<gn,Nn,Nnm1...>& H,
		const element_of_group_t<gn,Nn,Nnm1...>&s,
		const element_of_group_t<gn,Nn,Nnm1...>&t
	)	{
		using gr_t = group_t<gn,Nn,Nnm1...>;
		using elem_gr_t = element_of_group_t<gn,Nn,Nnm1...>;
		H.do_empty();
		elem_gr_t g{s};
		elem_gr_t n{t};
		for(
			uint i=1 ;
			i <= element_of_set_t<Nn,Nnm1...>::max_N ;
			++i ){
			for(
				uint j=1 ;
				j <= element_of_set_t<Nn,Nnm1...>::max_N ;
				++j ){
				const gr_t cH{H};
				gr_t::span_subgroup(
					H,cH,g.pow(i),n.pow(j)
				);
			}
		}
	}

	template<group_name gn, uint Nn, uint ... Nnm1>
	constexpr
	void generate_a_group_from_3_elements(
		group_t<gn,Nn,Nnm1...>& H,
		const element_of_group_t<gn,Nn,Nnm1...>&u,
		const element_of_group_t<gn,Nn,Nnm1...>&v,
		const element_of_group_t<gn,Nn,Nnm1...>&w
	)	{
		using gr_t = group_t<gn,Nn,Nnm1...>;
		using elem_gr_t = element_of_group_t<gn,Nn,Nnm1...>;
		for(
			uint i{0} ;
			i < element_of_set_t<Nn,Nnm1...>::max_N ;
			++i
		)	{
			for(
				uint j{0} ;
				j < element_of_set_t<Nn,Nnm1...>::max_N ;
				++j
			)	{
				for(
					uint k(0) ;
					k < element_of_set_t<Nn,Nnm1...>::max_N ;
					++k
				)	{
				/// POTENCIAS PRIMARIAS
				const elem_gr_t ui{
					u.pow(i)
				};
				const elem_gr_t vj{
					v.pow(j)
				};
				const elem_gr_t wk{
					w.pow(k)
				};
				///
				const elem_gr_t uj{
					u.pow(j)
				};
				const elem_gr_t vk{
					v.pow(k)
				};
				const elem_gr_t wi{
					w.pow(i)
				};
				///
				const elem_gr_t uk{
					u.pow(k)
				};
				const elem_gr_t vi{
					v.pow(i)
				};
				const elem_gr_t wj{
					w.pow(j)
				};
				/// POTENCIA PRIMARIAS OBTENIDAS :
				/// u^i,v^j,w^k,u^j,v^k,w^i,u^k,v^i,w^j
				/// DENOMINADAS :
				/// ui,vj,wk,uj,vk,wi,uk,vi,wj
				/// POTENCIAS INVERSAS
				const elem_gr_t inv_ui{
					ui.inv()
				};
				const elem_gr_t inv_vj{
					vj.inv()
				};
				const elem_gr_t inv_wk{
					wk.inv()
				};
				///
				const elem_gr_t inv_uj{
					uj.inv()
				};
				const elem_gr_t inv_vk{
					vk.inv()
				};
				const elem_gr_t inv_wi{
					wi.inv()
				};
				///
				const elem_gr_t inv_uk{
					uk.inv()
				};
				const elem_gr_t inv_vi{
					vi.inv()
				};
				const elem_gr_t inv_wj{
					wj.inv()
				};
				/// POTENCIA INVERSAS OBTENIDAS :
				/// u^-i,v^-j,w^-k
				/// u^-j,v^-k,w^-i
				/// u^-k,v^-i,w^-j
				/// DENOMINADAS :
				/// inv_ui,inv_vj,inv_wk
				/// inv_uj,inv_vk,inv_wi
				/// inv_uk,inv_vi,inv_wj

				///	COMBINACIONES u^i * v^j
				const elem_gr_t uivj{
					gr_t::bop(ui,vj)
				};
				const elem_gr_t inv_ui_vj{
					gr_t::bop(inv_ui,vj)
				};
				const elem_gr_t ui_inv_vj{
					gr_t::bop(ui,inv_vj)
				};
				const elem_gr_t inv_ui_inv_vj{
					gr_t::bop(inv_ui,inv_vj)
				};
				/// A PARTIR DE AQUÍ
				/// NO SE HAN HECHO
				/// LAS CUENTAS TIPO
				/// u^-i * v^-j
				const elem_gr_t uivj_inv{
					uivj.inv()
				};
				const elem_gr_t inv_ui_vj_inv{
					inv_ui_vj.inv()
				};
				const elem_gr_t ui_inv_vj_inv{
					ui_inv_vj.inv()
				};
				const elem_gr_t inv_ui_inv_vj_inv{
					inv_ui_inv_vj.inv()
				};
				/// PRODUCTOS OBTENIDOS :
				/// u^i*v^j
				/// u^-i*v^j
				/// u^i*v^-j
				/// u^-i*v^-j
				/// (u^i*v^j)^-1
				/// (u^-i*v^j)^-1
				/// (u^i*v^-j)^-1
				/// (u^-i*v^-j)^-1
				/// DENOMINADOS :
				/// uivj
				/// inv_ui_vj
				/// ui_inv_vj
				/// inv_ui_inv_vj
				/// uivj_inv
				/// inv_ui_inv_vj_inv
				/// ui_inv_vj_inv
				/// inv_ui_inv_vj_inv

				///	COMBINACIONES v^j * u^i
				const elem_gr_t vjui{
					gr_t::bop(vj,ui)
				};
				const elem_gr_t inv_vj_ui{
					gr_t::bop(inv_vj,ui)
				};
				const elem_gr_t vj_inv_ui{
					gr_t::bop(vj,inv_ui)
				};
				const elem_gr_t inv_vj_inv_ui{
					gr_t::bop(inv_vj,inv_ui)
				};
				/// A PARTIR DE AQUÍ
				/// NO SE HAN HECHO
				/// LAS CUENTAS TIPO
				/// v^-j * u^-i
				const elem_gr_t vjui_inv{
					vjui.inv()
				};
				const elem_gr_t inv_vj_ui_inv{
					inv_vj_ui.inv()
				};
				const elem_gr_t vj_inv_ui_inv{
					vj_inv_ui.inv()
				};
				const elem_gr_t inv_vj_inv_ui_inv{
					inv_vj_inv_ui.inv()
				};
				/// PRODUCTOS OBTENIDOS :
				/// v^j*u^i
				/// v^-j*u^i
				/// v^j*u^-i
				/// v^-j*u^-i
				/// (v^j*u^i)^-1
				/// (v^-j*u^i)^-1
				/// (v^j*u^-i)^-1
				/// (v^-j*u^-i)^-1
				/// DENOMINADOS :
				/// vjui
				/// inv_vj_ui
				/// vj_inv_ui
				/// inv_vj_inv_ui
				/// vjui_inv
				/// inv_vj_inv_ui_inv
				/// vj_inv_ui_inv
				/// inv_vj_inv_ui_inv

				///	COMBINACIONES u^i * w^k
				const elem_gr_t uiwk{
					gr_t::bop(ui,wk)
				};
				const elem_gr_t inv_ui_wk{
					gr_t::bop(inv_ui,wk)
				};
				const elem_gr_t ui_inv_wk{
					gr_t::bop(ui,inv_wk)
				};
				const elem_gr_t inv_ui_inv_wk{
					gr_t::bop(inv_ui,inv_wk)
				};
				/// A PARTIR DE AQUÍ
				/// NO SE HAN HECHO
				/// LAS CUENTAS TIPO
				/// u^-i * w^-k
				const elem_gr_t uiwk_inv{
					uiwk.inv()
				};
				const elem_gr_t inv_ui_wk_inv{
					inv_ui_wk.inv()
				};
				const elem_gr_t ui_inv_wk_inv{
					ui_inv_wk.inv()
				};
				const elem_gr_t inv_ui_inv_wk_inv{
					inv_ui_inv_wk.inv()
				};
				/// PRODUCTOS OBTENIDOS :
				/// u^i*w^k
				/// u^-i*w^k
				/// u^i*w^-k
				/// u^-i*w^-k
				/// (u^i*w^k)^-1
				/// (u^-i*w^k)^-1
				/// (u^i*w^-k)^-1
				/// (u^-i*w^-k)^-1
				/// DENOMINADOS :
				/// uiwk
				/// inv_ui_wk
				/// ui_inv_wk
				/// inv_ui_inv_wk
				/// uiwk_inv
				/// inv_ui_inv_wk_inv
				/// ui_inv_wk_inv
				/// inv_ui_inv_wk_inv

				///	COMBINACIONES w^k * u^i
				const elem_gr_t wkui{
					gr_t::bop(wk,ui)
				};
				const elem_gr_t inv_wk_ui{
					gr_t::bop(inv_wk,ui)
				};
				const elem_gr_t wk_inv_ui{
					gr_t::bop(wk,inv_ui)
				};
				const elem_gr_t inv_wk_inv_ui{
					gr_t::bop(inv_wk,inv_ui)
				};
				/// A PARTIR DE AQUÍ
				/// NO SE HAN HECHO
				/// LAS CUENTAS TIPO
				/// w^-k * u^-i
				const elem_gr_t wkui_inv{
					wkui.inv()
				};
				const elem_gr_t inv_wk_ui_inv{
					inv_wk_ui.inv()
				};
				const elem_gr_t wk_inv_ui_inv{
					wk_inv_ui.inv()
				};
				const elem_gr_t inv_wk_inv_ui_inv{
					inv_wk_inv_ui.inv()
				};
				/// PRODUCTOS OBTENIDOS :
				/// w^k*u^i
				/// w^-k*u^i
				/// w^k*u^-i
				/// w^-k*u^-i
				/// (w^k*u^i)^-1
				/// (w^-k*u^i)^-1
				/// (w^k*u^-i)^-1
				/// (w^-k*u^-i)^-1
				/// DENOMINADOS :
				/// wkui
				/// inv_wk_ui
				/// wk_inv_ui
				/// inv_wk_inv_ui
				/// wkui_inv
				/// inv_wk_inv_ui_inv
				/// wk_inv_ui_inv
				/// inv_wk_inv_ui_inv

				///	COMBINACIONES v^j * w^k
				const elem_gr_t vjwk{
					gr_t::bop(vj,wk)
				};
				const elem_gr_t inv_vj_wk{
					gr_t::bop(inv_vj,wk)
				};
				const elem_gr_t vj_inv_wk{
					gr_t::bop(vj,inv_wk)
				};
				const elem_gr_t inv_vj_inv_wk{
					gr_t::bop(inv_vj,inv_wk)
				};
				/// A PARTIR DE AQUÍ
				/// NO SE HAN HECHO
				/// LAS CUENTAS TIPO
				/// v^-j * w^-k
				const elem_gr_t vjwk_inv{
					vjwk.inv()
				};
				const elem_gr_t inv_vj_wk_inv{
					inv_vj_wk.inv()
				};
				const elem_gr_t vj_inv_wk_inv{
					vj_inv_wk.inv()
				};
				const elem_gr_t inv_vj_inv_wk_inv{
					inv_vj_inv_wk.inv()
				};
				/// PRODUCTOS OBTENIDOS :
				/// v^j*w^k
				/// v^-j*w^k
				/// v^j*w^-k
				/// v^-j*w^-k
				/// (v^j*w^k)^-1
				/// (v^-j*w^k)^-1
				/// (v^j*w^-k)^-1
				/// (v^-j*w^-k)^-1
				/// DENOMINADOS :
				/// vjwk
				/// inv_vj_wk
				/// vj_inv_wk
				/// inv_vj_inv_wk
				/// vjwk_inv
				/// inv_vj_inv_wk_inv
				/// vj_inv_wk_inv
				/// inv_vj_inv_wk_inv

				///	COMBINACIONES w^k * v^j
				const elem_gr_t wkvj{
					gr_t::bop(wk,vj)
				};
				const elem_gr_t inv_wk_vj{
					gr_t::bop(inv_wk,vj)
				};
				const elem_gr_t wk_inv_vj{
					gr_t::bop(wk,inv_vj)
				};
				const elem_gr_t inv_wk_inv_vj{
					gr_t::bop(inv_wk,inv_vj)
				};
				/// A PARTIR DE AQUÍ
				/// NO SE HAN HECHO
				/// LAS CUENTAS TIPO
				/// w^-k * v^-j
				const elem_gr_t wkvj_inv{
					wkvj.inv()
				};
				const elem_gr_t inv_wk_vj_inv{
					inv_wk_vj.inv()
				};
				const elem_gr_t wk_inv_vj_inv{
					wk_inv_vj.inv()
				};
				const elem_gr_t inv_wk_inv_vj_inv{
					inv_wk_inv_vj.inv()
				};
				/// PRODUCTOS OBTENIDOS :
				/// w^k*v^j
				/// w^-k*v^j
				/// w^k*v^-j
				/// w^-k*v^-j
				/// (w^k*v^j)^-1
				/// (w^-k*v^j)^-1
				/// (w^k*v^-j)^-1
				/// (w^-k*v^-j)^-1
				/// DENOMINADOS :
				/// wkvj
				/// inv_wk_vj
				/// wk_inv_vj
				/// inv_wk_inv_vj
				/// wkvj_inv
				/// inv_wk_inv_vj_inv
				/// wk_inv_vj_inv
				/// inv_wk_inv_vj_inv

				///	3 ELEMENTOS
				///	COMBINACIONES u^i * v^j * w^k
				const elem_gr_t uivjwk{
					gr_t::bop(uivj,wk)
				};
				const elem_gr_t inv_ui_vj_wk{
					gr_t::bop(inv_ui_vj,wk)
				};
				const elem_gr_t ui_inv_vj_wk{
					gr_t::bop(ui_inv_vj,wk)
				};
				const elem_gr_t ui_vj_inv_wk{
					gr_t::bop(uivj,inv_wk)
				};
				const elem_gr_t inv_ui_inv_vj_wk{
					gr_t::bop(inv_ui_inv_vj,wk)
				};
				const elem_gr_t inv_ui_vj_inv_wk{
					gr_t::bop(inv_ui_vj,inv_wk)
				};
				const elem_gr_t ui_inv_vj_inv_wk{
					gr_t::bop(ui_inv_vj,inv_wk)
				};
				const elem_gr_t inv_ui_inv_vj_inv_wk{
					gr_t::bop(inv_ui_inv_vj,inv_wk)
				};
				const elem_gr_t uivjwk_inv{
					uivjwk.inv()
				};
				const elem_gr_t inv_ui_vj_wk_inv{
					inv_ui_vj_wk.inv()
				};
				const elem_gr_t ui_inv_vj_wk_inv{
					ui_inv_vj_wk.inv()
				};
				const elem_gr_t ui_vj_inv_wk_inv{
					ui_vj_inv_wk.inv()
				};
				const elem_gr_t inv_ui_inv_vj_wk_inv{
					inv_ui_inv_vj_wk.inv()
				};
				const elem_gr_t inv_ui_vj_inv_wk_inv{
					inv_ui_vj_inv_wk.inv()
				};
				const elem_gr_t ui_inv_vj_inv_wk_inv{
					ui_inv_vj_inv_wk.inv()
				};
				const elem_gr_t inv_ui_inv_vj_inv_wk_inv{
					inv_ui_inv_vj_inv_wk.inv()
				};
				///	COMBINACIONES w^k * u^i * v^j
				const elem_gr_t wkuivj{
					gr_t::bop(wkui,vj)
				};
				const elem_gr_t inv_wk_ui_vj{
					gr_t::bop(inv_wk_ui,vj)
				};
				const elem_gr_t wk_inv_ui_vj{
					gr_t::bop(wk_inv_ui,vj)
				};
				const elem_gr_t wk_ui_inv_vj{
					gr_t::bop(wkui,inv_vj)
				};
				const elem_gr_t inv_wk_inv_ui_vj{
					gr_t::bop(inv_wk_inv_ui,vj)
				};
				const elem_gr_t inv_wk_ui_inv_vj{
					gr_t::bop(inv_wk_ui,inv_vj)
				};
				const elem_gr_t wk_inv_ui_inv_vj{
					gr_t::bop(wk_inv_ui,inv_vj)
				};
				const elem_gr_t inv_wk_inv_ui_inv_vj{
					gr_t::bop(inv_wk_inv_ui,inv_vj)
				};
				const elem_gr_t wkuivj_inv{
					wkuivj.inv()
				};
				const elem_gr_t inv_wk_ui_vj_inv{
					inv_wk_ui_vj.inv()
				};
				const elem_gr_t wk_inv_ui_vj_inv{
					wk_inv_ui_vj.inv()
				};
				const elem_gr_t wk_ui_inv_vj_inv{
					wk_ui_inv_vj.inv()
				};
				const elem_gr_t inv_wk_inv_ui_vj_inv{
					inv_wk_inv_ui_vj.inv()
				};
				const elem_gr_t inv_wk_ui_inv_vj_inv{
					inv_wk_ui_inv_vj.inv()
				};
				const elem_gr_t wk_inv_ui_inv_vj_inv{
					wk_inv_ui_inv_vj.inv()
				};
				const elem_gr_t inv_wk_inv_ui_inv_vj_inv{
					inv_wk_inv_ui_inv_vj.inv()
				};
				///	COMBINACIONES v^j * w^k * u^i
				const elem_gr_t vjwkui{
					gr_t::bop(vjwk,ui)
				};
				const elem_gr_t inv_vj_wk_ui{
					gr_t::bop(inv_vj_wk,ui)
				};
				const elem_gr_t vj_inv_wk_ui{
					gr_t::bop(vj_inv_wk,ui)
				};
				const elem_gr_t vj_wk_inv_ui{
					gr_t::bop(vjwk,inv_ui)
				};
				const elem_gr_t inv_vj_inv_wk_ui{
					gr_t::bop(inv_vj_inv_wk,ui)
				};
				const elem_gr_t inv_vj_wk_inv_ui{
					gr_t::bop(inv_vj_wk,inv_ui)
				};
				const elem_gr_t vj_inv_wk_inv_ui{
					gr_t::bop(vj_inv_wk,inv_ui)
				};
				const elem_gr_t inv_vj_inv_wk_inv_ui{
					gr_t::bop(inv_vj_inv_wk,inv_ui)
				};
				const elem_gr_t vjwkui_inv{
					vjwkui.inv()
				};
				const elem_gr_t inv_vj_wk_ui_inv{
					inv_vj_wk_ui.inv()
				};
				const elem_gr_t vj_inv_wk_ui_inv{
					vj_inv_wk_ui.inv()
				};
				const elem_gr_t vj_wk_inv_ui_inv{
					vj_wk_inv_ui.inv()
				};
				const elem_gr_t inv_vj_inv_wk_ui_inv{
					inv_vj_inv_wk_ui.inv()
				};
				const elem_gr_t inv_vj_wk_inv_ui_inv{
					inv_vj_wk_inv_ui.inv()
				};
				const elem_gr_t vj_inv_wk_inv_ui_inv{
					vj_inv_wk_inv_ui.inv()
				};
				const elem_gr_t inv_vj_inv_wk_inv_ui_inv{
					inv_vj_inv_wk_inv_ui.inv()
				};
				///				REFLEJADO
				///	COMBINACIONES w^k * v^j * u^i
				const elem_gr_t wkvjui{
					gr_t::bop(wkvj,ui)
				};
				const elem_gr_t inv_wk_vj_ui{
					gr_t::bop(inv_wk_vj,ui)
				};
				const elem_gr_t wk_inv_vj_ui{
					gr_t::bop(wk_inv_vj,ui)
				};
				const elem_gr_t wk_vj_inv_ui{
					gr_t::bop(wkvj,inv_ui)
				};
				const elem_gr_t inv_wk_inv_vj_ui{
					gr_t::bop(inv_wk_inv_vj,ui)
				};
				const elem_gr_t inv_wk_vj_inv_ui{
					gr_t::bop(inv_wk_vj,inv_ui)
				};
				const elem_gr_t wk_inv_vj_inv_ui{
					gr_t::bop(wk_inv_vj,inv_ui)
				};
				const elem_gr_t inv_wk_inv_vj_inv_ui{
					gr_t::bop(inv_wk_inv_vj,inv_ui)
				};
				const elem_gr_t wkvjui_inv{
					wkvjui.inv()
				};
				const elem_gr_t inv_wk_vj_ui_inv{
					inv_wk_vj_ui.inv()
				};
				const elem_gr_t wk_inv_vj_ui_inv{
					wk_inv_vj_ui.inv()
				};
				const elem_gr_t wk_vj_inv_ui_inv{
					wk_vj_inv_ui.inv()
				};
				const elem_gr_t inv_wk_inv_vj_ui_inv{
					inv_wk_inv_vj_ui.inv()
				};
				const elem_gr_t inv_wk_vj_inv_ui_inv{
					inv_wk_vj_inv_ui.inv()
				};
				const elem_gr_t wk_inv_vj_inv_ui_inv{
					wk_inv_vj_inv_ui.inv()
				};
				const elem_gr_t inv_wk_inv_vj_inv_ui_inv{
					inv_wk_inv_vj_inv_ui.inv()
				};
				///	COMBINACIONES v^j * u^i * w^k
				const elem_gr_t vjuiwk{
					gr_t::bop(vjui,wk)
				};
				const elem_gr_t inv_vj_ui_wk{
					gr_t::bop(inv_vj_ui,wk)
				};
				const elem_gr_t vj_inv_ui_wk{
					gr_t::bop(vj_inv_ui,wk)
				};
				const elem_gr_t vj_ui_inv_wk{
					gr_t::bop(vjui,inv_wk)
				};
				const elem_gr_t inv_vj_inv_ui_wk{
					gr_t::bop(inv_vj_inv_ui,wk)
				};
				const elem_gr_t inv_vj_ui_inv_wk{
					gr_t::bop(inv_vj_ui,inv_wk)
				};
				const elem_gr_t vj_inv_ui_inv_wk{
					gr_t::bop(vj_inv_ui,inv_wk)
				};
				const elem_gr_t inv_vj_inv_ui_inv_wk{
					gr_t::bop(inv_vj_inv_ui,inv_wk)
				};
				const elem_gr_t vjuiwk_inv{
					vjuiwk.inv()
				};
				const elem_gr_t inv_vj_ui_wk_inv{
					inv_vj_ui_wk.inv()
				};
				const elem_gr_t vj_inv_ui_wk_inv{
					vj_inv_ui_wk.inv()
				};
				const elem_gr_t vj_ui_inv_wk_inv{
					vj_ui_inv_wk.inv()
				};
				const elem_gr_t inv_vj_inv_ui_wk_inv{
					inv_vj_inv_ui_wk.inv()
				};
				const elem_gr_t inv_vj_ui_inv_wk_inv{
					inv_vj_ui_inv_wk.inv()
				};
				const elem_gr_t vj_inv_ui_inv_wk_inv{
					vj_inv_ui_inv_wk.inv()
				};
				const elem_gr_t inv_vj_inv_ui_inv_wk_inv{
					inv_vj_inv_ui_inv_wk.inv()
				};
				///	COMBINACIONES u^i * w^k * v^j
				const elem_gr_t uiwkvj{
					gr_t::bop(uiwk,vj)
				};
				const elem_gr_t inv_ui_wk_vj{
					gr_t::bop(inv_ui_wk,vj)
				};
				const elem_gr_t ui_inv_wk_vj{
					gr_t::bop(ui_inv_wk,vj)
				};
				const elem_gr_t ui_wk_inv_vj{
					gr_t::bop(uiwk,inv_vj)
				};
				const elem_gr_t inv_ui_inv_wk_vj{
					gr_t::bop(inv_ui_inv_wk,vj)
				};
				const elem_gr_t inv_ui_wk_inv_vj{
					gr_t::bop(inv_ui_wk,inv_vj)
				};
				const elem_gr_t ui_inv_wk_inv_vj{
					gr_t::bop(ui_inv_wk,inv_vj)
				};
				const elem_gr_t inv_ui_inv_wk_inv_vj{
					gr_t::bop(inv_ui_inv_wk,inv_vj)
				};
				const elem_gr_t uiwkvj_inv{
					uiwkvj.inv()
				};
				const elem_gr_t inv_ui_wk_vj_inv{
					inv_ui_wk_vj.inv()
				};
				const elem_gr_t ui_inv_wk_vj_inv{
					ui_inv_wk_vj.inv()
				};
				const elem_gr_t ui_wk_inv_vj_inv{
					ui_wk_inv_vj.inv()
				};
				const elem_gr_t inv_ui_inv_wk_vj_inv{
					inv_ui_inv_wk_vj.inv()
				};
				const elem_gr_t inv_ui_wk_inv_vj_inv{
					inv_ui_wk_inv_vj.inv()
				};
				const elem_gr_t ui_inv_wk_inv_vj_inv{
					ui_inv_wk_inv_vj.inv()
				};
				const elem_gr_t inv_ui_inv_wk_inv_vj_inv{
					inv_ui_inv_wk_inv_vj.inv()
				};
				//!///////////////////////
				//!////    	INSERTS    ///
				//!///////////////////////
				H.insert(uivjwk);
				H.insert(inv_ui_vj_wk);
				H.insert(ui_inv_vj_wk);
				H.insert(ui_vj_inv_wk);
				H.insert(inv_ui_inv_vj_wk);
				H.insert(inv_ui_vj_inv_wk);
				H.insert(ui_inv_vj_inv_wk);
				H.insert(inv_ui_inv_vj_inv_wk);
				H.insert(uivjwk_inv);
				H.insert(inv_ui_vj_wk_inv);
				H.insert(ui_inv_vj_wk_inv);
				H.insert(ui_vj_inv_wk_inv);
				H.insert(inv_ui_inv_vj_wk_inv);
				H.insert(inv_ui_vj_inv_wk_inv);
				H.insert(ui_inv_vj_inv_wk_inv);
				H.insert(inv_ui_inv_vj_inv_wk_inv);
				H.insert(wkuivj);
				H.insert(inv_wk_ui_vj);
				H.insert(wk_inv_ui_vj);
				H.insert(wk_ui_inv_vj);
				H.insert(inv_wk_inv_ui_vj);
				H.insert(inv_wk_ui_inv_vj);
				H.insert(wk_inv_ui_inv_vj);
				H.insert(inv_wk_inv_ui_inv_vj);
				H.insert(wkuivj_inv);
				H.insert(inv_wk_ui_vj_inv);
				H.insert(wk_inv_ui_vj_inv);
				H.insert(wk_ui_inv_vj_inv);
				H.insert(inv_wk_inv_ui_vj_inv);
				H.insert(inv_wk_ui_inv_vj_inv);
				H.insert(wk_inv_ui_inv_vj_inv);
				H.insert(inv_wk_inv_ui_inv_vj_inv);
				H.insert(vjwkui);
				H.insert(inv_vj_wk_ui);
				H.insert(vj_inv_wk_ui);
				H.insert(vj_wk_inv_ui);
				H.insert(inv_vj_inv_wk_ui);
				H.insert(inv_vj_wk_inv_ui);
				H.insert(vj_inv_wk_inv_ui);
				H.insert(inv_vj_inv_wk_inv_ui);
				H.insert(vjwkui_inv);
				H.insert(inv_vj_wk_ui_inv);
				H.insert(vj_inv_wk_ui_inv);
				H.insert(vj_wk_inv_ui_inv);
				H.insert(inv_vj_inv_wk_ui_inv);
				H.insert(inv_vj_wk_inv_ui_inv);
				H.insert(vj_inv_wk_inv_ui_inv);
				H.insert(inv_vj_inv_wk_inv_ui_inv);
				H.insert(wkvjui);
				H.insert(inv_wk_vj_ui);
				H.insert(wk_inv_vj_ui);
				H.insert(wk_vj_inv_ui);
				H.insert(inv_wk_inv_vj_ui);
				H.insert(inv_wk_vj_inv_ui);
				H.insert(wk_inv_vj_inv_ui);
				H.insert(inv_wk_inv_vj_inv_ui);
				H.insert(wkvjui_inv);
				H.insert(inv_wk_vj_ui_inv);
				H.insert(wk_inv_vj_ui_inv);
				H.insert(wk_vj_inv_ui_inv);
				H.insert(inv_wk_inv_vj_ui_inv);
				H.insert(inv_wk_vj_inv_ui_inv);
				H.insert(wk_inv_vj_inv_ui_inv);
				H.insert(inv_wk_inv_vj_inv_ui_inv);
				H.insert(vjuiwk);
				H.insert(inv_vj_ui_wk);
				H.insert(vj_inv_ui_wk);
				H.insert(vj_ui_inv_wk);
				H.insert(inv_vj_inv_ui_wk);
				H.insert(inv_vj_ui_inv_wk);
				H.insert(vj_inv_ui_inv_wk);
				H.insert(inv_vj_inv_ui_inv_wk);
				H.insert(vjuiwk_inv);
				H.insert(inv_vj_ui_wk_inv);
				H.insert(vj_inv_ui_wk_inv);
				H.insert(vj_ui_inv_wk_inv);
				H.insert(inv_vj_inv_ui_wk_inv);
				H.insert(inv_vj_ui_inv_wk_inv);
				H.insert(vj_inv_ui_inv_wk_inv);
				H.insert(inv_vj_inv_ui_inv_wk_inv);
				H.insert(uiwkvj);
				H.insert(inv_ui_wk_vj);
				H.insert(ui_inv_wk_vj);
				H.insert(ui_wk_inv_vj);
				H.insert(inv_ui_inv_wk_vj);
				H.insert(inv_ui_wk_inv_vj);
				H.insert(ui_inv_wk_inv_vj);
				H.insert(inv_ui_inv_wk_inv_vj);
				H.insert(uiwkvj_inv);
				H.insert(inv_ui_wk_vj_inv);
				H.insert(ui_inv_wk_vj_inv);
				H.insert(ui_wk_inv_vj_inv);
				H.insert(inv_ui_inv_wk_vj_inv);
				H.insert(inv_ui_wk_inv_vj_inv);
				H.insert(ui_inv_wk_inv_vj_inv);
				H.insert(inv_ui_inv_wk_inv_vj_inv);
				const gr_t cH(H);
				gr_t::span_subgroup(H,cH);
				const gr_t cH2(H);
				gr_t::span_subgroup(H,cH2);
				const gr_t cH3(H);
				gr_t::span_subgroup(H,cH3);
				const gr_t cH4(H);
				gr_t::span_subgroup(H,cH4);
				const gr_t cH5(H);
				gr_t::span_subgroup(H,cH5);
				const gr_t cH6(H);
				gr_t::span_subgroup(H,cH6);
				}
			}
		}
	}

	template<group_name gn, uint Nn, uint ... Nnm1>
	constexpr
	void
	fill_the_2_generated_subgroups_lattice(
		set_lattice_t<gn,Nn,Nnm1...>& L
	)	{
		using gr_t = group_t<gn,Nn,Nnm1...>;
		// Se van a insertar los subgrupos ciclicos
		fill_the_cyclic_subgroups_lattice(L);
		// Se van a insertar los subgrupo generados por 2 elementos
		gr_t K{};
		K.fill_the_group();
		const group_set_t<gn,Nn,Nnm1...> & K_Set(K.setdata);
		gr_t J{};
		J.fill_the_group();
		const group_set_t<gn,Nn,Nnm1...> & J_Set(J.setdata);
		for(auto t : K_Set){
			for(auto r : J_Set){
				gr_t H{};
				H.do_empty();
				generate_a_group_from_2_elements<
						gn,Nn,Nnm1...
					>(H,t,r);
				const gr_t cH(H);
				gr_t::span_subgroup(H,cH);
				const gr_t cH2(H);
				gr_t::span_subgroup(H,cH2);
				const gr_t cH3(H);
				gr_t::span_subgroup(H,cH3);
				const gr_t cH4(H);
				gr_t::span_subgroup(H,cH4);
				const gr_t cH5(H);
				gr_t::span_subgroup(H,cH5);
				const gr_t cH6(H);
				gr_t::span_subgroup(H,cH6);
				L.insert(H);
			}
		}
		//Se han insertado los subgrupos generados
		//estrictamente por dos elementos
	}

	template<group_name gn, uint Nn, uint ... Nnm1>
	constexpr
	void fill_the_3_generated_subgroups_lattice(
		set_lattice_t<gn,Nn,Nnm1...>& L
	)	{
		using gr_t = group_t<gn,Nn,Nnm1...>;
		// Se van a insertar los subgrupos ciclicos
		fill_the_2_generated_subgroups_lattice(L);
		const gr_t N{gr_t()};
		const group_set_t<gn,Nn,Nnm1...>& N_Set{N.setdata};
		const gr_t G{gr_t()};
		const group_set_t<gn,Nn,Nnm1...>& G_Set{G.setdata};
		const gr_t S{gr_t()};
		const group_set_t<gn,Nn,Nnm1...>& S_Set{S.setdata};

		// Se han insertado los subgrupos ciclicos
		// Se van a insertar los subgrupos
		//generados por 2 elementos
		for( auto u : G_Set ) {
			for( auto v : N_Set ) {
				for( auto w : S_Set ) {
					gr_t H{gr_t()};
					H.do_empty();
					generate_a_group_from_3_elements<
							gn,Nn,Nnm1...
						>(H,u,v,w);
					const gr_t cH(H);
					gr_t::span_subgroup(H,cH);
					const gr_t cH2(H);
					gr_t::span_subgroup(H,cH2);
					const gr_t cH3(H);
					gr_t::span_subgroup(H,cH3);
					const gr_t cH4(H);
					gr_t::span_subgroup(H,cH4);
					const gr_t cH5(H);
					gr_t::span_subgroup(H,cH5);
					const gr_t cH6(H);
					gr_t::span_subgroup(H,cH6);
					L.insert(H);
				}
			}
		}

		// Se han insertado los subgrupos generados
		//estrictamente por dos elementos
	}

	template<group_name gn, uint Nn, uint ... Nnm1>
	constexpr
	void generate_right_equivalence_classes(
		set_lattice_t<gn,Nn,Nnm1...>&	L,
		const group_t<gn,Nn,Nnm1...>&	G,
		const group_t<gn,Nn,Nnm1...>&	H
	)	{
		using gr_t = group_t<gn,Nn,Nnm1...>;
		L.clear();
		const group_set_t<gn,Nn,Nnm1...>& G_Set{G.setdata};
		const group_set_t<gn,Nn,Nnm1...>& H_Set{H.setdata};
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

	template<group_name gn, uint Nn, uint ... Nnm1>
	constexpr
	void generate_left_equivalence_classes(
		set_lattice_t<gn,Nn,Nnm1...>&	L,
		const group_t<gn,Nn,Nnm1...>&	G,
		const group_t<gn,Nn,Nnm1...>&	H
	)	{
		using gr_t = group_t<gn,Nn,Nnm1...>;
		L.clear();
		const group_set_t<gn,Nn,Nnm1...>& G_Set{G.setdata};
		const group_set_t<gn,Nn,Nnm1...>& H_Set{H.setdata};
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

	template<group_name gn, uint Nn, uint ... Nnm1>
	std::string to_string(
		std::string& result,
		const set_lattice_t<gn,Nn,Nnm1...>& container,
		const std::string & abecedario
	)	{
		using gr_t = group_t<gn,Nn,Nnm1...>;
		result="";
		result += "\\left\\lbrace\\right.{\n";
		const_lattice_const_iterator<gn,Nn,Nnm1...>
			itend=container.cend();
		lattice_const_iterator<gn,Nn,Nnm1...>
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
