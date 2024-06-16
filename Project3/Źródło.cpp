#include <cppconn/driver.h>
#include <cppconn/exception.h>
#include <cppconn/statement.h>
#include <iostream>
#include <mysql_connection.h>
#include <mysql_driver.h>
#include "Task.h"
using namespace std;
void add_task(sql::ResultSet* res, sql::Statement* stmt, sql::Connection* con);
void show_task(sql::Statement* stmt, sql::Connection* con);

// Menu nawigacyjne 
void menu(sql::ResultSet* res, sql::Statement* stmt, sql::Connection* con) {

    int wybor;

    // Zmienna do sprawdzania czy u¿ytkowanik wybra³ odpowiednie opcje dostêpne w menu
    int wykonane=0;

    // Pêtla do zapytania u¿ytkownika co chce wykonaæ 
    do {
        cout << "\nWhat would you like to do?\n1. Show me my task\n2. Add new task" << endl;
        cin >> wybor;
        if (wybor == 1) {
            wykonane = 1;
            system("cls");
            show_task(stmt, con);

        }
        else if (wybor == 2) {
            wykonane = 1;
            system("cls");
            add_task(res,stmt,con);
        }
    } while (wykonane==0);

}
// Wyœwietlanie zadañ
void show_task(sql::Statement* stmt, sql::Connection* con) {

        // Ponowne zapytanie o pobranie danych (w razie gdyby u¿ytkowanik doda³ nowe zadanie)
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
        }
        else {
            // Wyœwietlanie danych z bazy danych
            while (res->next()) {
                cout << "Task " << ++count << ": " << res->getString("task");
                cout << " " << res->getString("done") << endl;
            }
        }
            
            
        
        
    // Powrót do menu
    menu(res,stmt,con);
}

// Dodawanie zadañ
void add_task(sql::ResultSet* res, sql::Statement* stmt, sql::Connection* con) {
    string task_name;
    cout << "Enter your task: ";
    cin.ignore();
    getline(cin, task_name);
    Task t1(task_name);
        // SQL query to insert data into the table
        string insertDataSQL =
            "INSERT INTO TODO (task, done) VALUES "
            "('" + t1.name + "', " + (t1.done ? "1" : "0") + ")";
        
        stmt->execute(insertDataSQL);
 
    menu(res, stmt,con);
}

int main() {
    // Próba po³¹czenia siê do bazy danych
    try {
        sql::mysql::MySQL_Driver* driver;
        sql::Connection* con;

        driver = sql::mysql::get_mysql_driver_instance();
        con = driver->connect("tcp://localhost:3306", "root", "root");

        sql::Statement* stmt = con->createStatement();

        // Tworzenie bazy jeœli ona nie istnieje
        stmt->execute("CREATE DATABASE IF NOT EXISTS todo");

        // U¿ycie bazy danych
        con->setSchema("todo");

        // Tworzenie tablicy
        string createTableSQL =
            "CREATE TABLE IF NOT EXISTS TODO ("
            "id INT NOT NULL AUTO_INCREMENT PRIMARY KEY,"
            "task VARCHAR(255) NOT NULL,"
            "done BOOL NOT NULL"
            ")";

        stmt->execute(createTableSQL);

        // Zapytanie SQL pobieraj¹ce dane z tabeli
        string selectDataSQL = "SELECT * FROM TODO";

        sql::ResultSet* res = stmt->executeQuery(selectDataSQL);

        menu(res,stmt, con);
        // Usuwanie po³¹czenia
        delete res;
        delete stmt;
        delete con;
    }
    catch (sql::SQLException& e) {
        std::cerr << "SQL Error: " << e.what() << std::endl;
    }
    
    return 0;
}
