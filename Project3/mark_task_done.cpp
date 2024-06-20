#include "Task.h"


using namespace std;
// Zaznaczenie czy zadanie zosta³o wykonane
void Task::mark_task_done(sql::Statement* stmt, sql::Connection* con) {
    Task t0("wyœwietl");
    t0.show_tasks(stmt, con);
    // Ponowne zapytanie o pobranie danych (w razie gdyby u¿ytkowanik doda³ nowe zadanie)

    string taskID;
    cout << endl;
    cout << "   Enter the ID of the task you would like to mark as done : ";
    cin.ignore();
    getline(cin, taskID);
    string maxIdSQL = "SELECT MAX(id) AS max_id FROM TODO";
    sql::ResultSet* res = stmt->executeQuery(maxIdSQL);


    if (res->next()) {
        if (res->getInt("max_id") < stoi(taskID)) {
            cout << "   Task with ID " << taskID << " does not exist." << endl;
            Sleep(3000);
        }
        else {
            
            string updateSQL = "UPDATE TODO SET done = 1 WHERE id = '" + taskID + "'";
            stmt->execute(updateSQL);
        }
    }
};
