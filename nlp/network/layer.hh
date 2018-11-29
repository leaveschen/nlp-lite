//
// Created by c on 07/11/2018 19:05
//

#ifndef NLP_NETWORK_LAYER_HH
#define NLP_NETWORK_LAYER_HH

/* include section */

#include "utility/forward_declaration.hh"
#include "network/symbol.hh"

/* class & function section */

namespace nlp {

namespace detail {

template<class Shape>
struct traits< Layer<Shape> > {
	using shape_t = Shape;
};

} // namespace detail

template<class Shape>
class Layer : public Symbol< Layer<Shape> > {
private:
	/* members */
	Shape shape_;

public:
	/* ctor & dtor */
	Layer() : shape_() {}
	~Layer() {}

	/* shape attribute */
	Shape& shape() { return shape_; }
};

} // namespace nlp

#endif//