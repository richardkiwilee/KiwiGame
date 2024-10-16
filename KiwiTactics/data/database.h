#include <iostream>
#include <sqlite3.h>
#include <string>

using namespace std;

// 错误处理函数
void handleError(int result, sqlite3* db) {
    if (result != SQLITE_OK) {
        cerr << "SQL error: " << sqlite3_errmsg(db) << endl;
        sqlite3_close(db);
        exit(1);
    }
}

// 打印查询结果的回调函数
static int callback(void* NotUsed, int argc, char** argv, char** azColName) {
    for (int i = 0; i < argc; i++) {
        cout << azColName[i] << " = " << (argv[i] ? argv[i] : "NULL") << endl;
    }
    cout << endl;
    return 0;
}

// 加载SQLite数据库文件
sqlite3* loadDatabase(const string& filename) {
    sqlite3* db;
    int result = sqlite3_open(filename.c_str(), &db);  // 打开数据库文件
    if (result) {
        cerr << "Can't open database: " << sqlite3_errmsg(db) << endl;
        exit(1);
    } else {
        cout << "Loaded database successfully!" << endl;
    }
    return db;
}

// 执行SQL查询
void executeSQL(sqlite3* db, const string& sql) {
    char* errorMessage = 0;
    int result = sqlite3_exec(db, sql.c_str(), callback, 0, &errorMessage);
    if (result != SQLITE_OK) {
        cerr << "SQL error: " << errorMessage << endl;
        sqlite3_free(errorMessage);
    } else {
        cout << "SQL executed successfully!" << endl;
    }
}

// 创建表的SQL语句
const string createTableSQL = 
    "CREATE TABLE IF NOT EXISTS RECORDS("
    "ID INT PRIMARY KEY NOT NULL, "
    "NAME TEXT NOT NULL);";

// 示例：插入数据的SQL语句
const string insertDataSQL = 
    "INSERT INTO RECORDS (ID, NAME) VALUES (1, 'Alice'), (2, 'Bob');";

int main() {
    // 加载数据库文件（如果不存在则创建一个新的）
    sqlite3* db = loadDatabase("example.db");

    // 创建表
    executeSQL(db, createTableSQL);

    // 插入数据
    executeSQL(db, insertDataSQL);

    // 查询并打印数据
    cout << "Data in the database:" << endl;
    executeSQL(db, "SELECT * FROM RECORDS;");

    // 更新数据
    executeSQL(db, "UPDATE RECORDS SET NAME = 'Charlie' WHERE ID = 1;");

    // 删除数据
    executeSQL(db, "DELETE FROM RECORDS WHERE ID = 2;");

    // 打印修改后的数据
    cout << "Updated data in the database:" << endl;
    executeSQL(db, "SELECT * FROM RECORDS;");

    // 关闭数据库并保存文件
    sqlite3_close(db);
    cout << "Database saved and closed successfully!" << endl;

    return 0;
}
