//
// Created by c on 14/11/2018 10:57
//

#ifndef NLP_NETWORK_OP_DENSE_FORWARD_HH
#define NLP_NETWORK_OP_DENSE_FORWARD_HH

/* include section */

#include "utility/types.hh"
#include "network/operator.hh"
#include "network/storage/storage_dense.hh"
#include "network/storage/storage_dense_variable.hh"

/* class & function section */

namespace nlp {

namespace detail {

template<class Scalar>
struct traits< OpDenseForward<Scalar> > {
	using content_t = typename detail::traits< StorageDense<Scalar> >::data_t;
	using input_t = typename detail::traits< StorageDenseVariable<Scalar> >::data_t;
	using output_t = typename detail::traits< StorageDenseVariable<Scalar> >::data_t;
};

} // namespace detail

/* forward operator for dense layer */
template<class Scalar>
class OpDenseForward : public OperatorForward< OpDenseForward<Scalar> > {
public:
	/* type alias */
	using typename OperatorForward< OpDenseForward<Scalar> >::content_t;
	using typename OperatorForward< OpDenseForward<Scalar> >::input_t;
	using typename OperatorForward< OpDenseForward<Scalar> >::output_t;

	/* ctor & dtor */
	OpDenseForward() = default;
	OpDenseForward(OpDenseForward const&) = delete;
	OpDenseForward& operator=(OpDenseForward const&) = delete;
	~OpDenseForward() = default;

	/* implementation */
	void run_impl(content_t const& content, input_t const& input, output_t& output) {
		// TODO: update the storage major for performance
		output = content * input;
	}
};

} // namespace nlp

#endif//