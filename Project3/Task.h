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
	string getName() const { return name; }
	bool isDone() const { return done; }
	void markDone() { done = true; }

	friend void add_task(sql::ResultSet* res, sql::Statement* stmt, sql::Connection* con);
};