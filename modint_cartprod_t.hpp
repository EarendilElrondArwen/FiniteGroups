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

#ifndef modint_cartprod_t_HPP_INCLUDED
#define modint_cartprod_t_HPP_INCLUDED

#include <algorithm>
#include <initializer_list>
#include <array>
#include "modint_t.hpp"

namespace tfg {
  using std::enable_if;
  using std::enable_if_t;
  using std::conditional;
  using std::conditional_t;
  using std::move;
  using std::max;
  using std::min;
  using std::tuple;
  using std::get;
  using std::tie;
  using std::make_tuple;
  using std::size_t;
  using std::integer_sequence;
  using std::make_integer_sequence;
  using std::tuple_cat;
  using std::initializer_list;
  using std::ostream;
  using std::istream;
  using std::endl;
  using std::cout;
  using std::cin;
  using std::array;

template <typename UIntType,UIntType N_n,UIntType ... N_nm1>
struct modint_cartprod_t {
public:
	static constexpr auto mod_tup() {return make_tuple(N_n,N_nm1...);}; 
private:
	
	template<UIntType Mod_n,UIntType ... Mod_nm1>
	inline static constexpr
	UIntType
	min_of_int_pack() {
		if constexpr ((sizeof...(Mod_nm1))==0)
			return Mod_n;
		else
			return min(Mod_n,min_of_int_pack<Mod_nm1...>());
	}
	template<UIntType Mod_n,UIntType ... Mod_nm1>
	inline static constexpr
	UIntType
	max_of_int_pack() {
		if constexpr ((sizeof...(Mod_nm1))==0)
			return Mod_n;
		else
			return max(Mod_n,max_of_int_pack<Mod_nm1...>());
	}
public:
	
	inline static constexpr 
	UIntType max_mod() {
		if constexpr (dim()==0)
			return N_n;
		else
			return max_of_int_pack<N_n,N_nm1...>();
	}
	
	inline static constexpr 
	UIntType min_mod() {
		if constexpr (dim()==0)
			return N_n;
		else
			return min_of_int_pack<N_n,N_nm1...>();
	}
	
	inline static constexpr 
	UIntType dim() {
		if constexpr ((sizeof...(N_nm1))==0)
			return 1;
		else if constexpr ((sizeof...(N_nm1))==1)
			return 2;
		else 
			return ((sizeof...(N_nm1))+1);
	}
	
	inline static constexpr 
	ullint card() {
		if constexpr (dim()==1)
			return N_n;
		else
			return (N_n*((N_nm1)*...));
			
	}
	
	static_assert(
		card()<127,
		"El orden no debe ha "
		" de ser inferior a 256"
	);
	static_assert(
		min_mod()>1, 
		"No trabajamos con palotes o "
	    "sobre la nada"				
	);
	static_assert(max_mod()<64, 
		"No trabajamos con palotes o "
	    "sobre la nada"				
	);
	static_assert(
		dim()<6,
		"La dimensión del "
		"espacio modular ha "
		"de ser inferior a 256"
	);
	
	template <
		UIntType First,
		UIntType Actual,
		UIntType OnePastLast	
	>
	using static_for = impl::simple_static_for<UIntType,First,Actual,OnePastLast>;
	
	template<UIntType K>
	using	imod			=	modint_t<UIntType,K>;
	using	im_N			=	imod<N_n>;
	
	using	base_t 			= tuple<imod<N_n>,imod<N_nm1>...>;
	using	base_head_t 	= tuple<imod<N_n>>;
	using	base_tail_t 	= tuple<imod<N_nm1>...>;
	using	base_root_t 	= decltype(root<imod<N_n>,imod<N_nm1>...>(base_t{}));
	using	base_btail_t 	= decltype(btail<imod<N_n>,imod<N_nm1>...>(base_t{}));
	using	base_reverse_t 	= decltype(reverse<imod<N_n>,imod<N_nm1>...>(base_t{}));
	
	using	elem_t			=	modint_cartprod_t<UIntType,N_n,N_nm1...>;
	using	elem_head_t		=	modint_cartprod_t<UIntType,N_n>;
	
	using	elem_tail_t		=   modint_cartprod_t<UIntType,N_nm1...>;
	
	template<UIntType ... I>
	using	arg_index_sq_t 	=   integer_sequence<UIntType,I...>;
	using	ret_index_sq_t  =	make_integer_sequence<UIntType,dim()>;
	
	/////////////////////////////////////////////////////
	/// FUNCTIONS FROM MEMBER BASE_T AND ITS SUBTYPES ///
	/////////////////////////////////////////////////////
public :
	template<size_t idx>
	using
	modint_idx = modint_t<UIntType,get<idx>(mod_tup())>;
	
