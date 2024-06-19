#include "Task.h"
void Task::add_task(sql::ResultSet* res, sql::Statement* stmt, sql::Connection* con) {
	compact_ID(stmt);
	string insertDataSQL =
		"INSERT INTO TODO (task, done) VALUES "
		"('" + name + "', " + (done ? "1" : "0") + ")";

	stmt->execute(insertDataSQL);

};