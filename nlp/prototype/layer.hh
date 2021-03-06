//
// Created by c on 29/11/2018 11:49
//

#ifndef NLP_PROTOTYPE_DENSE_HH
#define NLP_PROTOTYPE_DENSE_HH

/* include section */

#include <iostream>
using std::cout;

/* class & function section */

namespace nlp {

namespace prototype {

/* layer base class */
class LayerBase {};

/* dense layer class */
//template<class Matrix, class Loss>
// TODO: seperate the class Loss and move into optimizer
template<class Matrix, class Activation, class Optimazer>
class Dense {
public:
	/* type alias */

public:
	/* members */
	Matrix param_;
	Optimazer optimizer_;

public:
	/* ctor & dtor */
	Dense(size_t input_dim, size_t output_dim) : param_(input_dim, output_dim) {
		//param_.setZero(); // must done here, for eigen deduction
		param_.setRandom();
		//param_ *= 0.01;
		optimizer_.initialize();
	}
	Dense(Dense const&) = delete;
	Dense& operator=(Dense const&) = delete;
	~Dense() {}

	/* interface */
	template<class In, class Out>
	void forward(In const& forward_in, Out& forward_out) {
		forward_out = forward_in * param_;
		Activation::forward(forward_out);
	}

	template<class ForwardIn, class ForwardOut, class BackwardIn, class BackwardOut>
	void backward(ForwardIn const& fin, ForwardOut const& fout,
			BackwardIn const& bin, BackwardOut& bout) {
		/* bin: as the gradient back propagated from the next layer */
		// activation backward
		Activation::backward(bin);

		// calculate residual
		bout = bin * param_.transpose(); // XXX: ???

		// update parameters
		optimizer_.compute(fin, bin, param_);
	}

	template<class ForwardIn, class ForwardOut, class BackwardIn, class BackwardOut>
	void backward(ForwardIn const& fin, ForwardOut const& fout,
		BackwardIn const& bin, BackwardOut& bout, float lr) {
		Activation::backward(bin);
		bout = bin * param_.transpose();
		optimizer_.compute(fin, bin, param_, lr);
	}

	template<class ForwardIn, class ForwardOut, class BackwardIn>
	void backward(ForwardIn const& fin, ForwardOut const& fout, BackwardIn& bin) {
		// backward without calculating the backward output
		//cout << bin.rows() << "," << bin.cols() << "\n";
		//bin = bin.array().cwiseMax(0.0);
		Activation::backward(bin);
		optimizer_.compute(fin, bin, param_);
	}

	template<class ForwardIn, class ForwardOut, class BackwardIn>
	void backward(ForwardIn const& fin, ForwardOut const& fout, BackwardIn& bin, float lr) {
		Activation::backward(bin);
		optimizer_.compute(fin, bin, param_, lr);
	}

	/*
	template<class ForwardIn, class ForwardOut, class BackwardIn, class BackwardOut>
	void forward_backward(ForwardIn const& fin, ForwardOut& fout,
			BackwardIn const& bin, BackwardOut& bout) {
		// forward
		forward(fin, fout);
		//cout << "param:\n" << param_ << "\n";
		//cout << "fout:\n" << fout << "\n";

		// compute gradient
		ForwardOut gradient;
		Loss::compute(fout, bin, gradient);
		//cout << "grad:\n" << gradient << "\n";

		// sgd optimization
		//ForwardIn diff = fin.transpose() * gradient; // dense/sparse depend on the input type
		//cout << "param before:\n" << param_ << "\n";
		//param_ = param_ - fin.transpose() * gradient * 0.001; // TODO: the lr param
		optimizer_.compute(fin, gradient, param_);
		//cout << "param after:\n" << param_ << "\n";
	}*/
};

} // namespace prototype

} // namespace nlp


#endif//
