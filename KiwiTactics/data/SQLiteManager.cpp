#include "SQLiteManager.h"
#include <fstream>

// 声明 SQLite API 函数
extern "C" {
    typedef void sqlite3;
    int sqlite3_open(const char* filename, void** db);
    int sqlite3_exec(void* db, const char* sql, int (*callback)(void*, int, char**, char**), void* data, char** errmsg);
    int sqlite3_close(void* db);
    void sqlite3_free(void* ptr);

    #define SQLITE_OK  0
}

// 获取单例实例
SQLiteManager& SQLiteManager::getInstance() {
    static SQLiteManager instance;
    return instance;
}

// 构造函数和析构函数
SQLiteManager::SQLiteManager() = default;

SQLiteManager::~SQLiteManager() {
    if (db) {
        sqlite3_close(db);
    }
}

// 加载指定的数据库
bool SQLiteManager::loadDatabase(const std::string& dbPath) {
    if (db) {
        sqlite3_close(db);  // 关闭现有数据库
    }
    if (sqlite3_open(dbPath.c_str(), &db) != 0) {
        std::cerr << "Failed to open database." << std::endl;
        db = nullptr;
        return false;
    }
    currentDBPath = dbPath;
    std::cout << "Loaded database: " << dbPath << std::endl;
    return true;
}

// 加载目录下的所有数据库
bool SQLiteManager::loadAllDatabasesInDirectory(const std::string& directoryPath) {
    bool success = true;
    for (const auto& entry : fs::directory_iterator(directoryPath)) {
        if (entry.path().extension() == ".db") {
            success &= loadDatabase(entry.path().string());
        }
    }
    return success;
}

// 保存当前数据库到指定目录
bool SQLiteManager::saveDatabase(const std::string& targetDirectory) {
    if (currentDBPath.empty()) {
        std::cerr << "No database loaded to save." << std::endl;
        return false;
    }
    fs::path targetPath = fs::path(targetDirectory) / fs::path(currentDBPath).filename();
    try {
        fs::copy(currentDBPath, targetPath, fs::copy_options::overwrite_existing);
        std::cout << "Database saved to: " << targetPath << std::endl;
        return true;
    } catch (const fs::filesystem_error& e) {
        std::cerr << "Error saving database: " << e.what() << std::endl;
        return false;
    }
}

// 执行 SQL 文件中的所有语句
bool SQLiteManager::executeSQLFile(const std::string& sqlFilePath) {
    std::ifstream sqlFile(sqlFilePath);
    if (!sqlFile.is_open()) {
        std::cerr << "Failed to open SQL file: " << sqlFilePath << std::endl;
        return false;
    }

    std::string sql((std::istreambuf_iterator<char>(sqlFile)),
                    std::istreambuf_iterator<char>());

    return executeSQL(sql);
}

// 执行单个 SQL 语句
bool SQLiteManager::executeSQL(const std::string& sql) {
    char* errorMessage = nullptr;
    if (sqlite3_exec(db, sql.c_str(), callback, nullptr, &errorMessage) != 0) {
        std::cerr << "SQL error: " << errorMessage << std::endl;
        sqlite3_free(errorMessage);
        return false;
    }

    std::cout << "SQL executed successfully." << std::endl;
    return true;
}

// 回调函数，用于处理 SQL 查询结果
int SQLiteManager::callback(void* data, int argc, char** argv, char** colName) {
    for (int i = 0; i < argc; i++) {
        std::cout << colName[i] << " = " << (argv[i] ? argv[i] : "NULL") << std::endl;
    }
    std::cout << std::endl;
    return 0;
}

bool SQLiteManager::executeSelectQuery(const std::string& query, std::vector<std::vector<std::string>>& result) {
    if (db == nullptr) {
        std::cerr << "Database not loaded." << std::endl;
        return false;
    }

    // 清空之前的结果
    result.clear();

    // 执行查询
    char* errMsg = nullptr;
    int rc = sqlite3_exec(reinterpret_cast<sqlite3*>(db), query.c_str(), callback, &result, &errMsg);

    if (rc != SQLITE_OK) {
        std::cerr << "SQL error: " << errMsg << std::endl;
        sqlite3_free(errMsg);
        return false;
    }

    return true;
}