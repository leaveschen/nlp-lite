//
// Created by c on 05/11/2018 16:49
//

#ifndef NLP_ANALYSER_TOKENIZER_HH
#define NLP_ANALYSER_TOKENIZER_HH

/* include section */

#include <vector>

#include "utility/string.hh"

/* class & function section */

namespace nlp {

/* cut type */
enum class CUT_TYPE : int { EN_WORD, ZH_CHAR, ZH_WORD };

namespace detail {

struct TokenEnWord {
	TokenEnWord() = default;
	~TokenEnWord() = default;
	void init(std::string const& dict_dir);
	std::vector<std::string> cut(std::string const& text) const;
};

struct TokenZhChar {
	TokenZhChar() = default;
	~TokenZhChar() = default;
	void init(std::string const& dict_dir);
	std::vector<std::string> cut(std::string const& text) const;
};

struct TokenZhWord {
	TokenZhWord() = default;
	~TokenZhWord() = default;
	void init(std::string const& dict_dir);
	std::vector<std::string> cut(std::string const& text) const;
};

} // namespace detail


/* class for tokenize */
template<CUT_TYPE Type>
class Tokenizer {
public:
	/* type alias */
	using tokenizer_t = std::conditional_t< Type == CUT_TYPE::EN_WORD, detail::TokenEnWord,
				std::conditional_t<Type == CUT_TYPE::ZH_CHAR, detail::TokenZhChar, detail::TokenZhWord> >;

protected:
	/* members */
	tokenizer_t impl_;

public:
	/* constructor & destructor */
	Tokenizer(std::string const& dict_dir) : impl_() { impl_.init(dict_dir); }
	Tokenizer(Tokenizer const&) = delete;
	Tokenizer& operator=(Tokenizer const&) = delete;
	~Tokenizer() = default;

	/* interface */
	std::vector<std::string> cut(std::string const& text) const { return impl_.cut(text); }
};

} // namespace nlp

#endif//


