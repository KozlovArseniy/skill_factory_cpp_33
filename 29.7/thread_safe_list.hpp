//
// Created by arseniy on 01.02.24.
//
#pragma once

#include <mutex>

struct Node
{
	int value;
	Node* next;
	std::mutex* node_mutex;
};

class FineGrainedQueue
{
public:
	FineGrainedQueue() = delete;
	FineGrainedQueue(const int value);
	void insertIntoMiddle(const int value, const int pos);
	void NotSafePrint();

private:
	Node* head;
	std::mutex* queue_mutex;
};
