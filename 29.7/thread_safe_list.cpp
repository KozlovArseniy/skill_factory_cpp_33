//
// Created by arseniy on 01.02.24.
//

#include <iostream>
#include <thread>
#include "thread_safe_list.hpp"


FineGrainedQueue::FineGrainedQueue(const int value){
	this->head = new Node();
	this->head->node_mutex = new std::mutex();
	this->head->value = value;
	this->head->next = nullptr;

	this->queue_mutex = new std::mutex();
}

void FineGrainedQueue::insertIntoMiddle(const int value, const int pos){

	std::cout<<std::this_thread::get_id()<<std::endl;

	Node *cur;
	this->queue_mutex->lock();
	//Обработка случая пустого списка

	cur = this->head;

	Node* new_element = new Node();
	new_element->node_mutex = new std::mutex();
	new_element->next = nullptr;
	new_element->value = value;
	int current_pos = 1;
	if (cur) // проверили и только потом залочили
		cur->node_mutex->lock();
	while (cur)
	{
		if( current_pos == pos || cur->next == nullptr )
		{
			new_element->next = cur->next;
			cur->next = new_element;
			cur->node_mutex->unlock();
			this->queue_mutex->unlock();
			return;
		}
		Node* prev = cur;
		cur = cur->next;
		prev->node_mutex->unlock();
		if (cur) // проверили и только потом залочили
			cur->node_mutex->lock();
	}

}

void FineGrainedQueue::NotSafePrint(){
	Node *cur;
	cur = this->head;
	while(cur != nullptr){
		std::cout<<cur->value<<std::endl;
		cur = cur->next;
	}
}