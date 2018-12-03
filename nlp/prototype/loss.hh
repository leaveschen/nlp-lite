//
// Created by c on 30/11/2018 12:00
//

#ifndef NLP_PROTOTYPE_LOSS_HH
#define NLP_PROTOTYPE_LOSS_HH

/* include section */

#include <limits>

/* class & function section */

namespace nlp {

namespace prototype {

//struct Softmax {
//	/* calculate softmax loss for given output
//	* source: the output of previous layer
//	* target: the target value to be fit
//	*/
//	template<class SourceType, class TargetType> 
//	static void compute(SourceType const& source, TargetType const& target, SourceType& gradient) {
//		// compute softmax output, assign to the gradient for temporary storing
//		gradient = source.array().exp();
//
//		for (size_t i = 0; i < gradient.rows(); ++i) {
//			gradient.row(i) = gradient.row(i) / (gradient.row(i).sum() + std::numeric_limits<float>::epsilon());
//		}
//
//		// compute the gradient
//		gradient -= target;
//	}
//};



struct CategoricalCrossentropy {
	/* calculate loss for categorical crossentropy
	 * source: the output of previous layer
	 * target: the target value to be fit
	 */
	template<class SourceType, class TargetType>
	static void compute(SourceType const& source, TargetType const& target, SourceType& loss) {
		loss = source - target;
	}
};

} // namespace prototype

} // namespace nlp

#endif//
