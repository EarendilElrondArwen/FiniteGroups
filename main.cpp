
#include <istream>
#include <iostream>
#include <string>
#include "basic_types.hpp"
#include "basic_types_metaprogramming_on_integers_types.hpp"
#include "factoring_ct.hpp"
#include "tuple_t.hpp"
#include "modint_t.hpp"
#include "modint_cartprod_t.hpp"
#include "binop_t.hpp"
#include "magma_t.hpp"
#include "subset_of_magma_t.hpp"
#include "subgroup_lattice_t.hpp"
#include "give_me_the_group_information.hpp"

	template<size_t K>
	void info_cyclic_group()
	{
		using uint = tfg::uint;
		using gn = tfg::group_name;
		constexpr uint N{static_cast<uint>(K)};
		std::string nombre = tfg::to_string(gn::C);
		std::string  cardinal_dim_1 = std::to_string(static_cast<size_t>(N));
		tfg::get_group_info<gn::C,uint,N>::work(nombre+cardinal_dim_1,"{{"+nombre+"}_{"+cardinal_dim_1+"}}","abcd");
	}
	
	template<size_t offset,size_t ... Is>
	void info_cyclic_group_series_IMPL(std::index_sequence<Is...>) {
		(info_cyclic_group<static_cast<size_t>(offset+Is)>(),...);
	}
	
	template<size_t from,size_t quantity>
	void info_cyclic_group_series(){
		info_cyclic_group_series_IMPL<from>(std::make_index_sequence<quantity>{});
	}
	
	template<size_t I,size_t J=0,size_t K=0,size_t L=0>
	void info_cyclic_direct_prod_group()
	{
		using uint = tfg::uint;
		using gn = tfg::group_name;
		constexpr uint N{static_cast<uint>(I)};
		constexpr uint M{static_cast<uint>(J)};
		constexpr uint P{static_cast<uint>(K)};
		constexpr uint Q{static_cast<uint>(L)};
		
		std::string  card_dim_1 = std::to_string(static_cast<size_t>(N));
		
		if((J==0)&&(L==0)&&(K==0)) {
			std::string nombre = tfg::to_string(gn::C);
			std::string nombre_latex = 
				"{{"+tfg::to_string(gn::C)+"}_{"+card_dim_1+"}}";
			std::string nombre_archivo = nombre+card_dim_1+"_desde_PD_Cyc";
			tfg::get_group_info<gn::PD_Cyc,uint,N>::work(nombre_archivo,nombre_latex,"abcd");
		}
		else if constexpr ((L==0)&&(K==0)) {
			std::string card_dim_2 = std::to_string(static_cast<size_t>(M));
			std::string nombre = tfg::to_string(gn::PD_Cyc);
			std::string nombre_latex = 
			"{{"+tfg::to_string(gn::C)+"}_{"+card_dim_1+
			"}x{"+tfg::to_string(gn::C)+"}_{"+card_dim_2+
			"}}";
			std::string nombre_archivo = nombre+card_dim_1+"x"+card_dim_2;
			tfg::get_group_info<gn::PD_Cyc,uint,N,M>::work(nombre_archivo,nombre_latex,"abcd");
		} else if constexpr (L==0) {
			std::string nombre = tfg::to_string(gn::PD_Cyc);
			std::string card_dim_2 = std::to_string(static_cast<size_t>(M));
			std::string card_dim_3 = std::to_string(static_cast<size_t>(P));
			std::string nombre_latex = 
			"{{"+tfg::to_string(gn::C)+"}_{"+card_dim_1+
			"}x{"+tfg::to_string(gn::C)+"}_{"+card_dim_2+
			"}x{"+tfg::to_string(gn::C)+"}_{"+card_dim_3+
			"}}";
			std::string nombre_archivo = nombre+card_dim_1+"x"+card_dim_2+"x"+card_dim_3;
			tfg::get_group_info<gn::PD_Cyc,uint,N,M,P>::work(nombre_archivo,nombre_latex,"abcd");
		} else {
			std::string nombre = tfg::to_string(gn::PD_Cyc);
			std::string card_dim_2 = std::to_string(static_cast<size_t>(M));
			std::string card_dim_3 = std::to_string(static_cast<size_t>(P));
			std::string card_dim_4 = std::to_string(static_cast<size_t>(Q));
			std::string nombre_latex = 
			"{{"+tfg::to_string(gn::C)+"}_{"+card_dim_1+
			"}x{"+tfg::to_string(gn::C)+"}_{"+card_dim_2+
			"}x{"+tfg::to_string(gn::C)+"}_{"+card_dim_3+
			"}x{"+tfg::to_string(gn::C)+"}_{"+card_dim_4+
			"}}";
			std::string nombre_archivo = nombre+card_dim_1+"x"+card_dim_2+"x"+card_dim_3+"x"+card_dim_4;
			tfg::get_group_info<gn::PD_Cyc,uint,N,M,P,Q>::work(nombre_archivo,nombre_latex,"abcd");
		}
	}
	/*
	template<size_t ... Is,size_t J>
	void info_cyclic_direct_prod_group_series_IMPL_1<J>(std::index_sequence<Is...>) {
		(info_cyclic_direct_prod_group<static_cast<size_t>(2+Is),J>(),...);
	}
	
	template<size_t quant,size_t J>
	void info_cyclic_direct_prod_group_series_1(){
		info_cyclic_direct_prod_group_series_IMPL_1<J>(std::make_index_sequence<quant>{});
	}
	*/
