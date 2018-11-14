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

template<class Shape, class Storage, class ForwardOp, class BackwardOp>
struct traits< Layer<Shape, Storage, ForwardOp, BackwardOp> > {
	using shape_t = Shape;
	using storage_t = Storage;
	using forward_t = ForwardOp;
	using backward_t = BackwardOp;
};

} // namespace detail

template<class Shape, class Storage, class ForwardOp, class BackwardOp>
class Layer : public Symbol< Layer<Shape, Storage, ForwardOp, BackwardOp> > {
private:
	/* members */
	Shape shape_;
	Storage data_;
	ForwardOp forward_op_;
	BackwardOp backward_op_;

public:
	/* ctor & dtor */
	Layer() : data_(), shape_(), forward_op_(), backward_op_() {}
	~Layer() {}

	/* shape attribute */
	Shape& shape() { return shape_; }

	/* forward */
	template<class Var>
	void forward(Var input) { forward_op_.run(data_, input); }

	/* backward */
	template<class Var>
	void backward(Var input) { backward_op_.run(data_, input); }
};

} // namespace nlp

#endif//