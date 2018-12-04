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

struct ActivateEmpty {
	template<class SourceType>
	static void compute(SourceType& source) {}
};


struct ActivateRelu {
	template<class SourceType>
	static void compute(SourceType& source) {
		source = (source.array().abs() + source.array()) / 2;
	}
};

} // namespace prototype
} // namespace nlp
#endif//