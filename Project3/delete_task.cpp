#include "Task.h"
void Task::deleteTask(sql::Statement* stmt, sql::Connection* con) {
    Task t0("wyœwietlanie");
    t0.show_tasks(stmt, con);
    string taskID;
    cout << "Enter your task you would like to mark as done: ";
    cin.ignore();
    cin >> taskID;
    string deleteDataSQL = "DELETE FROM TODO WHERE id = " + taskID;
    stmt->execute(deleteDataSQL);
    compact_ID(stmt);


}