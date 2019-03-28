/*
 * modint_t_t.hpp
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

#ifndef modint_tN_T__HPP__INCLUDED
#define modint_tN_T__HPP__INCLUDED

#include <utility>
#include <tuple>
#include <string>
#include "tuple_t.hpp"

namespace tfg {

using std::size_t;
using std::numeric_limits;
template<typename T>
auto digits = numeric_limits<T>::digits;
using std::tuple;
using std::get;
using std::is_integral_v;
using std::is_same_v;

template<typename UIntType ,UIntType N>
struct modint_t
{
	static_assert (
		N>1,
		"La base no puede ser menor que "
		"2, no trabajamos con palotes"
	);
	static_assert (
		is_integral_v<UIntType>,
		"El argumento de template tiene "
		"que ser un tipo integral"
	);
	static_assert (
		is_unsigned_int_t_v<UIntType>,
		"El argumento de template tiene "
		"que ser un tipo integral"
	);
		
	UIntType m_i{};
///////////////////////////////
/// CONSTRUCTORS BY DEFAULT ///
///////////////////////////////
	inline constexpr
	modint_t() = default;

	inline constexpr
	modint_t(const modint_t &) = default;

	inline constexpr
	modint_t(modint_t &&)=default;
/////////////////////////////////////////////
/// OPERATOR CONVERSION TO INTEGRAL TYPES ///
/////////////////////////////////////////////
	
	template<typename T>
	inline constexpr
	explicit
	operator T() const {
		static_assert(
			is_integral_v<T>&&(is_signed_int_t_v<T>||is_unsigned_int_t_v<T>),
			"No está definida la conversion de "
			"modint_t a tipo T no entero"
		);
		return static_cast<T>(this->m_i); 
	}

public:
///////////////////////////////////
/// CONSTRUCTORS BY NON-DEFAULT ///
/// ONLY FOR INTEGRAL TYPES		///
/// EXPLICIT EXPLICIT EXPLICIT	///
///////////////////////////////////	
	template<typename Int_t>
	inline constexpr
	explicit 
	modint_t(Int_t k) :
		m_i{to_UIntType<Int_t,UIntType,N>(k)}
	{}
///////////////////////////////////
/// ASSIGNATIONS BY DEFAULT 	///
///////////////////////////////////
	inline
	modint_t & operator=(modint_t &)=default;

	inline
	modint_t &
	operator=(modint_t &&)=default;

////////////////////////////////////////////
/// OPERATORS FOR COMPARATING AND ORDERS ///
////////////////////////////////////////////

	inline constexpr
	bool operator==(
		const modint_t & b
	) const	{
		return (this->m_i==b.m_i);
	}

	inline constexpr
	bool operator != (
		const modint_t & b
	) const {
		return (this->m_i!=b.m_i);
	}

	inline constexpr
	bool operator < (
		const modint_t & b
	) const {
		return (this->m_i < b.m_i);
	}

	inline constexpr
	bool operator > (
		const modint_t & b
	) const {
		return (this->m_i > b.m_i);
	}

	inline constexpr
	bool operator <= (
		const modint_t & b
	) const {
		return (this->m_i <= b.m_i);
	}

	inline constexpr
	bool operator >= (
		const modint_t & b
	) const	{
		return (this->m_i >= b.m_i);
	}

///////////////////////////////////////////
/// ARITHMETIC OPERATORS CONST TYPES 	///
///////////////////////////////////////////
	
	inline constexpr
	modint_t operator + (
		const modint_t & b
	) const {
		const auto m_i_result{this->m_i+b.m_i};
		const modint_t result{UIntType(
			m_i_result-((m_i_result>N-1)?(N):(0))
		)};
		return result;
	}

	inline constexpr
	modint_t operator -(const modint_t & b) const {
		const auto neg_b{-b};
		return ((*this)+neg_b);
	}

	inline constexpr
	modint_t operator* (modint_t b) const	{
		using LUIntType = next_int_t<next_int_t<UIntType>>;
		using LLUIntType = next_int_t<LUIntType>;
		const LUIntType this_m_i{this->m_i};
		const LUIntType b_m_i{b.m_i};
		const LLUIntType m_i_result{this_m_i*b_m_i};
		const UIntType int_result{
			UIntType(
				(m_i_result > N-1)	?
					(m_i_result%N)	:
					(m_i_result)
			)
		};
		return modint_t(UIntType(int_result));
	}

///////////////////////////////////////////
/// ARITHMETIC OPERATORS NON-CONST TYPES///
///////////////////////////////////////////
	
	inline
	const modint_t & operator += (const modint_t & b)	{
		this->m_i+=b.m_i;
		if (this->m_i>N-1)
			this->m_i-=N;
		return (*this);
	}

	inline
	const modint_t & operator -= (const modint_t & b)
	{
		*this += (-b);
		return (*this);
	}

	inline
	const modint_t & operator*= (const modint_t & b)
	{
		const ullint m_i_result{static_cast<ullint>(((this->m_i)*(b.m_i))%N)};
		this->m_i = to_UIntType<ullint,UIntType,N>(m_i_result);
		return (*this);
	}
///////////////////////////////////////////////////
/// OPERATIONS OF CB AND CBm1 					///
/// CB complement to base CONST	 				///
/// 	overload for OPERATOR-()				///
/// CB complement to base NO-CONST	 			///
/// 	USING a*=modint_t(-1)					///
/// CBm1 complement to base	minus 1 CONST		///
/// 	overload for OPERATOR ~()				///
/// mCBm1 complement to base minus 1 NON-CONST	///
/// 	overload for OPERATOR !()				///
///////////////////////////////////////////////////
	
	inline
	const modint_t & mCBm1(){
		//autocomplementa a la base N menos 1
		(this->m_i) = (N-1)-(this->m_i);
		return (*this);
	}
	
	inline
	modint_t operator !() {
		this->mCBm1();
		return (*this);
	}
	
	inline constexpr
	modint_t CBm1() const {
		//devuelve el complemento a la base N menos 1
		const modint_t result{UIntType((N-1)-(this->m_i))};
		return result;
	}
	
	inline constexpr
	modint_t operator~() const {
		const modint_t result{this->CBm1()};
		return result;
	}
	
	inline
	std::pair<const modint_t,modint_t> mCB() {
		//autocomplementa a la base N menos 1
		std::pair<modint_t,modint_t> result{*this,modint_t{0}};
		if constexpr(N==2) {
			result.second = N-1-result.first;
		} else {
			const bool neq_0{m_i==0};
			result.first = modint_t(neq_0?(0):(m_i=N-m_i));
			result.second = modint_t(neq_0?(1):(0));
		}
		return result;
	}
	
	inline constexpr
	modint_t operator -() const {
		return modint_t((m_i==0)?(0):(N-m_i));
	}
	
	inline constexpr
	std::pair<modint_t,modint_t> CB() const	{
		//devuelve el complemento a la base N menos 1
		std::pair<modint_t,modint_t> result{*this,modint_t{0}};
		if constexpr(N==2) {
			result.second = N-1-result.first;
		} else {
			const bool neq_0{m_i==0};
			result.first = modint_t(neq_0?0:(N-m_i));
			result.second = modint_t(neq_0?1:0);
		}
		return result;
	}
///////////////////////////////////////////////////////////////
/// NEXT AND PREV FUNCTIONS FOR CONSTEXPR AND NON-CONSTEXPR	///
/// OPERATORS ++ AND -- PRE AND POST						/// 
///////////////////////////////////////////////////////////////	
	inline constexpr
	modint_t next() const {
		const modint_t previous_result{*this};
		const modint_t result{
			UIntType(
				(((N-1)-(previous_result.m_i))>0)	?
				(previous_result.m_i)+1				:
				0
			)
		};
		return result;
	}
	
	inline constexpr
	modint_t prev() const {
		const modint_t previous_result{*this};
		const modint_t result{
			UIntType(
				((previous_result.m_i)>0)	?
				(previous_result.m_i)-1		:
				(N-1)
			)
		};
		return result;
	}
	
	inline
	const modint_t & operator++()
	{
		++(this->m_i);
		if (m_i>N-1)
			(this->m_i)-=N;
		return (*this);
	}

	inline
	const modint_t & operator--()
	{
		if (m_i > 0)
			--(this->m_i);
		else
			this->m_i=N-1;
		return (*this);
	}

	inline
	modint_t operator++(int)
	{
		const UIntType result{this->m_i};
		++(*this);
		return modint_t(UIntType(result));
	}

	inline
	modint_t operator--(int)
	{
		const auto result{this->m_i};
		--(*this);
		return modint_t(UIntType(result));
	}
///////////////////////////////////
/// UNARIES FUNCTIONS : 		///
///		INV FOR CONSTEXPR		///
///		INVERT FOR NON-CONSTEXPR///
///////////////////////////////////	
	inline constexpr
	modint_t inv() const {
		modint_t result{*this};
		result.invert();
		return (result);
	}

	inline
	const modint_t & invert() {
		using SIntType = signed_for_unsigned_t<UIntType>;
		const auto preresult{modInv<SIntType,N>(m_i)};
		m_i = to_UIntType<SIntType,UIntType,N>(preresult);
		return(*this);
	}
///////////////////////////////////////
/// OPERATOR FOR EUCLIEAN DIVISION 	///
/// OPERATOR / FOR CONSTEXPR	   	///
/// OPERATOR /= FOR NON_CONSTEXPR  	///
///////////////////////////////////////	
	inline constexpr
	modint_t operator / (const modint_t & b) const {
		const modint_t b_inv{b.inv()};
		return (*this)*b_inv;
	}

	inline
	const modint_t & operator /= (const modint_t & b) {
		const modint_t b_inv{b.inv()};
		return ((*this)*=b_inv);
	}

///////////////////////////////////////
/// MODULAR EXPONENTIATION 			///
/// OPERATOR ^ FOR CONSTEXPR	   	///
/// OPERATOR ^= FOR NON_CONSTEXPR  	///
///////////////////////////////////////	
	
	template<typename UInt_t>
	inline constexpr
	modint_t pow(UInt_t n) const {
		static_assert(
			is_unsigned_int_t_v<UInt_t>,
			"solo 0s y positivos en esta funcion"
		);
		if ((n==1)||(this->m_i==0)) {
			return (*this);
		} else if((n==0)||(this->m_i==1)) {
			return modint_t(1);
		} else {
			modint_t exp{UIntType(1)};
			modint_t x{*this};
			UInt_t m{n};
			while (m>0)
			{
				if (m%2==1)
					exp*= x;
				x*= x;
				m/=2;
			}
			return (exp);
		}
	}
	
	template<typename UInt_t>
	inline constexpr
	const modint_t & m_pow(UInt_t n) {
		static_assert(
			is_unsigned_int_t_v<UInt_t>,
			"solo 0s y positivos en esta funcion"
		);
		if ((n==1)||(this->m_i==0)) {
			return (*this);
		} else if((n==0)||(this->m_i==1)) {
			this->m_i=1;
			return (*this);
		} else {
			modint_t x{*this};
			this->m_i=1;
			UInt_t m{n};
			while (m>0)
			{
				if (m%2==1)
					(*this)*= x;
				x*= x;
				m/=2;
			}
			return (*this);
		}
	}
	
	template<typename Int_t>
	inline constexpr
	modint_t operator^(Int_t n) const {
		if constexpr (is_unsigned_int_t_v<Int_t>) {
			return this->pow<Int_t>(n);
		} else {
			const auto m{
				static_cast<unsigned_for_signed_t<Int_t>>(
					(n<0)?(-n):(n)
				)
			};
			modint_t base{*this};
			if (n<0) base.invert();
			return base.pow<unsigned_for_signed_t<Int_t>>(m);
		}
	}

	template<typename Int_t>
	inline
	const modint_t & operator^= (Int_t n) {
		if constexpr (is_unsigned_int_t_v<Int_t>) {
			return (this->m_pow<Int_t>(n));
		} else {
			const auto m{
				static_cast<unsigned_for_signed_t<Int_t>>(
					(n<0)?(-n):(n)
				)
			};
			if (n<0) this->invert();
			return this->m_pow<unsigned_for_signed_t<Int_t>>(m);
		}
	}

///////////////////////////////////////
/// FUNCTION TO_STRING NON-CONSTEXPR///
///////////////////////////////////////	

	std::string to_string() const
	{
		uint u{this->m_i};
		std::string R{std::to_string(u)};
		std::string B{std::to_string(N)};
		return (R + "_B" + B);
	}
};

///////////////////////////////////////////////////
/// FUNCTION OSTREAM << modint_t NON-CONSTEXPR	///
///////////////////////////////////////////////////	

template<typename UIntType,UIntType N>
std::ostream& operator << (ostream& out,modint_t<UIntType,N> arg) {
	out << arg.to_string();
	return out;
}
///////////////////////////////////////////////////
/// FUNCTION FOR CONSTANTS 0,1,N-1 CONSTEXPR	///
///////////////////////////////////////////////////	
template<typename T,T N>
constexpr
modint_t<T,N> imod_0()
{
	return modint_t<T,N>(0);
}

template<typename T,T N>
constexpr
modint_t<T,N> imod_1()
{
	return modint_t<T,N>(1);
}

template<typename T,T N>
constexpr
modint_t<T,N> imod_Nm1()
{
	return modint_t<T,N>(N-1);
}

template<typename Int_t, typename UIntType,UIntType N>
inline constexpr
modint_t<UIntType,N> operator*(Int_t a,modint_t<UIntType,N> A) {
	const modint_t<UIntType,N> B{UIntType(to_UIntType<Int_t,UIntType,N>(a))};
	return (B*A);
}
template<typename Int_t, typename UIntType,UIntType N>
inline constexpr
modint_t<UIntType,N> operator*(modint_t<UIntType,N> A,Int_t a) {
	const modint_t<UIntType,N> B{UIntType(to_UIntType<Int_t,UIntType,N>(a))};
	return (A*B);
}

}
#endif //modint_tN_T__HPP__INCLUDED
