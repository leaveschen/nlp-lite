//
// Created by c on 02/11/2018 11:13
//

#ifndef NLP_UTILITY_STRING_HH
#define NLP_UTILITY_STRING_HH

/* include section */

#include <string>
#include <vector>

/* class & function section */

namespace nlp {

// forward declaration
template<class CharT> struct basic_string;
using string = basic_string<char>;

template<class CharT>
struct basic_string {
	// type alias
	using StrT = std::basic_string<CharT>;

	/* convert a string into vector of basic characters, under utf8 encoding */
	static std::vector<StrT> to_vec(StrT const& str) {
		std::vector<StrT> ret;
		size_t nbyte = 0;
		for (size_t i = 0; i < str.size(); ) {
			if ((str[i] & 0xfc) == 0xfc) { nbyte = 6; }
			else if ((str[i] & 0xf8) == 0xf8) { nbyte = 5; }
			else if ((str[i] & 0xf0) == 0xf0) { nbyte = 4; }
			else if ((str[i] & 0xe0) == 0xe0) { nbyte = 3; }
			else if ((str[i] & 0xc0) == 0xc0) { nbyte = 2; }
			else { nbyte = 1; }
			ret.push_back(str.substr(i, nbyte));
			i += nbyte;
		}
		return ret;
	}

	/* split with given delimiter */
	static std::vector<StrT> split(StrT const& str, StrT delimiter) {
		std::vector<StrT> ret;
		typename StrT::size_type pfirst = 0;
		typename StrT::size_type plast = 0;
		while (plast < str.size()) {
			plast = str.find_first_of(delimiter, pfirst);
			if (plast == StrT::npos) {
				if (str.size() > pfirst) { ret.push_back(str.substr(pfirst, str.size()-pfirst)); }
				break;
			} else {
				if (plast > pfirst) { ret.push_back(str.substr(pfirst, plast-pfirst)); }
				pfirst = plast + 1;
			}
		}
		return ret;
	}

};

} // namespace nlp

#endif//


