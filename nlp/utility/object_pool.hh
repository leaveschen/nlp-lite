//
// Created by c on 09/11/2018 10:42
//

#ifndef NLP_UTILITY_OBJECT_POOL_HH
#define NLP_UTILITY_OBJECT_POOL_HH

/* include section */

#include <utility>
#include <memory>
#include <vector>
#include <iostream>

#include "utility/constant.hh"

/* class & function section */

namespace nlp {

namespace detail {

/* array allocator */
template<class T>
class ArrayAlloctor {
private:
	/* members */
	void* p_;
	size_t n_;

public:
	/* ctor & dtor */
	// TODO: check validation
	ArrayAlloctor(size_t n) : p_(std::malloc(sizeof(T) * n)), n_(n) {}
	ArrayAlloctor(ArrayAlloctor const&) = delete;
	ArrayAlloctor& operator=(ArrayAlloctor const&) = delete;
	~ArrayAlloctor() { std::free(p_); }

	/* interface, get pointer */
	void* pointer() const { return p_; }

	/* interface, get location of i-th element */
	T* location(size_t i) {
		if (i > n_) return nullptr;
		return static_cast<T*>(p_) + i;
	}

	/* interface, access the T* of i-th element */
	T* operator[](size_t i) {
		if (i > n_) return nullptr;
		return static_cast<T*>(p_) + i;
	}
};

/* class of object pool chunk
 * no thread safe guarantee */
template<class T,
	size_t Capacity,
	template<class> class Allocator = ArrayAlloctor>
class ObjectPoolChunk {
public:
	/* memory block */
	union Block {
		T t;
		Block* next;

		Block() : next(nullptr) {}
	};

public:
	/* members */
	constexpr static size_t capacity_ = Capacity;
	Allocator<Block> arr_;
	Block* head_;
	Block* tail_;
	size_t rest_;

public:
	/* ctor & dtor */
	ObjectPoolChunk() : arr_(capacity_), head_(nullptr), tail_(nullptr), rest_(capacity_) {
		static_assert(Capacity>1, "pool chunk size must be non-zero");
		for (size_t i = 0; i < capacity_ - 1; ++i) {
			new (arr_[i]) Block();
			arr_[i]->next = arr_[i+1];
		}
		head_ = arr_[0];

		// reserve the last one block as placeholder
		//new (arr_[capacity_-1]) Block();
		tail_ = arr_[capacity_-1];
		new (tail_) Block();
		//arr_[capacity_-1]->next = head_;
	}
	ObjectPoolChunk(ObjectPoolChunk const&) = delete;
	ObjectPoolChunk& operator=(ObjectPoolChunk const&) = delete;
	~ObjectPoolChunk() {
		// XXX: is this destruction safety?
		for (size_t i = 0; i < capacity_ - 1; ++i) {
			//std::cout << typeid(arr_[i]).name() << "\n";
			//std::cout << arr_[i] << "---" << &arr_[i]->t << "\n";
			destroy(&arr_[i]->t);
		}
	}

	/* interface, create new object */
	template<class... Args>
	T* create(Args&&... args) {
		// the case when only the placeholder remained
		if (head_ == tail_) return nullptr;

		Block* curr = head_;
		head_ = head_->next;
		return new (static_cast<void*>(curr)) T(std::forward<Args>(args)...);
	}

	/* interface, destroy object */
	void destroy(T* p) {
		p->~T();
		auto ptr = reinterpret_cast<Block*>(p);
		ptr->next = head_;
		head_ = ptr;
	}

	/* interface for state */
	bool is_full() { return head_ == tail_; }

	/* get head & tail pointer */
	Block* head() { return head_; }
	Block* tail() { return tail_; }
};

} // namespace detail

template<class T,
	size_t ChunkCapacity = POOL_CHUNK_SIZE,
	template<class> class Allocator = detail::ArrayAlloctor>
class ObjectPool {
public:
	/* type alias */
	using chunk_t = detail::ObjectPoolChunk<T, ChunkCapacity, Allocator>;
	using block_t = typename chunk_t::Block;

private:
	/* members */
	std::vector<chunk_t*> chunks_;
	chunk_t* curr_chunk_;
	block_t* head_;
	block_t* tail_;

public:
	/* ctor & dtor */
	ObjectPool() : chunks_(), curr_chunk_(nullptr), head_(nullptr), tail_(nullptr) {
		chunk_t* c = new chunk_t();
		head_ = c->head_;
		tail_ = c->tail_;
		chunks_.emplace_back(c);
	}
	ObjectPool(ObjectPool const&) = delete;
	ObjectPool& operator=(ObjectPool const&) = delete;
	~ObjectPool() { for (auto p : chunks_) delete p; }

	/* interface, create */
	template<class...Args>
	T* create(Args&&...args) {
		if (head_ == tail_) {
			chunk_t* c = new chunk_t();
			head_ = c->head_;
			tail_ = c->tail_;
			chunks_.emplace_back(c);
		}
		block_t* curr = head_;
		head_ = head_->next;
		return new (static_cast<void*>(curr)) T(std::forward<Args>(args)...);
	}

	/* interface, destroy */
	void destroy(T* p) {
		p->~T();
		auto ptr = reinterpret_cast<Block*>(p);
		ptr->next = head_;
		head_ = ptr;
	}
};

} // namespace nlp


#endif//