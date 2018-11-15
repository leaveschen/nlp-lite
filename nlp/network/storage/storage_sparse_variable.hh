//
// Created by c on 15/11/2018 14:51
//

#ifndef NLP_NETWORK_STORAGE_SPARSE_VARIABLE_HH
#define NLP_NETWORK_STORAGE_SPARSE_VARIABLE_HH

/* include section */

#include <third-party/eigen3/Eigen/Eigen>
#include "utility/forward_declaration.hh"
#include "network/storage.hh"

/* class & function section */

namespace nlp {

namespace detail {

template<class Scalar>
struct traits< StorageSparseVariable<Scalar> > {
	using data_t = Eigen::SparseMatrix<Scalar>; // sparse matrix with column major storage
};

} // namespace detail

/* variable storage */
template<class Scalar>
class StorageSparseVariable : public Storage< StorageSparseVariable<Scalar> > {
public:

private:

public:

};

} // namespace nlp

#endif//