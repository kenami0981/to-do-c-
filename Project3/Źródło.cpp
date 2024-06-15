#include <cppconn/driver.h>
#include <cppconn/exception.h>
#include <cppconn/statement.h>
#include <iostream>
#include <mysql_connection.h>
#include <mysql_driver.h>
#include "Task.h"
using namespace std;
void add_task();
void show_task();
void menu() {
    int wybor;
    do {

        cout << "What would you like to do?\n1. Show me my task\n2. Add new task" << endl;
        cin >> wybor;
        if (wybor == 1) {
            show_task();
        }
        else if (wybor == 2) {
            add_task();
        }
    } while (wybor != 1 & wybor != 2);

}
void show_task() {
    try {
        sql::mysql::MySQL_Driver* driver;
        sql::Connection* con;

        driver = sql::mysql::get_mysql_driver_instance();
        con = driver->connect("tcp://localhost:3306", "root", "root");

        sql::Statement* stmt = con->createStatement();

        // Create the database if it does not exist
        stmt->execute("CREATE DATABASE IF NOT EXISTS todo");

        // Use the database
        con->setSchema("todo");


        // SQL query to retrieve data from the table
        string selectDataSQL = "SELECT * FROM TODO";

        sql::ResultSet* res = stmt->executeQuery(selectDataSQL);

        // Loop through the result set and display data
        int count = 0;
        while (res->next()) {
            cout << "Task " << ++count << ": " << res->getString("task") << endl;
        }

        delete res;
        delete stmt;
        delete con;
    }
    catch (sql::SQLException& e) {
        std::cerr << "SQL Error: " << e.what() << std::endl;
    }
    menu();
}
void add_task() {
    string task;
    cout << "Enter your task: ";
    cin >> task;
    Task t1(task);
    
    
    try {
        sql::mysql::MySQL_Driver* driver;
        sql::Connection* con;

        driver = sql::mysql::get_mysql_driver_instance();
        con = driver->connect("tcp://localhost:3306", "root", "root");

        sql::Statement* stmt = con->createStatement();

        // Create the database if it does not exist
        stmt->execute("CREATE DATABASE IF NOT EXISTS todo");

        // Use the database
        con->setSchema("todo");

        // SQL query to create a table
        string createTableSQL =
            "CREATE TABLE IF NOT EXISTS TODO ("
            "id INT NOT NULL AUTO_INCREMENT PRIMARY KEY,"
            "task VARCHAR(255) NOT NULL"
            ")";

        stmt->execute(createTableSQL);

        // SQL query to insert data into the table
        string insertDataSQL =
            "INSERT INTO TODO (task) VALUES "
            "('"+t1.name+"')";
        
        stmt->execute(insertDataSQL);

        
        delete stmt;
        delete con;
    }
    catch (sql::SQLException& e) {
        std::cerr << "SQL Error: " << e.what() << std::endl;
    }
    menu();
}

int main() {
    
    menu();
    return 0;
}
