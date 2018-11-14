//
// Created by c on 14/11/2018 11:50
//

#ifndef NLP_NETWORK_STORAGE_VARIABLE_HH
#define NLP_NETWORK_STORAGE_VARIABLE_HH

/* include section */

#include <third-party/eigen3/Eigen/Eigen>
#include "utility/forward_declaration.hh"
#include "network/storage.hh"

/* class & function section */

namespace nlp {

namespace detail {

template<class Scalar>
struct traits< StorageVariable<Scalar> > {
	using data_t = Eigen::Matrix<Scalar, Eigen::Dynamic, Eigen::Dynamic>; // matrix with column major storage
};

} // namespace detail

/* variable storage */
template<class Scalar>
class StorageVariable : public Storage< StorageVariable<Scalar> > {
public:
	/* type alias */
	using data_t = typename detail::traits<StorageVariable>::data_t;

private:
	/* members */
	data_t data_;
	size_t n_; // batch size

public:
	/* data access */
	data_t& data() { return data_; }
	data_t const& data() const { return data_; }
};

} // namespace nlp



#endif//