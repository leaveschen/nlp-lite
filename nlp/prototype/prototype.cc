//
// Created by c on 29/11/2018 16:31
//

/* include section */

#include <iostream>
#include <limits>
#include "layer.hh"
#include "variable.hh"
#include "loss.hh"
#include "model.hh"
#include "io.hh"
using namespace nlp::prototype;
using std::cout;

/* class & function section */

int main(int argc, char* argv[]) {
	/*
	Dense<matrix_t, Softmax> d{5, 2};
	d.param_ << 1,2,
		3,4,
		5,6,
		7,8,
		9,0;
	v_sparse_t in{4, 5};
	in.insert(0, 4) = 3;
	in.insert(2, 2) = 1;
	v_dense_t out;
	v_sparse_t target{4, 2};
	target.insert(0, 0) = 1;

	v_dense_t bout;
	d.forward_backward(in, out, target, bout);
	*/

	Model model;
	model.train3(argv[1]);


	/*FileTrain ft;
	ft.load_data(argv[1]);
	v_sparse_t x_train, y_train, x_test, y_test;
	ft.get_data(x_train, y_train, x_test, y_test);
	cout << "x_train shape: " << x_train.rows() << "," << x_train.cols() << "\n";
	cout << "y_train shape: " << y_train.rows() << "," << y_train.cols() << "\n";
	cout << "x_test shape: " << x_test.rows() << "," << x_test.cols() << "\n";
	cout << "y_test shape: " << y_test.rows() << "," << y_test.cols() << "\n";*/

}


