//
// Created by c on 03/12/2018 15:48
//

#ifndef NLP_PROTOTYPE_OPTIMIZER_HH
#define NLP_PROTOTYPE_OPTIMIZER_HH

/* include section */

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
		param = param - fin.transpose() * bin * 0.001;
	}
};

} // namespace prototype

} // namespace nlp

#endif//