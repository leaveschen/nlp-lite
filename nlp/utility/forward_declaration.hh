//
// Created by c on 12/11/2018 16:06
//

#ifndef NLP_UTILITY_FORWARD_DECLARATION_HH
#define NLP_UTILITY_FORWARD_DECLARATION_HH

/* include section */

/* class & function section */

namespace nlp {

namespace detail {

template<class T> struct traits;

} // namespace detail

template<class Shape, class Storage> class Variable;
template<class Shape, class Storage, class ForwardOp, class BackwardOp> class Layer;

template<class Scalar> class StorageDense;
template<class Scalar> class StorageVariable;

} // namespace nlp

#endif//