	template<UIntType Mod>
	using
	modint_mod = modint_t<UIntType,Mod>;
	
	template<size_t k>
	inline constexpr
	UIntType
	get_int() const {
		return UIntType(get<k>(elem));
	}
	
	template<size_t k>
	inline constexpr
	modint_idx<k>&
	get_modint() {
		return (get<k>(elem));
	}
		
	inline constexpr 
	im_N get_head_val() const {
		return head_value<imod<N_n>,imod<N_nm1>...>(elem);
	}
	
	inline constexpr 
	base_head_t get_head() const {
		return make_tuple(head_value<imod<N_n>,imod<N_nm1>...>(elem));
	}
	
	inline constexpr 
	base_tail_t get_tail() const {
		const base_tail_t result{
			tail(elem)
		};
		return result;
	}
public :
	inline constexpr
	base_root_t get_root() const {
		const base_root_t result{root(elem)};
		return result;
	}
	
	inline constexpr
	decltype(auto) get_root_val() const {
		return root_value<imod<N_n>,imod<N_nm1>...>(elem);
	}
	
	inline constexpr 
	base_btail_t get_btail() const {
		const base_btail_t result{btail(elem)};
		return result;
	}
	
	inline constexpr 
	auto get_reverse() const {
		const base_reverse_t result{reverse(elem)};
		return result;
	}
private :
	inline static constexpr
	im_N
	g_imN(UIntType k) {
		return im_N{UIntType(k)}; 
	}
	
	template<UIntType I>
	inline static constexpr
	imod<I>
	g_im(UIntType k) {
		return imod<I>{UIntType(k)};
	}
	
	template<
		UIntType I,
		template<typename,UIntType> class Funct_t
	>
	inline static constexpr void
	genimpl_of_impl_impl(
		Funct_t<base_t,I> funct,
		base_t & A,
		const base_t & B)  			{
			return funct(A,B,I);	}
	
	template<
		UIntType...I,
		template<typename> typename Funct_t
	>
	inline static constexpr void
	genimpl_of_impl(
		Funct_t<base_t> funct,
		base_t & A,
		const base_t & B,
		arg_index_sq_t<I...>)									{
			return (genimpl_of_impl_impl(funct,A,B,I),...) ;	}
	
	template<
		UIntType...I,
		template<typename> typename Funct_t
	>
	inline static constexpr void
	genimpl_of_impl(
		Funct_t<base_t> funct,
		base_t & A,
		arg_index_sq_t<I...>)								{
			return (genimpl_of_impl_impl(funct,A,I),...) ;	}
	
	inline static constexpr
	void 
	DigitIncr(base_t& A,array<bool,dim()> && temp,UIntType I) {
		if constexpr (I==0) {
			if (get<0>(A.elem) < g_imN(N_n-1)) {
				get<0>(A.elem) += g_imN(1);
				get<1>(temp)	= false;
			}
			else {
				get<0>(A.elem)	+= g_imN(0);
				get<1>(temp) 	 = true;
			}
		}
		else {
			if (
				(get<I>(A) < g_im<I>(get<I>(mod_tup())-1))
					&&
				(get<I>(temp))
			) {
				get<I>(A) 			+=	g_im<I>(1);
				get<I+1>(temp)		 =	false;
			}
			else if  (
				(get<I>(A) == g_im<I>(get<I>(mod_tup())-1))
					&&
				(get<I>(temp))
			) {
				get<I>(A)			=	g_im<I>(0);
				get<I+1>(temp) 		=	true;
			}
			else {
				get<I+1>(temp)		=	false;
			}
		}
	}
		
	inline static constexpr
	void 
	DigitDecr(base_t& A,array<bool,dim()> && B,UIntType I) {
		if constexpr (I==0) {
			if (get<0>(A) > g_imN(0)) {
				get<0>(A) -= g_imN(1);
				get<1>(B) = false;
			}
			else {
				get<0>(A)		+=g_imN(N_n-1);
				get<1>(B) 	 	 = true;
			}
		} else {
			if (
				(get<I>(A) > g_im<I>(0))
					&&
				(get<I>(B))
			) {
				get<I>(A) 		-=	g_im<I>(1);
				get<I+1>(B)		 =	false;
			}
			else if  (
				(get<I>(A) == g_im<I>(0))
					&&
				(get<I>(B))
			) {
				get<I>(A)		=	g_im<I>(get<I>(mod_tup())-1);
				get<I+1>(B) 	=	true;
			}
			else {
				get<I+1>(B)		=	false;
			}
		}
	}
	
	/// BEGIN : UNICO DATO MIEMBRO
		base_t		elem{};
	/// END   : UNICO DATO MIEMBRO
public :	
	///////////////////////////
	/// BASIC CONSTRUCTORS ////
	///////////////////////////
	
