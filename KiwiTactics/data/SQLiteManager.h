#ifndef SQLITEMANAGER_H
#define SQLITEMANAGER_H

#include <string>
#include <vector>
#include <iostream>
#include <filesystem>

// 使用 C++17 的 filesystem 命名空间
namespace fs = std::filesystem;

class SQLiteManager {
public:
    // 获取单例实例
    static SQLiteManager& getInstance();

    // 禁止拷贝构造和赋值操作符
    SQLiteManager(const SQLiteManager&) = delete;
    SQLiteManager& operator=(const SQLiteManager&) = delete;

    // 加载指定数据库
    bool loadDatabase(const std::string& dbPath);

    // 加载目录下的所有数据库
    bool loadAllDatabasesInDirectory(const std::string& directoryPath);

    // 保存当前数据库到指定目录
    bool saveDatabase(const std::string& targetDirectory);

    // 执行 SQL 文件中的所有语句
    bool executeSQLFile(const std::string& sqlFilePath);

    // 执行单个 SQL 语句
    bool executeSQL(const std::string& sql);

private:
    // 私有构造函数和析构函数
    SQLiteManager();
    ~SQLiteManager();

    // SQLite 的内部数据库指针
    void* db = nullptr;

    // 当前加载的数据库路径
    std::string currentDBPath;

    // 执行 SQL 语句时的回调函数
    static int callback(void* data, int argc, char** argv, char** colName);
};

#endif // SQLITEMANAGER_H


/*
#include "SQLiteManager.h"

int main() {
    SQLiteManager& manager = SQLiteManager::getInstance();

    // 加载数据库
    manager.loadDatabase("example.db");

    // 执行 SQL 语句
    manager.executeSQL("CREATE TABLE IF NOT EXISTS test (id INTEGER PRIMARY KEY, name TEXT);");

    // 执行 SQL 文件
    manager.executeSQLFile("script.sql");

    // 保存数据库到指定目录
    manager.saveDatabase("backup");

    // 加载目录中的所有数据库
    manager.loadAllDatabasesInDirectory("databases");

    return 0;
}

*/