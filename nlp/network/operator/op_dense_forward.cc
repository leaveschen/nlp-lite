//
// Created by c on 14/11/2018 16:11
//

/* include section */

#include "network/operator/op_dense_forward.hh"

/* class & function section */

namespace nlp {

/* interface */
OpDenseForward::output_t OpDenseForward::run(content_t const& content, input_t const& input) {
	output_t output;
	run(content, input, output);
	return output;
}

void OpDenseForward::run(content_t const& content, input_t const& input, output_t& output) {
	// TODO: update the storage major for performance
	output = content * input;
}

} // namespace nlp

