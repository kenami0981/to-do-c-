#include "Task.h"
//Dodanie zadania do bazy danych
void Task::add_task(sql::ResultSet* res, sql::Statement* stmt, sql::Connection* con) {
	compact_ID(stmt);
	string insertDataSQL =
		"INSERT INTO TODO (task, done, deadline) VALUES "
		"('" + name + "', " + (done ? "1" : "0") + ", '"+ deadline+ "')";

	stmt->execute(insertDataSQL);

};