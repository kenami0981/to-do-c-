#include "Task.h"
void Task::get_task_from_user(sql::ResultSet* res, sql::Statement* stmt, sql::Connection* con) {
    string task_name;
    cout << "Enter your task: ";
    cin.ignore();
    getline(cin, task_name);
    Task t1(task_name);
    t1.add_task(res, stmt, con);
}