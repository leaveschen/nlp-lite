//
// Created by c on 30/11/2018 15:53
//

#ifndef NLP_PROTOTYPE_MODEL_HH
#define NLP_PROTOTYPE_MODEL_HH

/* include section */

#include <iostream>
#include <fstream>
#include <string>
#include "variable.hh"
#include "layer.hh"
#include "loss.hh"
#include "activation.hh"
#include "optimizer.hh"
#include "utility/string.hh"

/* class & function section */

namespace nlp {

namespace prototype {

// temporary code...
class Model {
public:
	Dense<matrix_t, ActivateEmpty, SGD>* p_layer_;
	v_sparse_t* p_feature_;
	v_sparse_t* p_label_;
	std::vector<int> label;

	v_sparse_t* p_feature_train_;
	v_sparse_t* p_label_train_;
	v_sparse_t* p_feature_test_;
	v_sparse_t* p_label_test_;
	std::vector<int> label_train;
	std::vector<int> label_test;
	
	Model() {}
	~Model() {}

	void load_data(std::string fn) {
		//std::vector<int> label;
		std::vector<std::vector<int>> feature;
		int nclass = 0; int nfeature = 0;

		std::ifstream fs;
		fs.open(fn);
		char line[1024];
		while (fs.getline(line, 1024)) {
			auto v = basic_string<char>::split(std::string(line), " ");
			if (v.size() < 2) continue;
			int l = std::stoi(v[0]);
			label.push_back(l);
			if (l > nclass) nclass = l;
			std::vector<int> tmp;
			for (int i = 0; i < v.size()-1; ++i) {
				int f = std::stoi(v[i]);
				tmp.push_back(f);
				if (f > nfeature) nfeature = f;
			}
			feature.push_back(tmp);
		}
		++nclass; ++nfeature;
		std::cout << "nclass: " << nclass << "\n";
		std::cout << "nfeature: " << nfeature << "\n";
		int nsample = label.size();
		std::cout << "nsample: " << nsample << "\n";

		p_layer_ = new Dense<matrix_t, ActivateEmpty, SGD>(nfeature, nclass);
		p_feature_ = new v_sparse_t(nsample, nfeature);
		p_label_ = new v_sparse_t(nsample, nclass);

		for (int i = 0; i < nsample; ++i) {
			p_label_->insert(i, label[i]) = 1;
		}
		for (int i = 0; i < nsample; ++i) {
			auto& v = feature[i];
			for (int j = 0; j < v.size(); ++j) {
				p_feature_->insert(i, v[j]) = 1;
			}
		}
		//std::cout << "feature:\n" << *p_feature_ << "\n";
		//std::cout << "label:\n" << *p_label_ << "\n";

		int n = label.size() / 10 * 8;
		int m = nsample - n;
		p_feature_train_ = new v_sparse_t(n, nfeature);
		p_feature_test_ = new v_sparse_t(m, nfeature);
		p_label_train_ = new v_sparse_t(n, nclass);
		p_label_test_ = new v_sparse_t(m, nclass);
		for (int i = 0; i < n; ++i) {
			p_label_train_->insert(i, label[i]) = 1;
			label_train.push_back(label[i]);
			auto& v = feature[i];
			for (int j = 0; j < v.size(); ++j) p_feature_train_->insert(i, v[j]) = 1;
		}
		for (int i = 0; i < m; ++i) {
			p_label_test_->insert(i, label[i+n]) = 1;
			label_test.push_back(label[i+n]);
			auto& v = feature[i+n];
			for (int j = 0; j < v.size(); ++j) p_feature_test_->insert(i, v[j]) = 1;
		}
		//std::cout << "p_feature_train_:\n" << *p_feature_train_ << "\n";
		//std::cout << "p_label_train_:\n" << *p_label_train_ << "\n";
		//std::cout << "p_feature_test_:\n" << *p_feature_test_ << "\n";
		//std::cout << "p_label_test_:\n" << *p_label_test_ << "\n";
	}

	void acc(v_dense_t const& fout, std::vector<int>& l) {
		v_dense_t::Index idx;
		float corr = 0.0;
		for (int i = 0; i < fout.rows(); ++i) {
			fout.row(i).maxCoeff(&idx);
			//cout << idx << "\n";
			if (idx == l[i]) corr += 1;
		}
		cout << "accuracy: " << corr / fout.rows() << "\n";
	}

	void train() {
		int epoch = 5;
		v_dense_t fout;
		v_dense_t bout;
		v_dense_t tout;

		for (int i = 0; i < epoch; ++i) {
			std::cout << "epoch: " << i << "\n";
			p_layer_->forward(*p_feature_test_, tout);
			//p_layer_->forward_backward(*p_feature_train_, fout, *p_label_train_, bout);

			// split into forward & backward step
			p_layer_->forward(*p_feature_train_, fout);
			v_dense_t gradient;
			CategoricalCrossentropy::backward(fout, *p_label_train_, gradient);
			p_layer_->backward(*p_feature_train_, fout, gradient, bout);
			//std::cout << bout.rows() << ":" << bout.cols() << "\n";

			std::cout << "train accuracy\n";
			acc(fout, label_train);
			std::cout << "test accuracy\n";
			acc(tout, label_test);
		}
	}
};

} // namespace prototype

} // namespace nlp

#endif//