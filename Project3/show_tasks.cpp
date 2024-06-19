#include "Task.h"
#include<iomanip>

void Task::show_tasks(sql::Statement* stmt, sql::Connection* con) {
    string selectDataSQL = "SELECT * FROM TODO";
    sql::ResultSet* res = stmt->executeQuery(selectDataSQL);


    // Pobranie iloœci danych z tablicy aby sprawdziæ czy baza jest pusta
    string countSQL = "SELECT COUNT(*) AS count FROM TODO";
    sql::Statement* stmt1 = con->createStatement();
    sql::ResultSet* res1 = stmt1->executeQuery(countSQL);
    res1->next();
    int ID_count = res1->getInt("count");
    int count = 0;

    // Sprawdzanie czy baza jest pusta
    if (ID_count == 0) {
        cout << "   +----------------------------------------------------------------------------------+" << endl;
        cout << "                                   No tasks available." << endl;
        cout << "   +----------------------------------------------------------------------------------+" << endl;
        string resetSQL = "ALTER TABLE TODO AUTO_INCREMENT = 1";
        stmt->execute(resetSQL);
    }
    else {
        // Wyœwietlanie danych z bazy danych
        cout << endl;
        cout << "   +------+--------------------------------------------------------------------+------+" << endl;
        cout << "   |  ID  | Task                                                               | Done |" << endl;
        cout << "   +------+--------------------------------------------------------------------+------+" << endl;
        while (res->next()) {
            string task = res->getString("task");
            if (task.length() > 60) {
                task = task.substr(0, 57) + "...";
                cout << "   | " << setw(4) << right << res->getInt("id") << " | " << left << setw(66) << task << " | " << setw(4) << (res->getInt("done") ? "Yes" : "No") << " |" << endl;
            }
            else {
            cout << "   | " << setw(4) <<right << res->getInt("id") << " | " << left << setw(66) << res->getString("task") << " | " <<setw(4)<< (res->getInt("done") ? "Yes" : "No") << " |" << endl;
            }
        }
        cout << "   +------+--------------------------------------------------------------------+------+" << endl;
    }
    
}