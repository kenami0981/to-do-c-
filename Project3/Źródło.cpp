#include <cppconn/driver.h>
#include <cppconn/exception.h>
#include <cppconn/statement.h>
#include <iostream>
#include <mysql_connection.h>
#include <mysql_driver.h>
#include "Task.h"
using namespace std;
void menu(sql::ResultSet* res, sql::Statement* stmt, sql::Connection* con);

// Menu nawigacyjne 

void mark_task_done(sql::Statement* stmt, sql::Connection* con) {

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

    // Powrót do menu
    menu(res, stmt, con);
}
// Wyœwietlanie zadañ
void show_task(sql::Statement* stmt, sql::Connection* con) {   
    Task t0("wyœwietl");
    t0.show_tasks(stmt, con);
    string selectDataSQL = "SELECT * FROM TODO";
    sql::ResultSet* res = stmt->executeQuery(selectDataSQL);
    // Powrót do menu
    menu(res,stmt,con);
}

// Dodawanie zadañ
void get_task_from_user(sql::ResultSet* res, sql::Statement* stmt, sql::Connection* con) {
    Task t2("test");
    t2.show_tasks(stmt, con);
    string task_name;
    cout << "Enter your task: ";
    cin.ignore();
    getline(cin, task_name);
    Task t1(task_name);
    t1.add_task(res, stmt, con);
 
    menu(res, stmt,con);
}
void deleteTask(sql::Statement* stmt, sql::Connection* con) {
    Task t1("test");
    t1.show_tasks(stmt, con);
    //show_task(stmt,con);
    string taskID;
    cout << "Enter your task you would like to mark as done: ";
    cin.ignore();
    cin >> taskID;
    std::string deleteSQL = "DELETE FROM TODO WHERE id = '" + taskID + "'";
    stmt->execute(deleteSQL);
    string selectSQL = "SELECT id FROM TODO ORDER BY id";
    sql::ResultSet* res = stmt->executeQuery(selectSQL);

    int newId = 1;
    while (res->next()) {
        int oldId = res->getInt("id");
        if (oldId != newId) {
            std::string updateSQL = "UPDATE TODO SET id = " + std::to_string(newId) + " WHERE id = " + std::to_string(oldId);
            stmt->execute(updateSQL);
        }
        newId++;
    }
    
    menu(res, stmt, con);
}
void menu(sql::ResultSet* res, sql::Statement* stmt, sql::Connection* con) {

    string choice;

    // Zmienna do sprawdzania czy u¿ytkowanik wybra³ odpowiednie opcje dostêpne w menu
    int wykonane = 0;

    // Pêtla do zapytania u¿ytkownika co chce wykonaæ 
    do {
        cout << "\nWhat would you like to do?\n1. Show me my task\n2. Add new task\n3. Mark task as done\n4. Delete task" << endl;
        cin >> choice;
        if (choice == "1") {
            wykonane = 1;
            system("cls");
            show_task(stmt, con);

        }
        else if (choice == "2") {
            wykonane = 1;
            system("cls");
            get_task_from_user(res, stmt, con);
        }
        else if (choice == "3") {
            wykonane = 1;
            system("cls");
            mark_task_done(stmt, con);
        }
        else if (choice == "4") {
            wykonane = 1;
            system("cls");
            deleteTask(stmt, con);
        }
    } while (wykonane == 0);

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
