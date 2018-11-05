//
// Created by c on 05/11/2018 15:28
//

/* include section */

#include "analyser/reader.hh"

/* class & function section */

namespace nlp {

namespace detail {

ReaderBase::ReaderBase() : fs_(), line_() {}
ReaderBase::ReaderBase(std::string const& fn) : fs_(fn, std::ios_base::in), line_() {}

void ReaderBase::open(std::string const& fn) { fs_.open(fn); }
void ReaderBase::close() { fs_.close(); }
bool ReaderBase::is_open() { return fs_.is_open(); }


ReaderL::ReaderL() : ReaderBase() {}
ReaderL::ReaderL(std::string const& fn) : ReaderBase(fn) {}

bool ReaderL::readline(std::string& text, std::string& label) {
	if (!is_open() or !fs_) return false;
	fs_.getline(line_, IO_LINE_MAX_LEN);
	std::vector<std::string> l = string::split(line_, "\t"); // XXX: optimize the delimeter
	if (l.size() != 2) return false;
	label = l[0];
	text = l[1];
	return true;
}


ReaderM::ReaderM() : ReaderBase() {}
ReaderM::ReaderM(std::string const& fn) : ReaderBase(fn) {}

bool ReaderM::readline(std::string& text, std::vector<std::string>& labels) {
	if (!is_open() or !fs_) return false;
	fs_.getline(line_, IO_LINE_MAX_LEN);
	std::vector<std::string> l = string::split(line_, "\t");
	if (l.size() != 2) return false;
	labels = string::split(l[0], "|"); // XXX: optimize the delimeter
	text = l[1];
	return true;
}


ReaderU::ReaderU() : ReaderBase() {}
ReaderU::ReaderU(std::string const& fn) : ReaderBase(fn) {}

bool ReaderU::readline(std::string& text) {
	if (!is_open() or !fs_) return false;
	fs_.getline(line_, IO_LINE_MAX_LEN);
	text = line_;
	return true;
}

} // namespace detail

} // namespace nlp


