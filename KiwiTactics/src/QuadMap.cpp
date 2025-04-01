#include "QuadMap.h"
#include "Logger.h"
#include <math.h>

QuadGridMap::QuadGridMap(uint8_t r, uint8_t c, uint8_t h, uint64_t s) : row(r), col(c), height(h), seed(s) {
    // 初始化三维网格地图
    gridMap.resize(row);
    for (auto& row_vec : gridMap) {
        row_vec.resize(col);
        for (auto& col_vec : row_vec) {
            col_vec.resize(height);
        }
    }
    _randomization();
}

QuadGrid* QuadGridMap::Get(uint8_t x, uint8_t y, uint8_t z) {
    if (x >= row || y >= col || z >= height) {
        return nullptr;
    }
    return &gridMap[x][y][z];
}

QuadGrid* QuadGridMap::Get(uint8_t x, uint8_t y) {
    if (x >= row || y >= col) {
        return nullptr;
    }
    // 返回该位置最上层的非空单元格
    for (int z = height - 1; z >= 0; --z) {
        if (gridMap[x][y][z].entity != 0) {  // 假设0表示空单元格
            return &gridMap[x][y][z];
        }
    }
    return &gridMap[x][y][0];  // 如果都是空的，返回最底层
}

bool QuadGridMap::InSight(QuadGrid* starter, QuadGrid* target) {
    if (!starter || !target) {
        return false;
    }
    
    // 获取起点和终点的坐标
    uint8_t start_x = 0, start_y = 0, start_z = 0;
    uint8_t end_x = 0, end_y = 0, end_z = 0;
    bool found_start = false, found_end = false;
    
    for (uint8_t i = 0; i < row && (!found_start || !found_end); ++i) {
        for (uint8_t j = 0; j < col && (!found_start || !found_end); ++j) {
            for (uint8_t k = 0; k < height && (!found_start || !found_end); ++k) {
                if (&gridMap[i][j][k] == starter) {
                    start_x = i;
                    start_y = j;
                    start_z = k;
                    found_start = true;
                }
                if (&gridMap[i][j][k] == target) {
                    end_x = i;
                    end_y = j;
                    end_z = k;
                    found_end = true;
                }
            }
        }
    }
    
    if (!found_start || !found_end) {
        return false;
    }
    
    // TODO: 实现更复杂的视线算法（如3D Bresenham's line算法）
    // 这里实现一个简单的检查：检查两点之间是否有实体阻挡
    return true;
}


void QuadGridMap::Serialize(const std::string& filename) const {
    std::ofstream ofs(filename, std::ios::binary);
    if (!ofs) {
        throw std::runtime_error("Cannot open file for writing: " + filename);
    }
    Serialize(ofs);
}

void QuadGridMap::Serialize(std::ofstream& ofs) const {
    // 写入基本信息
    ofs.write(reinterpret_cast<const char*>(&row), sizeof(row));
    ofs.write(reinterpret_cast<const char*>(&col), sizeof(col));
    ofs.write(reinterpret_cast<const char*>(&height), sizeof(height));
    ofs.write(reinterpret_cast<const char*>(&seed), sizeof(seed));

    // 写入网格数据
    for (const auto& row_vec : gridMap) {
        for (const auto& col_vec : row_vec) {
            for (const auto& grid : col_vec) {
                ofs.write(reinterpret_cast<const char*>(&grid.x), sizeof(grid.x));
                ofs.write(reinterpret_cast<const char*>(&grid.y), sizeof(grid.y));
                ofs.write(reinterpret_cast<const char*>(&grid.z), sizeof(grid.z));
                ofs.write(reinterpret_cast<const char*>(&grid.entity), sizeof(grid.entity));
                ofs.write(reinterpret_cast<const char*>(&grid.ground_effect), sizeof(grid.ground_effect));
                ofs.write(reinterpret_cast<const char*>(&grid.fill_effect), sizeof(grid.fill_effect));
                // 注意：不序列化指针，因为它们是运行时状态
            }
        }
    }
}

void QuadGridMap::Deserialize(const std::string& filename) {
    std::ifstream ifs(filename, std::ios::binary);
    if (!ifs) {
        throw std::runtime_error("Cannot open file for reading: " + filename);
    }
    this->Deserialize(ifs);
}

void QuadGridMap::Deserialize(std::ifstream& ifs) {
    // 读取基本信息
    ifs.read(reinterpret_cast<char*>(&row), sizeof(row));
    ifs.read(reinterpret_cast<char*>(&col), sizeof(col));
    ifs.read(reinterpret_cast<char*>(&height), sizeof(height));
    ifs.read(reinterpret_cast<char*>(&seed), sizeof(seed));

    // 调整网格大小
    gridMap.resize(row);
    for (auto& row_vec : gridMap) {
        row_vec.resize(col);
        for (auto& col_vec : row_vec) {
            col_vec.resize(height);
        }
    }

    // 读取网格数据
    for (auto& row_vec : gridMap) {
        for (auto& col_vec : row_vec) {
            for (auto& grid : col_vec) {
                ifs.read(reinterpret_cast<char*>(&grid.x), sizeof(grid.x));
                ifs.read(reinterpret_cast<char*>(&grid.y), sizeof(grid.y));
                ifs.read(reinterpret_cast<char*>(&grid.z), sizeof(grid.z));
                ifs.read(reinterpret_cast<char*>(&grid.entity), sizeof(grid.entity));
                ifs.read(reinterpret_cast<char*>(&grid.ground_effect), sizeof(grid.ground_effect));
                ifs.read(reinterpret_cast<char*>(&grid.fill_effect), sizeof(grid.fill_effect));
                // 指针初始化为nullptr
                grid.unit = nullptr;
                grid.building = nullptr;
                grid.anchor = nullptr;
            }
        }
    }
}

void QuadGridMap::_randomization() {
    // 使用seed进行地图随机化
    srand(seed);
    for (auto& row_vec : gridMap) {
        for (auto& col_vec : row_vec) {
            for (auto& grid : col_vec) {
                // 这里可以根据需要设置一些随机的地形或效果
                grid.entity = rand() % 3;  // 随机设置单元格类型
                grid.ground_effect = rand() % 2;  // 随机设置地面效果
                grid.fill_effect = rand() % 2;  // 随机设置填充效果
            }
        }
    }
}
