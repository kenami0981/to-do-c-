#pragma once
#include<iostream>
using namespace std;

class Task {

	string name;
	bool done = false;
public:
	Task(string _name) {
		name = _name;
	}
	friend void add_task();
};