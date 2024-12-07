#include "game/Manager.h"
#include <iostream>
#include <string>
#include <sstream>
#include <spdlog/spdlog.h>
#include <spdlog/sinks/basic_file_sink.h>
#include <spdlog/sinks/stdout_color_sinks.h>
#include "utils/call_python.h"
#include "utils/call_lua.h"

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
    if (command == "test")
    {
        Py_Initialize();
        PyRun_SimpleString("import sys");
        PyRun_SimpleString("sys.path.append('.')");
        sol::state lua;
        lua.open_libraries(sol::lib::base);

        SkillManager mgr = SkillManager();
        mgr.Register(nullptr, 1, "register.py", "FireBall");
        DamageCalcuteInfo t;
        t.Attacker.Armor = 10;
        auto _func = mgr.Get(1);
        double damage = _func(&t);
        std::cout << "Result of FireBall: " << damage << std::endl;

        Py_Finalize();
        return;
    }
    if (command == "testpy")
    {
        testPy();
        return;
    }
    if (command == "testlua")
    {
        testLua();
        return;
    }
    if (command == "reglua")
    {
        sol::state lua;
        lua.open_libraries(sol::lib::base);  // 打开基本库
        lua.set_function("add", add);  // 将 C++ 函数 add 注册到 Lua 中
        // 运行 Lua 脚本，替换 add 函数
        runLuaFromFile(lua, "add.lua");
        sol::protected_function_result ret = lua["add"](3, 4);
        // 调用 Lua 中的 add 函数
        std::cout << "Result of add(3, 4): " << ret.begin()->as<int>() << std::endl;  // 输出 12（3 * 4）
        return;
    }
    if (command == "regpy")
    {
        Py_Initialize();

        // 设置 Python 脚本路径
        PyRun_SimpleString("import sys");
        PyRun_SimpleString("sys.path.append('.')");

        // 注册 Python 函数
        register_python_function("register", "A2");

        // 调用动态函数
        A1_dynamic(42); // 如果 Python 函数注册成功，将调用 Python 的 A2；否则调用 C++ 的 A1

        // 关闭 Python 解释器
        Py_Finalize();
        return;
    }
    if (command == "save") {
        manager->Serialize();
        return;
    }
    if (command == "exit") {
        std::cout << "Goodbye!" << std::endl;
        exit(0);
    }
    if (command == "load") {
        std::string filename = getStringByIndex(input, 1);
        if (filename.empty()) {
			std::cout << "Error: Please specify a filename." << std::endl;
			return;
		}
		manager->Deserialize(filename);
		return;
	}
    if (command == "print") {
        std::string tar = getStringByIndex(input, 1);
        if (tar == "map") {
			manager->map->PrintMap();
			return;
		}
        return;
    }
    std::cout << "Unknown command: " << command << std::endl;
}

int main() {
    auto console = spdlog::stdout_color_mt("console");
    console->set_level(spdlog::level::info); // 设置日志级别
    console->set_pattern("[%Y-%m-%d %H:%M:%S] [%-5l] %v"); // 设置日志格式
    auto file_logger = spdlog::basic_logger_mt("file_logger", "logs/example.log");
    file_logger->set_level(spdlog::level::debug); // 设置文件日志级别
    file_logger->set_pattern("[%Y-%m-%d %H:%M:%S] [%l] %v"); // 设置日志格式

    // 创建 QuadGridMap 对象并填充 QuadGridMap
    ArchiveManager manager = ArchiveManager("test.sav");
    manager.module = new ModuleManager();
    manager.randomBuffer = new RandomSeed(255);
    manager.inventory = new Inventory();
    manager.buildings = new ObjectsManager<Building>();
    manager.alias = new ObjectsManager<Character>();
    manager.neutrals = new ObjectsManager<Character>();
    manager.emeries = new ObjectsManager<Character>();
    manager.map = new QuadGridMap(1, 5, 5);
    for (uint8_t i = 0; i < 5; ++i) {
        for (uint8_t j = 0; j < 5; ++j) {
            manager.map->gridMap[i][j].height = i + j;
            manager.map->gridMap[i][j].terrain = (i + j) % 3;
            manager.map->gridMap[i][j].effect = (i + j) % 2;
            manager.map->gridMap[i][j].objectid = 1234567890123456 + (i * 10 + j);
        }
    }
    manager.map->PrintMap();
    
    std::string input;
    while (std::cin && !(std::getline(std::cin, input) && input == "quit")) {
        handleCommand(&manager, input);
    }
    // 输出日志
    console->info("This is an info message");
    console->warn("This is a warning message");
    console->error("This is an error message");

    // 文件日志记录
    file_logger->info("This message is logged in a file");
    file_logger->debug("This is a debug message in the file");

    // 记录异常
    try {
        throw std::runtime_error("An example exception");
    }
    catch (const std::exception& e) {
        spdlog::error("Caught an exception: {}", e.what());
    }
    return 0;
}