//
// Created by c on 03/12/2018 15:48
//

#ifndef NLP_PROTOTYPE_OPTIMIZER_HH
#define NLP_PROTOTYPE_OPTIMIZER_HH

/* include section */

#include <iostream>
using std::cout;

/* class & function section */

namespace nlp {

namespace prototype {

struct SGD {
	/* initialize */
	void initialize() {}

	/* run sgd optimization */
	// TODO: is this interface generally?
	template<class ForwardIn, class BackwardIn, class ParamType>
	void compute(ForwardIn const& fin, BackwardIn const& bin, ParamType& param) {
		ParamType d = fin.transpose() * bin;
		//cout << "diff:\n" << d << "\n";
		//cout << "param:\n" << param << "\n";
		param = param - fin.transpose() * bin * 0.01;
		//cout << "param after update:\n" << param << "\n";
	}

	template<class ForwardIn, class BackwardIn, class ParamType>
	void compute(ForwardIn const& fin, BackwardIn const& bin, ParamType& param, float lr) {
		param = param - fin.transpose() * bin * lr;
	}
};

} // namespace prototype

} // namespace nlp

#endif//