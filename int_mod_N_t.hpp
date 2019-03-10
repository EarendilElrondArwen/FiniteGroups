/*
 * int_mod_N_t.hpp
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

#ifndef INT_MOD_NN_T__HPP__INCLUDED
#define INT_MOD_NN_T__HPP__INCLUDED

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
struct int_mod_N
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
	int_mod_N() = default;

	inline constexpr
	int_mod_N(const int_mod_N &) = default;

	inline constexpr
	int_mod_N(int_mod_N &&)=default;
/////////////////////////////////////////////
/// OPERATOR CONVERSION TO INTEGRAL TYPES ///
/////////////////////////////////////////////
/*	
	template<typename T>
	inline constexpr
	operator T() const {
		static_assert(
			is_integral_v<T>,
			"No está definida la conversion de "
			"int_mod_N a tipo T no entero"
		);
		return T(m_i); 
	}
*/
/////////////////////////////////////////////////////////
/// HELPING FUNCTION TO TRAIT "NEGATIVE" MODULAR INTS ///
/////////////////////////////////////////////////////////
public:
///////////////////////////////////
/// CONSTRUCTORS BY NON-DEFAULT ///
/// ONLY FOR INTEGRAL TYPES		///
/// EXPLICIT EXPLICIT EXPLICIT	///
///////////////////////////////////	
	template<typename Int_t>
	inline constexpr
	explicit 
	int_mod_N(Int_t k) :
		m_i{to_UIntType<Int_t>(k)}
	{}
///////////////////////////////////
/// ASSIGNATIONS BY DEFAULT 	///
///////////////////////////////////
	inline
	int_mod_N & operator=(int_mod_N &)=default;

	inline
	const int_mod_N & operator=(const int_mod_N & arg) {
		*this = arg;
		return (*this);
	}

	inline
	int_mod_N &
	operator=(int_mod_N &&)=default;

	//template<typename Int_t>
	//inline
	//int_mod_N &	operator=(Int_t k) {
	//	(this->m_i) = to_UIntType<Int_t>(k);
	//	return (*this);
	//}

////////////////////////////////////////////
/// OPERATORS FOR COMPARATING AND ORDERS ///
////////////////////////////////////////////

	inline constexpr
	bool operator==(
		const int_mod_N & b
	) const	{
		return (this->m_i==b.m_i);
	}

	inline constexpr
	bool operator != (
		const int_mod_N & b
	) const {
		return (this->m_i!=b.m_i);
	}

	inline constexpr
	bool operator < (
		const int_mod_N & b
	) const {
		return (this->m_i < b.m_i);
	}

	inline constexpr
	bool operator > (
		const int_mod_N & b
	) const {
		return (this->m_i > b.m_i);
	}

	inline constexpr
	bool operator <= (
		const int_mod_N & b
	) const {
		return (this->m_i <= b.m_i);
	}

	inline constexpr
	bool operator >= (
		const int_mod_N & b
	) const	{
		return (this->m_i >= b.m_i);
	}

///////////////////////////////////////////
/// ARITHMETIC OPERATORS CONST TYPES 	///
///////////////////////////////////////////
	
	inline constexpr
	int_mod_N operator + (
		const int_mod_N & b
	) const {
		const auto m_i_result{this->m_i+b.m_i};
		const int_mod_N result{UIntType(
			m_i_result-((m_i_result>N-1)?(N):(0))
		)};
		return result;
	}

	inline constexpr
	int_mod_N operator -(const int_mod_N & b) const {
		const auto neg_b{-b};
		return ((*this)+neg_b);
	}

	inline constexpr
	int_mod_N operator* (int_mod_N b) const	{
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
		return int_mod_N(UIntType(int_result));
	}

///////////////////////////////////////////
/// ARITHMETIC OPERATORS NON-CONST TYPES///
///////////////////////////////////////////
	
	inline
	const int_mod_N & operator += (const int_mod_N & b)	{
		m_i+=b.m_i;
		if (m_i>N-1)
			m_i-=N;
		return (*this);
	}

	inline
	const int_mod_N & operator -= (const int_mod_N & b)
	{
		*this += (-b);
		return (*this);
	}

	inline
	const int_mod_N & operator*= (const int_mod_N & b)
	{
		using LUIntType = next_int_t<UIntType>;
		const LUIntType m_i_result{(this->m_i)*(b.m_i)};
		this->m_i = to_UIntType<LUIntType>(m_i_result%N);
		return (*this);
	}
