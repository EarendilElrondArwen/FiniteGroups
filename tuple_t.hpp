#ifndef TUPLE_T_HPP_INCLUDED
#define TUPLE_T_HPP_INCLUDED

#include <cstdlib>
#include <cstdint>
#include <cmath>
#include <string>
#include <limits>
#include <array>
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
  using std::array;

  template<typename T>
  using initializer_list_it_t =
	const	typename
		initializer_list<T>::const_iterator;

	/// HEAD_AS_TUPLE_OF_ONE_ONLY_ELEMENT__THE_FIRST
  template<typename ... Ts>
  inline constexpr
  decltype(auto) head(const tuple<Ts...> t) {
	constexpr auto tp_sz{sizeof...(Ts)};
	if constexpr (tp_sz==0) {
		(void)t;
		return make_tuple();
	} else if constexpr (tp_sz==1) {
		return t;
	} else {
		return make_tuple(get<0>(t));
	}
  }
	
	/// HEAD_AS_ELEMENT__THE_FIRST
  template<typename T,typename ... Ts	>
  inline constexpr
  T head_value(const tuple<T,Ts...> t){
  	return get<0>(t);
  }
	/// ROOT_AS_TUPLE_OF_ONE_ONLY_ELEMENT__THE_LAST
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
	/// ROOT_AS_ELEMENT__THE_LAST
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
	/// TAKE THE FIRST N:0,1,...,N-1 ELEMENTS AS TUPLE
	/// LET N < TUPLE_SIZE_V<TUPLE>
  template<size_t N,class ... Ts>
  inline constexpr
  decltype(auto) take_front(tuple<Ts...> t) {
  constexpr size_t tp_sz 	= (sizeof...(Ts));
	static_assert(N<=tp_sz+1);
	return
		impl::take_front_impl<0>(
			t,
			make_index_sequence<N>{}
		);
  }
	/// TAKE THE ELEMENTS 1,...,N-1 ELEMENTS AS TUPLE
	/// THE ELEMENT 0 IS OFF, LET N BE TUPLE_SIZE_V<TUPLE>
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
	/// TAKE THE ELEMENTS 0,1,...,N-2 ELEMENTS AS TUPLE
	/// THE ELEMENT N-1 IS OFF, LET N BE TUPLE_SIZE_V<TUPLE>
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
	/// TAKE THE LATTER N ELEMENTS OF THE TUPLE AS TUPLE
	/// LET M == TUPLE_SIZE_V<TUPLE>
	/// REQUIREMENT: N<M
	/// TAKE THE ELEMENTS N,N+1,...,M-1 AS TUPLE
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
	/// TAKE THE RANGE FROM INDEX N ELEMENT TO INDEX M-1 AS TUPLE
	/// LET S == TUPLE_SIZE_V<TUPLE>
	/// REQUIREMENT: N<M<=S
	/// TAKE THE ELEMENTS N,N+1,...,M-1 AS TUPLE
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
	/// RETURN THE TUPLE EXCEPT THE N FIRSTS ELEMENTS
	/// LET S == TUPLE_SIZE_V<TUPLE>
	/// REQUIREMENT: N < S
	/// RETURN THE ELEMENTS N,N+1,...,S-1 AS TUPLE
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
	/// RETURN THE TUPLE EXCEPT THE N LATTER ELEMENTS
	/// LET S == TUPLE_SIZE_V<TUPLE>
	/// REQUIREMENT: N <= S-1
	/// RETURN THE ELEMENTS S-N-1,S-N-2,...,S-1 AS TUPLE
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
	/// RETURN THE REVERSE TUPLE OF SUBTUPLE M-N<-->M
	/// LET S == TUPLE_SIZE_V<TUPLE>
	/// REQUIREMENT: M <= N AND M <= S-1
	/// RETURN THE ELEMENTS M-1,M-2,...,M-N AS TUPLE
	/// RETURN THE ELEMENTS REVERSE(M-N,M-N+1,...,M-1) AS TUPLE
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
	/// RETURN THE REVERSE OF THE TUPLE
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
	/// RETURN THE TUPLE PLUS A NEW ELEMENT AS LAST ELEMENT
	/// LET S == TUPLE_SIZE_V<TUPLE>
	/// PUSH_BACK(Tuple Tup,R r) == tuple(0,1,2,...,S-1,S)
	/// WHERE THE ELEMENT AT POSITION S IS r OF R TYPE
  template <class S, class ... Ts>
  inline constexpr
  decltype(auto) push_back(tuple<Ts...> t,S s) {
	return tuple_cat(t,make_tuple(s));
  }
	/// RETURN THE TUPLE PLUS A NEW ELEMENT AS FIRST ELEMENT
	/// LET S == TUPLE_SIZE_V<TUPLE>
	/// PUSH_FRONT(Tuple Tup,R r) == tuple(0,1,2,...,S-1,S)
	/// WHERE THE ELEMENT AT POSITION 0 IS r OF R TYPE
  template <class S, class ... Ts>
  inline constexpr
  decltype(auto) push_front(tuple<Ts...> t,S s)	{
	return tuple_cat(make_tuple(s),t);
  }
	/// DIVIDE THE TUPLE IN 2 TUPLES AND MAKE A NEW TUPLE SWAPING THE TWO PARTS
	/// LET S BE THE LENGTH OF TUPLE
	/// TUPLE IS Tuple t
	/// LENGTH OF TUPLE IS S == tuple_size_v<t>
	/// N marks THE POINT OF DIVISION
	/// RETURN THE ELEMENTS OF INDEX N,N+1,...,S-1,0,1,2,...,N-1 AS NEW TUPLE
  template <size_t N, class ... Ts>
  inline constexpr
  decltype(auto) swap_subtuples(tuple<Ts...> t) {
	constexpr size_t tp_sz{tuple_size_v<decltype(t)>};
	static_assert(N<tp_sz);
	return tuple_cat(remove_front<N>(t),take_front<N>(t));
  }
	///
	///
	///
	///
	///
	///
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
	
	template <
		typename UIntType,
		template<typename,UIntType,UIntType...> class TT,
		UIntType Actual,
		UIntType OnePastLast,
		UIntType Mod_0,
		UIntType ... Mods
	>
	struct simple_static_for_fill {
		static_assert(
				(Actual <= OnePastLast),
				"Rango ascendente mal disenhado o "
				"indice actual fuera de rango"
		);
		static constexpr auto mod_tup{make_tuple(Mod_0,Mods...)};
		static constexpr size_t dim{1+(sizeof...(Mods))};
		static constexpr size_t card{Mod_0*((Mods)*...)}; 
		
		using Array_T = array<TT<UIntType,Mod_0,Mods...>,card>;
		using Arg_2_T = TT<UIntType,Mod_0,Mods...>;
		
		template<UIntType IX>
		inline static constexpr
		Arg_2_T Fill(Array_T array_obj,Arg_2_T temp=Arg_2_T{}) {
			if constexpr (IX==0) {
				constexpr Arg_2_T arg{};
				array_obj[0]=arg;
				return arg.next();
			}
			else {
				array_obj[IX]=temp;
				return temp.next();
			}
		}
		
		inline static constexpr
		Array_T recursive(Array_T array_arg_1=Array_T{},Arg_2_T arg_2=Arg_2_T{}) {
			if constexpr (Actual < OnePastLast) {
				auto arg_3{Fill<Actual>(array_arg_1,arg_2)};
				simple_static_for_fill<
					UIntType,
					TT,
					Actual+1,
					OnePastLast,
					Mod_0,
					Mods...
				>::recursive(array_arg_1,arg_3);
			}
			else {return array_arg_1;}
		}
	};
	
	template <
		typename UIntType,
		UIntType Actual,
		UIntType OnePastLast,
		template<typename,UIntType> class TT,
		UIntType Mod_0,
		UIntType ... Mods
	>
	struct simple_static_for_decr {
		static_assert(
				(Actual <= OnePastLast),
				"Rango ascendente mal disenhado o "
				"indice actual fuera de rango"
		);
		static constexpr auto mod_tup{make_tuple(Mod_0,Mods...)};
		static constexpr size_t dim{1+(sizeof...(Mods))}; 
		
		template<size_t Ix>
		inline static constexpr
		UIntType mod_idx() { return get<Ix>(mod_tup);}
		
		template<UIntType I> using
		TT_idx = TT<UIntType,mod_idx<I>()>;
		
		using Tuple_1_T = tuple<TT<UIntType,Mod_0>,TT<UIntType,Mods>...>;
		using Tuple_2_T = array<bool,dim+1>;
		
		template<UIntType IX>
		inline static constexpr
		void DigitDecr(Tuple_1_T& tup_obj,Tuple_2_T& temp) {
			if constexpr (IX==0) {
				if (get<IX>(tup_obj).is_not_0()) {
					--get<IX>(tup_obj);
					get<IX+1>(temp)	= false;
				}
				else {
					get<IX>(tup_obj).selfwrite_max();
					get<IX+1>(temp)  	 = true;
				}
			} else {
				if (get<IX>(temp)) {
					if (get<IX>(tup_obj).is_not_0()) {
						--get<IX>(tup_obj);
						get<IX+1>(temp)		 =	false;
					} else {
						get<IX>(tup_obj).selfwrite_max();
						get<IX+1>(temp) 	=	true;
					}
					
				} else {
					get<IX+1>(temp)		=	false;
				}
			}
		}
		
		inline static constexpr
		void recursive(Tuple_1_T & tuple_arg_1,Tuple_2_T & tuple_arg_2) {
			if constexpr (Actual <= OnePastLast-1) {
				DigitDecr<Actual>(tuple_arg_1,tuple_arg_2);
				simple_static_for_decr<
					UIntType,
					Actual+1,
					OnePastLast,
					TT,
					Mod_0,
					Mods...
				>::recursive(tuple_arg_1,tuple_arg_2);
			} else {}
		}
	};
		
	template <
		typename UIntType,
		UIntType Actual,
		UIntType OnePastLast,
		template<typename,UIntType> class TT,
		UIntType Mod_0,
		UIntType ... Mods
	>
	struct simple_static_for_incr {
		static_assert(
				(Actual <= OnePastLast),
				"Rango ascendente mal disenhado o "
				"indice actual fuera de rango"
		);
		static constexpr auto mod_tup{make_tuple(Mod_0,Mods...)};
		static constexpr size_t dim{1+(sizeof...(Mods))}; 
		
		template<size_t Ix>
		inline static constexpr 
		UIntType mod_idx() { return get<Ix>(mod_tup);}
		
		template<UIntType I> using
		TT_idx = TT<UIntType,mod_idx<I>()>;
		
		using Tuple_1_T = tuple<TT<UIntType,Mod_0>,TT<UIntType,Mods>...>;
		using Tuple_2_T = array<bool,dim+1>;
		
		template<UIntType IX>
		inline static constexpr
		void DigitIncr(Tuple_1_T& tup_obj,Tuple_2_T& temp) {
			if constexpr (IX==0) {
				if (get<IX>(tup_obj).is_not_max()) {
					++get<IX>(tup_obj);
					get<IX+1>(temp)		= false;
				}
				else {
					get<IX>(tup_obj).selfwrite_0();
					get<IX+1>(temp) 	 = true;
				}
			}
			else {
				if (get<IX>(temp)) {
					if (get<IX>(tup_obj).is_not_max()) {
						++get<IX>(tup_obj);
						get<IX+1>(temp)		 =	false;
					} else {
						get<IX>(tup_obj).selfwrite_0();
						get<IX+1>(temp) 	=	true;
					}
				} else {
					get<IX+1>(temp)		=	false;
				}
			}
		}
		
		inline static constexpr
		void recursive(Tuple_1_T & tuple_arg_1,Tuple_2_T & tuple_arg_2) {
			if constexpr (Actual <= OnePastLast-1){
				DigitIncr<Actual>(tuple_arg_1,tuple_arg_2);
				simple_static_for_incr<
					UIntType,
					Actual+1,
					OnePastLast,
					TT,
					Mod_0,
					Mods...
				>::recursive(tuple_arg_1,tuple_arg_2);
			} else {}
		}
	};
