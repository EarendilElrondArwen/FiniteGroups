/*
 * modint_cartprod_t.hpp
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

#include "modint_t.hpp"

namespace tfg {

/// ANILLO DADO POR EL PRODUCTO CARTESIANO DE VARIOS ANILLOS DE ENTEROS MODULARES
<UIntType,N_n,... N_nm1>
struct modint_cartprod_t {
	/// TUPLA DE LOS MODULOS (ENTEROS) ES CONSTEXPR
	static constexpr auto mod_tup {make_tuple(N_n,N_nm1...)};
	/// DEVUELVE EL MAXIMO DE LOS MODULOS
	static constexpr UIntType max_mod();
	/// DEVUELVE EL MINIMO DE LOS MODULOS
	static constexpr UIntType min_mod();
	/// DEVUELVE LA "DIMENSION" DEL ANILLO
	static constexpr UIntType dim();
	/// DEVUELVE EL NUMERO DE ELEMENTOS DEL ANILLO
	static constexpr ullint card();
	
	/// PRECONDICIONES PARA QUE SEA VALIDO EL ANILLO
	/// EL ANILLO UNIDAD NO ENTRA
	static_assert(card()<127);
	static_assert(min_mod()>1);
	static_assert(max_mod()<64);
	static_assert(dim()<6);
	
	/// BUCLE FOR EN TIEMPO DE COMPILACION PARA ITERAR 
	/// SOBRE UNA TUPLA CON UN ORDEN
	<First,Actual,OnePastLast>
	using 
	static_for  =	impl::simple_static_for<UIntType,First,Actual,OnePastLast>;
	
	/// TYPEDEFS PARA HACER MAS COMODA LA CODIFICACION
	<K>
	using	imod			=	modint_t<UIntType,K>;
	using	im_N			=	imod<N_n>;
	
	using	base_t 			= tuple<imod<N_n>,imod<N_nm1>...>;
	using	base_head_t 	= tuple<imod<N_n>>;
	using	base_tail_t 	= tuple<imod<N_nm1>...>;
	using	base_root_t 	= decltype(root<imod<N_n>,imod<N_nm1>...>(base_t{}));
	using	base_btail_t 	= decltype(btail<imod<N_n>,imod<N_nm1>...>(base_t{}));
	using	base_reverse_t 	= decltype(reverse<imod<N_n>,imod<N_nm1>...>(base_t{}));
	
	using	elem_t		=	modint_cartprod_t;
	using	elem_head_t	=	modint_cartprod_t<UIntType,N_n>;
	using	elem_tail_t	=   modint_cartprod_t<UIntType,N_nm1...>;
	
	/// BEGIN : UNICO DATO MIEMBRO
		base_t		elem{};
	/// END   : UNICO DATO MIEMBRO
	
	/// FUNCIONES DE AYUDA PARA NEXT Y PREV
	/// I debe ser constexpr
	static constexpr void 
	DigitIncr(base_t& A,array<bool,dim()> & temp,UIntType I);
	/// I debe ser constexpr	
	static constexpr void 
	DigitDecr(base_t& A,array<bool,dim()> & B,UIntType I);
	
	/////////////////////////////////////////////////////
	/// FUNCTIONS FROM MEMBER BASE_T AND ITS SUBTYPES ///
	/////////////////////////////////////////////////////
	
	im_N dm() const;
	UIntType mi() const;
	im_N & gdm();
	im_N head_val() const;
	base_head_t head() const;
	base_tail_t tail() const;
	base_tail_t edm() const;
	base_root_t root() const;
	auto root_val() const;
	base_btail_t btail() const;
	auto reverse() const;
	/// OBTIENE UN ENTERO MODULO N_n DE INICIALIZADO CON EL VALOR ENTERO k
	static im_N g_imN(UIntType k);
	/// OBTIENE UN ENTERO MODULO MOD<I> INICIALIZADO CON EL VALOR ENTERO k
	<I>	static imod<I>	g_im(UIntType k);
		
	///////////////////////////
	/// BASIC CONSTRUCTORS ////
	///////////////////////////
	
	modint_cartprod_t()=default;
	modint_cartprod_t(const modint_cartprod_t &)=default;
	modint_cartprod_t(modint_cartprod_t &&)=default;
	
	/////////////////////////////////
	/// QUASI BASIC CONSTRUCTORS ////
	/////////////////////////////////
	
	modint_cartprod_t(const base_t & otherbelem) 
		: elem{otherbelem} {}
	
	modint_cartprod_t(base_t && otherelem) 
		: elem{move(otherelem)} {}
	
	/////////////////////////////////////////////////////////
	/// modint_cartprod_t FROM THEIR PARTS CONSTRUCTORS ////
	/////////////////////////////////////////////////////////
	
	< ... Ps, ... Qs>
	modint_cartprod_t(
		const modint_cartprod_t<UIntType,Ps...> & arg_P,
		const modint_cartprod_t<UIntType,Qs...> & arg_Q
	) : elem{tuple_cat(arg_P.elem,arg_Q.elem)} {}
	
	//////////////////////////////////////////////////////////////////
	/// modint_cartprod_t FROM THEIR MEMBER TUPLES  CONSTRUCTORS /////
	//////////////////////////////////////////////////////////////////
	
	< ... Ps, ... Qs>
	modint_cartprod_t(
		const tuple<modint_t<UIntType,Ps>...> & arg_P,
		const tuple<modint_t<UIntType,Qs>...> & arg_Q
	) : elem{tuple_cat(arg_P,arg_Q)} {}
	
	////////////////////////////////////////////////////////////////////////
	/// modint_cartprod_t FROM THEIR SUB-MEMBER modint_t CONSTRUCTORS   ////
	////////////////////////////////////////////////////////////////////////
	
	modint_cartprod_t(im_N im_n,imod<N_nm1> ... im_nm1)
	: elem{make_tuple(im_n,im_nm1 ...)} {}
	
	/////////////////////////////////////////////////////////////////
	/// modint_cartprod_t FROM A TUPLE OF INTEGERS CONSTRUCTORS ////
	/////////////////////////////////////////////////////////////////
	
	<IntType_n, ... IntType_nm1>
	modint_cartprod_t(IntType_n	i_n,IntType_nm1	... i_nm1) 
	: elem{
	  make_tuple(im_N{IntType_n(i_n)},imod<N_nm1>{IntType_n(i_nm1)}...)
	} {}
    modint_cartprod_t(const im_N & in,const elem_tail_t & rnm1) 
	: elem{tuple_cat(make_tuple(in),rnm1.elem)} {}
	modint_cartprod_t(const im_N & in,const base_tail_t	& rnm1) 
	: elem{tuple_cat(make_tuple(in),rnm1)} {}
    modint_cartprod_t(im_N	&& in,elem_tail_t && rnm1) 
	: elem{tuple_cat(make_tuple(move(in)),move(rnm1.elem))} {}
	modint_cartprod_t(im_N & in,base_tail_t	&& rnm1) 
	: elem{tuple_cat(make_tuple(move(in)),move(rnm1))} {}
	
	//////////////////////////////////////
	/// ASIGNACIONES VARIAS			//////
	//////////////////////////////////////
	
	const modint_cartprod_t & operator=(const modint_cartprod_t &) = default;
	modint_cartprod_t & operator=(modint_cartprod_t &&) = default;
	const modint_cartprod_t & operator= (const base_t & arg);
	const modint_cartprod_t & operator= (base_t && arg) ;
	<UInt_n, ... UInt_nm1>
	const modint_cartprod_t & operator= ( tuple<UInt_n,UInt_nm1...> arg );
		/// usa build_from_tuple_of_ints
	const modint_cartprod_t & operator= (const tuple<const im_N,const base_tail_t>& arg);
	
	//////////////////////////////////////////////////////////
	///   OPERADORES DE COMPARACION, USAN EL ORDEN         ///
	///   LEXICOGRAFICO DE LAS TUPLAS INTERNAS PERO        ///
	///   DESPUES DE HACER REVERSE EN LAS TUPLAS INTERNAS  ///
	//////////////////////////////////////////////////////////
	
	bool operator <  (const modint_cartprod_t & rhs) const;
	bool operator >  (const modint_cartprod_t & rhs) const;
	bool operator <= (const modint_cartprod_t & rhs) const;
	bool operator >= (const modint_cartprod_t & rhs) const;
	bool operator==(const modint_cartprod_t & rhs) const;
	bool operator!=(const modint_cartprod_t & rhs) const;
	
	//////////////////////////////////////////////////////////////////
	///    OBTENER EL ELEMENTO CON LOS DIGITOS MAXIMOS EN CADA     ///
	///    MODULO, CON TODOS LOS DIGITOS A 0 (NEUTRO DE LA SUMA)   ///
	///    Y CON TODOS LOS DIGITOS A 1 (NEUTRO DE LA               ///
	///    MULTIPLICACION)                                         ///
	//////////////////////////////////////////////////////////////////
	
	static	modint_cartprod_t max_elem();
	static	modint_cartprod_t zero_elem();
	static	modint_cartprod_t unit_elem();
	
	////////////////////////////////////////////////////////////
	///    OBTENER EL ELEMENTO SIGUIENTE SEGUN EL ORDEN      ///
	///    ESTABLECIDO EN LOS OPERADORES DE COMPARACION      ///
	////////////////////////////////////////////////////////////
	
	modint_cartprod_t next() const;
	modint_cartprod_t prev() const ;
	/// ELEMENTOS SIGUIENTE Y PREVIO CON ASIGNACION
	const modint_cartprod_t & m_next();
	const modint_cartprod_t & m_prev();

	////////////////////////////////////////////////////////////
	///    OBTIENE UNA CADENA QUE EXPRESA EL ELEMENTO EN     ///
	///    NOTACION MULTIPLICATIVA                           ///
	////////////////////////////////////////////////////////////

	std::string to_string(const std::string & X) const;
	
	////////////////////////////////////////////////////////////
	///    OPERADORES DE SUMA                                ///
	////////////////////////////////////////////////////////////
	
	<I> static void
	add_assign_impl_impl(base_t & A,const base_t & B);
	<... I> static void
	add_assign_impl(base_t & A,const base_t & B,integer_sequence<UIntType,I...>);
	elem_t operator + (const elem_t & rhs) const;
	const elem_t & operator += (const elem_t & rhs);
	
	////////////////////////////////////////////////////////////
	///    OPERADORES DE SUBSTRACCION                        ///
	////////////////////////////////////////////////////////////
	
	<I> static void
	substract_assign_impl_impl(base_t & A,const base_t & B);
	<... I> static void
	substract_assign_impl(base_t & A,const base_t & B,integer_sequence<UIntType,I...>);
	elem_t operator - (const elem_t & rhs) const;
	const elem_t & operator -= (const elem_t & rhs);
	
	////////////////////////////////////////////////////////////
	///    OPERADORES DE MENOS UNARIO                        ///
	////////////////////////////////////////////////////////////
	
	<... I>
	static void
	minus_assign_impl(base_t & A,integer_sequence<UIntType,I...>);
	elem_t operator - () const;
	
	////////////////////////////////////////////////////////////
	///    OPERADORES DE COMPLEMENTO A LA BASE MENOS 1       ///
	////////////////////////////////////////////////////////////
	
	<I>
	static void
	tilde_assign_impl_impl(base_t & A,const base_t & B);
	< ... I>
	static void
	tilde_assign_impl(base_t & A,const base_t & B,integer_sequence<UIntType,I...>);
	elem_t operator ~()  const;
	
	////////////////////////////////////////////////////////////
	///    OPERADORES DE COMPLEMENTO A LA BASE               ///
	///    (O CAMBIO DE SIGNO) CON ASIGNACION                ///
	////////////////////////////////////////////////////////////
	
	< ... I>
	static void
	exclam_assign_impl(base_t & A,integer_sequence<UIntType,I...>);
	const elem_t & operator !();
	
	////////////////////////////////////////////////////////////
	///    OPERADORES DE MULTIPLICACION                      ///
	////////////////////////////////////////////////////////////
	
	<I>
	static void
	mult_assign_impl_impl(base_t & A,const base_t & B);
	< ... I>
	static void
	mult_assign_impl(base_t & A,const base_t & B,integer_sequence<UIntType,I...>);
	elem_t operator * (const elem_t & rhs) const;
	const elem_t & operator *= (const elem_t & rhs);
	
	////////////////////////////////////////////////////////////
	///    INVERSO MULTIPLICATIVO SI LO HAY, SINO 0s         ///
	////////////////////////////////////////////////////////////
	
	<I>
	static void
	mult_assign_impl_impl(base_t & A,const base_t & B);
	< ... I>
	static void
	mult_assign_impl(base_t & A,const base_t & B,integer_sequence<UIntType,I...>);
	elem_t operator * (const elem_t & rhs) const;
	const elem_t & operator *= (const elem_t & rhs);
	
};
}
#endif // modint_cartprod_t_HPP_INCLUDED
