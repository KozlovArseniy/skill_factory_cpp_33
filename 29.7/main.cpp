#include <iostream>
#include <future>
#include <vector>
#include <csignal>
#include "thread_safe_list.hpp"

int main() {
	FineGrainedQueue queue(15);

	const int n = 150;

	std::vector<std::future<void>> future_arr;

	for (int i =0 ; i < n; i++){
		future_arr.push_back(async(std::launch::async, [&, i]() {
			queue.insertIntoMiddle(10000 +i, 20000);
		}));
	}
	sleep(10);

	for(int i =0;i<n;i++){
		future_arr[i].get();
	}
	queue.NotSafePrint();
	return 0;
}
