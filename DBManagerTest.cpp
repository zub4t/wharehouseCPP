#include <iostream>
#include <string>
#include "DBManager.h" // Include your DBManager header here

class DBManagerTest {
private:
    DBManager dbManager;

public:
    DBManagerTest() : dbManager("tcp://127.0.0.1:3306", "admin", "password", "WharehouseDB") {}

    void testInsert() {
        std::string insertQuery = "INSERT INTO asset (name, amount, price) VALUES ('New Asset', 10, 100)";
        if (dbManager.execute(insertQuery)) {
            std::cout << "Insert operation successful." << std::endl;
        } else {
            std::cout << "Insert operation failed." << std::endl;
        }
    }

    void testSelect() {
        std::string selectQuery = "SELECT * FROM asset";
        if (dbManager.execute(selectQuery)) {
            std::cout << "Select operation successful." << std::endl;
            sql::ResultSet* results = dbManager.getResults();
            while (results->next()) {
                std::cout << "ID: " << results->getInt("id")
                          << ", Name: " << results->getString("name")
                          << ", Amount: " << results->getInt("amount")
                          << ", Price: " << results->getInt("price") << std::endl;
            }
        } else {
            std::cout << "Select operation failed." << std::endl;
        }
    }

    void testUpdate() {
        std::string updateQuery = "UPDATE asset SET price = 150 WHERE name = 'New Asset'";
        if (dbManager.execute(updateQuery)) {
            std::cout << "Update operation successful." << std::endl;
        } else {
            std::cout << "Update operation failed." << std::endl;
        }
    }

    void testDelete() {
        std::string deleteQuery = "DELETE FROM asset WHERE name = 'New Asset'";
        if (dbManager.execute(deleteQuery)) {
            std::cout << "Delete operation successful." << std::endl;
        } else {
            std::cout << "Delete operation failed." << std::endl;
        }
    }
};

int main() {
    DBManagerTest test;

    test.testInsert();
    test.testSelect();
    test.testUpdate();
    test.testSelect(); // To verify the update
    test.testDelete();
    test.testSelect(); // To verify the delete

    return 0;
}

