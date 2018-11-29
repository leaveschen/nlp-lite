//
// Created by c on 12/11/2018 11:56
//

#ifndef NLP_NETWORK_SYMBOL_HH
#define NLP_NETWORK_SYMBOL_HH

/* include section */

#include "utility/forward_declaration.hh"
#include "network/symbol_binary_op.hh"

/* class & function section */

namespace nlp {

/* basic symbol class,
 * define the interface here */
template<class Derived>
class Symbol {
public:
	/* type alias */
	using shape_t = typename detail::traits<Derived>::shape_t;
	//using storage_t = typename detail::traits<Derived>::storage_t;

	/* derived object */
	Derived& derived() { return static_cast<Derived&>(*this); }
	Derived const& derived() const { return static_cast<Derived const&>(*this); }

	/* interface method here, shape attribute */
	void set_shape(shape_t const& shape) { derived().shape() = shape; }
	shape_t get_shape() { return derived().shape(); }

	/* symbol operator */
	template<class OtherDerived>
	decltype(auto) operator+(OtherDerived const& other) const {
		/* TODO: check shape equality */
		return SymbolBinaryOp<SymbolBinaryAdd, Derived, OtherDerived>(static_cast<Derived const&>(*this), other);
	}

	template<class OtherDerived>
	decltype(auto) operator-(OtherDerived const& other) const {
		/* TODO: check shape equality */
		return SymbolBinaryOp<SymbolBinarySub, Derived, OtherDerived>(static_cast<Derived const&>(*this), other);
	}
};

} // namespace nlp

#endif//