//
// Created by c on 07/11/2018 19:13
//

#ifndef NLP_NETWORK_OPERATOR_HH
#define NLP_NETWORK_OPERATOR_HH

/* include section */

#include "utility/forward_declaration.hh"

/* class & function section */

namespace nlp {

/* generic forward operator class */
template<class Derived>
class OperatorForward {
public:
	/* type alias */
	using content_t = typename detail::traits<Derived>::content_t;
	using input_t = typename detail::traits<Derived>::input_t;
	using output_t = typename detail::traits<Derived>::output_t;

	/* derived object */
	Derived& derived() { return static_cast<Derived&>(*this); }
	Derived const& derived() const { return static_cast<Derived const&>(*this); }

	/* interface */
	void run(content_t const& content, input_t const& input, output_t& output) {
		derived().run_impl(content, input, output);
	}

	output_t run(content_t const& content, input_t const& input) {
		output_t output;
		derived().run_impl(content, input, output);
		return output;
	}
};


/* generic backward operator class */
template<class Derived>
class OperatorBackward {
public:
	/* derived object */
	Derived& derived() { return static_cast<Derived&>(*this); }
	Derived const& derived() const { return static_cast<Derived const&>(*this); }

	/* interface */
	//template<class Lhs, class Rhs>
	//void run(Lhs const& lhs, Rhs const& rhs) {}
};

} // namespace nlp

#endif//