	inline constexpr
	modint_cartprod_t()=default;
	
	inline constexpr
	modint_cartprod_t(
		const modint_cartprod_t &
	)=default;
	
	inline constexpr
	modint_cartprod_t(
		modint_cartprod_t &&
	)=default;
	
	/////////////////////////////////
	/// QUASI BASIC CONSTRUCTORS ////
	/////////////////////////////////
	
	inline constexpr
	modint_cartprod_t(
		const base_t & otherbelem
	) : elem{otherbelem} {}
	
	//inline constexpr
	//modint_cartprod_t(
	//	base_t && otherelem
	//) : elem{otherelem} {}
	
	////////////////////////////////////////////////////////////////////////
	/// modint_cartprod_t FROM THEIR SUB-MEMBER modint_t CONSTRUCTORS ////
	////////////////////////////////////////////////////////////////////////
	
	inline constexpr
	modint_cartprod_t(
		im_N im_n ,
		imod<N_nm1> ... im_nm1
	)
		: elem{make_tuple(im_n,im_nm1 ...)} {
		static_assert(
			sizeof...(N_nm1)==sizeof...(im_nm1),
			"El numero de argumentos modint_t de entrada "
			"no coincide con la longitud de la tupla"
		);
	}
	
	/////////////////////////////////////////////////////////////////
	/// modint_cartprod_t FROM A TUPLE OF INTEGERS CONSTRUCTORS ////
	/////////////////////////////////////////////////////////////////
	
	template<typename IntType_n,typename ... IntType_nm1>
	inline constexpr
	modint_cartprod_t(
		IntType_n 		i_n		,
		IntType_nm1 	... i_nm1
	) : 
		elem{make_tuple(
			im_N{IntType_n(i_n)},
			imod<N_nm1>{IntType_n(i_nm1)}
			...
		)} {
		static_assert(
			sizeof...(IntType_nm1)==sizeof...(N_nm1),
			"El numero de argumentos enteros de entrada "
			"no coincide con la longitud del la tupla"
		);
		static_assert(
			sizeof...(i_nm1)==sizeof...(N_nm1),
			"El numero de argumentos enteros de entrada "
			"no coincide con la longitud del la tupla"
		);
	}
	
	inline constexpr explicit
	modint_cartprod_t(
		const im_N			& in,
		const base_tail_t	& rnm1
	) :	elem{tuple_cat(make_tuple(in),rnm1)} {}
	
	inline constexpr explicit
	modint_cartprod_t(
		im_N	&&	 in,
		base_tail_t	&& rnm1
	) :	elem{
		tuple_cat(
			make_tuple(in),
			rnm1
		)} {}
	
	///////////////////////////////////////
	///		OPERADORES DE ASIGNACION	///
	///////////////////////////////////////
	
	inline constexpr
	modint_cartprod_t & operator=(
		modint_cartprod_t &
	) = default;
	
	inline constexpr
	const modint_cartprod_t & operator=(
		const modint_cartprod_t & arg
	) {
		(*this)=arg;
		return (*this);
	}
	
	inline constexpr
	modint_cartprod_t & operator=(
		modint_cartprod_t &&
	) = default;
	
	template<typename UInt_n, typename ... UInt_nm1>
	inline constexpr const modint_cartprod_t & 
	operator=(const tuple<UInt_n,UInt_nm1...> & arg) {
		const auto result{
			build_from_tuple_of_ints<
				UIntType,
				N_n,N_nm1...,
				modint_t,
				UInt_n,UInt_nm1...
			>(arg)
		};
		this->elem = result;
		return (*this);
	}
	
	inline constexpr bool 
	operator<(const modint_cartprod_t & rhs) const {
		const auto LHS {get_reverse()};
		const auto RHS {rhs.get_reverse()};
		return (LHS<RHS);
	}

	inline constexpr bool 
	operator>(const modint_cartprod_t & rhs) const {
		const auto LHS {get_reverse()};
		const auto RHS {rhs.get_reverse()};
		return (LHS>RHS);
	}
	
	inline constexpr bool 
	operator <= (const modint_cartprod_t & rhs) const {
		const auto LHS {get_reverse()};
		const auto RHS {rhs.get_reverse()};
		return (LHS<=RHS);
	}

	inline constexpr bool
	operator >= (const modint_cartprod_t & rhs) const {
		const auto LHS {get_reverse()};
		const auto RHS {rhs.get_reverse()};
		return (LHS>=RHS);
	}

	inline constexpr bool 
	operator==(const modint_cartprod_t & rhs) const {
		return (elem==rhs);
	}

