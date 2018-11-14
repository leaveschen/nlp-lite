//
// Created by c on 12/11/2018 14:53
//

#ifndef NLP_NETWORK_VARIABLE_HH
#define NLP_NETWORK_VARIABLE_HH

/* include section */

#include "utility/forward_declaration.hh"
#include "network/symbol.hh"

/* class & function section */

namespace nlp {

namespace detail {

template<class Shape, class Storage>
struct traits< Variable<Shape, Storage> > {
	using shape_t = Shape;
	using storage_t = Storage;
};

} // namespace detail

template<class Shape, class Storage>
class Variable : public Symbol< Variable<Shape, Storage> > {
private:
	/* members */
	Shape shape_;
	Storage data_;

public:
	/* ctor & dtor */
	Variable() : data_(), shape_() {}
	~Variable() {}

	/* assign of symbol operator */
	template<class Sop>
	Variable& operator=(Sop const& sop) {
		shape_ = sop.lhs().shape();
		return *this;
	}

	/* shape attribute */
	Shape& shape() { return shape_; }
	Shape const& shape() const { return shape_; }
};

} // namespace nlp


#endif//