int main() {
	using namespace tfg;
	using std::string;
	using UInt_t = uint;
	constexpr UInt_t Base[]{2_ui8,2_ui8,3_ui8};
	using modint_cartprod = modint_cartprod_t<UInt_t,Base[0],Base[1],Base[2]>;
	using group_op = binop_t<group_name::C2_2__C3,UInt_t,Base[0],Base[1],Base[2]>;
	using magma = magma_t<group_name::C2_2__C3,UInt_t,Base[0],Base[1],Base[2]>;
	using group = subset_of_magma_t<group_name::C2_2__C3,UInt_t,Base[0],Base[1],Base[2]>;
	using lattice = set_lattice_t<group_name::C2_2__C3,UInt_t,Base[0],Base[1],Base[2]>;
	using gr_info = get_group_info<group_name::C2_2__C3,UInt_t,Base[0],Base[1],Base[2]>;
	
	constexpr auto cmod0_Nm1 	{imod_Nm1<UInt_t,Base[0]>()};
	constexpr auto cmod0_1 		{imod_1<UInt_t,Base[0]>()};
	constexpr auto cmod0_0 		{imod_0<UInt_t,Base[0]>()};
	constexpr auto cmod1_Nm1 	{imod_Nm1<UInt_t,Base[1]>()};
	constexpr auto cmod1_1 		{imod_1<UInt_t,Base[1]>()};
	constexpr auto cmod1_0 		{imod_0<UInt_t,Base[1]>()};
	constexpr auto cmod2_Nm1 	{imod_Nm1<UInt_t,Base[2]>()};
	constexpr auto cmod2_1 		{imod_1<UInt_t,Base[2]>()};
	constexpr auto cmod2_0 		{imod_0<UInt_t,Base[2]>()};
	
	constexpr auto cmodprod_max  {modint_cartprod::max_elem()};
	constexpr auto cmodprod_zero {modint_cartprod::zero_elem()};
	constexpr auto cmodprod_unit {modint_cartprod::unit_elem()};
		
	cout << "Hello Group_Theory_World!" << endl;
	/*	
	modint_cartprod Index{};
	modint_cartprod old_Index{Index};
	Index.m_next();
	while(Index >= old_Index) {
		cout 	<< old_Index.to_string("abcd") << " < " << Index.to_string("abcd") 
				<< ((old_Index<Index)?"\tverdadero":"\tfalso") << endl;
		old_Index = Index;
		Index.m_next();
	}
	
	cout << endl << endl;
	
	Index = cmodprod_max;
	old_Index = Index;
	Index.m_prev();
	while(Index <= old_Index) {
		cout 	<< old_Index.to_string("abcd") << " > " << Index.to_string("abcd") 
				<< ((old_Index>Index)?"\tverdadero":"\tfalso") << endl;
		old_Index = Index;
		Index.m_prev();
	}
	
	cout << endl << endl;
	
	modint_cartprod lhs{};
	size_t left_it{0};
	while(left_it < 12) {
		modint_cartprod rhs{};
		size_t right_it{0};
		while(right_it < 12) {
			{
				const auto result{group_op::gr_bop(lhs,rhs)};
				cout	<< result.to_string("abcd")
						<< " ";
			}
			rhs.m_next();
			++right_it;
		}
		cout << endl;
		lhs.m_next();
		++left_it;
	}
	
	magma prueba{};
	
	cout << prueba.to_string() << endl;
	cout << magma::card() << endl;
	cout << size_t(magma::dim()) << endl;
	cout << size_t(magma::max_mod()) << endl;
	cout << size_t(magma::min_mod()) << endl;
	cout << size_t(magma::mod_idx<0>())  << size_t(magma::mod_idx<1>())  << size_t(magma::mod_idx<2>()) << endl;
	cout << endl << endl << endl;
	
	string magma_is_group{(magma::is_associative())?("SI es Asociativa"):("NO es Asociativa")};
	cout << endl;
	cout << magma_is_group << endl;
	
	magma_is_group =(magma::exists_neutral_elem())?("SI EXISTE Elemento NEUTRO"):("NO EXISTE Elemento NEUTRO");
	cout << endl;
	cout << magma_is_group << endl;
	
	cout << endl;
	cout << magma::get_the_identity().to_string() << endl;
	
	magma_is_group =(magma::exists_gr_inv_for_all())?("SI EXISTE Elemento INVERSO para TODOS"):("NO EXISTE Elemento INVERSO para TODOS");
	cout << endl;
	cout << magma_is_group << endl;
	
	magma_is_group =(magma::is_abelian())?("SI ES ABELIANO"):("NO ES ABELIANO");
	cout << endl;
	cout << magma_is_group << endl;
	
	const size_t  orden_del_uno{magma::order_of_one_past_zero()};
	cout << endl;
	cout << orden_del_uno << endl;
	
	magma x{magma::get_the_identity()};
	for(size_t i{0} ; i < magma::card() ; ++i) {
		cout 	<< "El ELEMENTO : " 
				<< x.to_string() 
				<< " tiene ORDEN : " 
				<< static_cast<size_t>(x.elem_order())
				<< endl;
		x.m_next();
	}
	
	string magma_is_left_cancellative =(magma::is_left_cancellative())?("SI ES CANCELATIVO A LA IZQUIERDA"):("NO ES CANCELATIVO A LA IZQUIERDA");
	cout << endl;
	cout << magma_is_left_cancellative << endl;
	
	string magma_is_right_cancellative =(magma::is_right_cancellative())?("SI ES CANCELATIVO A LA DERECHA"):("NO ES CANCELATIVO A LA DERECHA");
	cout << endl;
	cout << magma_is_right_cancellative << endl;
	
	string magma_is_cancellative =(magma::is_cancellative())?("SI ES CANCELATIVO"):("NO ES CANCELATIVO");
	cout << endl;
	cout << magma_is_cancellative << endl;
	
	x=magma{};
	for(size_t i{0} ; i < magma::card() ; ++i) {
		cout 	<< "El INVERSO DE : " 
				<< x.to_string() 
				<< " ES : " 
				<< magma::get_gr_inv_for(x).to_string()
				<< endl;
		x.m_next();
	}
	
	cout << "sizeof modint_cartprod : " << sizeof(x.get_elem_t()) << "  sizeof magma_t : " << sizeof(x) << endl;
	cout << endl;
	group H{};
	x = magma{modint_cartprod(0,0,1)};
	magma y{modint_cartprod(1,0,1)};
	cout << "<" << x.to_string("abcd") << " , " << y.to_string() << "> = ";
	H.span_group(x,y);
	
	cout	<< H.to_string("abcd") 
			<< " Su cardinal es :  " 
			<<  H.size()
			<< endl;
	
	H.do_empty();
	*/
	/*
	for(size_t i{0} ; i < magma::card() ; ++i) {
		for(size_t i{0} ; i < magma::card() ; ++i) {
			cout << "<" << x.to_string("abcd") << " , " << y.to_string() << "> = ";
			H.span_group(x,y);
			cout<< H.to_string("abcd") << " CARDINAL:  " <<  H.size()
				<< endl;
			H.do_empty();
			y.m_next();
		}
		x.m_next();
	}
	
	H.do_empty();
	magma z{};
	x=magma{};
	y=magma{};
	for(size_t i{0} ; i < magma::card() ; ++i) {
		for(size_t i{0} ; i < magma::card() ; ++i) {
			for(size_t i{0} ; i < magma::card() ; ++i) {
				cout << "<" << x.to_string("abcd") << " , " << y.to_string("abcd")  << " , " << z.to_string("abcd") << "> = ";
				H.span_group(x,y,z);
				cout<< H.to_string("abcd") << " CARDINAL:  " <<  H.size()
					<< endl;
				H.do_empty();
				z.m_next();
			}
			y.m_next();
		}
		x.m_next();
	}
	*/
	/*
	lattice L{};
	string strresult{};
	fill_the_subgroups_from_1_generator_of_lattice(L);
	to_string(strresult,L,"abcd");
	cout << endl << strresult << endl;
	L.clear();
	strresult.clear();
	fill_the_subgroups_from_2_generators_of_lattice(L);
	to_string(strresult,L,"abcd");
	cout << endl << strresult << endl;
	L.clear();
	strresult.clear();
	fill_the_subgroups_from_3_generators_of_lattice(L);
	to_string(strresult,L,"abcd");
	cout << endl << strresult << endl;
	*/
	//	T=1,
	//	C=2,
	/*
		PD=3,
		PD_Cyc=4,
		C2_2=5,
		Dih=6,
		C2_3=7,C4xC2=8,Q=9,Dic=10,
		C3_2=11,
		C6xC2=12,C3__C4=13,C3__C2_2=14,Dih6=15,
		Dih3xC2=16,C6__C2=17,Dic3=18,
		C2_2__C3=19,A4=20,
		C2_4=21,C4xC2_2=22,C4_2=23,C8xC2=24,
		C16=25,M16=26,Dih8=27,Dic4=28,SDih8=29,
		C4__C4=30,Dih4xC2=31,
		Q8xC2=32,Q16=33,Dih4_c_C2=34,
		GDih=35,
		C4xC2__C2=36,
		C6xC3=37,C18=38,GDih9=39,Dih3xC3=40,
		C5__C4=41,
		C7__C3=42
	*/
	//info_cyclic_group_series<19,5>();
	info_cyclic_direct_prod_group<2,2,2>();
	system("pause");
    return 0;
}




