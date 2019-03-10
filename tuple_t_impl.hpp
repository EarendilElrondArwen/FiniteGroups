// *** ADDED BY HEADER FIXUP ***
#include <istream>
// *** END ***
#ifndef TUPLE_T_IMPL_HPP_INCLUDED
#define TUPLE_T_IMPL_HPP_INCLUDED

#include <iostream>
#include <cstdlib>
#include <cstdint>
#include <cmath>
#include <string>
#include <limits>
#include <utility>
#include <type_traits>
#include <tuple>
#include <string>
#include <string_view>
#include <optional>
#include <functional>
#include <initializer_list>

#include "basic_types_metaprogramming_on_integers_types.hpp"
#include "factoring_ct.hpp"

namespace tfg::impl {
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
	using std::function;
	using std::bind;
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
    using	initializer_list_it_t =	typename
		initializer_list<T>::const_iterator;

	template<
		size_t Offset,
		class ... Ts,
		size_t... Is	>
	inline constexpr
	decltype(auto) take_front_impl(
			tuple<Ts...> t,
			index_sequence<Is...>
		) {
		constexpr size_t tp_sz 	= (sizeof...(Ts));
		constexpr size_t ix_sz 	= (sizeof...(Is));
		static_assert(ix_sz<=tp_sz);
		static_assert((((Is+Offset)<tp_sz)&&...));
		if constexpr (ix_sz==0)	{
			(void)t;
			return make_tuple();
		}
		else if constexpr (ix_sz==1) {
			return make_tuple(get<Offset>(t));
		}
		else if constexpr (ix_sz==tp_sz) {
			return t;
		}
		else {
			return
				make_tuple(
						get<Offset+Is>(t)...
				);
		}
	}

	template<
		size_t Offset	,
		class ... Ts	,
		size_t ... Is	>
	inline constexpr
	decltype(auto)
	take_rfront_impl(
			tuple<Ts...> t,
			index_sequence<Is...>
		)	{
		constexpr size_t tp_sz = (sizeof...(Ts));
		constexpr size_t ix_sz = (sizeof...(Is));
		static_assert(ix_sz<=tp_sz);
		static_assert((((Offset+Is)<tp_sz)&&...));
		static_assert((((Offset+Is)>=0)&&...));
		if constexpr (ix_sz==0) {
			(void)t;
			return make_tuple();
		}
		else if constexpr (ix_sz==1) {
			return
				make_tuple(
					get<tp_sz-Offset-1>(t)
				);
		}
		else {
			return
				make_tuple(
					get<
						tp_sz-(Offset+Is)-1
					>(t)...
				);
		}
	}

	template<	class ...Ts	,
				class ...Rs	,
				size_t ...Is>
	tuple<tuple<Ts,Rs>...> spaces_product_impl (
			tuple<Ts...> t,
			tuple<Rs...> r,
			index_sequence<Is...>
		) {
		constexpr size_t tp_sz{sizeof...(Ts)};
		constexpr size_t tp_r_sz{sizeof...(Rs)};
		constexpr size_t ix_sz{sizeof...(Is)};
		static_assert(tp_sz==tp_r_sz);
		static_assert(ix_sz<=tp_sz);
		static_assert(((Is<tp_sz)&&...));
		if constexpr (ix_sz==0) {
			(void)t;
			(void)r;
			return make_tuple(make_tuple());
		}
		else if constexpr (ix_sz==1) {
			return make_tuple(
				make_tuple(get<0>(t),get<0>(r))
			);
		}
		else {
			return
				make_tuple(
					make_tuple(
							get<Is>(t),
							get<Is>(r)
						)
						...
				);
		}
	}

	template<
		class ...Ts,
		class ...Rs,
		class ...Ss,
		size_t ...Is >
	tuple<tuple<Ts,Rs,Ss>...> spaces_product_impl(
		tuple<Ts...> t,
		tuple<Rs...> r,
		tuple<Ss...> s,
		index_sequence<Is...>
		) {
		constexpr size_t tp_sz{sizeof...(Ts)};
		constexpr size_t tp_r_sz{sizeof...(Rs)};
		constexpr size_t tp_s_sz{sizeof...(Ss)};
		constexpr size_t ix_sz{sizeof...(Is)};
		static_assert(tp_sz==tp_r_sz);
		static_assert(tp_sz==tp_s_sz);
		static_assert(ix_sz<=tp_sz);
		static_assert(((Is<tp_sz)&&...));
		if constexpr (ix_sz==0)	{
			return
				make_tuple(make_tuple());
		}
		else if constexpr (ix_sz==1) {
			return
				make_tuple(
					make_tuple(
						get<0>(t),
						get<0>(r),
						get<0>(s)
					)
				);
		}
		else {
			return
				make_tuple(
					make_tuple(
						get<Is>(t),
						get<Is>(r),
						get<Is>(s)
					)
					...
				);
		}
	}

