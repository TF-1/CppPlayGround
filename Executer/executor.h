#pragma once

#include <iostream>
#include <memory>
#include <queue>
#include <string>
#include <sstream>
#include <thread>
#include <vector>
#include <atomic>
#include <mutex>

// Base class for all kinds of tasks that can be executed
class executable : public std::enable_shared_from_this<executable>{
    public:
    virtual void execute() noexcept = 0;
    virtual ~executable() = default;
};

using executable_ptr = std::shared_ptr<executable>;

// Runs executables in background threads
class executor final{
    public:
    executor(const executor&) = delete;
    executor(executor&&) = delete;
    auto operator = (const executor&) = delete;
    auto operator = (executor&&) = delete;

    executor(size_t nof_threads) {
        if (nof_threads < 2)
            throw std::runtime_error("Executor requires at least two threads");
        for (size_t i = 0; i < nof_threads; ++i){
            threads_.emplace_back(&executor::run_thread, this);
        }
    }

	void stop()
	{
		active_.store(false, std::memory_order_release);
		wakeup_.notify_all();

		for (auto &t : threads_)
		{
			if (t.joinable())
				t.join();
		}
	}

    ~executor() 
	{
		stop();
    }

    void schedule(executable_ptr what){
        if (!active_.load(std::memory_order_acquire)){
            throw std::runtime_error("Executor is being destroyed. You can't schedule any more work.");
        }

        {
            std::lock_guard<std::mutex> lock(mutex_);
            queue_.push(std::move(what));
        }
        wakeup_.notify_one();
    }

    private:
    void run_thread() noexcept {
        while (true){
            std::unique_lock<std::mutex> lock(mutex_);
            //while(!pred()){
            //    wakeup_.wait(lock);
            //}
            wakeup_.wait(lock, [this](){
                auto active = this->active_.load(std::memory_order_acquire);
                return !(this->queue_.empty() && active);
            });
            // If queue is empty, active_ is false!
            if (queue_.empty())
                break;
            auto next = std::move(queue_.front());
            queue_.pop();
            lock.unlock();

            next->execute();
        }
    }

    std::vector<std::thread> threads_;

    std::mutex mutex_;
    std::queue<executable_ptr> queue_;
    std::condition_variable wakeup_;

    std::atomic<bool> active_ = true;
};

constexpr size_t DEFAULT_CONCURRENCY = 4;

template<size_t concurrency_level = DEFAULT_CONCURRENCY>
class executor_provider {
    public:
    static executor &getExecutor(){
		static class executor ex(concurrency_level);
        return ex;
    }
};

//template<typename T>
//concept ExecutorProvider = std::is_same<decltype(T::executor()), executor&>::value;