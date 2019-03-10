/*
 * give_me_the_group_information.hpp
 *
 * Copyright 2018 Julian Calderon Almendros <julian.calderon.almendros@gmail.com>
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

#ifndef GIVE_ME_THE_GROUP_INFORMATION_HPP_INCLUDED
#define GIVE_ME_THE_GROUP_INFORMATION_HPP_INCLUDED

#include "lattice_subgroup_t.hpp"


namespace tfg
{
	template<group_name gn,uint N_n,uint...N_nm1>
	struct get_group_info {

	using elem_t = element_of_set_t<N_n,N_nm1...>;
	static constexpr std::size_t Gr_Ord = elem_t::Order_Of_This_Group;
	using op_t	= group_binop_t<gn,N_n,N_nm1...>;
	using elem_gr_t = element_of_group_t<gn,N_n,N_nm1...>;
	using gr_iterator = typename std::set<elem_gr_t>::const_iterator;
	using const_gr_iterator = const gr_iterator;
	using gr_t = group_t<gn,N_n,N_nm1...>;
	using groups_by_its_generators_t = typename std::map<gr_t,gr_t>;
	using lattice_t = set_lattice_t<gn,N_n,N_nm1...>;

	static void work(std::string nombre_de_grupo,
								std::string nombre_de_grupo_en_latex,
								std::string abecedario) {

	std::string temp_formato_de_tabla{"|c"};
	for(uint i{1}; i < Gr_Ord ; ++i) {
		temp_formato_de_tabla += "|c";
	}
	temp_formato_de_tabla += "|";
	const std::string formato_de_tabla{temp_formato_de_tabla};
	const std::string Gr_Name = 	nombre_de_grupo 		+
									".ord_grp_" 			+
									std::to_string(Gr_Ord) 	+
									".info.txt"					;

	std::ofstream tCayley(Gr_Name, std::ofstream::out);

    std::string latex_nom=nombre_de_grupo_en_latex;
	tCayley << std::boolalpha;
	elem_gr_t eg_i;
	elem_t es_j;
	elem_t es_k;
	gr_t G{};
	G.fill_the_group();
	gr_t gr{};
	gr.fill_the_group();
	lattice_t lattice{};

	const std::string letras = abecedario;

	tCayley			 	<< "\n \t\tPor enumeración, iterando sobre los elementos del grupo "
								<< "\n \t\t\tLA TABLA DE CAYLEY "
								<< "\n\n\n";
	tCayley			 	<< "\\begin{align*}\n";
	tCayley			 	<< "\\begin{array}{"+formato_de_tabla+"}\n";
	tCayley			 	<< "\\hline\n";
	uint index = 1;
	for(auto a : gr) {
		for(auto b : gr) {
			const elem_gr_t  r = op_t::gr_bop(a,b);
			const std::string R{r.to_string(letras)};
			tCayley 	<< R;
			if (index%Gr_Ord==0)
				tCayley 	<< "\\\\";
			else
				tCayley 	<< "&";
			++index;
		}
		tCayley 	<< "\n" << "\\hline\n";
	}
	tCayley << "\\end{array}\n";
	tCayley << "\\end{align*}\n\n\n";


	const bool es_asociativo{gr.is_associative()};
	if (es_asociativo) {
		tCayley << "SI : El grupo " + Gr_Name +" ES ASOCIATIVO\n";
	}
	else {
		tCayley << "NO : El grupo " + Gr_Name +" NO ES ASOCIATIVO (NI GRUPO)\n";
	}

	const bool tiene_elemento_inverso{gr.exists_inverse_for_every_element()};
	if (tiene_elemento_inverso) {
		tCayley << "SI : El grupo " + Gr_Name +" TIENE ELEMENTO INVERSO\n";
	}
	else {
		tCayley << "NO : El grupo " + Gr_Name +" NO TIENE ELEMENTO INVERSO (NI ES GRUPO)\n";
	}

	const bool existe_elemento_neutro{gr.has_the_trusthed_unity()};
	if (existe_elemento_neutro) {
		tCayley << "SI : El grupo " + Gr_Name +" TIENE ELEMENTO NEUTRO\n";
	}
	else {
		tCayley << "NO : El grupo " + Gr_Name +" NO TIENE ELEMENTO NEUTRO (NI ES GRUPO)\n";
	}


	const elem_gr_t defecto{elem_gr_t()};
	const auto unidad_result{gr.get_the_trusthed_unity()};
	const elem_gr_t unidad = unidad_result.first;
	gr_t vacio{};
	vacio.do_empty();
	vacio.setdata.insert(unidad);
	const gr_t VACIO(vacio);
	tCayley 	<< "Si ha salido SI anteriormente, el grupo " + Gr_Name +" "
				<< "?tiene como neutro?? : "
				<< unidad_result.second << "\n";
	if (unidad_result.second) {
		tCayley 	<< "El \"neutro\" del producto directo es : "
					<< unidad_result.first.to_string(letras) << "\n";
		tCayley 	<< "El neutro de la operacion del grupo " + Gr_Name +" es : "
					<< unidad_result.first.to_string(letras) << "\n";
		tCayley 	<< "?coincide el neutro de la operacion del grupo " + Gr_Name +" con el del Producto Directo?? : "
					<< (defecto==unidad_result.first) << "\n";
		tCayley 	<< "?coincide el neutro de la operacion del grupo " + Gr_Name +" con el del Producto Directo?? [FUNCION] : "
					<< (VACIO.dp_unit_equal_gr_unit()) << "\n";
	}

	const bool es_abeliano{gr.is_abelian()};
	if (es_abeliano) {
		tCayley << "El grupo " + Gr_Name +" ES ABELIANO\n";
	}
	else {
		tCayley << "El grupo " + Gr_Name +" ES GRUPO NO ABELIANO\n";
	}

	tCayley << "\n\n" << "\t\tSUBGRUPOS CICLICOS DE "+Gr_Name+"" << "\n\n";
	std::string Lcyclic{};
	lattice_t L{};
	L.clear();
	fill_the_cyclic_subgroups_lattice(L);

	for(auto K : L) {
		tCayley << K.to_string(letras) << "\n";
		tCayley << "Es operacion interna : " << K.is_inner_binary_operation() << "\n";
		tCayley << "Tiene todos los inversos : " << K.is_inner_inverter() << "\n";
		tCayley << "Tiene el elemento neutro : " << K.has_the_trusthed_unity() << "\n";
		tCayley << "Es abeliano : " << K.is_abelian() << "\n";
		tCayley << "Es resoluble : " << K.is_solvable() << "\n";
		tCayley << "Es nilpotente : " << K.is_nilpotent() << "\n";
		tCayley << "Su orden es : " << K.cardinal() << "\n";
	}
	to_string(Lcyclic,L,letras);
	tCayley << Lcyclic << "\n";
	tCayley << "nº de subgrupos ciclicos " << L.size() << "\n";

	tCayley << "\n\n" << "\t\tSUBGRUPOS GENERADOS POR 2 O MENOS ELEMENTOS DE " << Gr_Name << "\n\n";
	std::string L2generated{};
	fill_the_2_generated_subgroups_lattice(L);
	for(auto K : L) {
		tCayley << K.to_string(letras) << "\n";
		tCayley << "Es operacion interna : " << K.is_inner_binary_operation() << "\n";
		tCayley << "Tiene todos los inversos : " << K.is_inner_inverter() << "\n";
		tCayley << "Tiene el elemento neutro : " << K.has_the_trusthed_unity() << "\n";
		tCayley << "Es abeliano : " << K.is_abelian() << "\n";
		tCayley << "Es resoluble : " << K.is_solvable() << "\n";
		tCayley << "Es nilpotente : " << K.is_nilpotent() << "\n";
		tCayley << "Su orden es : " << K.cardinal() << "\n";
	}
	to_string(L2generated,L,letras);
	tCayley << L2generated << "\n";
	tCayley << "nº de subgrupos generados por 2 o menos elementos " << L.size() << "\n";

	tCayley 	<< "\n\n\n"
						<< "\t\t/////////////////////////////////////////////////////////"
						<< "\n";
	tCayley 	<< "\t\tSUBGRUPOS GENERADOS POR 3 O MENOS ELEMENTOS DE "+Gr_Name+""
						<< "\n";
	tCayley 	<< "\t\t/////////////////////////////////////////////////////////"
						<< "\n\n";
	std::string L3generated{};
	fill_the_3_generated_subgroups_lattice(L);
	for(auto K : L) {
		tCayley << K.to_string(letras) << "\n";
		tCayley << "Es operacion interna : \t" << K.is_inner_binary_operation() << "\n";
		tCayley << "Tiene todos los inversos : \t" << K.is_inner_inverter() << "\n";
		tCayley << "Tiene el elemento neutro : \t" << K.has_the_trusthed_unity() << "\n";
		tCayley << "Es abeliano : \t\t" << K.is_abelian() << "\n";
		tCayley << "Es resoluble : \t\t" << K.is_solvable() << "\n";
		tCayley << "Es nilpotente : \t\t" << K.is_nilpotent() << "\n";
		tCayley << "Su orden es : \t\t" << K.cardinal() << "\n";
	}
	to_string(L3generated,L,letras);
	tCayley << L3generated << "\n";
	tCayley << "nº de subgrupos generados por 3 o menos elementos " << L.size() << "\n";

	tCayley << "\n\n\tELEMENTOS DEL GRUPO "+Gr_Name+"" << "\n";
	gr_t H{};
	H.fill_the_group();
	for(auto a : H) {
		tCayley << a.to_string(letras) << "\n";
	}
tCayley << "\n\n\tTESTEO DE LOS ORDENES DE LOS ELEMENTOS DEL GRUPO "+Gr_Name+"" << "\n";
	H.do_empty();
	H.fill_the_group();
	for(auto a : H) {
		const uint orden{a.elem_order()};
		tCayley 	<< "\\mathsf{o}{\\left({"
							<< a.to_string(letras)
							<< "}\\right)} = "
							<< orden << "\n";
	}

	gr_t ZG{H.centre()};
	tCayley << "\n\n" << "\t\tEL CENTRO DE " + Gr_Name +" ES" << "\n\n";
	tCayley << ZG.to_string(letras) << "\n\n";

	tCayley << "\n\n" << "\t\tLOS NORMALIZADORES DE LOS SUBGRUPOS DE " + Gr_Name +" SON" << "\n\n";

	for(auto P : L) {
		auto Q=H.normalizer(P);
		tCayley 	<< "\\mathsf{N}_{"
							<< latex_nom
							<< "}\\left("
							<< P.to_string(letras)
							<< "\\right) = "
							<< Q.to_string(letras) << "\\\\\n";
	}

	tCayley << "\n\n" << "\t\tLOS CENTRALIZADORES DE LOS SUBGRUPOS DE " + Gr_Name +" en " + Gr_Name +" son" << "\n\n";

	for(auto R : L) {
		auto Cdor=H.centralizer(R);
		tCayley 	<< "\\mathsf{C}_{"
							<< latex_nom
							<< "}\\left("
							<< R.to_string(letras)
							<< "\\right) = "
							<< Cdor.to_string(letras) << "\\\\\n";
	}

	tCayley << "\n\n" << "\t\tSUBGRUPOS DERIVADOS D DE " + Gr_Name +" en " + Gr_Name +" son" << "\n\n";

	for(uint i{1}; i < elem_t::Order_Of_This_Group ; ++i) {
		gr_t DERIVADO{H.derived(i)};
		tCayley 	<< "\\mathsf{D^{(" << i << ")}}{\\left("
							<< latex_nom
							<< "\\right)} = "
							<< DERIVADO.to_string(letras) << "\\\\\n";
	}


	tCayley << "\n\n" << "\t\tSUBGRUPOS L__DERIVADOS L DE " + Gr_Name +" en " + Gr_Name +" son" << "\n\n";

	for(uint i{1}; i< elem_t::Order_Of_This_Group ; ++i) {
		gr_t L_DERIVADO{H.L_derived(i)};
		tCayley 	<< "\\mathsf{D^{(" << i << ")}}{\\left("
							<< latex_nom
							<< "\\right)} = "
							<< L_DERIVADO.to_string(letras) << "\\\\\n";
	}

	const bool	G_es_abeliano{G.is_abelian()};
	const bool G_es_nilpotente{H.is_nilpotent()};
	const bool G_es_resoluble{H.is_solvable()};

	tCayley << "\n\n" << "\t\tEL GRUPO " + Gr_Name +" en " + Gr_Name +" ES RESOLUBLE, NILPOTENTE ..." << "\n\n";

	tCayley 	<< "ES ABELIANO : \t" << G_es_abeliano  << " \n";
	tCayley 	<< "ES RESOLUBLE : \t" << G_es_resoluble  << " \n";
	tCayley 	<< "ES NILPOTENTE : \t" << G_es_nilpotente  << " \n";

	tCayley << "\n\n" << "\t\tTESTEO DE INVERSION DE ELEMENTOS DE " + Gr_Name +" " << "\n\n";
	for(auto h : H){
			const elem_gr_t h_inv = h.inv();
			const elem_gr_t res = op_t::gr_bop(h,h_inv);
			tCayley 	<< h.to_string(letras)
								<< "*"
								<< h_inv.to_string(letras)
								<< "="
								<< res.to_string(letras)
								<< "\n";
	}
	groups_by_its_generators_t N_L;
	N_L.clear();
	for(auto Hsubgr : L) {
		for(auto g : Hsubgr) {
			elem_gr_t dp_unit{};
			gr_t HGens{};
			HGens.do_empty();
			if(g != dp_unit) {
				HGens.insert(g);
				gr_t::span_subgroup(HGens,Hsubgr);
				gr_t::span_subgroup(HGens,Hsubgr);
				gr_t::span_subgroup(HGens,Hsubgr);
				gr_t::span_subgroup(HGens,Hsubgr);
				gr_t::span_subgroup(HGens,Hsubgr);
				gr_t::span_subgroup(HGens,Hsubgr);
				gr_t::span_subgroup(HGens,Hsubgr);
				gr_t::span_subgroup(HGens,Hsubgr);
				gr_t::span_subgroup(HGens,Hsubgr);
				gr_t::span_subgroup(HGens,Hsubgr);
				gr_t::span_subgroup(HGens,Hsubgr);
				gr_t::span_subgroup(HGens,Hsubgr);
				gr_t::span_subgroup(HGens,Hsubgr);
				gr_t::span_subgroup(HGens,Hsubgr);
				gr_t::span_subgroup(HGens,Hsubgr);
				gr_t::span_subgroup(HGens,Hsubgr);
				gr_t::span_subgroup(HGens,Hsubgr);
				gr_t::span_subgroup(HGens,Hsubgr);
				gr_t BaseGen{};
				BaseGen.insert(g);
				if (HGens == Hsubgr) {
					N_L.emplace(BaseGen,Hsubgr);
					break;
				}
			}
		}
	}
	for(auto Hsubgr : L) {
		bool ya_generado{false};
		for(auto N_H : N_L) {
			if (N_H.second==Hsubgr) {
				ya_generado = true;
				break;
			}
		}
		if (!(ya_generado)) {
			for(auto g : Hsubgr) {
				for(auto k : Hsubgr) {
					elem_gr_t dp_unit{};
					gr_t HGens{};
					HGens.do_empty();
					if( (g != dp_unit )and
						(k != dp_unit )and
						(g != k		  )and
						(	(k != op_t::gr_bop(g,g)) and
							(g != op_t::gr_bop(k,k))
						)
					)
					{
						HGens.insert(g);
						HGens.insert(k);
						gr_t::span_subgroup(HGens,Hsubgr);
						gr_t::span_subgroup(HGens,Hsubgr);
						gr_t::span_subgroup(HGens,Hsubgr);
						gr_t::span_subgroup(HGens,Hsubgr);
						gr_t::span_subgroup(HGens,Hsubgr);
						gr_t::span_subgroup(HGens,Hsubgr);
						gr_t::span_subgroup(HGens,Hsubgr);
						gr_t::span_subgroup(HGens,Hsubgr);
						gr_t::span_subgroup(HGens,Hsubgr);
						gr_t::span_subgroup(HGens,Hsubgr);
						gr_t::span_subgroup(HGens,Hsubgr);
						gr_t::span_subgroup(HGens,Hsubgr);
						gr_t::span_subgroup(HGens,Hsubgr);
						gr_t::span_subgroup(HGens,Hsubgr);
						gr_t::span_subgroup(HGens,Hsubgr);
						gr_t::span_subgroup(HGens,Hsubgr);

						gr_t BaseGen{};
						BaseGen.insert(g);
						BaseGen.insert(k);
						if (HGens == Hsubgr) {
							N_L.emplace(BaseGen,Hsubgr);
							break;
						}
					}
				}
			}
		}
	}
	for(auto Hsubgr : L) {
		bool ya_generado{false};
		for(auto N_H : N_L) {
			if (N_H.second==Hsubgr) {
				ya_generado = true;
				break;
			}
		}
		if (!(ya_generado)) {
			for(auto g : Hsubgr) {
				for(auto k : Hsubgr) {
					for(auto h : Hsubgr) {
						elem_gr_t dp_unit{};
						gr_t HGens{};
						HGens.do_empty();
						if( (g != dp_unit )	and
							(k != dp_unit )	and
							(h != dp_unit) 	and
							(g != h)		and
							(g != k)		and
							(h != k)		and
							(	(k != op_t::gr_bop(g,g)) and
								(k != op_t::gr_bop(h,h)) and
								(g != op_t::gr_bop(k,k)) and
								(g != op_t::gr_bop(h,h)) and
								(h != op_t::gr_bop(k,k)) and
								(h != op_t::gr_bop(g,g)) and
								(k != op_t::gr_bop(k,g)) and
								(k != op_t::gr_bop(g,k)) and
								(k != op_t::gr_bop(k,h)) and
								(k != op_t::gr_bop(h,k)) and
								(k != op_t::gr_bop(g,h)) and
								(k != op_t::gr_bop(h,g)) and
								(g != op_t::gr_bop(k,g)) and
								(g != op_t::gr_bop(g,k)) and
								(g != op_t::gr_bop(k,h)) and
								(g != op_t::gr_bop(h,k)) and
								(g != op_t::gr_bop(g,h)) and
								(g != op_t::gr_bop(h,g)) and
								(h != op_t::gr_bop(k,g)) and
								(h != op_t::gr_bop(g,k)) and
								(h != op_t::gr_bop(k,h)) and
								(h != op_t::gr_bop(h,k)) and
								(h != op_t::gr_bop(g,h)) and
								(h != op_t::gr_bop(h,g))
							)
						)
						{
							HGens.insert(g);
							HGens.insert(k);
							HGens.insert(h);
							gr_t::span_subgroup(HGens,Hsubgr);
							gr_t::span_subgroup(HGens,Hsubgr);
							gr_t::span_subgroup(HGens,Hsubgr);
							gr_t::span_subgroup(HGens,Hsubgr);
							gr_t::span_subgroup(HGens,Hsubgr);
							gr_t::span_subgroup(HGens,Hsubgr);
							gr_t::span_subgroup(HGens,Hsubgr);
							gr_t::span_subgroup(HGens,Hsubgr);
							gr_t::span_subgroup(HGens,Hsubgr);
							gr_t::span_subgroup(HGens,Hsubgr);
							gr_t::span_subgroup(HGens,Hsubgr);
							gr_t::span_subgroup(HGens,Hsubgr);
							gr_t::span_subgroup(HGens,Hsubgr);
							gr_t::span_subgroup(HGens,Hsubgr);
							gr_t::span_subgroup(HGens,Hsubgr);
							gr_t::span_subgroup(HGens,Hsubgr);

							gr_t BaseGen{};
							BaseGen.insert(g);
							BaseGen.insert(k);
							BaseGen.insert(h);
							if (HGens == Hsubgr) {
								N_L.emplace(BaseGen,Hsubgr);
								break;
							}
						}
					}
				}
			}
		}
	}
	tCayley 	<< "\n\n GENERADORES Y GENERADOS \n";
	for(auto pair_set_group : N_L) {
		gr_t keys{pair_set_group.first};
		gr_t values{pair_set_group.second};
		tCayley 	<< "{\\left\\langle{"
							<< keys.to_string(letras)
							<< "}\\right\\rangle} = "
							<< values.to_string(letras)
							<< "\n";
	}
	tCayley.close();
	return;
}

};

template<uint N>
	struct get_group_info<group_name::Dic,2,N> {
	static_assert(N>3);
	static_assert(N%2==0);
	static void work(std::string nombre_de_grupo,
								std::string nombre_de_grupo_en_latex,
								std::string abecedario) {

	using elem_t = element_of_set_t<2,N>;
	constexpr std::size_t Gr_Ord = elem_t::Order_Of_This_Group;
	using op_t	= group_binop_t<group_name::Dic,2,N>;
	using elem_gr_t = element_of_group_t<group_name::Dic,2,N>;
	using gr_t = group_t<group_name::Dic,2,N>;
	using groups_by_its_generators_t = typename std::map<gr_t,gr_t>;
	using lattice_t = set_lattice_t<group_name::Dic,2,N>;

	std::string temp_formato_de_tabla{"|c"};
	for(uint i{1}; i < Gr_Ord ; ++i) {
		temp_formato_de_tabla += "|c";
	}
	temp_formato_de_tabla += "|";
	const std::string formato_de_tabla{temp_formato_de_tabla};
	const std::string Gr_Name = 	nombre_de_grupo 		+
									".ord_grp_" 			+
									std::to_string(Gr_Ord) 	+
									".info.txt"					;

	std::ofstream tCayley(Gr_Name, std::ofstream::out);

    std::string latex_nom=nombre_de_grupo_en_latex;
	tCayley << std::boolalpha;
	elem_gr_t eg_i;
	elem_t es_j;
	elem_t es_k;
	gr_t G{};
	G.fill_the_group();
	gr_t gr{};
	gr.fill_the_group();
	lattice_t lattice{};

	const std::string letras = abecedario;

	tCayley			 	<< "\n \t\tPor enumeración, iterando sobre los elementos del grupo "
								<< "\n \t\t\tLA TABLA DE CAYLEY "
								<< "\n\n\n";
	tCayley			 	<< "\\begin{align*}\n";
	tCayley			 	<< "\\begin{array}{"+formato_de_tabla+"}\n";
	tCayley			 	<< "\\hline\n";
	uint index = 1;
	for(auto a : gr) {
		for(auto b : gr) {
			const elem_gr_t  r = op_t::gr_bop(a,b);
			const std::string R{r.to_string(letras)};
			tCayley 	<< R;
			if (index%Gr_Ord==0)
				tCayley 	<< "\\\\";
			else
				tCayley 	<< "&";
			++index;
		}
		tCayley 	<< "\n" << "\\hline\n";
	}
	tCayley << "\\end{array}\n";
	tCayley << "\\end{align*}\n\n\n";


	const bool es_asociativo{gr.is_associative()};
	if (es_asociativo) {
		tCayley << "SI : El grupo " + Gr_Name +" ES ASOCIATIVO\n";
	}
	else {
		tCayley << "NO : El grupo " + Gr_Name +" NO ES ASOCIATIVO (NI GRUPO)\n";
	}

	const bool tiene_elemento_inverso{gr.exists_inverse_for_every_element()};
	if (tiene_elemento_inverso) {
		tCayley << "SI : El grupo " + Gr_Name +" TIENE ELEMENTO INVERSO\n";
	}
	else {
		tCayley << "NO : El grupo " + Gr_Name +" NO TIENE ELEMENTO INVERSO (NI ES GRUPO)\n";
	}

	const bool existe_elemento_neutro{gr.has_the_trusthed_unity()};
	if (existe_elemento_neutro) {
		tCayley << "SI : El grupo " + Gr_Name +" TIENE ELEMENTO NEUTRO\n";
	}
	else {
		tCayley << "NO : El grupo " + Gr_Name +" NO TIENE ELEMENTO NEUTRO (NI ES GRUPO)\n";
	}


	const elem_gr_t defecto{elem_gr_t()};
	const auto unidad_result{gr.get_the_trusthed_unity()};
	const elem_gr_t unidad = unidad_result.first;
	gr_t vacio{};
	vacio.do_empty();
	vacio.setdata.insert(unidad);
	const gr_t VACIO(vacio);
	tCayley 	<< "Si ha salido SI anteriormente, el grupo " + Gr_Name +" "
				<< "?tiene como neutro?? : "
				<< unidad_result.second << "\n";
	if (unidad_result.second) {
		tCayley 	<< "El \"neutro\" del producto directo es : "
					<< unidad_result.first.to_string(letras) << "\n";
		tCayley 	<< "El neutro de la operacion del grupo " + Gr_Name +" es : "
					<< unidad_result.first.to_string(letras) << "\n";
		tCayley 	<< "?coincide el neutro de la operacion del grupo " + Gr_Name +" con el del Producto Directo?? : "
					<< (defecto==unidad_result.first) << "\n";
		tCayley 	<< "?coincide el neutro de la operacion del grupo " + Gr_Name +" con el del Producto Directo?? [FUNCION] : "
					<< (VACIO.dp_unit_equal_gr_unit()) << "\n";
	}

	const bool es_abeliano{gr.is_abelian()};
	if (es_abeliano) {
		tCayley << "El grupo " + Gr_Name +" ES ABELIANO\n";
	}
	else {
		tCayley << "El grupo " + Gr_Name +" ES GRUPO NO ABELIANO\n";
	}

	tCayley << "\n\n" << "\t\tSUBGRUPOS CICLICOS DE "+Gr_Name+"" << "\n\n";
	std::string Lcyclic{};
	lattice_t L{};
	L.clear();
	fill_the_cyclic_subgroups_lattice(L);

	for(auto K : L) {
		tCayley << K.to_string(letras) << "\n";
		tCayley << "Es operacion interna : " << K.is_inner_binary_operation() << "\n";
		tCayley << "Tiene todos los inversos : " << K.is_inner_inverter() << "\n";
		tCayley << "Tiene el elemento neutro : " << K.has_the_trusthed_unity() << "\n";
		tCayley << "Es abeliano : " << K.is_abelian() << "\n";
		tCayley << "Es resoluble : " << K.is_solvable() << "\n";
		tCayley << "Es nilpotente : " << K.is_nilpotent() << "\n";
		tCayley << "Su orden es : " << K.cardinal() << "\n";
	}
	to_string(Lcyclic,L,letras);
	tCayley << Lcyclic << "\n";
	tCayley << "nº de subgrupos ciclicos " << L.size() << "\n";

	tCayley << "\n\n" << "\t\tSUBGRUPOS GENERADOS POR 2 O MENOS ELEMENTOS DE " << Gr_Name << "\n\n";
	std::string L2generated{};
	fill_the_2_generated_subgroups_lattice(L);
	for(auto K : L) {
		tCayley << K.to_string(letras) << "\n";
		tCayley << "Es operacion interna : " << K.is_inner_binary_operation() << "\n";
		tCayley << "Tiene todos los inversos : " << K.is_inner_inverter() << "\n";
		tCayley << "Tiene el elemento neutro : " << K.has_the_trusthed_unity() << "\n";
		tCayley << "Es abeliano : " << K.is_abelian() << "\n";
		tCayley << "Es resoluble : " << K.is_solvable() << "\n";
		tCayley << "Es nilpotente : " << K.is_nilpotent() << "\n";
		tCayley << "Su orden es : " << K.cardinal() << "\n";
	}
	to_string(L2generated,L,letras);
	tCayley << L2generated << "\n";
	tCayley << "nº de subgrupos generados por 2 o menos elementos " << L.size() << "\n";

	tCayley 	<< "\n\n\n"
						<< "\t\t/////////////////////////////////////////////////////////"
						<< "\n";
	tCayley 	<< "\t\tSUBGRUPOS GENERADOS POR 3 O MENOS ELEMENTOS DE "+Gr_Name+""
						<< "\n";
	tCayley 	<< "\t\t/////////////////////////////////////////////////////////"
						<< "\n\n";
	std::string L3generated{};
	fill_the_3_generated_subgroups_lattice(L);
	for(auto K : L) {
		tCayley << K.to_string(letras) << "\n";
		tCayley << "Es operacion interna : \t" << K.is_inner_binary_operation() << "\n";
		tCayley << "Tiene todos los inversos : \t" << K.is_inner_inverter() << "\n";
		tCayley << "Tiene el elemento neutro : \t" << K.has_the_trusthed_unity() << "\n";
		tCayley << "Es abeliano : \t\t" << K.is_abelian() << "\n";
		tCayley << "Es resoluble : \t\t" << K.is_solvable() << "\n";
		tCayley << "Es nilpotente : \t\t" << K.is_nilpotent() << "\n";
		tCayley << "Su orden es : \t\t" << K.cardinal() << "\n";
	}
	to_string(L3generated,L,letras);
	tCayley << L3generated << "\n";
	tCayley << "nº de subgrupos generados por 3 o menos elementos " << L.size() << "\n";

	tCayley << "\n\n\tELEMENTOS DEL GRUPO "+Gr_Name+"" << "\n";
	gr_t H{};
	H.fill_the_group();
	for(auto a : H) {
		tCayley << a.to_string(letras) << "\n";
	}
tCayley << "\n\n\tTESTEO DE LOS ORDENES DE LOS ELEMENTOS DEL GRUPO "+Gr_Name+"" << "\n";
	H.do_empty();
	H.fill_the_group();
	for(auto a : H) {
		const uint orden{a.elem_order()};
		tCayley 	<< "\\mathsf{o}{\\left({"
							<< a.to_string(letras)
							<< "}\\right)} = "
							<< orden << "\n";
	}

	gr_t ZG{H.centre()};
	tCayley << "\n\n" << "\t\tEL CENTRO DE " + Gr_Name +" ES" << "\n\n";
	tCayley << ZG.to_string(letras) << "\n\n";

	tCayley << "\n\n" << "\t\tLOS NORMALIZADORES DE LOS SUBGRUPOS DE " + Gr_Name +" SON" << "\n\n";

	for(auto P : L) {
		auto Q=H.normalizer(P);
		tCayley 	<< "\\mathsf{N}_{"
							<< latex_nom
							<< "}\\left("
							<< P.to_string(letras)
							<< "\\right) = "
							<< Q.to_string(letras) << "\\\\\n";
	}

	tCayley << "\n\n" << "\t\tLOS CENTRALIZADORES DE LOS SUBGRUPOS DE " + Gr_Name +" en " + Gr_Name +" son" << "\n\n";

	for(auto R : L) {
		auto Cdor=H.centralizer(R);
		tCayley 	<< "\\mathsf{C}_{"
							<< latex_nom
							<< "}\\left("
							<< R.to_string(letras)
							<< "\\right) = "
							<< Cdor.to_string(letras) << "\\\\\n";
	}

	tCayley << "\n\n" << "\t\tSUBGRUPOS DERIVADOS D DE " + Gr_Name +" en " + Gr_Name +" son" << "\n\n";

	for(uint i{1}; i < elem_t::Order_Of_This_Group ; ++i) {
		gr_t DERIVADO{H.derived(i)};
		tCayley 	<< "\\mathsf{D^{(" << i << ")}}{\\left("
							<< latex_nom
							<< "\\right)} = "
							<< DERIVADO.to_string(letras) << "\\\\\n";
	}


	tCayley << "\n\n" << "\t\tSUBGRUPOS L__DERIVADOS L DE " + Gr_Name +" en " + Gr_Name +" son" << "\n\n";

	for(uint i{1}; i< elem_t::Order_Of_This_Group ; ++i) {
		gr_t L_DERIVADO{H.L_derived(i)};
		tCayley 	<< "\\mathsf{D^{(" << i << ")}}{\\left("
							<< latex_nom
							<< "\\right)} = "
							<< L_DERIVADO.to_string(letras) << "\\\\\n";
	}

	const bool G_es_abeliano{G.is_abelian()};
	const bool G_es_nilpotente{H.is_nilpotent()};
	const bool G_es_resoluble{H.is_solvable()};

	tCayley << "\n\n" << "\t\tEL GRUPO " + Gr_Name +" en " + Gr_Name +" ES RESOLUBLE, NILPOTENTE ..." << "\n\n";

	tCayley 	<< "ES ABELIANO : \t" << G_es_abeliano  << " \n";
	tCayley 	<< "ES RESOLUBLE : \t" << G_es_resoluble  << " \n";
	tCayley 	<< "ES NILPOTENTE : \t" << G_es_nilpotente  << " \n";

	tCayley << "\n\n" << "\t\tTESTEO DE INVERSION DE ELEMENTOS DE " + Gr_Name +" " << "\n\n";
	for(auto h : H){
			const elem_gr_t h_inv = h.inv();
			const elem_gr_t res = op_t::gr_bop(h,h_inv);
			tCayley 	<< h.to_string(letras)
								<< "*"
								<< h_inv.to_string(letras)
								<< "="
								<< res.to_string(letras)
								<< "\n";
	}
	groups_by_its_generators_t N_L;
	N_L.clear();
	for(auto Hsubgr : L) {
		for(auto g : Hsubgr) {
			elem_gr_t dp_unit{};
			gr_t HGens{};
			HGens.do_empty();
			if(g != dp_unit) {
				HGens.insert(g);
				gr_t::span_subgroup(HGens,Hsubgr);
				gr_t::span_subgroup(HGens,Hsubgr);
				gr_t::span_subgroup(HGens,Hsubgr);
				gr_t::span_subgroup(HGens,Hsubgr);
				gr_t::span_subgroup(HGens,Hsubgr);
				gr_t::span_subgroup(HGens,Hsubgr);
				gr_t::span_subgroup(HGens,Hsubgr);
				gr_t::span_subgroup(HGens,Hsubgr);
				gr_t::span_subgroup(HGens,Hsubgr);
				gr_t::span_subgroup(HGens,Hsubgr);
				gr_t::span_subgroup(HGens,Hsubgr);
				gr_t::span_subgroup(HGens,Hsubgr);
				gr_t::span_subgroup(HGens,Hsubgr);
				gr_t::span_subgroup(HGens,Hsubgr);
				gr_t::span_subgroup(HGens,Hsubgr);
				gr_t::span_subgroup(HGens,Hsubgr);
				gr_t::span_subgroup(HGens,Hsubgr);
				gr_t::span_subgroup(HGens,Hsubgr);
				gr_t BaseGen{};
				BaseGen.insert(g);
				if (HGens == Hsubgr) {
					N_L.emplace(BaseGen,Hsubgr);
					break;
				}
			}
		}
	}
	for(auto Hsubgr : L) {
		bool ya_generado{false};
		for(auto N_H : N_L) {
			if (N_H.second==Hsubgr) {
				ya_generado = true;
				break;
			}
		}
		if (!(ya_generado)) {
			for(auto g : Hsubgr) {
				for(auto k : Hsubgr) {
					elem_gr_t dp_unit{};
					gr_t HGens{};
					HGens.do_empty();
					if( (g != dp_unit )and
						(k != dp_unit )and
						(g != k		  )and
						(	(k != op_t::gr_bop(g,g)) and
							(g != op_t::gr_bop(k,k))
						)
					)
					{
						HGens.insert(g);
						HGens.insert(k);
						gr_t::span_subgroup(HGens,Hsubgr);
						gr_t::span_subgroup(HGens,Hsubgr);
						gr_t::span_subgroup(HGens,Hsubgr);
						gr_t::span_subgroup(HGens,Hsubgr);
						gr_t::span_subgroup(HGens,Hsubgr);
						gr_t::span_subgroup(HGens,Hsubgr);
						gr_t::span_subgroup(HGens,Hsubgr);
						gr_t::span_subgroup(HGens,Hsubgr);
						gr_t::span_subgroup(HGens,Hsubgr);
						gr_t::span_subgroup(HGens,Hsubgr);
						gr_t::span_subgroup(HGens,Hsubgr);
						gr_t::span_subgroup(HGens,Hsubgr);
						gr_t::span_subgroup(HGens,Hsubgr);
						gr_t::span_subgroup(HGens,Hsubgr);
						gr_t::span_subgroup(HGens,Hsubgr);
						gr_t::span_subgroup(HGens,Hsubgr);

						gr_t BaseGen{};
						BaseGen.insert(g);
						BaseGen.insert(k);
						if (HGens == Hsubgr) {
							N_L.emplace(BaseGen,Hsubgr);
							break;
						}
					}
				}
			}
		}
	}
	for(auto Hsubgr : L) {
		bool ya_generado{false};
		for(auto N_H : N_L) {
			if (N_H.second==Hsubgr) {
				ya_generado = true;
				break;
			}
		}
		if (!(ya_generado)) {
			for(auto g : Hsubgr) {
				for(auto k : Hsubgr) {
					for(auto h : Hsubgr) {
						elem_gr_t dp_unit{};
						gr_t HGens{};
						HGens.do_empty();
						if( (g != dp_unit )	and
							(k != dp_unit )	and
							(h != dp_unit) 	and
							(g != h)		and
							(g != k)		and
							(h != k)		and
							(	(k != op_t::gr_bop(g,g)) and
								(k != op_t::gr_bop(h,h)) and
								(g != op_t::gr_bop(k,k)) and
								(g != op_t::gr_bop(h,h)) and
								(h != op_t::gr_bop(k,k)) and
								(h != op_t::gr_bop(g,g)) and
								(k != op_t::gr_bop(k,g)) and
								(k != op_t::gr_bop(g,k)) and
								(k != op_t::gr_bop(k,h)) and
								(k != op_t::gr_bop(h,k)) and
								(k != op_t::gr_bop(g,h)) and
								(k != op_t::gr_bop(h,g)) and
								(g != op_t::gr_bop(k,g)) and
								(g != op_t::gr_bop(g,k)) and
								(g != op_t::gr_bop(k,h)) and
								(g != op_t::gr_bop(h,k)) and
								(g != op_t::gr_bop(g,h)) and
								(g != op_t::gr_bop(h,g)) and
								(h != op_t::gr_bop(k,g)) and
								(h != op_t::gr_bop(g,k)) and
								(h != op_t::gr_bop(k,h)) and
								(h != op_t::gr_bop(h,k)) and
								(h != op_t::gr_bop(g,h)) and
								(h != op_t::gr_bop(h,g))
							)
						)
						{
							HGens.insert(g);
							HGens.insert(k);
							HGens.insert(h);
							gr_t::span_subgroup(HGens,Hsubgr);
							gr_t::span_subgroup(HGens,Hsubgr);
							gr_t::span_subgroup(HGens,Hsubgr);
							gr_t::span_subgroup(HGens,Hsubgr);
							gr_t::span_subgroup(HGens,Hsubgr);
							gr_t::span_subgroup(HGens,Hsubgr);
							gr_t::span_subgroup(HGens,Hsubgr);
							gr_t::span_subgroup(HGens,Hsubgr);
							gr_t::span_subgroup(HGens,Hsubgr);
							gr_t::span_subgroup(HGens,Hsubgr);
							gr_t::span_subgroup(HGens,Hsubgr);
							gr_t::span_subgroup(HGens,Hsubgr);
							gr_t::span_subgroup(HGens,Hsubgr);
							gr_t::span_subgroup(HGens,Hsubgr);
							gr_t::span_subgroup(HGens,Hsubgr);
							gr_t::span_subgroup(HGens,Hsubgr);

							gr_t BaseGen{};
							BaseGen.insert(g);
							BaseGen.insert(k);
							BaseGen.insert(h);
							if (HGens == Hsubgr) {
								N_L.emplace(BaseGen,Hsubgr);
								break;
							}
						}
					}
				}
			}
		}
	}
	tCayley 	<< "\n\n GENERADORES Y GENERADOS \n";
	for(auto pair_set_group : N_L) {
		gr_t keys{pair_set_group.first};
		gr_t values{pair_set_group.second};
		tCayley 	<< "{\\left\\langle{"
							<< keys.to_string(letras)
							<< "}\\right\\rangle} = "
							<< values.to_string(letras)
							<< "\n";
	}
	tCayley.close();
	return;
}
};

template<uint p,uint q>
	struct get_group_info<group_name::GDih,p,q> {
	static_assert(p>2);
	static_assert(q>p);
	static_assert(is_prime(p));
	static_assert(is_prime(q));
	static_assert((q-1)%p==0);
	using elem_t = element_of_set_t<p,q>;
	static constexpr std::size_t Gr_Ord = p*q;
	using op_t	= group_binop_t<group_name::GDih,p,q>;
	using elem_gr_t = element_of_group_t<group_name::GDih,p,q>;
	using gr_t = group_t<group_name::GDih,p,q>;
	using lattice_t = set_lattice_t<group_name::GDih,p,q>;
	using groups_by_its_generators_t = typename std::map<gr_t,gr_t>;
	constexpr static uint r = (q-1)/p;

	static void work(std::string nombre_de_grupo,
								std::string nombre_de_grupo_en_latex,
								std::string abecedario) {
	std::string temp_formato_de_tabla{"|c"};
	for(uint i{1}; i < Gr_Ord ; ++i) {
		temp_formato_de_tabla += "|c";
	}
	temp_formato_de_tabla += "|";
	const std::string formato_de_tabla{temp_formato_de_tabla};
	const std::string Gr_Name = 	nombre_de_grupo 		+
									".ord_grp_" 			+
									std::to_string(Gr_Ord) 	+
									".info.txt"					;

	std::ofstream tCayley(Gr_Name, std::ofstream::out);

    std::string latex_nom=nombre_de_grupo_en_latex;
	tCayley << std::boolalpha;
	elem_gr_t eg_i;
	elem_t es_j;
	elem_t es_k;
	gr_t G{};
	G.fill_the_group();
	gr_t gr{};
	gr.fill_the_group();
	lattice_t lattice{};

	const std::string letras = abecedario;

	tCayley			 	<< "\n \t\tPor enumeración, iterando sobre los elementos del grupo "
								<< "\n \t\t\tLA TABLA DE CAYLEY "
								<< "\n\n\n";
	tCayley			 	<< "\\begin{align*}\n";
	tCayley			 	<< "\\begin{array}{"+formato_de_tabla+"}\n";
	tCayley			 	<< "\\hline\n";
	uint index = 1;
	for(auto a : gr) {
		for(auto b : gr) {
			const elem_gr_t  rs = op_t::gr_bop(a,b);
			const std::string R{rs.to_string(letras)};
			tCayley 	<< R;
			if (index%Gr_Ord==0)
				tCayley 	<< "\\\\";
			else
				tCayley 	<< "&";
			++index;
		}
		tCayley 	<< "\n" << "\\hline\n";
	}
	tCayley << "\\end{array}\n";
	tCayley << "\\end{align*}\n\n\n";


	const bool es_asociativo{gr.is_associative()};
	if (es_asociativo) {
		tCayley << "SI : El grupo " + Gr_Name +" ES ASOCIATIVO\n";
	}
	else {
		tCayley << "NO : El grupo " + Gr_Name +" NO ES ASOCIATIVO (NI GRUPO)\n";
	}

	const bool tiene_elemento_inverso{gr.exists_inverse_for_every_element()};
	if (tiene_elemento_inverso) {
		tCayley << "SI : El grupo " + Gr_Name +" TIENE ELEMENTO INVERSO\n";
	}
	else {
		tCayley << "NO : El grupo " + Gr_Name +" NO TIENE ELEMENTO INVERSO (NI ES GRUPO)\n";
	}

	const bool existe_elemento_neutro{gr.has_the_trusthed_unity()};
	if (existe_elemento_neutro) {
		tCayley << "SI : El grupo " + Gr_Name +" TIENE ELEMENTO NEUTRO\n";
	}
	else {
		tCayley << "NO : El grupo " + Gr_Name +" NO TIENE ELEMENTO NEUTRO (NI ES GRUPO)\n";
	}


	const elem_gr_t defecto{elem_gr_t()};
	const auto unidad_result{gr.get_the_trusthed_unity()};
	const elem_gr_t unidad = unidad_result.first;
	gr_t vacio{};
	vacio.do_empty();
	vacio.setdata.insert(unidad);
	const gr_t VACIO(vacio);
	tCayley 	<< "Si ha salido SI anteriormente, el grupo " + Gr_Name +" "
				<< "?tiene como neutro?? : "
				<< unidad_result.second << "\n";
	if (unidad_result.second) {
		tCayley 	<< "El \"neutro\" del producto directo es : "
					<< unidad_result.first.to_string(letras) << "\n";
		tCayley 	<< "El neutro de la operacion del grupo " + Gr_Name +" es : "
					<< unidad_result.first.to_string(letras) << "\n";
		tCayley 	<< "?coincide el neutro de la operacion del grupo " + Gr_Name +" con el del Producto Directo?? : "
					<< (defecto==unidad_result.first) << "\n";
		tCayley 	<< "?coincide el neutro de la operacion del grupo " + Gr_Name +" con el del Producto Directo?? [FUNCION] : "
					<< (VACIO.dp_unit_equal_gr_unit()) << "\n";
	}

	const bool es_abeliano{gr.is_abelian()};
	if (es_abeliano) {
		tCayley << "El grupo " + Gr_Name +" ES ABELIANO\n";
	}
	else {
		tCayley << "El grupo " + Gr_Name +" ES GRUPO NO ABELIANO\n";
	}

	tCayley << "\n\n" << "\t\tSUBGRUPOS CICLICOS DE "+Gr_Name+"" << "\n\n";
	std::string Lcyclic{};
	lattice_t L{};
	L.clear();
	fill_the_cyclic_subgroups_lattice(L);

	for(auto K : L) {
		tCayley << K.to_string(letras) << "\n";
		tCayley << "Es operacion interna : " << K.is_inner_binary_operation() << "\n";
		tCayley << "Tiene todos los inversos : " << K.is_inner_inverter() << "\n";
		tCayley << "Tiene el elemento neutro : " << K.has_the_trusthed_unity() << "\n";
		tCayley << "Es abeliano : " << K.is_abelian() << "\n";
		tCayley << "Es resoluble : " << K.is_solvable() << "\n";
		tCayley << "Es nilpotente : " << K.is_nilpotent() << "\n";
		tCayley << "Su orden es : " << K.cardinal() << "\n";
	}
	to_string(Lcyclic,L,letras);
	tCayley << Lcyclic << "\n";
	tCayley << "nº de subgrupos ciclicos " << L.size() << "\n";

	tCayley << "\n\n" << "\t\tSUBGRUPOS GENERADOS POR 2 O MENOS ELEMENTOS DE " << Gr_Name << "\n\n";
	std::string L2generated{};
	fill_the_2_generated_subgroups_lattice(L);
	for(auto K : L) {
		tCayley << K.to_string(letras) << "\n";
		tCayley << "Es operacion interna : " << K.is_inner_binary_operation() << "\n";
		tCayley << "Tiene todos los inversos : " << K.is_inner_inverter() << "\n";
		tCayley << "Tiene el elemento neutro : " << K.has_the_trusthed_unity() << "\n";
		tCayley << "Es abeliano : " << K.is_abelian() << "\n";
		tCayley << "Es resoluble : " << K.is_solvable() << "\n";
		tCayley << "Es nilpotente : " << K.is_nilpotent() << "\n";
		tCayley << "Su orden es : " << K.cardinal() << "\n";
	}
	to_string(L2generated,L,letras);
	tCayley << L2generated << "\n";
	tCayley << "nº de subgrupos generados por 2 o menos elementos " << L.size() << "\n";
/*
	tCayley 	<< "\n\n\n"
						<< "\t\t/////////////////////////////////////////////////////////"
						<< "\n";
	tCayley 	<< "\t\tSUBGRUPOS GENERADOS POR 3 O MENOS ELEMENTOS DE "+Gr_Name+""
						<< "\n";
	tCayley 	<< "\t\t/////////////////////////////////////////////////////////"
						<< "\n\n";
	std::string L3generated{};
	fill_the_3_generated_subgroups_lattice(L);
	for(auto K : L) {
		tCayley << K.to_string(letras) << "\n";
		tCayley << "Es operacion interna : \t" << K.is_inner_binary_operation() << "\n";
		tCayley << "Tiene todos los inversos : \t" << K.is_inner_inverter() << "\n";
		tCayley << "Tiene el elemento neutro : \t" << K.has_the_trusthed_unity() << "\n";
		tCayley << "Es abeliano : \t\t" << K.is_abelian() << "\n";
		tCayley << "Es resoluble : \t\t" << K.is_solvable() << "\n";
		tCayley << "Es nilpotente : \t\t" << K.is_nilpotent() << "\n";
		tCayley << "Su orden es : \t\t" << K.cardinal() << "\n";
	}
	to_string(L3generated,L,letras);
	tCayley << L3generated << "\n";
	tCayley << "nº de subgrupos generados por 3 o menos elementos " << L.size() << "\n";
*/
	tCayley << "\n\n\tELEMENTOS DEL GRUPO "+Gr_Name+"" << "\n";
	gr_t H{};
	H.fill_the_group();
	for(auto a : H) {
		tCayley << a.to_string(letras) << "\n";
	}
