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

    // ʹ��stringstream���ո�ָ��ַ���
    while (ss >> word) {
        words.push_back(word);
    }

    // ��������Ƿ���Ч
    if (index < words.size()) {
        return words[index];
    }
    else {
        return ""; // ���ؿ��ַ�����ʾ������Ч
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
        lua.open_libraries(sol::lib::base);  // �򿪻�����
        lua.set_function("add", add);  // �� C++ ���� add ע�ᵽ Lua ��
        // ���� Lua �ű����滻 add ����
        runLuaFromFile(lua, "add.lua");
        sol::protected_function_result ret = lua["add"](3, 4);
        // ���� Lua �е� add ����
        std::cout << "Result of add(3, 4): " << ret.begin()->as<int>() << std::endl;  // ��� 12��3 * 4��
        return;
    }
    if (command == "regpy")
    {
        Py_Initialize();

        // ���� Python �ű�·��
        PyRun_SimpleString("import sys");
        PyRun_SimpleString("sys.path.append('.')");

        // ע�� Python ����
        register_python_function("register", "A2");

        // ���ö�̬����
        A1_dynamic(42); // ��� Python ����ע��ɹ��������� Python �� A2��������� C++ �� A1

        // �ر� Python ������
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
    console->set_level(spdlog::level::info); // ������־����
    console->set_pattern("[%Y-%m-%d %H:%M:%S] [%-5l] %v"); // ������־��ʽ
    auto file_logger = spdlog::basic_logger_mt("file_logger", "logs/example.log");
    file_logger->set_level(spdlog::level::debug); // �����ļ���־����
    file_logger->set_pattern("[%Y-%m-%d %H:%M:%S] [%l] %v"); // ������־��ʽ

    // ���� QuadGridMap ������� QuadGridMap
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
    // �����־
    console->info("This is an info message");
    console->warn("This is a warning message");
    console->error("This is an error message");

    // �ļ���־��¼
    file_logger->info("This message is logged in a file");
    file_logger->debug("This is a debug message in the file");

    // ��¼�쳣
    try {
        throw std::runtime_error("An example exception");
    }
    catch (const std::exception& e) {
        spdlog::error("Caught an exception: {}", e.what());
    }
    return 0;
}