	inline constexpr bool 
	operator!=(const modint_cartprod_t & rhs) const {
		return (elem!=rhs);
	}
private:	
	template<UIntType I>
	inline static constexpr bool
	is_zero_impl_impl(const & A) {
		return (get<I>(A)==g_im<I>(0));
	}
	
	template<UIntType... I>
	inline static constexpr bool
	is_zero_impl(const & A,arg_index_sq_t<I...>) {
		return (is_zero_impl_impl<I>(A)&&...);
	} 
public:	
	inline constexpr bool
	is_zero_elem() const {
		return is_zero_impl(elem,ret_index_sq_t{});
	}
private:	
	template<UIntType I>
	inline static constexpr bool
	is_unit_impl_impl(const & A) {
		return (get<I>(A)==g_im<I>(1));
	}
	
	template<UIntType ... I>
	inline static constexpr bool
	is_unit_impl(const & A,arg_index_sq_t<I...>) {
		return (is_unit_impl_impl<I>(A)&&...);
	} 
public:	
	inline constexpr bool
	is_unit_elem() const {
		return is_unit_impl(elem,ret_index_sq_t{});
	}
private:	
	template<UIntType I>
	inline static constexpr bool
	is_max_impl_impl(const base_t & A) {
		return (get<I>(A)==g_im<I>(get<I>(mod_tup)-1));
	}
	
	template<UIntType ... I>
	inline static constexpr bool
	is_max_impl(const base_t & A,arg_index_sq_t<I...>) {
		return ((is_max_impl_impl<I>(A))&&...);
	} 
public:	
	inline constexpr bool
	is_max_elem() const {
		return is_max_impl(elem,ret_index_sq_t{});
	}
	
	inline static constexpr
	modint_cartprod_t max_elem() {
		constexpr
		modint_cartprod_t result {
			make_tuple(
				imod<N_n>{UIntType(N_n-1)},
				imod<N_nm1>{UIntType(N_nm1-1)}...
			)
		};
		return result;
	}
	
	inline static constexpr
	modint_cartprod_t zero_elem() {
		constexpr
		modint_cartprod_t result {
			make_tuple(
				imod<N_n>{UIntType(0)},
				imod<N_nm1>{UIntType(0)}...
			)
		};
		return result;
	}
	
	inline static constexpr
	modint_cartprod_t unit_elem() {
		constexpr
		modint_cartprod_t result {
			make_tuple(
				imod<N_n>{UIntType(1)},
				imod<N_nm1>{UIntType(1)}...
			)
		};
		return result;
	}
		
	inline constexpr
	modint_cartprod_t next() const {
		modint_cartprod_t result{*this};
		array<bool,dim()+1> borrow_tup{false};
		static_for<0,0,dim()>(DigitIncr,result.elem,borrow_tup);
		return result;
	}

	inline constexpr
	modint_cartprod_t prev() const {
		modint_cartprod_t result{*this}; 
		array<bool,dim()+1> borrow_tup{false};
		static_for<0,0,dim()>(DigitDecr,result.elem,borrow_tup);
		return result;
	}

	inline constexpr
	const modint_cartprod_t & m_next()  { 
		array<bool,dim()+1> carry_tup{false};
		static_for<0,0,dim()>(DigitIncr,elem,carry_tup);
		return (*this);
	}

	inline constexpr
	const modint_cartprod_t & m_prev() {
		array<bool,dim()+1> carry_tup{};
		static_for<0,0,dim()>(DigitDecr,elem,carry_tup);
		return (*this);
	}


	std::string to_string(const std::string & X) const {
		std::string Y = X;
		const std::string si_n{std::to_string(UIntType(get_head_val()))};
		std::string letra(1,Y.front());
		Y = Y.substr(1,std::string::npos);
		const elem_tail_t cthistail{get_tail()};
		const std::string sr_nm1{cthistail.to_string(Y)};

		if((get_head_val()==g_imN(0))and(get_tail()==base_tail_t{})) {
			return "1";
		} else {
			if (get_tail() == base_tail_t{}) {
				if(get_head_val() == g_imN(1))
					return letra;
				else if(get_head_val() > g_imN(1))
					return letra + "^" + si_n;
				else
					return "";
			} else {
				if(get_head_val() == g_imN(1))
					return letra + sr_nm1;
				else if(get_head_val() > im_N(1))
					return letra + "^" + si_n + sr_nm1;
				else
					return sr_nm1;
			}
		}
	}
	
private :
	
	template<UIntType K>
	static constexpr
	void
	add_impl_impl(base_t & A, const base_t & B) {
		get<K>(A) += get<K>(B);
	}
	
	template<UIntType ... K>
	static constexpr
	void
	add_impl(base_t & A, const base_t & B,arg_index_sq_t<K...>) {
		(add_impl_impl<K>(A,B),...);
	}
	
public:
	
