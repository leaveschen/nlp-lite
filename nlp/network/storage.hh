//
// Created by c on 14/11/2018 11:31
//

#ifndef NLP_NETWORK_STORAGE_HH
#define NLP_NETWORK_STORAGE_HH

/* include section */

#include "utility/forward_declaration.hh"

/* class & function section */

namespace nlp {

/* basic storage class,
 * define the interface here */
template<class Derived>
class Storage {
public:
	/* type alias */
	using data_t = typename detail::traits<Derived>::data_t;

	/* derived object */
	Derived& derived() { return static_cast<Derived&>(*this); }
	Derived const& derived() const { return static_cast<Derived const&>(*this); }

	/* interface, data attribute */
	// TODO: implement move_to_data function for avoiding copy data
	void set_data(data_t const& data) { derived().data() = data; }
	data_t& get_data() { return derived().data(); }
	data_t const& get_data() const { return derived().data(); }
};

} // namespace nlp

#endif//