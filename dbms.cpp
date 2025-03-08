#include <iostream>
#include <vector>
#include <string>
#include <unordered_map>
#include <stdexcept>

// Abstract class for database query handler
class QueryHandler {
public:
    virtual void execute() = 0; // Pure virtual function for executing queries
};

// Table class to store data in rows and columns
class Table {
private:
    std::string name;
    std::vector<std::unordered_map<std::string, std::string>> rows;
    std::unordered_map<std::string, int> indexes; // For indexing primary keys

public:
    Table(std::string tableName) : name(tableName) {}

    void insert(std::unordered_map<std::string, std::string> row) {
        rows.push_back(row);
    }

    void update(int rowIndex, std::unordered_map<std::string, std::string> newRow) {
        if (rowIndex < 0 || rowIndex >= rows.size()) {
            throw std::out_of_range("Row index out of range");
        }
        rows[rowIndex] = newRow;
    }

    void deleteRow(int rowIndex) {
        if (rowIndex < 0 || rowIndex >= rows.size()) {
            throw std::out_of_range("Row index out of range");
        }
        rows.erase(rows.begin() + rowIndex);
    }

    void select() {
        for (const auto& row : rows) {
            for (const auto& cell : row) {
                std::cout << cell.first << ": " << cell.second << "\t";
            }
            std::cout << std::endl;
        }
    }

    void addIndex(std::string column) {
        indexes[column] = rows.size();  // For simplicity, index is just a count of rows
    }

    std::string getTableName() const {
        return name;
    }

    const std::vector<std::unordered_map<std::string, std::string>>& getRows() const {
        return rows;
    }
};

// Database class to manage multiple tables
class Database {
private:
    std::unordered_map<std::string, Table*> tables; // Tables indexed by name

public:
    ~Database() {
        for (auto& table : tables) {
            delete table.second;
        }
    }

    void createTable(std::string tableName) {
        if (tables.find(tableName) != tables.end()) {
            throw std::runtime_error("Table already exists");
        }
        tables[tableName] = new Table(tableName);
    }

    Table* getTable(std::string tableName) {
        if (tables.find(tableName) == tables.end()) {
            throw std::runtime_error("Table not found");
        }
        return tables[tableName];
    }

    void executeQuery(QueryHandler* queryHandler) {
        queryHandler->execute();
    }
};

// Insert Query Handler (Implementation of the QueryHandler interface)
class InsertQueryHandler : public QueryHandler {
private:
    Table* table;
    std::unordered_map<std::string, std::string> rowData;

public:
    InsertQueryHandler(Table* t, std::unordered_map<std::string, std::string> data) : table(t), rowData(data) {}

    void execute() override {
        table->insert(rowData);
    }
};

// Update Query Handler (Implementation of the QueryHandler interface)
class UpdateQueryHandler : public QueryHandler {
private:
    Table* table;
    int rowIndex;
    std::unordered_map<std::string, std::string> newRowData;

public:
    UpdateQueryHandler(Table* t, int index, std::unordered_map<std::string, std::string> newData) : table(t), rowIndex(index), newRowData(newData) {}

    void execute() override {
        table->update(rowIndex, newRowData);
    }
};

// Delete Query Handler (Implementation of the QueryHandler interface)
class DeleteQueryHandler : public QueryHandler {
private:
    Table* table;
    int rowIndex;

public:
    DeleteQueryHandler(Table* t, int index) : table(t), rowIndex(index) {}

    void execute() override {
        table->deleteRow(rowIndex);
    }
};

// Select Query Handler (Implementation of the QueryHandler interface)
class SelectQueryHandler : public QueryHandler {
private:
    Table* table;

public:
    SelectQueryHandler(Table* t) : table(t) {}

    void execute() override {
        table->select();
    }
};

// Main function
int main() {
    try {
        // Create database instance
        Database db;

        // Create tables
        db.createTable("employees");
        db.createTable("departments");

        // Get table references
        Table* employees = db.getTable("employees");
        Table* departments = db.getTable("departments");

        // Insert some data into employees table
        InsertQueryHandler insertEmployeeQuery(employees, {{"id", "1"}, {"name", "Garvit"}, {"department", "HR"}});
        db.executeQuery(&insertEmployeeQuery);

        InsertQueryHandler insertEmployeeQuery2(employees, {{"id", "2"}, {"name", "Ashish"}, {"department", "IT"}});
        db.executeQuery(&insertEmployeeQuery2);

        // Insert some data into departments table
        InsertQueryHandler insertDeptQuery(departments, {{"id", "1"}, {"name", "HR"}});
        db.executeQuery(&insertDeptQuery);

        InsertQueryHandler insertDeptQuery2(departments, {{"id", "2"}, {"name", "IT"}});
        db.executeQuery(&insertDeptQuery2);

        // Select data from employees table
        SelectQueryHandler selectEmployeeQuery(employees);
        db.executeQuery(&selectEmployeeQuery);

        // Update a row in employees table
        UpdateQueryHandler updateEmployeeQuery(employees, 0, {{"id", "1"}, {"name", "Garvit Updated"}, {"department", "HR"}});
        db.executeQuery(&updateEmployeeQuery);

        // Delete a row from employees table
        DeleteQueryHandler deleteEmployeeQuery(employees, 1);
        db.executeQuery(&deleteEmployeeQuery);

        // Select data from employees table after update and delete
        std::cout << "Employees after update and delete:" << std::endl;
        db.executeQuery(&selectEmployeeQuery);

    } catch (const std::exception& e) {
        std::cerr << "Error: " << e.what() << std::endl;
    }

    return 0;
}