	inline constexpr
	elem_t operator + (const elem_t & rhs) const {
		elem_t result{elem};
		add_impl(
			result.elem,
			rhs.elem,
			ret_index_sq_t{}
		);
		return (result);
	}
	
	inline constexpr
	const elem_t & operator += (const elem_t & rhs) {
		add_impl(
			elem,
			rhs.elem,
			ret_index_sq_t{}
		);
		return (*this);
	}
	
private :
	
	template<UIntType K>
	static constexpr
	void
	substract_impl_impl(base_t & A, const base_t & B) {
		get<K>(A) -= get<K>(B);
	}
	
	template<UIntType ... K>
	static constexpr
	void
	substract_impl(base_t & A, const base_t & B,arg_index_sq_t<K...>) {
		(substract_impl_impl<K>(A,B),...);
	}
	
public:	
	
	inline constexpr
	elem_t operator - (const elem_t & rhs) const {
		elem_t result{elem};
		substract_impl(
			result.elem,
			rhs.elem,
			ret_index_sq_t{}
		);
		return (result);
	}
	
	inline constexpr
	const elem_t & operator -= (const elem_t & rhs) {
		substract_impl(
			elem,
			rhs.elem,
			ret_index_sq_t{}
		);
		return (*this);
	}
	
private :
	
	template<UIntType K>
	static constexpr
	void
	minus_impl_impl(base_t & A) {
		get<K>(A).mCB();
	}
	
	template<UIntType ... K>
	static constexpr
	void
	minus_impl(base_t & A,arg_index_sq_t<K...>) {
		(minus_impl_impl<K>(A),...);
	}
	
public:
	
	inline constexpr
	elem_t operator - () const {
		elem_t result{elem};
		minus_impl(
			result.elem,
			ret_index_sq_t{}
		);
		return (result);
	}

private :
	
	template<UIntType K>
	static constexpr
	void
	tilde_impl_impl(base_t & A) {
		get<K>(A).mCBm1();
	}
	
	template<UIntType ... K>
	static constexpr
	void
	tilde_impl(base_t & A,arg_index_sq_t<K...>) {
		(tilde_impl_impl<K>(A),...);
	}
	
public:

	inline constexpr
	elem_t operator ~() const {
		elem_t result{elem};
		tilde_impl(
			result.elem,
			ret_index_sq_t{}
		);
		return (result);
	}
	
private :
	
	template<UIntType K>
	static constexpr
	void
	exclam_impl_impl(base_t & A) {
		get<K>(A).mCB();
	}
	
	template<UIntType ... K>
	static constexpr
	void
	exclam_impl(base_t & A,arg_index_sq_t<K...>) {
		(exclam_impl_impl<K>(A),...);
	}
	
public:
	inline constexpr
	const elem_t & operator !() {
		exclam_impl(
			elem,
			ret_index_sq_t{}
		);
		return (*this);
	}
	
private :
	
	template<UIntType K>
	static constexpr
	void
	mult_impl_impl(base_t & A,const base_t & B) {
		get<K>(A)*=get<K>(B);
	}
	
	template<UIntType ... K>
	static constexpr
	void
	mult_impl(base_t & A,const base_t & B,arg_index_sq_t<K...>) {
		(mult_impl_impl<K>(A,B),...);
	}
	
public:
	
	inline constexpr
	elem_t operator * (const elem_t & rhs) const {
		elem_t result{elem};
		mult_impl(
			result.elem,
			rhs.elem,
			ret_index_sq_t{}
		);
		return (result);
	}
	
	inline constexpr
	const elem_t & operator *= (const elem_t & rhs) {
		mult_impl(
			elem,
			rhs.elem,
			ret_index_sq_t{}
		);
		return (*this);
	}

private :
	
	template<UIntType K>
	static constexpr
	void
	inv_impl_impl(base_t & A) {
		get<K>(A).invert();
	}
	
	template<UIntType ... K>
	static constexpr
	void
	inv_impl(base_t & A,arg_index_sq_t<K...>) {
		(inv_impl_impl<K>(A),...);
	}
	
public:
	
	inline constexpr
	elem_t inv() const {
		elem_t result{*this};
		inv_impl(
			result.elem,
			ret_index_sq_t{}
		);
		return (result);
	}
	
	inline constexpr
	const elem_t & invert() {
		inv_impl(
			elem,
			ret_index_sq_t{}
		);
		return (*this);
	}
	
