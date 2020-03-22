#include "Queue.h"

Job::Job() : next(nullptr)
{

}

Queue::Queue() : head(nullptr), lock()
{

}

void Queue::Add(std::unique_ptr<Job> job)
{
	this->lock.lock();
	if (this->head == nullptr)
		this->head = std::move(job);
	else
	{
		Job* current = this->head.get();
		while (current)
		{
			if (current->next != nullptr)
			{
				current = current->next.get();
				continue;
			}
			current->next = std::move(job);
			break;
		}
	}
	this->lock.unlock();
}

std::unique_ptr<Job> Queue::Get()
{
	std::lock_guard<std::mutex> guard(this->lock);
	if (this->head == nullptr)
		return nullptr;
	std::unique_ptr<Job> result = std::move(this->head);
	std::unique_ptr<Job> newHead = std::move(result->next);
	this->head = std::move(newHead);
	return result;
}