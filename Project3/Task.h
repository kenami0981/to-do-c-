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


	void add_task(sql::ResultSet* res, sql::Statement* stmt, sql::Connection* con) {
		string insertDataSQL =
			"INSERT INTO TODO (task, done) VALUES "
			"('" + name + "', " + (done ? "1" : "0") + ")";

		stmt->execute(insertDataSQL);

	};
	friend void add_task(sql::ResultSet* res, sql::Statement* stmt, sql::Connection* con);
};