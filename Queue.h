#pragma once
#include <memory>
#include <mutex>

class Job
{
	public:
		Job();

		std::unique_ptr<Job> next;

};

class Queue
{
	public:
		Queue();
		void Add(std::unique_ptr<Job> job);
		std::unique_ptr<Job> Get();

		std::unique_ptr<Job> head;
		std::mutex lock;
};