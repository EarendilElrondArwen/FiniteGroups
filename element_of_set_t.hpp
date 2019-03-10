/*
 * element_of_set_t.hpp
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

#ifndef element_of_set_t_HPP_INCLUDED
#define element_of_set_t_HPP_INCLUDED

//#include <initializer_list>
#include "int_mod_N_t.hpp"

namespace tfg {
// DEFINICION GENERAL
template <uint N_n,uint ... N_nm1>
struct element_of_set_t {
public:
	static_assert(N_n*((N_nm1)*...)<256,
					"El orden no debe ha "
					" de ser inferior a 256");
	static_assert(N_n>1, "No trabajamos con palotes o "
				         "sobre la nada"				);
	static_assert((sizeof...(N_nm1))+1<256,
					"La dimensión del "
					"espacio modular ha "
					"de ser inferior a 256");

	using	elem_n_t	=	element_of_set_t;
	using	im_N		=	int_mod_N<uint, N_n>;
	using	elem_nm1_t	=   typename
				element_of_set_t::element_of_set_t<
					N_nm1...
				>;

	static constexpr uint max_N 	=
		std::max(N_n,elem_nm1_t::max_N);
	static constexpr ullint max_dim	=
		(sizeof...(N_nm1))+1;
	static constexpr ullint gr_order=
		N_n*((N_nm1)*...);

	im_N			dm{};
	elem_nm1_t		edm{};
	//base_t 					elem;
    constexpr
	element_of_set_t(
		const im_N & in,
		const elem_nm1_t & rnm1
	) :	dm{in},
		edm{rnm1} {}

    constexpr
	element_of_set_t(
		im_N && in,
		elem_nm1_t && rnm1
	) :	dm{std::move(in)},
		edm{std::move(rnm1)} {}

	//static const im_N& get<>

	template<typename T,typename ... Ts>
	constexpr
	element_of_set_t(
		const std::integer_sequence<uint,N_n,N_nm1...> & arg
	)	:	dm{im_N(arg.dm)},
			edm{arg.edm}	{
		static_assert((sizeof...(Ts))==(sizeof...(N_nm1)),
			"la longitud de la lista de uints como argumentos "
			"de entrada no coindice con la longitud descrita "
			"por el tipo element_of_set_t<unsigned Nn,unsigned"
			" ... Nnm1>"
		);
	}

	constexpr
	element_of_set_t(
		uint i_n,
		const elem_nm1_t & rnm1
	) :	dm{im_N(i_n)},
		edm{rnm1}		{}

	constexpr
	element_of_set_t() :
		dm{im_N(0)},
		edm{elem_nm1_t()} {}

	constexpr
	element_of_set_t(
		const element_of_set_t & arg
	) :	dm{arg.dm},
		edm{arg.edm}{}

	constexpr
	element_of_set_t(
		element_of_set_t &&
	)=default;

	constexpr
	const element_of_set_t & operator=(
		const element_of_set_t & arg
	) {
		dm = arg.dm;
		edm = arg.edm;
		return (*this);
	}

	constexpr
	const element_of_set_t & operator= (
		const std::pair<
			const im_N &,
			const element_of_set_t &
		>& arg
	){
		dm = arg.first;
		edm = arg.second;
		return (*this);
	}

	constexpr
	const element_of_set_t & operator= (
		const std::pair<
			uint,
			element_of_set_t<N_nm1...>
		>& arg
	) {
		dm = arg.first;
		edm = arg.second;
		return (*this);
	}

	constexpr
	element_of_set_t & operator=(
		element_of_set_t &
	)=default;
    constexpr
	element_of_set_t & operator=(
		element_of_set_t &&
	)=default;

	constexpr
	bool operator<(
		const element_of_set_t & B
	) const	{
		if		(dm < B.dm) return true;
		else if	(dm > B.dm) return false;
		else {
			if (edm < B.edm) return true;
			else return false;
		}
	}

	constexpr
	bool operator>(
		const element_of_set_t & B
	) const {
		if		(dm > B.dm) return true;
		else if	(dm < B.dm) return false;
		else {
			if (edm > B.edm) return true;
			else  return false;
		}
	}

	constexpr
	bool operator<=(
		const element_of_set_t & B
	) const {
		if		(dm < B.dm) return true;
		else if	(dm > B.dm) return false;
		else {
			if (edm <= B.edm) return true;
			else return false;
		}
	}

	constexpr
	bool operator>=(
		const element_of_set_t & B
	) const {
		if		(dm > B.dm) return true;
		else if	(dm < B.dm) return false;
		else {
			if (edm >= B.edm) return true;
			else  return false;
		}
	}

	constexpr
	bool operator==(
		const element_of_set_t & B
	) const {
		const bool bh{dm==B.dm};
		const bool bt{edm==B.edm};

		const bool result{bh&&bt};
		return result;
	}

	constexpr
	bool operator!= (
		const element_of_set_t & B
	) const {
		const bool bh{dm!=B.dm};
		const bool bt{edm!=B.edm};

		const bool result{bh||bt};
		return result;
	}

	static constexpr
	element_of_set_t elem_max() {
		constexpr
		int_mod_N<uint,N_n> im_N_max =
			int_mod_N<uint,N_n>(N_n-1);
		constexpr
		element_of_set_t<N_nm1...> elem_nm1_max =
			element_of_set_t<N_nm1...>::elem_max();
		constexpr
		element_of_set_t result =
			element_of_set_t(im_N_max,elem_nm1_max);
		return result;
	}

	constexpr
	element_of_set_t  next() const {
		im_N c_dm(dm);
		elem_nm1_t c_edm(edm);
		if (dm < im_N(N_n-1)){
			c_dm.m_next();
		}
		else{
			c_dm = im_N(0);
			if(edm < elem_nm1_t::elem_max()) {
				c_edm.m_next();
			}
			else {
				c_edm = elem_nm1_t();
			}
		}
		return element_of_set_t(c_dm,c_edm);
	}

	constexpr
	element_of_set_t prev() const {
		im_N c_dm(dm);
		elem_nm1_t c_edm(edm);
		if (dm > im_N(0)){
			c_dm.m_prev();
		}
		else{
			c_dm = im_N(N_n-1);
			if(edm > elem_nm1_t()) {
				c_edm.m_next();
			}
			else {
				c_edm = elem_nm1_t::elem_max();
			}
		}
		return element_of_set_t(c_dm,c_edm);
	}

	constexpr
	const element_of_set_t & m_next()  {
		if (dm < im_N(N_n-1)) {
			++dm;
		}
		else {
			dm = im_N(0);
			if (edm < elem_nm1_t::elem_max()){
				edm.m_next();
			}
			else {
				edm = elem_nm1_t();
			}
		}
		return (*this);
	}

	constexpr
	const element_of_set_t & m_prev() {
		if (dm > im_N(0))
			--dm;
		else {
			dm = im_N(N_n-1);
			if (edm > elem_nm1_t())
				edm.m_prev();
			else
				edm = elem_nm1_t::elem_max();
		}
		return (*this);
	}


	std::string to_string(const std::string & X) const {
		std::string Y = X;
		const std::string si_n = std::to_string(dm.m_i);
		std::string letra(1,Y.front());
		Y = Y.substr(1,std::string::npos);
		const std::string sr_nm1 = edm.to_string(Y);


		if((dm==im_N(0))and(edm==elem_nm1_t())) {
			return "1";
		}
		else {
			if (edm == elem_nm1_t()) {
				if(dm == im_N(1))
					return letra;
				else if(dm > im_N(1))
					return letra + "^" + si_n;
				else
					return "";
			}
			else {
				if(dm == im_N(1))
					return letra + sr_nm1;
				else if(dm > im_N(1))
					return letra + "^" + si_n + sr_nm1;
				else
					return sr_nm1;
			}
		}
	}

	constexpr
	elem_n_t operator + (const elem_n_t & b) const {
		im_N n_dm{(dm + b.dm)};
		elem_nm1_t    n_edm{edm+b.edm};
		return elem_n_t(n_dm,n_edm);
	}

	constexpr
	elem_n_t operator - (const elem_n_t & b) const {
		im_N n_dm{(dm - b.dm)};
		elem_nm1_t    n_edm{edm-b.edm};
		return elem_n_t(n_dm,n_edm);
	}

	constexpr
	elem_n_t operator - () const {
		im_N n_dm{-dm};
		elem_nm1_t    n_edm{-edm};
		return elem_n_t(n_dm,n_edm);
	}

	constexpr
	const elem_n_t & operator += (const elem_n_t & b) {
		dm  += b.dm;
		edm += b.edm;
		return (*this);
	}

	constexpr
	const elem_n_t & operator -= (const elem_n_t & b) {
		dm  -=  b.dm;
		edm -=  b.edm;
		return (*this);
	}

	constexpr
	elem_n_t operator ~()  const {
		int_mod_N a{~dm};
		elem_nm1_t b{~edm};
		return element_of_set_t(a,b);
	}

	constexpr
	const elem_n_t & operator !(){
		!dm;
		!edm;
		return (*this);
	}
};

template <uint N_1_n>
constexpr
struct element_of_set_t<N_1_n> {
public:
	static_assert(N_1_n > 1);
	using	elem_n_t		=	element_of_set_t;
	using	im_N			=	int_mod_N<uint,N_1_n>;
	static constexpr uint max_N 	= N_1_n;
	static constexpr uint max_dim 	= 1;
	static constexpr uint gr_order 	= N_1_n;

	im_N					dm{0};

	constexpr
	element_of_set_t( uint i1) : dm{im_N(i1)} {}
    constexpr
	element_of_set_t(const im_N & i1) : dm{im_N(i1)} {}

	constexpr element_of_set_t() : dm{im_N(0)} {}

	constexpr
	element_of_set_t(const element_of_set_t &)=default;

	constexpr
	element_of_set_t(element_of_set_t &&)=default;

	constexpr
	const element_of_set_t & operator= (uint arg){
		dm = arg;
		return (*this);
	}

	constexpr
	const element_of_set_t & operator= (const im_N & arg){
		dm = arg;
		return (*this);
	}

	constexpr
	const element_of_set_t & operator=(
		const element_of_set_t & arg
	){
		dm = arg.dm;
		return (*this);
	}

	constexpr
	element_of_set_t & operator= (
		element_of_set_t &
	)=default;

	constexpr
	element_of_set_t & operator= (
		element_of_set_t &&
	)=default;

	constexpr
	bool operator<(
		const element_of_set_t & B
	) const {
		return(dm < B.dm);
	}

	constexpr
	bool operator>(
		const element_of_set_t & B
	) const {
		return(dm > B.dm);
	}

    constexpr
	bool operator<=(
		const element_of_set_t & B
	) const {
		return(dm <= B.dm);
	}

	constexpr
	bool operator>= (
		const element_of_set_t & B
	) const {
		return (dm >= B.dm);
	}

	constexpr
	bool operator== (
		const element_of_set_t & B
	) const {
		return (dm==B.dm);
	}

	constexpr
	bool operator!= (
		const element_of_set_t & B
	) const {
		return (dm!=B.dm);
	}

	static constexpr
	element_of_set_t elem_max() {
		element_of_set_t result(N_1_n-1);
		return result;
	}

	constexpr
	element_of_set_t  next() const {
		im_N next_1(dm);
		if (dm < im_N(N_1_n-1))
			++next_1;
		else
			next_1 = 0;
		return element_of_set_t(next_1);
	}

	constexpr
	element_of_set_t prev() const {
		im_N prev_1(dm);
		if (dm > im_N(0))
			--prev_1;
		else
			prev_1 = im_N(N_1_n-1);
		return element_of_set_t(prev_1);
	}

    constexpr
	const element_of_set_t & m_next()  {
		if (dm < im_N(N_1_n-1))
			++dm;
		else
			dm = 0;
		return (*this);
	}

	constexpr
	const element_of_set_t & m_prev()  {
		if (dm > im_N(0))
			--dm;
		else
			dm = im_N(N_1_n-1);
		return (*this);
	}

	std::string to_string(const std::string & X) const {
		const std::string si_n{std::to_string(dm.m_i)};
		const std::string letra(1,X.front());

		if(dm==im_N(0))
			return "1";
		else if(dm == im_N(1))
			return letra;
		else
			return letra + "^" + si_n;
	}

	constexpr
	element_of_set_t operator + (
		const element_of_set_t & b
	) const {
		return element_of_set_t((dm+b.dm).m_i);
	}

	constexpr
	element_of_set_t operator - (
		const element_of_set_t & b
	) const {
		return element_of_set_t((dm-b.dm).m_i);
	}

	constexpr
	element_of_set_t operator - () const {
		return element_of_set_t((-dm).m_i);
	}

	constexpr
	const element_of_set_t & operator += (
		const element_of_set_t & b
	) {
		dm += b.dm;
		return (*this);
	}

	constexpr
	element_of_set_t operator -= (
		const element_of_set_t & b
	) {
		dm -= b.dm;
		return (*this);
	}

	constexpr
	element_of_set_t operator ~ () {
		~dm;
		return (*this);
	}

};
}
#endif
