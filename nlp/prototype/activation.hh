//
// Created by c on 03/12/2018 14:22
//

#ifndef NLP_PROTOTYPE_ACTIVATION_HH
#define NLP_PROTOTYPE_ACTIVATION_HH

/* include section */

#include <limits>

/* class & function section */

namespace nlp {

namespace prototype {

struct Softmax {
	/* calculate softmax activation
	* source: the output of previous layer
	*/
	template<class SourceType>
	static void compute(SourceType& source) {
		// compute softmax output
		source = source.array().exp();

		for (size_t i = 0; i < source.rows(); ++i) {
			source.row(i) = source.row(i) /
				(source.row(i).sum() + std::numeric_limits<typename SourceType::Scalar>::epsilon());
		}
	}
};

} // namespace prototype
} // namespace nlp
#endif//