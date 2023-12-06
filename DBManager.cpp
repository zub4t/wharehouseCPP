#include "DBManager.h"

DBManager::DBManager(const std::string& host, const std::string& user, const std::string& pass, const std::string& db) {
    try {
        sql::mysql::MySQL_Driver* driver = sql::mysql::get_mysql_driver_instance();
        con.reset(driver->connect(host, user, pass));
        con->setSchema(db);
    } catch (sql::SQLException& e) {
        std::cerr << "Error connecting to the database: " << e.what() << std::endl;
    }
}

bool DBManager::execute(const std::string& query) {
    try {
        stmt.reset(con->createStatement());
        if (query.find("SELECT") == 0 || query.find("select") == 0) {
            res.reset(stmt->executeQuery(query));
            return true;
        } else {
            stmt->execute(query);
            return true;
        }
    } catch (sql::SQLException& e) {
        std::cerr << "Error executing query: " << e.what() << std::endl;
        return false;
    }
}

sql::ResultSet* DBManager::getResults() const {
    return res.get();
}

