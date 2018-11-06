//
// Created by c on 05/11/2018 13:04
//

#ifndef NLP_ANALYSER_READER_HH
#define NLP_ANALYSER_READER_HH

/* include section */

#include <fstream>
#include <vector>
#include <type_traits>

#include "utility/constant.hh"
#include "utility/string.hh"

/* class & function section */

namespace nlp {

/* file type */
enum class READER_TYPE : int { LABELED, MULTI_LABELED, UNLABELED };


/* type traits */
template<READER_TYPE Type>
struct ReaderTraits {};

template<>
struct ReaderTraits<READER_TYPE::LABELED> {
	using label_t = std::string;
};

template<>
struct ReaderTraits<READER_TYPE::MULTI_LABELED> {
	using label_t = std::vector<std::string>;
};


/* class for file reading */
template<READER_TYPE Type>
class Reader {
public:
	using label_t = std::enable_if_t<Type != READER_TYPE::UNLABELED,
				typename ReaderTraits<Type>::label_t>;

private:
	/* members */
	std::fstream fs_;
	char line_[IO_LINE_MAX_LEN];

public:
	/* common interface */
	void open(std::string const& fn) { fs_.open(fn); }
	void close() { fs_.close(); }
	bool is_open() { return fs_.is_open(); }
	bool eof() { return !bool(fs_); }

	/* interface for read line
	 * different interface allowed to compile with the template parameter Type
	 * READER_TYPE::LABELED - bool readline(std::string& text, std::string& label);
	 * READER_TYPE::MULTILABELED - bool readline(std::string& text, std::vector<std::string>& labels);
	 * READER_TYPE::UNLABELED - readline(std::string& text);
	 */
	template<READER_TYPE U = Type>
	std::enable_if_t<U == READER_TYPE::LABELED, bool>
	readline(std::string& text, std::string& label) {
		if (!is_open() or !fs_) return false;
		fs_.getline(line_, IO_LINE_MAX_LEN);
		std::vector<std::string> l = string::split(line_, "\t"); // XXX: optimize the delimeter
		if (l.size() != 2) return false;
		label = l[0];
		text = l[1];
		return true;
	}

	template<READER_TYPE U = Type>
	std::enable_if_t<U == READER_TYPE::MULTI_LABELED, bool>
	readline(std::string& text, std::vector<std::string>& labels) {
		if (!is_open() or !fs_) return false;
		fs_.getline(line_, IO_LINE_MAX_LEN);
		std::vector<std::string> l = string::split(line_, "\t");
		if (l.size() != 2) return false;
		labels = string::split(l[0], "|"); // XXX: optimize the delimeter
		text = l[1];
		return true;
	}

	template<READER_TYPE U = Type>
	std::enable_if_t<U == READER_TYPE::UNLABELED, bool>
	readline(std::string& text) {
		if (!is_open() or !fs_) return false;
		fs_.getline(line_, IO_LINE_MAX_LEN);
		text = line_;
		return true;
	}

	/* constructor & destructor */
	Reader() : fs_(), line_() {}
	Reader(std::string const& fn) : fs_(fn, std::ios_base::in), line_() {}
	Reader(Reader const&) = delete;
	Reader& operator=(Reader const&) = delete;
	~Reader() = default;
};

}

#endif//


