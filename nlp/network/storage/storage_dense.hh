//
// Created by c on 14/11/2018 11:18
//

#ifndef NLP_NETWORK_STORAGE_DENSE_HH
#define NLP_NETWORK_STORAGE_DENSE_HH

/* include section */

#include <third-party/eigen3/Eigen/Eigen>
#include "utility/forward_declaration.hh"
#include "network/storage.hh"

/* class & function section */

namespace nlp {

namespace detail {

template<class Scalar>
struct traits< StorageDense<Scalar> > {
	using data_t = Eigen::Matrix<Scalar, Eigen::Dynamic, Eigen::Dynamic, Eigen::RowMajor>; // matrix with row major storage
};

} // namespace detail

/* dense layer storage */
template<class Scalar>
class StorageDense : public Storage< StorageDense<Scalar> > {
public:
	/* type alias */
	//using data_t = typename detail::traits<StorageDense>::data_t;

private:
	/* members */
	//data_t data_;

public:
	/* data access */
	//data_t& data() { return data_; }
	//data_t const& data() const { return data_; }
};

} // namespace nlp

#endif//