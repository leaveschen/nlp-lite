//
// Created by c on 05/11/2018 13:04
//

#ifndef NLP_ANALYSER_READER_HH
#define NLP_ANALYSER_READER_HH

/* include section */

#include <fstream>
#include <vector>

#include "utility/constant.hh"
#include "utility/string.hh"

/* class & function section */

namespace nlp {

/* file type */
enum class READER_TYPE : int { LABELED, MULTI_LABELED, UNLABELED };

namespace detail {

/* base class for file reading */
struct ReaderBase {
	/* members */
	std::fstream fs_;
	char line_[IO_LINE_MAX_LEN];

	/* constructor & destructor */
	ReaderBase();
	ReaderBase(std::string const& fn);
	ReaderBase(ReaderBase const&) = delete;
	ReaderBase& operator=(ReaderBase const&) = delete;
	~ReaderBase() = default;

	/* interface */
	void open(std::string const& fn);
	void close();
	bool is_open();
};


/* implementation class for labeled file reading */
struct ReaderL : ReaderBase {
	/* type alias */
	using label_t = std::string;

	/* constructor */
	ReaderL();
	ReaderL(std::string const& fn);

	/* interface */
	bool readline(std::string& text, std::string& label);
};


/* implementation class for multi-labeled file reading */
struct ReaderM : ReaderBase {
	/* type alias */
	using label_t = std::vector<std::string>;

	/* constructor */
	ReaderM();
	ReaderM(std::string const& fn);

	/* interface */
	bool readline(std::string& text, std::vector<std::string>& labels);
};


/* implementation class for unlabeled file reading */
struct ReaderU : ReaderBase {
	/* constructor */
	ReaderU();
	ReaderU(std::string const& fn);

	/* interface */
	bool readline(std::string& text);
};

} // namespace detail

/* class for file reading */

template<READER_TYPE Type>
using ReaderT = std::conditional_t< Type == READER_TYPE::LABELED, detail::ReaderL,
			std::conditional_t<Type == READER_TYPE::MULTI_LABELED, detail::ReaderM, detail::ReaderU> >;

template<READER_TYPE Type>
class Reader : public ReaderT<Type> {
public:
	/* type alias */
	using reader_t = ReaderT<Type>;

	/* constructor & destructor */
	Reader() : reader_t() {}
	Reader(std::string const& fn) : reader_t(fn) {}
	~Reader() = default;

	/* interface for read line
	 * different interface allowed with the template parameter Type
	 * READER_TYPE::LABELED - bool readline(std::string& text, std::string& label);
	 * READER_TYPE::MULTILABELED - bool readline(std::string& text, std::vector<std::string>& labels);
	 * READER_TYPE::UNLABELED - readline(std::string& text);
	 */

	/* interface for eof */
	bool eof() { return !bool(detail::ReaderBase::fs_); }
};

}

#endif//