///////////////////////////////////////////////////
/// OPERATIONS OF CB AND CBm1 					///
/// CB complement to base CONST	 				///
/// 	overload for OPERATOR-()				///
/// CB complement to base NO-CONST	 			///
/// 	USING a*=INT_MOD_N(-1)					///
/// CBm1 complement to base	minus 1 CONST		///
/// 	overload for OPERATOR ~()				///
/// mCBm1 complement to base minus 1 NON-CONST	///
/// 	overload for OPERATOR !()				///
///////////////////////////////////////////////////
	
	inline
	const int_mod_N & mCBm1(){
		//autocomplementa a la base N menos 1
		(this->m_i) = (N-1)-(this->m_i);
		return (*this);
	}
	
	inline
	int_mod_N operator !() {
		this->mCBm1();
		return (*this);
	}
	
	inline constexpr
	int_mod_N CBm1() const {
		//devuelve el complemento a la base N menos 1
		const int_mod_N result{UIntType((N-1)-(this->m_i))};
		return result;
	}
	
	inline constexpr
	int_mod_N operator~() const {
		const int_mod_N result{this->CBm1()};
		return result;
	}
	
	inline
	std::pair<const int_mod_N,int_mod_N> mCB() {
		//autocomplementa a la base N menos 1
		std::pair<int_mod_N,int_mod_N> result{*this,int_mod_N{0}};
		if constexpr(N==2) {
			result.second = N-1-result.first;
		} else {
			const bool neq_0{m_i==0};
			result.first = int_mod_N(neq_0?(0):(m_i=N-m_i));
			result.second = int_mod_N(neq_0?(1):(0));
		}
		return result;
	}
	
	inline constexpr
	int_mod_N operator -() const {
		return int_mod_N((m_i==0)?(0):(N-m_i));
	}
	
	inline constexpr
	std::pair<int_mod_N,int_mod_N> CB() const	{
		//devuelve el complemento a la base N menos 1
		std::pair<int_mod_N,int_mod_N> result{*this,int_mod_N{0}};
		if constexpr(N==2) {
			result.second = N-1-result.first;
		} else {
			const bool neq_0{m_i==0};
			result.first = int_mod_N(neq_0?0:(N-m_i));
			result.second = int_mod_N(neq_0?1:0);
		}
		return result;
	}
///////////////////////////////////////////////////////////////
/// NEXT AND PREV FUNCTIONS FOR CONSTEXPR AND NON-CONSTEXPR	///
/// OPERATORS ++ AND -- PRE AND POST						/// 
///////////////////////////////////////////////////////////////	
	inline constexpr
	int_mod_N next() const {
		const int_mod_N previous_result{*this};
		const int_mod_N result{
			UIntType(
				(((N-1)-(previous_result.m_i))>0)	?
				(previous_result.m_i)+1				:
				0
			)
		};
		return result;
	}
	
	inline constexpr
	int_mod_N prev() const {
		const int_mod_N previous_result{*this};
		const int_mod_N result{
			UIntType(
				((previous_result.m_i)>0)	?
				(previous_result.m_i)-1		:
				(N-1)
			)
		};
		return result;
	}
	
	inline
	const int_mod_N & operator++()
	{
		++(this->m_i);
		if (m_i>N-1)
			(this->m_i)-=N;
		return (*this);
	}

	inline
	const int_mod_N & operator--()
	{
		if (m_i > 0)
			--(this->m_i);
		else
			this->m_i=N-1;
		return (*this);
	}

	inline
	int_mod_N operator++(int)
	{
		const UIntType result{this->m_i};
		++(*this);
		return int_mod_N(UIntType(result));
	}

	inline
	int_mod_N operator--(int)
	{
		const auto result{this->m_i};
		--(*this);
		return int_mod_N(UIntType(result));
	}
///////////////////////////////////
/// UNARIES FUNCTIONS : 		///
///		INV FOR CONSTEXPR		///
///		INVERT FOR NON-CONSTEXPR///
///////////////////////////////////	
	inline constexpr
	int_mod_N inv() const {
		using SIntType = signed_for_unsigned_t<UIntType>;
		return int_mod_N(SIntType(modInv<SIntType,N>(this->m_i)));
	}

	inline
	const int_mod_N & invert() {
		(*this)=this->inv();
		return(*this);
	}
///////////////////////////////////////
/// OPERATOR FOR EUCLIEAN DIVISION 	///
/// OPERATOR / FOR CONSTEXPR	   	///
/// OPERATOR /= FOR NON_CONSTEXPR  	///
///////////////////////////////////////	
	constexpr
	int_mod_N operator / (const int_mod_N & b) const {
		const int_mod_N b_inv{b.inv()};
		return (*this)*b_inv;
	}

	inline
	const int_mod_N & operator /= (const int_mod_N & b) {
		const int_mod_N b_inv{b.inv()};
		return ((*this)*=b_inv);
	}
