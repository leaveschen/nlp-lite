//
// Created by c on 15/11/2018 15:07
//

#ifndef NLP_NETWORK_OP_DENSE_SPARSE_FORWARD_HH
#define NLP_NETWORK_OP_DENSE_SPARSE_FORWARD_HH

/* include section */

#include "utility/types.hh"
#include "network/operator.hh"
#include "network/storage/storage_dense.hh"
#include "network/storage/storage_dense_variable.hh"
#include "network/storage/storage_sparse_variable.hh"

/* class & function section */

namespace nlp {

namespace detail {

template<class Scalar>
struct traits< OpDenseSparseForward<Scalar> > {
	using content_t = typename detail::traits< StorageDense<Scalar> >::data_t;
	using input_t = typename detail::traits< StorageSparseVariable<Scalar> >::data_t;
	using output_t = typename detail::traits< StorageDenseVariable<Scalar> >::data_t;
}; 

} // namespace detail

template<class Scalar>
class OpDenseSparseForward : public OperatorForward< OpDenseSparseForward<Scalar> > {
public:
	/* type alias */
	using typename OperatorForward< OpDenseSparseForward<Scalar> >::content_t;
	using typename OperatorForward< OpDenseSparseForward<Scalar> >::input_t;
	using typename OperatorForward< OpDenseSparseForward<Scalar> >::output_t;

	/* ctor & dtor */
	OpDenseSparseForward() = default;
	OpDenseSparseForward(OpDenseSparseForward const&) = delete;
	OpDenseSparseForward& operator=(OpDenseSparseForward const&) = delete;
	~OpDenseSparseForward() = default;

	/* implementation */
	void run_impl(content_t const& content, input_t const& input, output_t& output) {
		// TODO: update the storage major for performance
		output = content * input;
	}
};

} // namespace nlp

#endif//