#include "Task.h"
void Task::compact_ID(sql::Statement* stmt) {
    std::string selectSQL = "SELECT id FROM TODO ORDER BY id";
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
    std::string resetSQL = "ALTER TABLE TODO AUTO_INCREMENT = 1";
    stmt->execute(resetSQL);
}