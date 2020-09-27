// Executer.cpp : This file contains the 'main' function. Program execution begins and ends there.
//

#include "pch.h"
#include <iostream>
#include <thread>
#include <chrono>
#include "executor.h"
#include <set>


static std::set<std::thread::id> tids;
static std::mutex mutex1;

void print_thread_id() {
	std::cout << "Current thread ID: " << std::this_thread::get_id() << std::endl;
}

class ExecutableTask : public executable 
{
public:
	ExecutableTask() 
	{
		instance = count++;
	}

	void execute() noexcept override;

private:
	static std::atomic<int> count;
	int instance;
};

std::atomic<int> ExecutableTask::count = 0;

void ExecutableTask::execute() noexcept
{
	std::this_thread::sleep_for(std::chrono::microseconds(100));

	std::unique_lock<std::mutex> lock(mutex1);
	std::cout << "Executing #" << instance << " on ";
	print_thread_id();
	tids.insert(std::this_thread::get_id());
}

int main()
{
	std::vector<executable_ptr> tasks;
	for (int i = 0; i < 100; i++)
	{
		tasks.emplace_back(new ExecutableTask);
	}
	{
		auto& myExecutor = executor_provider<8>::getExecutor();
		for (auto& t : tasks)
		{
			myExecutor.schedule(t);
		}
		myExecutor.stop();
	}

	std::cout << "List of threads" << std::endl;
	for (const auto& tid : tids)
	{
		std::cout << "TID = " << tid << std::endl;
	}

}

