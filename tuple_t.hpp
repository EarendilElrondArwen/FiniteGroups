#ifndef TUPLE_T_HPP_INCLUDED
#define TUPLE_T_HPP_INCLUDED

#include <cstdlib>
#include <cstdint>
#include <cmath>
#include <string>
#include <limits>
#include "tuple_t_impl.hpp"

namespace tfg
{

  using std::tuple;
  using std::get;
  using std::tie;
  using std::make_tuple;
  using std::size_t;
  using std::integral_constant;
  using std::integer_sequence;
  using std::index_sequence;
  using std::make_index_sequence;
  using std::tuple_size;
  using std::tuple_size_v;
  using std::tuple_element;
  using std::tuple_element_t;
  using std::tuple_cat;
  using std::forward;
  using std::apply;
  using std::nullopt_t;
  using std::nullopt;
  using std::optional;
  using std::initializer_list;
  using std::ostream;
  using std::istream;
  using std::endl;
  using std::cout;
  using std::cin;

  template<typename T>
  using initializer_list_it_t =
	const	typename
		initializer_list<T>::const_iterator;

  template<typename ... Ts>
  inline constexpr
  decltype(auto) head(const tuple<Ts...> t) {
	constexpr auto tp_sz{sizeof...(Ts)};
	if constexpr (tp_sz==0) {
		(void)t;
		return make_tuple();
	}
	else if constexpr (tp_sz==1) {
		return t;
	}
	else {
		return make_tuple(get<0>(t));
	}
  }

  template<typename T,typename ... Ts	>
  inline constexpr
  T head_value(const tuple<T,Ts...> t){
  	return get<0>(t);
  }

  template<typename ... Ts>
  inline constexpr
  decltype(auto) root(const tuple<Ts...> t) {
	constexpr auto tp_sz{sizeof...(Ts)};
	if constexpr (tp_sz==0) {
		(void)t;
		return make_tuple();
	}
	else if constexpr (tp_sz==1) {
		return t;
	}
	else {
		return make_tuple(get<tp_sz-1>(t));
	}
  }

  template<typename ... Ts>
  inline constexpr
  decltype(auto) root_value(const tuple<Ts...> t) {
	constexpr auto tp_sz{sizeof...(Ts)};
	if constexpr (tp_sz==0) {
		return nullopt;
	}
	else if constexpr (tp_sz==1) {
		return get<0>(t);
	}
	else {
		return get<tp_sz-1>(t);
	}
  }

  template<size_t N,class ... Ts>
  inline constexpr
  decltype(auto) take_front(tuple<Ts...> t) {
  constexpr size_t tp_sz 	= (sizeof...(Ts));
	static_assert(N<=tp_sz);
	return
		impl::take_front_impl<0>(
			t,
			make_index_sequence<N>{}
		);
  }

  template<class ... Ts>
  inline constexpr
  decltype(auto) tail(tuple<Ts...> t) {
	constexpr size_t tp_sz 	= (sizeof...(Ts));
	if constexpr (tp_sz<=1) {
		(void)t;
		return make_tuple();
	}
	else if constexpr (tp_sz==2) {
		return make_tuple(get<1>(t));
	}
	else {
		return
		impl::take_front_impl<1>(
			t,
			make_index_sequence<tp_sz-1>{}
		);
	}
  }

  template<class ... Ts>
  inline constexpr
  decltype(auto) btail(tuple<Ts...> t) {
	constexpr size_t tp_sz 	= (sizeof...(Ts));
	if constexpr (tp_sz==0) {
		(void)t;
		return make_tuple();
	}
	else if constexpr (tp_sz==1) {
		(void)t;
		return make_tuple();
	}
	else if constexpr (tp_sz==2) {
		return make_tuple(get<0>(t));
	}
	else {
		return
		impl::take_front_impl<0>(
			t,
			make_index_sequence<tp_sz-1>{}
		);
	}
  }

  template<size_t N,class ... Ts>
  inline constexpr
  decltype(auto) take_back(tuple<Ts...> t) {
	constexpr size_t tp_sz 	= (sizeof...(Ts));
	static_assert(N<=tp_sz);
	if constexpr (N==0) {
		(void)t;
		return make_tuple();
	}
	else if constexpr (N==1) {
		return
		make_tuple(
			get<tp_sz-1>(t)
		);
	}
	else if constexpr (N==2) {
		return
		make_tuple(
			get<tp_sz-2>(t),
			get<tp_sz-1>(t)
		);
	}
	else {
		return
		impl::take_front_impl<tp_sz-N>(
			t,
			make_index_sequence<N>{}
		);
	}
  }

  template<size_t N,size_t M,class ... Ts>
  inline constexpr
  decltype(auto) subtuple(tuple<Ts...> t) {
	constexpr size_t tp_sz 	= (sizeof...(Ts));
	if constexpr ((N<=tp_sz)&&(M<=tp_sz+1)&&(N<=M)) {
		if constexpr (N==M) {
			(void)t;
			return make_tuple();
		}
		else if constexpr (N+1==M) {
			return make_tuple(get<N>(t));
		}
		else if constexpr (N+2==M) {
			return
			make_tuple(
				get<N>(t)		,
					get<N+1>(t)
			);
		}
		else {
			return
			impl::take_front_impl<N>(
				t,
				make_index_sequence<M-N>{}
			);
		}
	}
	else {
		(void)t;
		return make_tuple();
	}
  }

  template<size_t N,class ... Ts>
  inline constexpr
  decltype(auto) remove_front(tuple<Ts...> t) {
	constexpr size_t tp_sz = (sizeof...(Ts));
	static_assert(N<=tp_sz);
	return
		impl::take_front_impl<N>(
			t,
			make_index_sequence<tp_sz-N>{}
	);
  }