///////////////////////////////////////////////////////////////////
/// OPERATOR FOR MODULAR MULPLICATION WITH SCALAR AND VECTOR 	///
/// DON'T FUNCTIONS BY NOW	   									///
///////////////////////////////////////////////////////////////////	
	
	/*
	template<typename Int_t>
	inline constexpr
	int_mod_N bexop(Int_t a) const {
		const auto b{to_UIntType<Int_t>(a)};
		const int_mod_N op{UIntType(b)};
		return ((*this)*op);
	}
	
	template<typename Int_t>
	inline
	int_mod_N bexop_n_assign(Int_t a) {
		const auto b{to_UIntType<Int_t>(a)};
		const int_mod_N op{UIntType(b)};
		(*this)*=op;
		return (*this);
	}
	*/
///////////////////////////////////////
/// MODULAR EXPONENTIATION 			///
/// OPERATOR ^ FOR CONSTEXPR	   	///
/// OPERATOR ^= FOR NON_CONSTEXPR  	///
///////////////////////////////////////	

	template<typename Int_t>
	inline constexpr
	int_mod_N operator^(Int_t n) const {
		if constexpr (is_unsigned_int_t_v<Int_t>) {
			if (this->m_i==0)
				return (*this);
			else if((n==0)||(m_i==1))
				return int_mod_N(1);
			else if(n==1)
				return (*this);
			else {
				int_mod_N exp{1};
				int_mod_N x{m_i};
				while ((n >0)&&(x>1))
				{
					if  (x%2==0)
						exp *= x;
					x*= x;
					n/=2;
				}
				return (exp);
			}
		}
		else {
			if (n<0) {
				const ullint mn{-n};
				const int_mod_N cthisinv{this->inv()};
				return (cthisinv^mn);
			}
			else if (n==0) {
				return int_mod_N(UIntType(1));
			}
			else {
				return ((*this)^n);
			}
		}
	}

	template<typename Int_t>
	inline
	int_mod_N operator^= (Int_t n)
	{
		if (this->m_i==0)
			return (*this);
		else if(n==0)
		{
			(*this)=0;
			return (*this);
		}
		else if (n==1)
			return (*this);
		else
		{
			*this=1;  ///???
			int_mod_N x{*this};
			while ((n>0)&&(x.m_i>1)) {
				if  (n%2==0)
					(*this)*= x;
				x*= x;
				n/=2;
			}
			return (*this);
		}
	}
///////////////////////////////////////
/// CREATION OF PRINCPIPAL CONSTEXPR///
///////////////////////////////////////	

	static constexpr
	int_mod_N max = int_mod_N(N-1);
	
	static constexpr
	int_mod_N Nm1 = int_mod_N(N-1);
	
	static constexpr
	int_mod_N min = int_mod_N(0);
	
	static constexpr
	int_mod_N zero = int_mod_N(0);
	
	static constexpr
	int_mod_N unit = int_mod_N(1);

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
/// FUNCTION OSTREAM << INT_MOD_N NON-CONSTEXPR	///
///////////////////////////////////////////////////	

template<typename UIntType,UIntType N>
std::ostream& operator << (ostream& out,int_mod_N<UIntType,N> arg) {
	out << arg.to_string();
	return out;
}
///////////////////////////////////////////////////
/// FUNCTION FOR CONSTANTS 0,1,N-1 CONSTEXPR	///
///////////////////////////////////////////////////	
template<typename T,T N>
constexpr
int_mod_N<T,N> imod_0()
{
	return int_mod_N<T,N>(0);
}

template<typename T,T N>
constexpr
int_mod_N<T,N> imod_1()
{
	return int_mod_N<T,N>(1);
}

template<typename T,T N>
constexpr
int_mod_N<T,N> imod_Nm1()
{
	return int_mod_N<T,N>(N-1);
}
///////////////////////////////////////////////////////////////////
/// OPERATOR FOR MODULAR MULPLICATION WITH SCALAR AND VECTOR 	///
/// DON'T FUNCTIONS BY NOW	   									///
///////////////////////////////////////////////////////////////////	

/*
template<typename UIntType,UIntType N,typename Int_t>
inline constexpr
int_mod_N<UIntType,N> bexop(Int_t a,int_mod_N<UIntType,N> A) {
	return (A.bexop(Int_t(a)));
}
*/
}
#endif //INT_MOD_NN_T__HPP__INCLUDED
