//
// Created by c on 06/12/2018 11:56
//

/* include section */

#include <iostream>
#include "io.hh"

/* class & function section */

namespace nlp {

namespace prototype {

// implementation for class FileBase
bool FileBase::getline(std::string& line) {
	auto& r = fs_.getline(line_, MAX_LINE_LENGTH);
	line = line_;
	return bool(r);
}

// implementation for class FileTrain
void FileTrain::load_data(std::string fn) {
	open(fn);
	std::string line;
	while (getline(line)) {
		auto v = basic_string<char>::split(std::string(line), " ");
		if (v.size() < 2) continue;
		int l = std::stoi(v[0]);
		labels_.push_back(l);
		if (l > nclass_) nclass_ = l;
		std::vector<int> tmp;
		for (int i = 1; i < v.size(); ++i) {
			int f = std::stoi(v[i]);
			if (f > nfeature_) nfeature_ = f;
			tmp.emplace_back(f);
		}
		features_.emplace_back(tmp);
	}
	++nclass_; ++nfeature_;
	nsample_ = labels_.size();
	fs_.close();
	std::cout << "nclass: " << nclass_ << "\n";
	std::cout << "nfeature: " << nfeature_ << "\n";
	std::cout << "nsample: " << nsample_ << "\n";
}

void FileTrain::get_data(v_sparse_t& x_train, v_sparse_t& y_train,
	v_sparse_t& x_test, v_sparse_t& y_test,
	float ratio) {
	int n = nsample_ * ratio;
	int m = nsample_ - n;
	x_train.resize(n, nfeature_);
	y_train.resize(n, nclass_);
	x_test.resize(m, nfeature_);
	y_test.resize(m, nclass_);
	for (int i = 0; i < n; ++i) {
		y_train.insert(i, labels_[i]) = 1;
		for (auto j : features_[i]) x_train.insert(i, j) = 1;
		//label_train.push_back(label[i]);
		//auto& v = features_[i];
		//for (int j = 0; j < v.size(); ++j) x_train.insert(i, v[j]) = 1;
	}
	for (int i = 0; i < m; ++i) {
		y_test.insert(i, labels_[i+n]) = 1;
		for (auto j : features_[i+n]) x_test.insert(i, j) = 1;
		//label_test.push_back(label[i+n]);
		//auto& v = features_[i+n];
		//for (int j = 0; j < v.size(); ++j) p_feature_test_->insert(i, v[j]) = 1;
	}
}

} // namespace prototype

} // namespace nlp

