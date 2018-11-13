//
// Created by c on 07/11/2018 16:39
//

#ifndef NLP_NETWORK_SHAPE_HH
#define NLP_NETWORK_SHAPE_HH

/* include section */

#include <vector>
#include <initializer_list>

#include "utility/types.hh"

/* class & function section */

namespace nlp {

/* struct for dimension info */
struct Dimension {
	// type alias
	using value_t = Index;

	// members
	value_t value_;

	// ctor & dtor
	Dimension() = default;
	Dimension(value_t value) : value_(value) {}
	~Dimension() = default;

	// operator ==
	bool operator==(Dimension const& other) const { return value_ == other.value_; }
};

/* struct for shape info */
struct Shape {
	// members
	Index rank_;
	std::vector<Dimension> dims_;

	// ctor & dtor
	Shape() = default;
	Shape(std::initializer_list<Dimension> l) : rank_(l.size()), dims_(l) {}
	~Shape() = default;

	// copy ctor
	Shape(Shape const& other) = default;
	Shape& operator=(Shape const& other) = default;

	// operator ==
	bool operator==(Shape const& other) const { return dims_ == other.dims_; }
};

} // namespace nlp

#endif//