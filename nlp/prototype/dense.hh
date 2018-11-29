//
// Created by c on 29/11/2018 11:49
//

#ifndef NLP_PROTOTYPE_DENSE_HH
#define NLP_PROTOTYPE_DENSE_HH

/* include section */

/* class & function section */

namespace nlp {

namespace prototype {

/* dense layer class */
template<class Scalar,
	template<class> class InMat,
	template<class> class OutMat,
	template<class> class ParamMat>
class Dense {
public:
	/* type alias */
	using in_type = InMat<Scalar>;
	using out_type = OutMat<Scalar>;
	using param_type = ParamMat<Scalar>; // default dense matrix

private:
	/* members */
	param_type param_;

public:
	/* ctor & dtor */
	Dense() : param_() {}
	Dense(Dense const&) = delete;
	Dense& operator=(Dense const&) = delete;
	~Dense() {}

	/* interface */
	void forward(in_type const& forward_in, out_type& forward_out) {
		param_.mul(forward_in, forward_out);
	}

	void backward(out_type const& backward_in, in_type& backward_out);
};

} // namespace prototype

} // namespace nlp


#endif//