	inline constexpr
	base_t to_base_t() {return elem;}
};

/////////////////////////////////////////////////////////
/// modint_cartprod_t FROM THEIR PARTS CONSTRUCTORS ////
/////////////////////////////////////////////////////////

template<typename UIntType, UIntType ... Ps,UIntType ... Qs>
inline constexpr auto
concat(
	const modint_cartprod_t<UIntType,Ps...> & arg_P,
	const modint_cartprod_t<UIntType,Qs...> & arg_Q
)->modint_cartprod_t<UIntType,Ps...,Qs...>
{
	auto preresult{tuple_cat(arg_P.to_base_t(),arg_Q.to_base_t())};
	modint_cartprod_t<UIntType,Ps...,Qs...> result{preresult};
	return result; 
}


//////////////////////////////////////////////////////////////////
/// modint_cartprod_t FROM THEIR MEMBER TUPLES  CONSTRUCTORS ////
//////////////////////////////////////////////////////////////////

template<typename UIntType, UIntType ... Ps,UIntType ... Qs>
inline constexpr auto
concat(
	const tuple<modint_t<UIntType,Ps>...> & arg_P,
	const tuple<modint_t<UIntType,Qs>...> & arg_Q
)->modint_cartprod_t<UIntType,Ps...,Qs...>
{
	auto preresult{tuple_cat(arg_P,arg_Q)};
	modint_cartprod_t<UIntType,Ps...,Qs...> result{preresult};
	return result; 
}


template<typename IntType,typename UIntType,UIntType N_n,UIntType ... N_nm1>
modint_cartprod_t<UIntType,N_n,N_nm1...>
operator * (IntType lhs,const modint_cartprod_t<UIntType,N_n,N_nm1...> & rhs) {
	modint_cartprod_t<UIntType,N_n,N_nm1...> LHS{
		modint_t<UIntType,N_n>{IntType(lhs)},
		modint_t<UIntType,N_nm1>{IntType(lhs)}...
	};
	LHS *= rhs;
	return LHS;
}

template<typename IntType,typename UIntType,UIntType N_n,UIntType ... N_nm1>
modint_cartprod_t<UIntType,N_n,N_nm1...>
operator * (const modint_cartprod_t<UIntType,N_n,N_nm1...> & lhs,IntType rhs) {
	modint_cartprod_t<UIntType,N_n,N_nm1...> RHS{
		modint_t<UIntType,N_n>{IntType(rhs)},
		modint_t<UIntType,N_nm1>{IntType(rhs)}...
	};
	RHS *= lhs;
	return RHS;
}

template<typename IntType,typename UIntType,UIntType N_n,UIntType ... N_nm1>
const modint_cartprod_t<UIntType,N_n,N_nm1...> &
operator *= (modint_cartprod_t<UIntType,N_n,N_nm1...> & lhs,IntType rhs) {
	modint_cartprod_t<UIntType,N_n,N_nm1...> RHS{
		modint_t<UIntType,N_n>{IntType(rhs)},
		modint_t<UIntType,N_nm1>{IntType(rhs)}...
	};
	lhs *= RHS;
	return (lhs);
}

template <typename UIntType,UIntType N_n>
struct modint_cartprod_t<UIntType,N_n> {
public:
	inline static constexpr 
	tuple<UIntType> mod_tup() {return make_tuple(N_n);} 
	
	template<size_t k>
	inline static constexpr 
	UIntType get_mod_tup() {
		return get<k>(mod_tup());
	} 
	
	inline static constexpr 
	UIntType max_mod() {return N_n;}
	
	inline static constexpr 
	UIntType min_mod() {return N_n;}
	
	inline static constexpr 
	UIntType dim() {return 1;}
	
	inline static constexpr 
	ullint card() {return N_n;}
	
	static_assert(
		card()<127,
		"El orden no debe ha "
		" de ser inferior a 256"
	);
	static_assert(
		min_mod()>1, 
		"No trabajamos con palotes o "
	    "sobre la nada"				
	);
	static_assert(max_mod()<64, 
		"No trabajamos con palotes o "
	    "sobre la nada"				
	);
	static_assert(
		dim()<6,
		"La dimensión del "
		"espacio modular ha "
		"de ser inferior a 256"
	);

	
	using	im_N			= modint_t<UIntType,N_n>;
	
	using	base_t 			= tuple<im_N>;
	using	base_head_t 	= tuple<im_N>;
	using	base_tail_t 	= void;
	using	base_root_t 	= tuple<im_N>;
	using	base_btail_t 	= void;
	using	base_reverse_t 	= tuple<im_N>;
	
	using	elem_t		=	modint_cartprod_t<UIntType,N_n>;
	using	elem_head_t	=	modint_cartprod_t<UIntType,N_n>;
	
	using	elem_tail_t	=   void;
	
	/////////////////////////////////////////////////////
	/// FUNCTIONS FROM MEMBER BASE_T AND ITS SUBTYPES ///
	/////////////////////////////////////////////////////
private :
	inline constexpr
	im_N & gdm() {
		return get<0>(elem);
	}
public :
	
