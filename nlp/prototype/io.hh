//
// Created by c on 06/12/2018 11:41
//

#ifndef NLP_PROTOTYPE_IO
#define NLP_PROTOTYPE_IO

/* include section */

#include <fstream>
#include <string>
#include <vector>
#include "variable.hh"
#include "utility/string.hh"

/* class & function section */

namespace nlp {

namespace prototype {

class FileBase {
protected:
	std::fstream fs_;
	static constexpr int MAX_LINE_LENGTH = 1<<16;
	char line_[MAX_LINE_LENGTH];

public:
	inline void open(std::string fn) { fs_.open(fn); }
	bool getline(std::string& line);
};

class FileTrain : public FileBase {
protected:
	std::vector<int> labels_;
	std::vector<std::vector<int>> features_;
	int nclass_;
	int nfeature_;
	int nsample_;

public:
	FileTrain() : labels_(), features_(), nclass_(0), nfeature_(0), nsample_(0) {}

	inline int nclass() const { return nclass_; }
	inline int nfeature() const { return nfeature_; }
	inline int nsample() const { return nsample_; }

	void load_data(std::string fn);

	void get_data(v_sparse_t& x_train, v_sparse_t& y_train,
		v_sparse_t& x_test, v_sparse_t& y_test,
		float ratio = 0.8);
};

} // namespace prototype

} // namespace nlp

#endif//