/*	
	/////////////////////////////////////////////////////////////
	/////////////////////////////////////////////////////////////
	//////  TRATAMIENTO DE LOS ARGUMENTOS EN UNA FUNCION   //////
	/////////////////////////////////////////////////////////////
	/////////////////////////////////////////////////////////////
	
	/// El argumento de posicion "I" es un elemento destacado del tipo "T", "arg_I == id"
	template<size_t I,typename S,typename T0,typename ... Ts>
	inline constexpr
	bool _id_(S Id,T0 t0,Ts ... ts) {
		if constexpr (I==0) {
			const bool result{(t0==Id)};
			return result;
		} else {
			const auto arg_tuple{make_tuple(ts...)};
			const bool result{((get<I-1>(arg_tuple))==Id)};
			return result;
		}
	}
	
	/// Para Todo argumento : argumento es la identidad
	template<typename S,typename T0,typename ... Ts>
	constexpr 
	bool all_id(S Id,T0 t0,Ts ... ts) {
		const bool result{((t0 == Id)&&((ts == Id)&&...&&true))};
		return result;
	}
	
	/// Existe argumento : argumento no es la identidad
	template<typename S,typename T0,typename ... Ts>
	constexpr
	bool some_notid(S Id,T0 t0,Ts ... ts) {
		const bool result{((t0 != Id)||((ts != Id)||...||false))};
		return result;
	}
	
	/// Existe argumento : argumento es la identidad
	template<typename S,typename T0,typename ... Ts>
	constexpr
	bool some_id(S Id,T0 t0,Ts ... ts) {
		const bool result{((t0 == Id)||((ts == Id)||...||false))};
		return result;
	}
	
	/// Para Todos argumento : argumento no es la identidad
	template<typename S,typename T0,typename ... Ts>
	constexpr 
	bool nothing_id(S Id,T0 t0,Ts ... ts) {
		const bool result{((t0 != Id)&&((ts != Id)&&...&&true))};
		return result;
	}
	
	/// Aplicar la función "f" solo a los ultimos "N" argumentos de la lista
	/// identico a f(arg_(N),...,arg_(tuple_size(args)))
	/// Pasamos de 
	/// f(arg_(0),arg_(1),...,arg_(M-1))
	/// a
	/// f(arg_(N),arg_(N+1),...,arg_(M-1))
	/// f devuelve bool
	template<size_t N,typename F,typename T0, typename ...Ts>
	constexpr 
	bool
	take_back_args(F f,T0 t0,Ts ... ts) {
		if constexpr (N==0) {
			const auto object{make_tuple(t0,ts...)};
			return apply(f,object);
		} else if constexpr (N==1) {
			const auto object{make_tuple(ts...)};
			return apply(f,object);
		} else {
			const auto object{take_back<N,t0,ts...>(make_tuple(t0,ts...))};
			return apply(f,object);
		}
	}
	
	/// Aplicar la función "f" solo a los primeros "N" argumentos de la lista
	/// identico a f(arg_(0),...,arg_(N-1))
	/// Pasamos de 
	/// f(arg_(0),arg_(1),...,arg_(M-1))
	/// a
	/// f(arg_(0),arg_(1),...,arg_(N-1)) con N <= M
	/// f devuelve bool
	template<size_t N,typename F,typename T0, typename ...Ts>
	constexpr
	bool
	take_front_args(F f,T0 t0,Ts ... ts) {
		if constexpr (N == 0) {
			return f(t0);
		} else if constexpr (N == 1) {
			const auto h{head_value<Ts...>(make_tuple(ts...))};
			return f(h);
		} else {
			const auto init_object{make_tuple(t0,ts...)};
			const auto final_object{take_front<N,T0,Ts...>(init_object)};
			return apply(f,final_object);
		}
	}
	
	/// El primer argumento es diferente de todos los siguientes
	template<typename T0,typename ... Ts>
	inline constexpr 
	bool neq_from_0(T0 t0,Ts ... ts) {
		return ((t0!=ts)&&...&&true);
	}
	
	/// El primer argumento es igual a alguno de los siguientes
	template<typename T0,typename ... Ts>
	inline constexpr
	bool eq_from_0(T0 t0,Ts ... ts) {
		return ((t0!=ts)||...||false);
	}
	
	/// Cogemos el argumento "I" y los "N,N+1,...,N+K-1" en una tupla
	/// Donde "I < N" y "N+K-1 < numero_de_argumentos"
	/// Devuelve los argumentos de indices I,N,N+1,...,N+K-1 a la funcion f 
	/// f devuelve bool
	/// f es la funcion que da true si todos los argumentos son distinto
	/// en valor del primero : neq_from_0
	template<size_t I,size_t N,size_t K,typename T0, typename ...Ts>
	inline constexpr 
	bool
	all_from_N_to_NpK_neq_I(T0 t0,Ts ... ts) {
		static_assert(I<N);
		static_assert(N+K < (sizeof...(Ts))+2);
		if constexpr ((I==0)&&(N==1)&&(K==(sizeof...(Ts)-1))) {
			return neq_from_0(t0,ts...);
		} else if constexpr((I==1)&&(N==2)&&(K==(sizeof...(Ts)-2))) {
			return neq_from_0(ts...);
		} else if constexpr((N==I+1)&&(K==(sizeof...(Ts)-I-1))) {
			const auto temp_object_tt{make_tuple(t0,ts...)};
			const auto arg_tuple{take_back<I>(temp_object_tt)};
			return apply(neq_from_0,arg_tuple);
		} else if constexpr (N==I+1) {
			const auto temp_object_tt{make_tuple(t0,ts...)};
			const auto arg_back{take_back<I>(temp_object_tt)};
			const auto arg_tuple{take_front<K+1>(arg_back)};
			return apply(neq_from_0,arg_tuple);
		} else {
			const auto temp_object_tt{make_tuple(t0,ts...)};
			const auto arg_head{make_tuple(get<I>(temp_object_tt))};
			const auto temp_arg_back{take_back<N,T0,Ts...>(temp_object_tt)};
			const auto arg_tail{take_front<K>(temp_arg_back)};
			const auto arg_tuple{tuple_cat(arg_head,arg_tail)};
			return apply(neq_from_0<T0,Ts...>,arg_tuple);
		}
	}
	
	/// Cogemos el argumento "I" y los "N,N+1,...,N+K-1" en una tupla
	/// Donde "I<N" y "N+K-1 < numero_de_argumentos"
	/// f devuelve bool
	/// f es la funcion que da true si alguno de los argumentos es igual
	/// en valor que el primero : eq_from_0
	template<size_t I,size_t N,size_t K,typename T0, typename ...Ts>
	inline constexpr 
	bool
	some_from_N_to_NpK_eq_I(T0 t0,Ts ... ts) {
		static_assert(I > N);
		static_assert(N+K <= (sizeof...(Ts))+2);
		if constexpr (N==0) {
			const auto object_tt{make_tuple(t0,ts...)};
			const auto arg_head{make_tuple(get<I>(object_tt))};
			const auto arg_tail{take_front<K,T0,Ts...>(object_tt)};
			const auto arg_tuple{tuple_cat(arg_head,arg_tail)};
			return apply(eq_from_0,arg_tuple);
		} else if constexpr (N==1) {
			const auto object_tt{make_tuple(t0,ts...)};
			const auto arg_head{make_tuple(get<I>(object_tt))};
			const auto arg_tail{tail<T0,Ts...>(object_tt)};
			const auto arg_tuple{tuple_cat(arg_head,arg_tail)};
			return apply(eq_from_0,arg_tuple);
		} else {
			const auto object_tt{make_tuple(t0,ts...)};
			const auto arg_head{make_tuple(get<I>(object_tt))};
			const auto temp_arg_back{take_back<N,T0,Ts...>(object_tt)};
			const auto arg_tail{take_front<K>(temp_arg_back)};
			const auto arg_tuple{tuple_cat(arg_head,arg_tail)};
			return apply(eq_from_0,arg_tuple);
		}
	}
	
	/// El argumento "I" es diferente de los "N,N+1,...,N+K-1"
	/// Donde "I < N" y "N+K-1 < numero_de_argumentos"
	template<size_t I,size_t N,size_t K,typename T0,typename ... Ts>
	inline constexpr
	bool neq_from(T0 t0,Ts ... ts) {
		static_assert(I<N);
		static_assert((N+K) < ((sizeof...(Ts))+2));
		const bool result{all_from_N_to_NpK_neq_I<I,N,K,T0,Ts...>(t0,ts...)};
		return result;
	}
	
	/// El argumento "I" es igual a alguno de los "N,N+1,...,N+K-1"
	/// Donde "I < numero_de_argumentos" y "N+K-1 < I"
	template<size_t I,size_t N,size_t K,typename T0,typename ... Ts>
	inline constexpr
	bool equal_from(T0 t0,Ts ... ts) {
		static_assert(N+K-1 < I);
		static_assert(I < ((sizeof...(Ts))+2));
		return some_from_N_to_NpK_eq_I<I,N,K,T0,Ts...>(t0,ts...);
	}
	
	template<size_t N,typename T0,typename ... Ts,size_t ... Is>
	inline constexpr
	bool neq_firsts_IMPL(T0 t0,Ts ... ts,std::index_sequence<Is...>) {
		return ((neq_from<Is,Is+1,N-Is,T0,Ts...>(t0,ts...))&&...);
	}
	
	/// Los primeros "N" argumentos son distintos entre si
	/// arg_0,arg_1,...,arg_(N-1)
	/// Donde "N-1 < numero_de_argumentos"
	template<size_t N,typename T0,typename ... Ts>
	inline constexpr
	bool neq_firsts(T0 t0,Ts ... ts) {
		return neq_firsts_IMPL<0,T0,Ts...>(t0,ts...,std::make_index_sequence<N>{});
	}
	
	template<size_t I,size_t N,typename T0,typename ... Ts,size_t ... Is>
	inline constexpr
	bool equal_to_some_firsts_IMPL(T0 t0,Ts ... ts,std::index_sequence<Is...>) {
		return ((equal_from<I,1,Is+1,T0,Ts...>(t0,ts...))||...);
	}
	
	/// El argumento "I" es igual a alguno de los primeros "N" argumentos
	/// arg_0,arg_1,...,arg_(N-1)
	/// Donde "N-1 < numero_de_argumentos"
	template<size_t I,size_t N,typename T0,typename ... Ts>
	inline constexpr
	bool equal_to_some_firsts(T0 t0,Ts ... ts) {
		return equal_to_some_firsts_IMPL<I>(t0,ts...,std::make_index_sequence<N+1>{});
	}
	
	template<size_t I,size_t N,typename S,typename T0,typename ... Ts,size_t ... Is>
	inline constexpr
	bool equal_to_some_firsts_or_id_IMPL(S Id,T0 t0,Ts ... ts,std::index_sequence<Is...>) {
		return ((equal_from<I,1,Is+1,T0,Ts...>(t0,ts...)||...||false)||(_id_<I,S,T0,Ts...>(Id,t0,ts...)));
	}
	
	/// El argumento "I" es igual a alguno de los primeros "N" argumentos o es "id"
	/// arg_0,arg_1,...,arg_(N-1)
	/// Donde "N-1 < numero_de_argumentos"
	template<size_t I,size_t N,typename S,typename T0,typename ... Ts>
	inline constexpr
	bool equal_to_some_firsts_or_id(S Id,T0 t0,Ts ... ts) {
		return (equal_to_some_firsts_or_id_IMPL<I,N,S,T0,Ts...>(Id,t0,ts...,std::make_index_sequence<N>{}));
	}
	
	template<size_t N,typename S,typename T0,typename ... Ts,size_t ... Is>
	inline constexpr
	bool all_latter_equal_to_some_firsts_or_id_IMPL(S Id,T0 t0,Ts ... ts,std::index_sequence<Is...>) {
		return ((equal_to_some_firsts_or_id<Is+N,N>(Id,t0,ts...))&&...);
	}
	
	/// Los argumentos a partir del "N" inclusive 
	/// son cada uno igual a alguno de los primeros "N" argumentos o es "id"
	/// para todos los ultimos.
	/// ((arg_N != arg_0) OR ... OR (arg_N != arg_(N-1))  OR (arg_N == id))
	/// AND
	/// ...
	/// AND
	/// ((arg_(M-1)) != arg_0) OR ... OR (arg_(M-1)) != arg_(N-1))  OR (arg_(M-1)) == id))
	/// Donde "N-1 < numero_de_argumentos" Y "M == numero_de_argumentos"
	
	template<size_t N,typename S,typename T0,typename ... Ts>
	inline constexpr 
	bool all_latter_equal_to_some_firsts_or_id(S Id,T0 t0,Ts ... ts) {
		return all_latter_equal_to_some_firsts_or_id_IMPL<N,S,T0,Ts...>(Id,t0,ts...,std::make_index_sequence<((sizeof...(Ts))+2)-N>{});
	}
	
	/// Solo los primeros "N" argumentos son distintos entre si y de la "id"
	/// Los siguientes (si los hubiera) son iguales a alguno de los "N" primeros
	/// o son iguales a la identidad "id"
	/// "N > 1" y "N <= (sizeof...(Ts))+1"
	template<unsigned N,typename S,typename T0,typename ... Ts>
	constexpr
	bool exactly(S Id,T0 t0,Ts ... ts) {
		return (all_latter_equal_to_some_firsts_or_id<N>(Id,t0,ts...) && neq_firsts<N>(t0,ts...));
	}
*/	
}
#endif // TUPLE_T_HPP_INCLUDED