	template<size_t idx>
	using
	modint_idx = modint_t<UIntType,get<idx>(mod_tup())>;
	
	template<UIntType Mod>
	using
	modint_mod = modint_t<UIntType,Mod>;

	inline constexpr 
	im_N get_head_val() const {
		return head_value<im_N>(elem);
	}
	
	inline constexpr 
	base_head_t get_head() const {
		return make_tuple(head_value<im_N>(elem));
	}
	
public :
	inline constexpr
	base_root_t get_root() const {
		const base_root_t result{root(elem)};
		return result;
	}
	
	inline constexpr
	decltype(auto) get_root_val() const {
		return root_value<im_N>(elem);
	}
		
	inline constexpr 
	auto get_reverse() const {
		const base_reverse_t result{reverse(elem)};
		return result;
	}
	
private :
	
	inline static constexpr
	im_N
	g_imN(UIntType k) {
		return im_N{UIntType(k)}; 
	}
	
	/// BEGIN : UNICO DATO MIEMBRO
		base_t		elem{};
	/// END   : UNICO DATO MIEMBRO
public :
	template<size_t k>
	inline constexpr
	UIntType
	get_int() const {
		return UIntType(get<k>(elem));
	}
	
	template<UIntType k>
	inline constexpr
	modint_t<UIntType,get_mod_tup<k>()> &
	get_modint() {
		return (get<k>(elem));
	}
	
	
	///////////////////////////
	/// BASIC CONSTRUCTORS ////
	///////////////////////////
	
	inline constexpr
	modint_cartprod_t()=default;
	
	inline constexpr
	modint_cartprod_t(
		const modint_cartprod_t &
	)=default;
	
	inline constexpr
	modint_cartprod_t(
		modint_cartprod_t &&
	)=default;
	
	/////////////////////////////////
	/// QUASI BASIC CONSTRUCTORS ////
	/////////////////////////////////
	
	inline constexpr
	modint_cartprod_t(
		const base_t & otherbelem
	) : elem{otherbelem} {}
	
	//inline constexpr
	//modint_cartprod_t(
	//	base_t && otherelem
	//) : elem{otherelem} {}
	
	////////////////////////////////////////////////////////////////////////
	/// modint_cartprod_t FROM THEIR SUB-MEMBER modint_t CONSTRUCTORS ////
	////////////////////////////////////////////////////////////////////////
	
	inline constexpr
	modint_cartprod_t(
		im_N im_n
	)
		: elem{make_tuple(im_n)} {}
	
	/////////////////////////////////////////////////////////////////
	/// modint_cartprod_t FROM A TUPLE OF INTEGERS CONSTRUCTORS ////
	/////////////////////////////////////////////////////////////////
	
	inline constexpr
	modint_cartprod_t(
		UIntType 		i_n
	) : 
		elem{make_tuple(g_imN(i_n))} 
	{}
	
	///////////////////////////////////////
	///		OPERADORES DE ASIGNACION	///
	///////////////////////////////////////
	
	inline constexpr
	modint_cartprod_t & operator=(
		modint_cartprod_t &
	) = default;
	
	inline constexpr
	const modint_cartprod_t & operator=(
		const modint_cartprod_t & arg
	) {
		elem = arg.elem;
		return (*this);
	}
	
	inline constexpr
	modint_cartprod_t & operator=(
		modint_cartprod_t &&
	) = default;
	
	inline constexpr
	const modint_cartprod_t & operator= (
		const base_t & arg
	) {
		elem = arg;
		return (*this);
	}
	
	template<typename UInt_n>
	inline constexpr const modint_cartprod_t & 
	operator=(const tuple<UInt_n> & arg) {
		elem = make_tuple(g_imN(get<0>(arg)));
		return (*this);
	}
	
	inline constexpr bool 
	operator<(const modint_cartprod_t & rhs) const {
		return (elem<rhs.elem);
	}

	inline constexpr bool 
	operator>(const modint_cartprod_t & rhs) const {
		return (elem>rhs.elem);
	}
	
	inline constexpr bool 
	operator <= (const modint_cartprod_t & rhs) const {
		return (elem<=rhs.elem);
	}

	inline constexpr bool
	operator >= (const modint_cartprod_t & rhs) const {
		return (elem>=rhs.elem);
	}

	inline constexpr bool 
	operator==(const modint_cartprod_t & rhs) const {
		return (elem==rhs.elem);
	}

	inline constexpr bool 
	operator!=(const modint_cartprod_t & rhs) const {
		return (elem!=rhs.elem);
	}

	inline constexpr bool
	is_zero_elem() const {
		return (std::get<0>(elem)==g_imN(0));
	}
	
	inline constexpr bool
	is_unit_elem() const {
		return (get<0>(elem)==g_imN(1));
	}

