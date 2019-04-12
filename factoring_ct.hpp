#ifndef FACTORING_CT_HPP_INCLUDED
#define FACTORING_CT_HPP_INCLUDED

#include "basic_types_metaprogramming_on_integers_types.hpp"

#include <cstdlib>
#include <cstdint>
#include <utility>
#include <tuple>
#include <cmath>
#include <string>
#include <limits>

namespace tfg {

using std::size_t;
using std::numeric_limits;
template<typename T>
using nl = typename std::numeric_limits<T>;
template<typename T>
auto digits = nl<T>::digits;
using std::tuple;
using std::get;
using std::make_tuple;

// C++ function for extended Euclidean Algorithm
// (g,x,y) := gcdExtd<N>(a)
// g = x*a+y*N
template<typename Int_t,Int_t Mod>
inline constexpr
std::tuple<
	signed_for_unsigned_t<Int_t>,
	signed_for_unsigned_t<Int_t>,
	signed_for_unsigned_t<Int_t>
> gcdExtd(Int_t a) {
	using SInt_t = signed_for_unsigned_t<Int_t>;
	// Base Case
	if (Mod==0) {
		return make_tuple(0,0,0);
	} else if (a == 1) {
		return make_tuple(1,1,0);
	} else if (Mod == 1) {
		return make_tuple(0,0,0);
	} else if (a == Mod-1) {
		return make_tuple(1,-1,1);
	} else if (a == 0) { 
        return make_tuple(Mod,0,1);
    } else if (a == Mod) { 
        return make_tuple(Mod,0,1); 
    } else {
		struct step {
			SInt_t r;
			SInt_t x;
			SInt_t y;
			step(SInt_t R,SInt_t X,SInt_t Y) : r{R},x{X},y{Y} {}
		};
		step st[2]{
			step(Mod        ,0          ,1      ),
			step(a%Mod      ,1          ,0      )
		};
		while(st[1].r != 0) {
			
			const next_int_t<SInt_t> q{st[0].r/st[1].r};
			const step rs(
					st[0].r-(q*st[1].r),
					st[0].x-(q*st[1].x),
					st[0].y-(q*st[1].y)
			);
			st[0]=st[1];
			st[1]=rs;
		}
		return make_tuple(st[0].r,st[0].x,st[0].y);
	}
} 
  
// C++ function to find modular inverse of "a" 
template<typename Int_t,Int_t Mod>
inline constexpr
signed_for_unsigned_t<Int_t> modInv(Int_t a) 
{
	using SInt_t = next_int_t<signed_for_unsigned_t<Int_t>>;
	const std::tuple<SInt_t,SInt_t,SInt_t> g{gcdExtd<SInt_t,Mod>(a)}; 
    if (get<0>(g) != 1) 
        return SInt_t(0); 
    else
        return SInt_t{get<1>(g)};
} 
  
inline constexpr
ullint mid(ullint low,ullint high) {
  return ((low + high) / 2);
}

// precondition: low*low <= n, high*high > n.
inline constexpr
ullint ceilsqrt(ullint n,ullint low,ullint high) {
  return
  (
  (low + 1 >= high) ?
      high
    : (mid(low, high) * mid(low, high) == n) ?
          mid(low, high)
        : (mid(low, high) * mid(low, high) <  n) ?
            ceilsqrt(n, mid(low, high), high)
          : ceilsqrt(n, low, mid(low, high))
  );
}

// returns ceiling(sqrt(n))
inline constexpr
ullint ceilsqrt(ullint n) {
  return(
		(n < 3) 								?
			n									:
			ceilsqrt(
				n,
				1,
				size_t(1)<<(digits<ullint> / 2)
			)
  );
}

// returns true if n is divisible by an odd integer in
// [2 * low + 1, 2 * high + 1).
inline constexpr
bool find_factor(ullint n,ullint low,ullint high) {
  return(
		(low + 1 >= high)
											?
			((n % (2 * low + 1)) == 0)		:
			(			find_factor(n, low, mid(low, high))
			 ||		find_factor(n, mid(low, high), high))
	);
}

inline constexpr
bool is_prime(ullint n) {
  return( 	(n > 1)
		&& 	(
				(n == 2)
			||  (		(n % 2 == 1)
					&&  (
							(n == 3)
						||
							(!find_factor(
								n,
								1,
								((ceilsqrt(n) + 1) / 2)
							  )
							)
						)
				)
			)
		);
}

enum class n_case {
	z,u,d,t,q,c,s
};
enum class t_case {
	I,
	A,B,C,D,E,F,
	AB,AC,AD,AE,AF,BC,BD,BE,BF,CD,CE,CF,DE,DF,EF,
	ABC,ABD,ABE,ABF,ACD,ACE,ACF,ADE,ADF,AEF,BCD,BCE,BCF,BDE,BDF,BEF,CDE,CDF,CEF,DEF,
	ABCD,ABCE,ABDE,ACDE,BCDE,ABCF,ABDF,ACDF,BCDF,ABEF,ACEF,BCEF,ADEF,BDEF,CDEF,
	ABCDE,ABCDF,ABCEF,ABDEF,ACDEF,BCDEF,
	ABCDEF
};

}
#endif // FACTORING_CT_HPP_INCLUDED
