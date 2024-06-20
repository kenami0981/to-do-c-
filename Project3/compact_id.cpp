#include "Task.h"
//Updatowanie ID aby by³o po kolei po usuniêciu taska
void Task::compact_ID(sql::Statement* stmt) {
    string selectSQL = "SELECT id FROM TODO ORDER BY id";
    sql::ResultSet* res = stmt->executeQuery(selectSQL);

    int newId = 1;
    while (res->next()) {
        int oldId = res->getInt("id");
        if (oldId != newId) {
            string updateSQL = "UPDATE TODO SET id = " + to_string(newId) + " WHERE id = " + to_string(oldId);
            stmt->execute(updateSQL);
        }
        newId++;
    }
    string resetSQL = "ALTER TABLE TODO AUTO_INCREMENT = 1";
    stmt->execute(resetSQL);
}