tCayley << "\n\n\tTESTEO DE LOS ORDENES DE LOS ELEMENTOS DEL GRUPO "+Gr_Name+"" << "\n";
	H.do_empty();
	H.fill_the_group();
	for(auto a : H) {
		const uint orden{a.elem_order()};
		tCayley 	<< "\\mathsf{o}{\\left({"
							<< a.to_string(letras)
							<< "}\\right)} = "
							<< orden << "\n";
	}

	gr_t ZG{H.centre()};
	tCayley << "\n\n" << "\t\tEL CENTRO DE " + Gr_Name +" ES" << "\n\n";
	tCayley << ZG.to_string(letras) << "\n\n";

	tCayley << "\n\n" << "\t\tLOS NORMALIZADORES DE LOS SUBGRUPOS DE " + Gr_Name +" SON" << "\n\n";
	for(auto P : L) {
		auto Q=H.normalizer(P);
		tCayley 	<< "\\mathsf{N}_{"
							<< latex_nom
							<< "}\\left("
							<< P.to_string(letras)
							<< "\\right) = "
							<< Q.to_string(letras) << "\\\\\n";
	}

	tCayley << "\n\n" << "\t\tLOS CENTRALIZADORES DE LOS SUBGRUPOS DE " + Gr_Name +" en " + Gr_Name +" son" << "\n\n";

	for(auto R : L) {
		auto Cdor=H.centralizer(R);
		tCayley 	<< "\\mathsf{C}_{"
							<< latex_nom
							<< "}\\left("
							<< R.to_string(letras)
							<< "\\right) = "
							<< Cdor.to_string(letras) << "\\\\\n";
	}

	tCayley << "\n\n" << "\t\tSUBGRUPOS DERIVADOS D DE " + Gr_Name +" en " + Gr_Name +" son" << "\n\n";

	for(uint i{1}; i < elem_t::Order_Of_This_Group ; ++i) {
		gr_t DERIVADO{H.derived(i)};
		tCayley 	<< "\\mathsf{D^{(" << i << ")}}{\\left("
							<< latex_nom
							<< "\\right)} = "
							<< DERIVADO.to_string(letras) << "\\\\\n";
	}


	tCayley << "\n\n" << "\t\tSUBGRUPOS L__DERIVADOS L DE " + Gr_Name +" en " + Gr_Name +" son" << "\n\n";

	for(uint i{1}; i< elem_t::Order_Of_This_Group ; ++i) {
		gr_t L_DERIVADO{H.L_derived(i)};
		tCayley 	<< "\\mathsf{L_{(" << i << ")}}{\\left("
							<< latex_nom
							<< "\\right)} = "
							<< L_DERIVADO.to_string(letras) << "\\\\\n";
	}

	const bool	G_es_abeliano{G.is_abelian()};
	const bool G_es_nilpotente{H.is_nilpotent()};
	const bool G_es_resoluble{H.is_solvable()};

	tCayley << "\n\n" << "\t\tEL GRUPO " + Gr_Name +" en " + Gr_Name +" ES RESOLUBLE, NILPOTENTE ..." << "\n\n";

	tCayley 	<< "ES ABELIANO : \t" << G_es_abeliano  << " \n";
	tCayley 	<< "ES RESOLUBLE : \t" << G_es_resoluble  << " \n";
	tCayley 	<< "ES NILPOTENTE : \t" << G_es_nilpotente  << " \n";

	tCayley << "\n\n" << "\t\tTESTEO DE INVERSION DE ELEMENTOS DE " + Gr_Name +" " << "\n\n";
	for(auto h : H){
			const elem_gr_t h_inv = h.inv();
			const elem_gr_t res = op_t::gr_bop(h,h_inv);
			tCayley 	<< h.to_string(letras)
								<< "*"
								<< h_inv.to_string(letras)
								<< "="
								<< res.to_string(letras)
								<< "\n";
	}
	groups_by_its_generators_t N_L;
	N_L.clear();
	for(auto Hsubgr : L) {
		for(auto g : Hsubgr) {
			elem_gr_t dp_unit{};
			gr_t HGens{};
			HGens.do_empty();
			if(g != dp_unit) {
				HGens.insert(g);
				gr_t::span_subgroup(HGens,Hsubgr);
				gr_t::span_subgroup(HGens,Hsubgr);
				gr_t::span_subgroup(HGens,Hsubgr);
				gr_t::span_subgroup(HGens,Hsubgr);
				gr_t::span_subgroup(HGens,Hsubgr);
				gr_t::span_subgroup(HGens,Hsubgr);
				gr_t::span_subgroup(HGens,Hsubgr);
				gr_t::span_subgroup(HGens,Hsubgr);
				gr_t::span_subgroup(HGens,Hsubgr);
				gr_t::span_subgroup(HGens,Hsubgr);
				gr_t::span_subgroup(HGens,Hsubgr);
				gr_t::span_subgroup(HGens,Hsubgr);
				gr_t::span_subgroup(HGens,Hsubgr);
				gr_t::span_subgroup(HGens,Hsubgr);
				gr_t::span_subgroup(HGens,Hsubgr);
				gr_t::span_subgroup(HGens,Hsubgr);
				gr_t::span_subgroup(HGens,Hsubgr);
				gr_t::span_subgroup(HGens,Hsubgr);
				gr_t BaseGen{};
				BaseGen.insert(g);
				if (HGens == Hsubgr) {
					N_L.emplace(BaseGen,Hsubgr);
					break;
				}
			}
		}
	}
	for(auto Hsubgr : L) {
		bool ya_generado{false};
		for(auto N_H : N_L) {
			if (N_H.second==Hsubgr) {
				ya_generado = true;
				break;
			}
		}
		if (!(ya_generado)) {
			for(auto g : Hsubgr) {
				for(auto k : Hsubgr) {
					elem_gr_t dp_unit{};
					gr_t HGens{};
					HGens.do_empty();
					if( (g != dp_unit )and
						(k != dp_unit )and
						(g != k		  )and
						(	(k != op_t::gr_bop(g,g)) and
							(g != op_t::gr_bop(k,k))
						)
					)
					{
						HGens.insert(g);
						HGens.insert(k);
						gr_t::span_subgroup(HGens,Hsubgr);
						gr_t::span_subgroup(HGens,Hsubgr);
						gr_t::span_subgroup(HGens,Hsubgr);
						gr_t::span_subgroup(HGens,Hsubgr);
						gr_t::span_subgroup(HGens,Hsubgr);
						gr_t::span_subgroup(HGens,Hsubgr);
						gr_t::span_subgroup(HGens,Hsubgr);
						gr_t::span_subgroup(HGens,Hsubgr);
						gr_t::span_subgroup(HGens,Hsubgr);
						gr_t::span_subgroup(HGens,Hsubgr);
						gr_t::span_subgroup(HGens,Hsubgr);
						gr_t::span_subgroup(HGens,Hsubgr);
						gr_t::span_subgroup(HGens,Hsubgr);
						gr_t::span_subgroup(HGens,Hsubgr);
						gr_t::span_subgroup(HGens,Hsubgr);
						gr_t::span_subgroup(HGens,Hsubgr);

						gr_t BaseGen{};
						BaseGen.insert(g);
						BaseGen.insert(k);
						if (HGens == Hsubgr) {
							N_L.emplace(BaseGen,Hsubgr);
							break;
						}
					}
				}
			}
		}
	}
	for(auto Hsubgr : L) {
		bool ya_generado{false};
		for(auto N_H : N_L) {
			if (N_H.second==Hsubgr) {
				ya_generado = true;
				break;
			}
		}
		if (!(ya_generado)) {
			for(auto g : Hsubgr) {
				for(auto k : Hsubgr) {
					for(auto h : Hsubgr) {
						elem_gr_t dp_unit{};
						gr_t HGens{};
						HGens.do_empty();
						if( (g != dp_unit )	and
							(k != dp_unit )	and
							(h != dp_unit) 	and
							(g != h)		and
							(g != k)		and
							(h != k)		and
							(	(k != op_t::gr_bop(g,g)) and
								(k != op_t::gr_bop(h,h)) and
								(g != op_t::gr_bop(k,k)) and
								(g != op_t::gr_bop(h,h)) and
								(h != op_t::gr_bop(k,k)) and
								(h != op_t::gr_bop(g,g)) and
								(k != op_t::gr_bop(k,g)) and
								(k != op_t::gr_bop(g,k)) and
								(k != op_t::gr_bop(k,h)) and
								(k != op_t::gr_bop(h,k)) and
								(k != op_t::gr_bop(g,h)) and
								(k != op_t::gr_bop(h,g)) and
								(g != op_t::gr_bop(k,g)) and
								(g != op_t::gr_bop(g,k)) and
								(g != op_t::gr_bop(k,h)) and
								(g != op_t::gr_bop(h,k)) and
								(g != op_t::gr_bop(g,h)) and
								(g != op_t::gr_bop(h,g)) and
								(h != op_t::gr_bop(k,g)) and
								(h != op_t::gr_bop(g,k)) and
								(h != op_t::gr_bop(k,h)) and
								(h != op_t::gr_bop(h,k)) and
								(h != op_t::gr_bop(g,h)) and
								(h != op_t::gr_bop(h,g))
							)
						)
						{
							HGens.insert(g);
							HGens.insert(k);
							HGens.insert(h);
							gr_t::span_subgroup(HGens,Hsubgr);
							gr_t::span_subgroup(HGens,Hsubgr);
							gr_t::span_subgroup(HGens,Hsubgr);
							gr_t::span_subgroup(HGens,Hsubgr);
							gr_t::span_subgroup(HGens,Hsubgr);
							gr_t::span_subgroup(HGens,Hsubgr);
							gr_t::span_subgroup(HGens,Hsubgr);
							gr_t::span_subgroup(HGens,Hsubgr);
							gr_t::span_subgroup(HGens,Hsubgr);
							gr_t::span_subgroup(HGens,Hsubgr);
							gr_t::span_subgroup(HGens,Hsubgr);
							gr_t::span_subgroup(HGens,Hsubgr);
							gr_t::span_subgroup(HGens,Hsubgr);
							gr_t::span_subgroup(HGens,Hsubgr);
							gr_t::span_subgroup(HGens,Hsubgr);
							gr_t::span_subgroup(HGens,Hsubgr);

							gr_t BaseGen{};
							BaseGen.insert(g);
							BaseGen.insert(k);
							BaseGen.insert(h);
							if (HGens == Hsubgr) {
								N_L.emplace(BaseGen,Hsubgr);
								break;
							}
						}
					}
				}
			}
		}
	}
	tCayley 	<< "\n\n GENERADORES Y GENERADOS \n";
	for(auto pair_set_group : N_L) {
		gr_t keys{pair_set_group.first};
		gr_t values{pair_set_group.second};
		tCayley 	<< "{\\left\\langle{"
							<< keys.to_string(letras)
							<< "}\\right\\rangle} = "
							<< values.to_string(letras)
							<< "\n";
	}
	tCayley.close();
	return;
}

};



}

#endif // GIVE_ME_THE_GROUP_INFORMATION_HPP_INCLUDED
