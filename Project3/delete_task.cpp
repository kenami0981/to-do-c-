#include "Task.h"
 
void Task::deleteTask(sql::Statement* stmt, sql::Connection* con) {
    Task t0("wyœwietlanie");
    t0.show_tasks(stmt, con);
    string taskID;
    string checkSQL = "SELECT COUNT(*) AS count FROM TODO WHERE id = '" + taskID + "'";
    cout << endl;
    string maxIdSQL = "SELECT MAX(id) AS max_id FROM TODO";
    sql::ResultSet* res = stmt->executeQuery(maxIdSQL);
    cout << "   Enter the ID of the task you would like to delete: ";
    cin.ignore();
    cin >> taskID;
    
    
    if (res->next()) {
        if (res->getInt("max_id") < stoi(taskID)) {
            cout << "   Task with ID " << taskID << " does not exist." << endl;
            Sleep(3000);
        }
        else {


            string deleteSQL = "DELETE FROM TODO WHERE id = '" + taskID + "'";
            stmt->execute(deleteSQL);
            cout << "Task " << taskID << " deleted." << endl;

            string selectSQL = "SELECT id FROM TODO ORDER BY id";
            res = stmt->executeQuery(selectSQL);

            string deleteDataSQL = "DELETE FROM TODO WHERE id = " + taskID;
            stmt->execute(deleteDataSQL);
            compact_ID(stmt);
        }
    }
    

}