  template<size_t N,class ... Ts>
  inline constexpr
  decltype(auto) remove_back(tuple<Ts...> t) {
	constexpr size_t tp_sz = (sizeof...(Ts));
	static_assert(N<=tp_sz);
	return impl::take_front_impl<0>(
		t,
		make_index_sequence<tp_sz-N>{}
	);
  }

  template<size_t N,size_t M,class ... Ts>
  inline constexpr
  decltype(auto) r_subtuple(tuple<Ts...> t) {
	constexpr size_t tp_sz 	= (sizeof...(Ts));
	static_assert(M<tp_sz);
	static_assert(N<=tp_sz+1);
	static_assert(M<=N);
	if constexpr (N==M) {
		(void)t;
		return make_tuple();
	}
	else if constexpr (M+1==N) {
		return
			make_tuple(get<M>(t));
	}
	else if constexpr (M+2==N) {
		return
			make_tuple(
				get<M+1>(t),
				get<M>(t)
			);
	}
	else {
		return
			impl::take_rfront_impl<M>(
				t,
				make_index_sequence<N-M>{}
			);
	}
  }

  template<class ... Ts>
  inline constexpr
  decltype(auto) reverse(tuple<Ts...> t) {
	constexpr size_t tp_sz = sizeof...(Ts);
	if constexpr (tp_sz==0) {
		(void)t;
		return make_tuple();
	}
	else if constexpr (tp_sz==1) {
		return t;
	}
	else {
		return
			impl::take_rfront_impl<0>(
				t,
				make_index_sequence<tp_sz>{}
		);
	}
  }

  template <class S, class ... Ts>
  inline constexpr
  decltype(auto) push_back(tuple<Ts...> t,S s) {
	return tuple_cat(t,make_tuple(s));
  }

  template <class S, class ... Ts>
  inline constexpr
  decltype(auto) push_front(tuple<Ts...> t,S s)	{
	return tuple_cat(make_tuple(s),t);
  }

  template <size_t N, class ... Ts>
  inline constexpr
  decltype(auto) swap_subtuples(tuple<Ts...> t) {
	constexpr size_t tp_sz{tuple_size_v<decltype(t)>};
	static_assert(N<tp_sz);
	return tuple_cat(remove_front<N>(t),take_front<N>(t));
  }

  template<class ...Ts,class ...Rs>
  tuple<tuple<Ts,Rs>...> spaces_product(
	tuple<Ts...> t,
	tuple<Rs...> r
	) {
	constexpr size_t sz_t{tuple_size_v<decltype(t)>};
	constexpr size_t sz_r{tuple_size_v<decltype(r)>};
	static_assert(sz_t==sz_r);
	return
		impl::spaces_product_impl(
			t,
			r,
			make_index_sequence<sz_t>()
		);
  }

  template<class ...Ts,class ...Rs,class ...Ss>
  tuple<tuple<Ts,Rs,Ss>...> spaces_product(
	tuple<Ts...> t,
	tuple<Rs...> r,
	tuple<Ss...> s
	) {
	constexpr size_t sz_t{
		tuple_size_v<decltype(t)>
	};
	constexpr size_t sz_r{
		tuple_size_v<decltype(r)>
	};
	constexpr size_t sz_s{
		tuple_size_v<decltype(s)>
	};
	static_assert(sz_t==sz_r);
	static_assert(sz_t==sz_s);
	return
		impl::spaces_product_impl(
			t,
			r,
			s,
			make_index_sequence<sz_t>{}
		);
  }

  template<
	typename	IntType,
	unsigned_for_signed_t<IntType>	...	Is,
	template<
		typename,
		unsigned_for_signed_t<IntType>
	>
		typename TT
  >
  inline constexpr
  auto
  build_tuple_from_list (
	const initializer_list<IntType> & lista
  )
  ->
	tuple<
		TT<
			unsigned_for_signed_t<IntType>,
			Is
		>
		...
	>
  {
	return
		impl::build_tuple_from_list_impl<
			IntType,
			Is...,
			TT
			> (
			lista,
			integer_sequence<
				unsigned_for_signed_t<IntType>,
				Is ...
				>{}
		);
  }
    
	template<
		typename UInt_t	    ,				// UIntType
		UInt_t ... Ns	    ,				// Modulos
		template<
			typename,						//   UIntType
			unsigned_for_signed_t<UInt_t>  	//   Modulo
		> typename TT,						// int_mod_N
		typename ... IntType_s				// types of the argument tuple
	>
	inline constexpr
	auto build_from_tuple_of_ints(
			tuple<IntType_s...> t
	)
	-> tuple<TT<unsigned_for_signed_t<UInt_t>,Ns>...>
	{
		using UUInt_t = unsigned_for_signed_t<UInt_t>;
		using tuple_ret_type = tuple<TT<UUInt_t,Ns>...>;
		constexpr size_t tup_ret_sz{tuple_size_v<tuple_ret_type>};
		using tuple_arg_type = tuple<IntType_s...>;
		constexpr size_t tup_arg_sz{tuple_size_v<tuple_arg_type>};
		static_assert(tup_ret_sz==tup_arg_sz);
		return 
			impl::build_from_tuple_of_ints_impl<
					UInt_t,
					Ns...,
					TT,
					IntType_s ...
				>(
					t,
					make_index_sequence<tup_ret_sz>{}
				);
	}
}
#endif // TUPLE_T_HPP_INCLUDED
