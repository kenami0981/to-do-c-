#pragma once
#include<iostream>
#include <cppconn/driver.h>
#include <cppconn/exception.h>
#include <cppconn/statement.h>
#include <iostream>
#include <mysql_connection.h>
#include <mysql_driver.h>
using namespace std;

class Task {

	string name;
	bool done = false;
public:
	Task(string _name) {
		name = _name;
	}

    void mark_task_done(sql::Statement* stmt, sql::Connection* con);


    // Dodawanie zadañ
    void get_task_from_user(sql::ResultSet* res, sql::Statement* stmt, sql::Connection* con);
    void deleteTask(sql::Statement* stmt, sql::Connection* con);
    // Wyœwietlanie zadañ
    void show_tasks(sql::Statement* stmt, sql::Connection* con);
    void add_task(sql::ResultSet* res, sql::Statement* stmt, sql::Connection* con);
    void compact_ID(sql::Statement* stmt);
	friend void add_task(sql::ResultSet* res, sql::Statement* stmt, sql::Connection* con);
};