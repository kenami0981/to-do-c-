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

	void show_tasks(sql::Statement* stmt, sql::Connection* con) {
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
	void add_task(sql::ResultSet* res, sql::Statement* stmt, sql::Connection* con) {
		string insertDataSQL =
			"INSERT INTO TODO (task, done) VALUES "
			"('" + name + "', " + (done ? "1" : "0") + ")";

		stmt->execute(insertDataSQL);

	};
	friend void add_task(sql::ResultSet* res, sql::Statement* stmt, sql::Connection* con);
};