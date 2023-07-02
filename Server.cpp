#include "Server.hpp"

Server::Server() {
    int rc = sqlite3_open(NameDataBase.c_str(), &DataBase);
    if (rc != SQLITE_OK) {
        std::cerr << "Can't create data base\n";
        throw BadEdit("Failed creating data base\n");
    }
}

Server::~Server() {
    sqlite3_close(DataBase);
}

bool Server::RemoveAllTables() {
    for (auto &table_name: tables) {
        std::string sql = "DROP TABLE IF EXISTS " + table_name + ";";
        int rc = sqlite3_exec(DataBase, sql.c_str(), nullptr, nullptr, nullptr);
        if (rc != SQLITE_OK) {
            std::cerr << "Failed to drop table: " << sqlite3_errmsg(DataBase) << std::endl;
            throw BadDrop{"Failed to drop table\n "};
        }
    }
    return true;
}

std::string Server::FiltrationBy(std::string filter, std::string table_name) {
    std::string filtrate_table;
    sqlite3_stmt *statement;
    std::string query = "SELECT * FROM " + table_name + " WHERE " + filter;
    int rc = sqlite3_prepare_v2(DataBase, query.c_str(), -1, &statement, 0);
    if (rc != SQLITE_OK) {
        std::cout << "Failed to prepare SQL-query\n";
        throw BadPrepare{"Failed to prepare SQL-query\n"};
    }
    return GetResponse(query, statement);
}

std::string Server::GetResponse(std::string query, sqlite3_stmt *statement) {
    std::string res_table;
    int rc = sqlite3_prepare_v2(DataBase, query.c_str(), -1, &statement, 0);
    if (rc == SQLITE_OK) {
        int columnCount = sqlite3_column_count(statement);
        std::vector<std::string> columnNames;
        std::vector<std::vector<std::string>> rows;

        for (int i = 0; i < columnCount; i++) {   //getting column names
            const char *columnName = sqlite3_column_name(statement, i);
            columnNames.emplace_back(columnName);
        }

        while (sqlite3_step(statement) == SQLITE_ROW) {  //getting appropriate rows values
            std::vector<std::string> rowValues;
            for (int i = 0; i < columnCount; i++) {
                const unsigned char *columnValue = sqlite3_column_text(statement, i);
                rowValues.emplace_back(reinterpret_cast<const char *>(columnValue));
            }
            rows.emplace_back(rowValues);
        }

        std::vector<int> columnWidths(columnCount, 0);

        for (int i = 0; i < columnCount; i++) {
            columnWidths[i] = columnNames[i].length();
            for (const auto &row: rows) {
                int valueLength = row[i].length();
                if (valueLength > columnWidths[i]) {
                    columnWidths[i] = valueLength;
                }
            }
        }


        for (int i = 0; i < columnCount; i++) {
            res_table += columnNames[i];
            res_table += std::string(columnWidths[i] - columnNames[i].length() + 1, ' ');
        }
        res_table += "\n";

        for (const auto &row: rows) {
            for (int i = 0; i < columnCount; i++) {
                res_table += row[i];
                res_table += std::string(columnWidths[i] - row[i].length() + 1, ' ');
            }
            res_table += "\n";
        }
    } else {
        std::cerr << "Failed to execute the query: " << sqlite3_errmsg(DataBase) << std::endl;
        // add exception
    }
    return res_table;
}

std::string Server::SortBy(std::string sort_by, std::string table_name) {
    sqlite3_stmt *statement;
    std::string query = "SELECT * FROM " + table_name + " ORDER BY " + sort_by;
    return GetResponse(query, statement);
}

std::string Server::ParseColumns(std::string p) {
    std::stringstream ss{p};
    std::string word;
    std::string tmp = "";
    ss >> word;
    tmp += word;
    while (ss >> word) {
        tmp += ", " + word;
    }
    return tmp;
}

Tables Server::ColumnsInfo() {
    Tables col_info;
    for (auto &table_name: tables) {
        std::stringstream ss;
        std::string query = "PRAGMA table_info(" + table_name + ");";
        sqlite3_stmt *stmt;
        int rc = sqlite3_prepare_v2(DataBase, query.c_str(), -1, &stmt, nullptr);
        if (rc != SQLITE_OK) {
            std::cerr << "Failed to prepare SQL statement: " << sqlite3_errmsg(DataBase) << std::endl;
            throw BadPrepare("Failed to prepare SQL statement\n");
        }
        ss << "Column names: ";
        while (sqlite3_step(stmt) == SQLITE_ROW) {
            std::string column_name(reinterpret_cast<const char *>(sqlite3_column_text(stmt, 1)));
            std::string data_type(reinterpret_cast<const char *>(sqlite3_column_text(stmt, 2)));
            ss << column_name << ' ';
        }
        ss << std::endl;
        col_info[table_name] = ss.str();
    }
    return col_info;
}

