#ifndef DBMANAGER_H
#define DBMANAGER_H

#include <memory>
#include <string>
#include <mysql_driver.h>
#include <mysql_connection.h>
#include <cppconn/resultset.h>
#include <cppconn/statement.h>
#include <cppconn/exception.h>

class DBManager {
private:
    std::unique_ptr<sql::Connection> con;
    std::unique_ptr<sql::Statement> stmt;
    std::unique_ptr<sql::ResultSet> res;

public:
    DBManager(const std::string& host, const std::string& user, const std::string& pass, const std::string& db);
    bool execute(const std::string& query);
    sql::ResultSet* getResults() const;
};

#endif // DBMANAGER_H