	template<
		class ... Ts,
		size_t... Is	>
	inline constexpr
	ostream& show_elements_impl(
		ostream& 		os				,
		tuple<Ts...> 	t				,
		index_sequence<Is...>
		)	{
		constexpr size_t tp_sz 	= sizeof...(Ts);
		constexpr size_t ix_sz 	= sizeof...(Is);
		static_assert(ix_sz<=tp_sz);
		static_assert(((Is < tp_sz)&&...));
		os << "(";
		if constexpr (tp_sz>1) {
			((os << get<Is>(t) << ","),...);
		}
		else if constexpr (tp_sz==1) {
			((os << get<Is>(t)),...);
		}
		else {
			(void)t;
		}
		(void)t;
		return os;
	}

	template <
		uint First,
		uint Actual,
		uint Last	>
	struct static_for {
		static_assert(
				(First <= Actual)&&(Actual <= Last),
				"Rango ascendente mal diseñado o "
				"indice actual fuera de rango"
		);

		template <
			typename Fn,
			typename Tuple_T,
			typename UInt_Type
		>
		inline constexpr
		void operator()(
			const Fn & fn,
			Tuple_T & tuple_arg,
			initializer_list_it_t<UInt_Type> it_begin,
			initializer_list_it_t<UInt_Type> it_end
		) const {
			if constexpr (
					(First <= Actual)				&&
					(Actual < Last)					&&
					((it_begin+Actual) != it_end)
				) {
					fn(tuple_arg,it_begin+Actual);
					static_for<First, Actual+1, Last>()(
						fn,
						tuple_arg,
						it_begin,
						it_end
					);
			}
			else if constexpr (
					(First <= Actual)				&&
					(Actual == Last)				&&
					(it_begin+Actual==it_end)
			) {}
			else {
				static_assert(
					true,
					"Error: \"First\" es mayor que \"Last\" o"
					" \"Actual\" es mayor que \"Last\" o"
					" \"Actual\" es menor que \"First\" o"
					" \"it_begin+Actual\" es distinto a"
					" \"it_end\" "
				);
			}
		}
	};

	template<
		typename	IntType,
		unsigned_for_signed_t<IntType>...Is,
		template<
			typename,
			unsigned_for_signed_t<IntType>
		> typename TT
	>
	inline constexpr
	auto build_tuple_from_list_impl(
			const initializer_list<IntType> & lista,
			index_sequence<Is...>()
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
		constexpr size_t ListSz{lista.size()};
		constexpr size_t Sz{sizeof...(Is)};
		static_assert(
				ListSz==Sz,
				"No coinciden las longitudes de las listas "
				"de módulos y de valores-argumentos"
		);
		constexpr
			initializer_list_it_t<IntType>
				it_first{lista.begin()};
		constexpr
			initializer_list_it_t<IntType>
				it_last{lista.end()};
		constexpr static_for<0,0,Sz> for_loop{};
		constexpr auto
			tup_of_mods{make_tuple(Is...)};
		tuple<TT<IntType,Is>...> another_tuple{};
		auto asignation_to_one_elem_of_tuple =
		[tup_of_mods](
			tuple<
				TT<
					unsigned_for_signed_t<IntType>,Is
				>
				...
			>
				other_tup,
			size_t
				actual_N,
			initializer_list_it_t<IntType>
				list_it_begin,
			initializer_list_it_t<IntType>
				list_it_end
		) -> void
		{
				std::get<actual_N>(other_tup)	=
					TT<
							IntType,
							std::get<actual_N>(tup_of_mods)
					>(*(list_it_begin+actual_N));
		};
		for_loop(
			asignation_to_one_elem_of_tuple,
			another_tuple,
			it_first,
			it_last
		);
		return another_tuple;
	}
}

#endif // TUPLE_T_IMPL_HPP_INCLUDED
