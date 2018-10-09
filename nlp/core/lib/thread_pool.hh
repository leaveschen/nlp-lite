//
// Created by c on 09/10/2018 02:29 PM
//

#ifndef NLP_CORE_THREAD_POOL_HH
#define NLP_CORE_THREAD_POOL_HH

/* include section */

#include <thread>
#include <vector>
#include <queue>
#include <functional>
#include <mutex>
#include <condition_variable>

/* class & function section */

namespace nlp {
namespace core {

template<size_t N,
	template<class T, class Container = std::deque<T>> class Queue = std::queue>
class ThreadPool {
protected:
	// members
	std::vector<std::thread> _workers;
	Queue<std::function<void()>> _tasks;
	std::mutex _mtx;
	std::condition_variable _cond;
	std::atomic_bool _task_queue_valid;

	// thread function
	void _work() {
		for(;;) {
			std::function<void()> task;
			// safe pop
			{
				std::unique_lock<std::mutex> lk(_mtx);
				_cond.wait(lk, [&](){ return !_tasks.empty() || !_task_queue_valid; });
				if (!_task_queue_valid) { return; }
				task = std::move(_tasks.front());
				_tasks.pop();
			}
			task();
		}
	}

public:
	// constructor
	ThreadPool() : _task_queue_valid(true) {
		for (size_t i = 0; i < N; ++i)
			_workers.emplace_back(std::thread(&ThreadPool::_work, this));
	}

	// destructor
	~ThreadPool() { for (auto& t : _workers) { t.join(); }}

	// submit interface
	template<class F, class... Args>
	void submit(F&& f, Args&&... args) {
		auto task = std::bind(std::forward<F>(f), std::forward<Args>(args)...);
		_tasks.push(task);
	}
};

} // namespace core
} // namespace nlp

#endif//


