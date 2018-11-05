//
// Created by c on 05/11/2018 17:27
//

/* include section */

#include "analyser/tokenizer.hh"

/* class & function section */

namespace nlp {

namespace detail {

// TODO: to be done
void TokenEnWord::init(std::string const& dict_dir) {}
std::vector<std::string> TokenEnWord::cut(std::string const& text) const {
	std::vector<std::string> ret;
	return ret;
}


void TokenZhChar::init(std::string const& dict_dir) {}
std::vector<std::string> TokenZhChar::cut(std::string const& text) const {
	auto ret = string::to_vec(text);
	return ret;
}


// TODO: to be done
void TokenZhWord::init(std::string const& dict_dir) {}
std::vector<std::string> TokenZhWord::cut(std::string const& text) const {
	std::vector<std::string> ret;
	return ret;
}


} // namespace detail

} // namespace nlp


