//
// Created by c on 30/11/2018 11:29
//

#ifndef NLP_PROTOTYPE_VARIABLE_HH
#define NLP_PROTOTYPE_VARIABLE_HH

/* include section */

#include <third-party/eigen3/Eigen/Eigen>

/* class & function section */

namespace nlp {

namespace prototype {

/* types alias */
using matrix_t = Eigen::Matrix<float, Eigen::Dynamic, Eigen::Dynamic>; // column major
using v_dense_t = Eigen::Matrix<float, Eigen::Dynamic, Eigen::Dynamic, Eigen::RowMajor>; // row major
using v_sparse_t = Eigen::SparseMatrix<float, Eigen::RowMajor>; // row major

} // namespace prototype

} // namespace nlp


#endif//