	inline constexpr bool
	is_max_elem() const {
		return (get<0>(elem)==g_imN(N_n-1));
	}
	
	inline static constexpr
	modint_cartprod_t max_elem() {
		constexpr
		modint_cartprod_t result{make_tuple(g_imN(N_n-1))};
		return result;
	}
	
	inline static constexpr
	modint_cartprod_t zero_elem() {
		constexpr
		modint_cartprod_t result{make_tuple(g_imN(0))};
		return result;
	}
	
	inline static constexpr
	modint_cartprod_t unit_elem() {
		constexpr
		modint_cartprod_t result{make_tuple(g_imN(1))};
		return result;
	}
		
	inline constexpr
	modint_cartprod_t next() const {
		modint_cartprod_t result{*this};
		++get<0>(result.elem);
		return result;
	}

	inline constexpr
	modint_cartprod_t prev() const {
		modint_cartprod_t result{*this}; 
		--get<0>(result.elem);
		return result;
	}

	inline constexpr
	const modint_cartprod_t & m_next()  { 
		++get<0>(elem);
		return (*this);
	}

	inline constexpr
	const modint_cartprod_t & m_prev() {
		--get<0>(elem);
		return (*this);
	}


	std::string to_string(const std::string & X) const {
		std::string Y = X;
		const std::string si_n{std::to_string(UIntType(get_head_val()))};
		std::string letra(1,Y.front());
				
		if(get_head_val()==g_imN(0)) {
			return "1";
		} else {
			if(get_head_val() == g_imN(1))
				return letra;
			else if(get_head_val() > g_imN(1))
				return letra + "^" + si_n;
			else
				return "";
		}
	}
			
public :
	
	inline constexpr
	elem_t operator + (const elem_t & rhs) const {
		const elem_t result{get_head_val()+rhs.get_head_val()};
		return (result);
	}
	
	inline constexpr
	const elem_t & operator += (const elem_t & rhs) {
		get<0>(elem)+=rhs.get_head_val();
		return (*this);
	}
	
	inline constexpr
	elem_t operator - (const elem_t & rhs) const {
		const elem_t result{get_head_val()-rhs.get_head_val()};
		return (result);
	}
	
	inline constexpr
	const elem_t & operator -= (const elem_t & rhs) {
		get<0>(elem)-=rhs.get_head_val();
		return (*this);
	}

	inline constexpr
	elem_t operator - () const {
		base_t result{elem};
		get<0>(result).mCB();
		return (result);
	}
	
	inline constexpr
	elem_t operator ~() const {
		base_t result{elem};
		get<0>(result).mCBm1();
		return (result);
	}
	
	inline constexpr
	const elem_t & operator !() {
		get<0>(elem).mCB();
		return (*this);
	}
	
	inline constexpr
	elem_t operator * (const elem_t & rhs) const {
		elem_t result{elem};
		get<0>(result.elem)*=get<0>(rhs.elem);
		return result;
	}
	
	inline constexpr
	const elem_t & operator *= (const elem_t & rhs) const {
		get<0>(elem)*=get<0>(rhs.elem);
		return (*this);
	}
	
	inline constexpr
	elem_t inv() const {
		elem_t result{elem};
		get<0>(result.elem).invert();
		return result;
	}
	
	inline constexpr
	const elem_t & invert() {
		get<0>(elem).invert();
		return (*this);
	}
	
	inline constexpr
	base_t & to_base_t() {return (this->elem);}
};

template<typename IntType,typename UIntType,UIntType N_n>
modint_cartprod_t<UIntType,N_n>
operator * (IntType lhs,const modint_cartprod_t<UIntType,N_n> & rhs) {
	modint_cartprod_t<UIntType,N_n> LHS{
		modint_t<UIntType,N_n>{IntType(lhs)}
	};
	LHS *= rhs;
	return LHS;
}

template<typename IntType,typename UIntType,UIntType N_n>
modint_cartprod_t<UIntType,N_n>
operator * (const modint_cartprod_t<UIntType,N_n> & lhs,IntType rhs) {
	modint_cartprod_t<UIntType,N_n> RHS{
		modint_t<UIntType,N_n>{IntType(rhs)}
	};
	RHS *= lhs;
	return RHS;
}

template<typename IntType,typename UIntType,UIntType N_n>
const modint_cartprod_t<UIntType,N_n> &
operator *= (modint_cartprod_t<UIntType,N_n> & lhs,IntType rhs) {
	modint_cartprod_t<UIntType,N_n> RHS{
		modint_t<UIntType,N_n>{IntType(rhs)}
	};
	lhs *= RHS;
	return (lhs);
}


}
#endif // modint_cartprod_t_HPP_INCLUDED
