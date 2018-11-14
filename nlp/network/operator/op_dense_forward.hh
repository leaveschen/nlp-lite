//
// Created by c on 14/11/2018 10:57
//

#ifndef NLP_NETWORK_OP_DENSE_FORWARD_HH
#define NLP_NETWORK_OP_DENSE_FORWARD_HH

/* include section */

#include "utility/types.hh"
#include "network/operator.hh"
#include "network/storage/storage_dense.hh"
#include "network/storage/storage_variable.hh"

/* class & function section */

namespace nlp {

/* forward operator for dense layer */
class OpDenseForward : public OperatorForward<OpDenseForward> {
public:
	/* type alias */
	using content_t = typename detail::traits< StorageDense<Real> >::data_t;
	using input_t = typename detail::traits< StorageVariable<Real> >::data_t;
	using output_t = typename detail::traits< StorageVariable<Real> >::data_t;

	/* ctor & dtor */
	OpDenseForward() = default;
	OpDenseForward(OpDenseForward const&) = delete;
	OpDenseForward& operator=(OpDenseForward const&) = delete;
	~OpDenseForward() = default;

	/* interface */
	output_t run(content_t const& content, input_t const& input);
	void run(content_t const& content, input_t const& input, output_t& output);
};

} // namespace nlp

#endif//