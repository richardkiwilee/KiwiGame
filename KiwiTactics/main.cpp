#include "game/Manager.h"
#include <iostream>
#include <string>
#include <sstream>
#include "data/SQLiteManager.h"
std::string getStringByIndex(const std::string& str, size_t index) {
    std::stringstream ss(str);
    std::string word;
    std::vector<std::string> words;

    // 使用stringstream按空格分割字符串
    while (ss >> word) {
        words.push_back(word);
    }

    // 检查索引是否有效
    if (index < words.size()) {
        return words[index];
    }
    else {
        return ""; // 返回空字符串表示索引无效
    }
}
void handleCommand(ArchiveManager* manager, const std::string& input) {
    std::string command = getStringByIndex(input, 0);
    if (command == "db")
    {
        SQLiteManager& manager = SQLiteManager::getInstance();
        // 加载数据库
        manager.loadDatabase("D:\\KiwiGame\\database\\data.db");

        std::vector<std::vector<std::string>> result;
        std::string query = "SELECT * FROM Terrain";

        if (manager.executeSelectQuery(query, result)) {
            // 输出查询结果
            for (const auto& row : result) {
                for (const auto& cell : row) {
                    std::cout << cell << " ";
                }
                std::cout << std::endl;
            }
        }
        else {
            std::cerr << "Query execution failed." << std::endl;
        }
        return;

    }
    if (command == "test")
    {
        SkillManager mgr = SkillManager();
        mgr.Register(nullptr, 1, "register.py", "FireBall");
        DamageCalcuteInfo t;
        t.Attacker.Armor = 10;
        auto _func1 = mgr.Get(1);
        double damage1 = _func1(&t);
        std::cout << "Result of FireBall: " << damage1 << std::endl;
        return;
    }
    if (command == "exit") {
        std::cout << "Goodbye!" << std::endl;
        exit(0);
    }
    std::cout << "Unknown command: " << command << std::endl;
}

int main() {
    ArchiveManager manager = ArchiveManager();
    
    std::string input;
    while (std::cin && !(std::getline(std::cin, input) && input == "quit")) {
        handleCommand(&manager, input);
    }

    return 0;
}