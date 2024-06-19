#include "Task.h"


using namespace std;

void Task::mark_task_done(sql::Statement* stmt, sql::Connection* con) {
    Task t0("wyœwietl");
    t0.show_tasks(stmt, con);
    // Ponowne zapytanie o pobranie danych (w razie gdyby u¿ytkowanik doda³ nowe zadanie)
    string selectDataSQL = "SELECT * FROM TODO";
    sql::ResultSet* res = stmt->executeQuery(selectDataSQL);

    string taskID;
    cout << "Enter your task you would like to mark as done: ";
    cin.ignore();
    getline(std::cin, taskID);
    std::string updateSQL = "UPDATE TODO SET done = 1 WHERE id = '" + taskID + "'";
    stmt->execute(updateSQL);
};
