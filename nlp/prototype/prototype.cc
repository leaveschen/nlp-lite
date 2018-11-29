//
// Created by c on 29/11/2018 16:31
//

/* include section */

#include <iostream>
#include "matrix.hh"
using namespace nlp::prototype;

/* class & function section */

int main() {
	MatDense<float, 0> m1{3,2};
	std::cout << m1.row() << "\n";
	std::cout << m1.col() << "\n";
}


