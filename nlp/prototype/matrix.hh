//
// Created by c on 29/11/2018 12:08
//

#ifndef NLP_PROTOTYPE_MATRIX_HH
#define NLP_PROTOTYPE_MATRIX_HH

/* include section */

#include <memory>
#include <cassert>

/* class & function section */

namespace nlp {

namespace prototype {

/* basic class for matrix */
template<class Derived>
class MatBase {
protected:
	/* members */
	size_t row_;
	size_t col_;

public:
	/* ctor */
	MatBase(size_t row, size_t col) : row_(row), col_(col) {}

	/* derived object */
	Derived& derived() { return static_cast<Derived&>(*this); }
	Derived const& derived() const { return static_cast<Derived const&>(*this); }

	/* size */
	inline size_t& row() { return row_; }
	inline size_t& col() { return col_; }
};


/* dense matrix class */
template<class Scalar, int Option>
class MatDense : public MatBase< MatDense<Scalar, Option> > {
public:
	/* type alias */
	using base_t = MatBase< MatDense<Scalar, Option> >;
	using coef_ptr_t = std::unique_ptr<Scalar[]>;

protected:
	/* members */
	coef_ptr_t coef_; // coefficient the storage major determined by the template parameter 'Option'

public:
	/* ctor & dtor */
	MatDense(size_t row, size_t col) : base_t(row, col), coef_(nullptr) {
		// TODO: check dimension valid
		assert(row > 0 and col > 0);
		coef_ = std::make_unique<Scalar[]>(this->row() * this->col());
	}

	/* coefficient accessor */
	Scalar& coef_nocheck(size_t i) { return coef_[i]; }
	Scalar const& coef_nocheck(size_t i) const { return coef_[i]; }

	Scalar& coef(size_t i) {
		assert(i < this->row() * this->col());
		return coef_[i];
	}
	Scalar const& coef(size_t i) const {
		assert(i < this->row() * this->col());
		return coef_[i];
	}

	Scalar& coef_nocheck(size_t i, size_t j) { return coef_[i*this->row()+j]; }
	Scalar const& coef_nocheck(size_t i, size_t j) const { return coef_[i*this->row()+j]; }

	Scalar& coef(size_t i, size_t j) {
		assert(i < this->row() and j < this->col());
		return coef_[i*this->row()+j];
	}
	Scalar const& coef(size_t i, size_t j) const {
		assert(i < this->row() and j < this->col());
		return coef_[i*this->row()+j];
	}


	/* addition */
	template<class OtherDerived>
	void add(OtherDerived const& other);

	/* multiply */
	template<class OtherDerived>
	void mul(OtherDerived const& other);
};


/* sparse matrix class */
// TODO: implement
template<class Scalar, int Option>
class MatSparse : public MatBase< MatSparse<Scalar, Option> > {
public:
	/* type alias */
	using base_t = MatBase< MatSparse<Scalar, Option> >;

	struct coef_unit_t {
		size_t inner_index;
		Scalar value;
	};

	struct coef_array_t {
		size_t outer_index;
		std::vector<coef_unit_t> array;
	};

	/* members */
};

} // namespace prototype

} // namespace nlp

#endif//
