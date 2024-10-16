#include <iostream>
#include <vector>
#include <memory>
#include <optional>
#include <fstream>
#include <stdexcept>
#include <string>

// 定义结构体 map grid，包含一些可空的成员。
struct MapGrid {
    std::optional<int> id;
    std::optional<std::string> name;
    std::optional<double> value;

    // 重载流运算符以支持序列化和反序列化
    friend std::ostream& operator<<(std::ostream& os, const MapGrid& grid) {
        os << (grid.id ? std::to_string(*grid.id) : "null") << " "
           << (grid.name ? *grid.name : "null") << " "
           << (grid.value ? std::to_string(*grid.value) : "null");
        return os;
    }

    friend std::istream& operator>>(std::istream& is, MapGrid& grid) {
        std::string idStr, nameStr, valueStr;
        is >> idStr >> nameStr >> valueStr;

        grid.id = (idStr != "null") ? std::stoi(idStr) : std::optional<int>{};
        grid.name = (nameStr != "null") ? nameStr : std::optional<std::string>{};
        grid.value = (valueStr != "null") ? std::stod(valueStr) : std::optional<double>{};
        return is;
    }
};

// 单例 Map 类
class Map {
private:
    std::vector<std::vector<std::vector<MapGrid>>> grid;
    static std::unique_ptr<Map> instance;

    // 私有构造函数，禁止直接创建对象
    Map() = default;

public:
    // 禁止拷贝构造和赋值操作
    Map(const Map&) = delete;
    Map& operator=(const Map&) = delete;

    // 获取单例实例的方法
    static Map& getInstance() {
        if (!instance) {
            instance.reset(new Map());
        }
        return *instance;
    }

    // 初始化三维数组
    void init(int x, int y, int z) {
        grid.resize(x, std::vector<std::vector<MapGrid>>(y, std::vector<MapGrid>(z)));
    }

    // 获取特定坐标的结构体数据
    MapGrid& get(int x, int y, int z) {
        if (x >= grid.size() || y >= grid[0].size() || z >= grid[0][0].size()) {
            throw std::out_of_range("Coordinates out of range.");
        }
        return grid[x][y][z];
    }

    // 序列化数组到文件
    void serialize(const std::string& filename) {
        std::ofstream ofs(filename);
        if (!ofs) {
            throw std::runtime_error("Failed to open file for writing.");
        }
        for (const auto& layer : grid) {
            for (const auto& row : layer) {
                for (const auto& cell : row) {
                    ofs << cell << std::endl;
                }
            }
        }
    }

    // 从文件反序列化数组
    void deserialize(const std::string& filename, int x, int y, int z) {
        std::ifstream ifs(filename);
        if (!ifs) {
            throw std::runtime_error("Failed to open file for reading.");
        }
        init(x, y, z);
        for (auto& layer : grid) {
            for (auto& row : layer) {
                for (auto& cell : row) {
                    ifs >> cell;
                }
            }
        }
    }
};

// 初始化静态成员变量
std::unique_ptr<Map> Map::instance = nullptr;

/*
int main() {
    // 获取单例实例
    Map& map = Map::getInstance();

    // 初始化3x3x3的三维数组
    map.init(3, 3, 3);

    // 设置特定坐标的结构体数据
    MapGrid& cell = map.get(1, 1, 1);
    cell.id = 42;
    cell.name = "Center";
    cell.value = 99.99;

    // 序列化数组到文件
    map.serialize("map_data.txt");

    // 反序列化数组
    Map& map2 = Map::getInstance();
    map2.deserialize("map_data.txt", 3, 3, 3);

    // 打印反序列化后的数据
    MapGrid& loadedCell = map2.get(1, 1, 1);
    std::cout << "ID: " << (loadedCell.id ? std::to_string(*loadedCell.id) : "null") << ", "
              << "Name: " << (loadedCell.name ? *loadedCell.name : "null") << ", "
              << "Value: " << (loadedCell.value ? std::to_string(*loadedCell.value) : "null")
              << std::endl;

    return 0;
}
*/