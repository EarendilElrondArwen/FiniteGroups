
#include <istream>
#include <iostream>
#include "basic_types.hpp"
#include "basic_types_metaprogramming_on_integers_types.hpp"
#include "factoring_ct.hpp"
#include "tuple_t.hpp"
#include "int_mod_N_t.hpp"

//using tfg::int_mod_N;
using tfg::uint;
using tfg::usint;
using tfg::ulint;
using tfg::ullint;
using tfg::sint;
using tfg::ssint;
using tfg::slint;
using tfg::sllint;
using std::cout;
using std::endl;
using std::cin;

int main()
{
	using UInt_t = uint;
	constexpr UInt_t Base{11};
	using SInt_t = tfg::signed_for_unsigned_t<UInt_t>;
	using int_mod_N = tfg::int_mod_N<UInt_t,Base>;
	
	cout << "Hello Group_Theory_World!" << endl;
	
	const int_mod_N K(UInt_t(3));
	const int_mod_N L(SInt_t(5));
	int_mod_N M(K);
	M=K*L;
	cout << "K= " << K << " L= " << " K*=L;K= " << M << endl;
	/*
	for(UInt_t k{0};k<Base;++k) {
		const int_mod_N K(UInt_t(k));
		for(SInt_t l{-2*Base}; l<=2*Base ; ++l) {
			const int_mod_N L(SInt_t(l));
			int_mod_N M(K);
			cout << M << " , ";
			M*=L;
		}
		cout << endl;
	}
	*/ 
    return 0;
}
