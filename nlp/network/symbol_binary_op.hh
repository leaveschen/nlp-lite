//
// Created by c on 13/11/2018 15:23
//

#ifndef NLP_NETWORK_SYMBOL_BINARY_OP_HH
#define NLP_NETWORK_SYMBOL_BINARY_OP_HH

/* include section */

/* class & function section */

namespace nlp {

/* binary operator class */
struct SymbolBinaryAdd {};
struct SymbolBinarySub {};
struct SymbolBinaryMul {};
struct SymbolBinaryDiv {};


/* symbol binary operator class
 * it is a proxy class of real symbol operator */
template<class BinaryOp, class Lhs, class Rhs>
class SymbolBinaryOp {
protected:
	/* members */
	const Lhs* p_lhs_;
	const Rhs* p_rhs_;

public:
	/* type alias */
	using op_t = BinaryOp;
	using lhs_t = Lhs;
	using rhs_t = Rhs;

	/* ctor & dtor*/
	SymbolBinaryOp(Lhs const& lhs, Rhs const& rhs) : p_lhs_(&lhs), p_rhs_(&rhs) {}
	~SymbolBinaryOp() {}

	/* accessor */
	Lhs const& lhs() const { return *p_lhs_; }
	Rhs const& rhs() const { return *p_rhs_; }
};

} // namespace nlp

#endif//