#include "Task.h"
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
        cout << "No tasks available." << endl;
        string resetSQL = "ALTER TABLE TODO AUTO_INCREMENT = 1";
        stmt->execute(resetSQL);
    }
    else {
        // Wyœwietlanie danych z bazy danych
        while (res->next()) {
            cout << "Task " << ++count << ": " << res->getString("task");
            cout << " " << res->getString("done") << endl;
        }
    }
}