bool Server::CreateTable(std::string file_name) {          //creating a table, file's name is table's name
    tables.push_back(file_name);
    std::fstream data_file(file_name);
    if (!data_file) {
        std::cerr << "Failed to open file." << std::endl;
        throw std::ifstream::failure("Failed open file");
    }
    std::string columns;
    getline(data_file, columns);  //getting columns in file
    std::string tmp = ParseColumns(columns);
    auto temp = "CREATE TABLE IF NOT EXISTS " + file_name + " (" + tmp + ");";
    int rc = sqlite3_exec(DataBase, temp.c_str(), nullptr, nullptr, nullptr);
    if (rc != SQLITE_OK) {
        std::cerr << "Failed to insert data into users table: " << sqlite3_errmsg(DataBase) << std::endl;
        throw BadEdit("Failed to insert data into users table");
    }
    std::string fileLine;    // copy table from file to sql table
    while (getline(data_file, fileLine)) {
        fileLine = ParseColumns(fileLine);
        std::string sql_req = "INSERT INTO " + file_name + " (" + tmp + ") VALUES " + "(" + fileLine + ")";
        char *err_msg;
        rc = sqlite3_exec(DataBase, sql_req.c_str(), nullptr, nullptr, nullptr);
        if (rc != SQLITE_OK) {
            std::cerr << "Can't insert into table: " << sqlite3_errmsg(DataBase) << std::endl;
            throw BadEdit("Failed insert into tabl\ne");
        }
    }
    return true;
}

void Server::Display(std::string name_table) {
    int rc = sqlite3_open(NameDataBase.c_str(), &DataBase);
    if (rc != SQLITE_OK) {
        std::cerr << "Can't open database\n";
        throw BadEdit("Failed open data base\n");
    }

    sqlite3_stmt *stmt;
    std::string sql = "SELECT * FROM " + name_table + ";";
    rc = sqlite3_prepare_v2(DataBase, sql.c_str(), -1, &stmt, 0);
    if (rc != SQLITE_OK) {
        std::cerr << "Can't prepare SQL statement: " << sqlite3_errmsg(DataBase) << std::endl;
        throw BadPrepare("Failed prepare SQL statement");
    }
    // Getting info about columns
    int columnCount = sqlite3_column_count(stmt);
    std::vector<int> columnWidths(columnCount, 0);
    for (int i = 0; i < columnCount; i++) {
        columnWidths[i] = std::strlen(sqlite3_column_name(stmt, i));
    }

    // Width each column
    while (sqlite3_step(stmt) == SQLITE_ROW) {
        for (int i = 0; i < columnCount; i++) {
            int width = std::strlen(reinterpret_cast<const char *>(sqlite3_column_text(stmt, i)));
            if (width > columnWidths[i]) {
                columnWidths[i] = width;
            }
        }
    }
    std::cout << "Table name: " << name_table << std::endl;
    //Columns output
    for (int i = 0; i < columnCount; i++) {
        std::cout << std::left << std::setw(columnWidths[i]) << sqlite3_column_name(stmt, i) << " ";
    }
    std::cout << std::endl;

    // creating line separator
    for (int i = 0; i < columnCount; i++) {
        std::cout << std::left << std::setw(columnWidths[i]) << std::setfill('-') << "" << " ";
    }
    std::cout << std::endl;

    //Results output
    sqlite3_reset(stmt);
    while (sqlite3_step(stmt) == SQLITE_ROW) {
        for (int i = 0; i < columnCount; i++) {
            std::string value(reinterpret_cast<const char *>(sqlite3_column_text(stmt, i)));
            int padding = (columnWidths[i] - value.length()) / 2;
            std::cout << std::left << std::setw(columnWidths[i]) << std::setfill(' ')
                      << std::string(padding, ' ') + value + std::string(padding, ' ') << " ";
        }
        std::cout << std::endl;
    }
    std::cout << std::endl;
    sqlite3_finalize(stmt);
}
