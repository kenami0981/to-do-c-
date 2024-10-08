#include <cppconn/driver.h>
#include <cppconn/exception.h>
#include <cppconn/statement.h>
#include <iostream>
#include <mysql_connection.h>
#include <mysql_driver.h>
#include "Task.h"

using namespace std;

// Menu nawigacyjne 
void menu(sql::ResultSet* res, sql::Statement* stmt, sql::Connection* con) {
    Task t0("wy�wietl");
    string choice;

    // Zmienna do sprawdzania czy u�ytkowanik wybra� odpowiednie opcje dost�pne w menu
    int wykonane = 0;

    // P�tla do zapytania u�ytkownika co chce wykona� 
    do {
        cout << endl;
        cout << "   +----------------------------------------------------------------------------------+" << endl;
        cout << "   |                                   MAIN MENU                                      |" << endl;
        cout << "   +----------------------------------------------------------------------------------+" << endl;
        cout << "   | 1. Show me my tasks                                                              |" << endl;
        cout << "   | 2. Add new task                                                                  |" << endl;
        cout << "   | 3. Mark task as done                                                             |" << endl;
        cout << "   | 4. Delete task                                                                   |" << endl;
        cout << "   +----------------------------------------------------------------------------------+" << endl;
        cout << "   | Enter your choice (1-4): ";
        cin >> choice;
        cout << "   +----------------------------------------------------------------------------------+" << endl;
        if (choice == "1") {
            wykonane = 1;
            system("cls");
            t0.show_tasks(stmt,con);

            // Powr�t do menu
            menu(res, stmt, con);

        }
        else if (choice == "2") {
            wykonane = 1;
            system("cls");
            t0.show_tasks(stmt, con);
            t0.get_task_from_user(res, stmt, con);
            system("cls");
            t0.show_tasks(stmt, con);
            menu(res, stmt, con);
        }
        else if (choice == "3") {
            wykonane = 1;
            system("cls");
            t0.mark_task_done(stmt, con);
            system("cls");
            t0.show_tasks(stmt, con);

            // Powr�t do menu
            menu(res, stmt, con);
        }
        else if (choice == "4") {
            wykonane = 1;
            system("cls");
            t0.deleteTask(stmt, con);
            system("cls");
            t0.show_tasks(stmt, con);
            menu(res, stmt, con);
        }
    } while (wykonane == 0);

}
int main() {
    // Pr�ba po��czenia si� do bazy danych
    string password;
    cout << "Enter password to database : ";
    cin >> password;
    try {
        sql::mysql::MySQL_Driver* driver;
        sql::Connection* con;

        driver = sql::mysql::get_mysql_driver_instance();
        con = driver->connect("tcp://localhost:3306", "root", password);

        sql::Statement* stmt = con->createStatement();

        // Tworzenie bazy je�li ona nie istnieje
        stmt->execute("CREATE DATABASE IF NOT EXISTS todo");

        // U�ycie bazy danych
        con->setSchema("todo");

        // Tworzenie tablicy
        string createTableSQL =
            "CREATE TABLE IF NOT EXISTS TODO ("
            "id INT NOT NULL AUTO_INCREMENT PRIMARY KEY,"
            "task VARCHAR(255) NOT NULL,"
            "done BOOL NOT NULL,"
            "deadline VARCHAR(255)"
            ")";

        stmt->execute(createTableSQL);

        // Zapytanie SQL pobieraj�ce dane z tabeli
        string selectDataSQL = "SELECT * FROM TODO";

        sql::ResultSet* res = stmt->executeQuery(selectDataSQL);

        menu(res,stmt, con);
        // Usuwanie po��czenia
        delete res;
        delete stmt;
        delete con;
    }
    catch (sql::SQLException& e) {
        cerr << "SQL Error: " << e.what() << endl;
    }
    
    return 0;
}
