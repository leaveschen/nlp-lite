//
// Created by c on 24/05/2018 02:28 PM
//

#ifndef NLP_HEAP_HH
#define NLP_HEAP_HH

/* include section */

#include <vector>
#include <algorithm>
#include <functional>

/* class & function section */

namespace nlp {

// compare type
template<class T>
using struct HeapMinCompare = std::less<T>;

template<class T>
using struct HeapMaxCompare = std::greater<T>;

// heap type, with limit size
template<class T, class Compare>
class LimitHeap {
public:
	// types
	using value_type = T;
	using container_t = std::vector<T>;

protected:
	// members
	size_t _limit;
	container_t _container;
	Compare _compare;

public:
	// constructor
	LimitHeap(size_t limit = 0) : _limit(), _container(), _compare() {
		_limit = std::max(1, limit);
		_container.reserve(_limit);
	}
	LimitHeap(LimitHeap<T> const&) = delete;
	LimitHeap<T>& operator=(LimitHeap<T> const&) = delete;

	bool empty() { return _container.empty() ? true : false; }

	void push(T const& elem) {
		if (empty()) {
			_container.push_back(elem);
			return;
		}

		if (_container.size() < _limit) {
			_container.push_back(elem);
			std::push_heap(_container.begin(), _container.end(), _compare);
			return;
		}

		auto& bound_elem = _container.front();
		if (_compare(elem, bound_elem)) {
			std::pop_heap(_container.begin(), _container.end(), _compare);
			_container.back() = elem;
			std::push_heap(_container.begin(), _container.end(), _compare);
		}
	}

	T top() const {
		if (empty()) { throw std::range_error("error, empty heap..."); }
		return _container.front();
	}
};

// min heap & max heap
template<T>
using MinLimitHeap = LimitHeap<T, HeapMinCompare<T>>;

template<T>
using MaxLimitHeap = LimitHeap<T, HeapMaxCompare<T>>;

} // namespace nlp

#endif//


