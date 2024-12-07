#include <iostream>
#include <vector>
#include <memory>
#include <optional>
#include <fstream>
#include <stdexcept>
#include <string>


// 地格
struct QuadGrid {
    uint8_t height = 0x00;         // 不处理类似拱门的空洞结构，只考虑地面高度
    uint8_t terrain = 0x00;        // 地形类型
    uint8_t effect = 0x00;         // 地格效果 属于空中效果 类似燃烧和浓雾不能共存
    uint64_t objectid = 0x00;      // 占用对象 包括建筑方块、单位、资源等

    // 序列化: 将 QuadGrid 对象的字段写入文件
    void Serialize(std::ofstream& ofs) const {
        ofs.write(reinterpret_cast<const char*>(&height), sizeof(height));
        ofs.write(reinterpret_cast<const char*>(&terrain), sizeof(terrain));
        ofs.write(reinterpret_cast<const char*>(&effect), sizeof(effect));
        ofs.write(reinterpret_cast<const char*>(&objectid), sizeof(objectid));
    }

    // 反序列化: 从文件读取数据并恢复 QuadGrid 对象的字段
    void Deserialize(std::ifstream& ifs) {
        ifs.read(reinterpret_cast<char*>(&height), sizeof(height));
        ifs.read(reinterpret_cast<char*>(&terrain), sizeof(terrain));
        ifs.read(reinterpret_cast<char*>(&effect), sizeof(effect));
        ifs.read(reinterpret_cast<char*>(&objectid), sizeof(objectid));
    }

    // 重载输出流运算符以支持序列化输出
    friend std::ostream& operator<<(std::ostream& os, const QuadGrid& grid) {
        os << "Height: " << +grid.height << ", "
            << "Terrain: " << +grid.terrain << ", "
            << "Effect: " << +grid.effect << ", "
            << "ObjectID: " << grid.objectid << "\n";
        return os;
    }

    // 重载输入流运算符以支持反序列化输入
    friend std::istream& operator>>(std::istream& is, QuadGrid& grid) {
        is >> grid.height >> grid.terrain >> grid.effect >> grid.objectid;
        return is;
    }
};

class QuadGridMap {
public:
    uint8_t version = 1;        // 地图版本
    uint8_t row = 0;            // 地图的行数 (高度)
    uint8_t col = 0;            // 地图的列数 (宽度)
    std::vector<std::vector<QuadGrid>> gridMap;  // 组成地图的二维网格

    QuadGridMap(uint8_t version, uint8_t row, uint8_t col)
        : version(version), row(row), col(col) {
        gridMap.resize(row, std::vector<QuadGrid>(col));  // 行数为 row，列数为 col
    }

    // 获取指定位置的 QuadGrid 指针
    QuadGrid* Get(uint8_t x, uint8_t y)
    {
        if (x >= col || y >= row)  // 检查是否越界
            return nullptr;
        return &gridMap[y][x];  // 返回 gridMap 中对应位置的指针
    }

    // 序列化: 将 QuadGridMap 对象的字段以及 QuadGridMap 数组写入文件
    void Serialize(const std::string& filename) const {
        std::ofstream ofs(filename, std::ios::binary);
        if (!ofs.is_open()) {
            std::cerr << "Error opening file for serialization!" << std::endl;
            return;
        }
        this->Serialize(ofs);
        ofs.close();
    }

    void Serialize(std::ofstream& ofs) const {
        // 写入版本号，row 和 col
        ofs.write(reinterpret_cast<const char*>(&version), sizeof(version));
        ofs.write(reinterpret_cast<const char*>(&row), sizeof(row));
        ofs.write(reinterpret_cast<const char*>(&col), sizeof(col));
        // 遍历并序列化二维网格
        for (size_t i = 0; i < row; ++i) {
            for (size_t j = 0; j < col; ++j) {
                gridMap[i][j].Serialize(ofs);
            }
        }
    }

    // 反序列化: 从文件读取数据并恢复 QuadGridMap 对象的字段以及 QuadGridMap 数组
    void Deserialize(const std::string& filename) {
        std::ifstream ifs(filename, std::ios::binary);
        if (!ifs.is_open()) {
            std::cerr << "Error opening file for deserialization!" << std::endl;
            return;
        }
        this->Deserialize(ifs);
        ifs.close();
    }
    
    void Deserialize(std::ifstream& ifs) {
        // 读取版本号，row 和 col
        ifs.read(reinterpret_cast<char*>(&version), sizeof(version));
        ifs.read(reinterpret_cast<char*>(&row), sizeof(row));
        ifs.read(reinterpret_cast<char*>(&col), sizeof(col));
        // 调整 gridMap 的大小
        gridMap.resize(row, std::vector<QuadGrid>(col));
        // 遍历并反序列化二维网格
        for (size_t i = 0; i < row; ++i) {
            for (size_t j = 0; j < col; ++j) {
                gridMap[i][j].Deserialize(ifs);
            }
        }
    }
    // 打印整个 QuadGridMap 信息
    void PrintMap() const {
        for (size_t i = 0; i < row; ++i) {
            for (size_t j = 0; j < col; ++j) {
                std::cout << gridMap[i][j] << " ";
            }
            std::cout << std::endl;
        }
    }
};
