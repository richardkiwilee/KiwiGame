#include "QuadMap.h"
#include "Logger.h"

void QuadGrid::Serialize(std::ofstream& ofs) const {
    ofs.write(reinterpret_cast<const char*>(&height), sizeof(height));
    ofs.write(reinterpret_cast<const char*>(&terrain), sizeof(terrain));
    ofs.write(reinterpret_cast<const char*>(&effect), sizeof(effect));
    ofs.write(reinterpret_cast<const char*>(&objectid), sizeof(objectid));
}

void QuadGrid::Deserialize(std::ifstream& ifs) {
    ifs.read(reinterpret_cast<char*>(&height), sizeof(height));
    ifs.read(reinterpret_cast<char*>(&terrain), sizeof(terrain));
    ifs.read(reinterpret_cast<char*>(&effect), sizeof(effect));
    ifs.read(reinterpret_cast<char*>(&objectid), sizeof(objectid));
}

std::ostream& operator<<(std::ostream& os, const QuadGrid& grid) {
    os << "Height: " << +grid.height << ", "
        << "Terrain: " << +grid.terrain << ", "
        << "Effect: " << +grid.effect << ", "
        << "ObjectID: " << grid.objectid << "\n";
    return os;
}

std::istream& operator>>(std::istream& is, QuadGrid& grid) {
    is >> grid.height >> grid.terrain >> grid.effect >> grid.objectid;
    return is;
}

QuadGridMap::QuadGridMap(uint8_t version, uint8_t row, uint8_t col, int64_t seed)
    : version(version), row(row), col(col) {
    gridMap.resize(row, std::vector<QuadGrid>(col));  
    this->seed = seed;
    _randomization();
}

QuadGrid* QuadGridMap::Get(uint8_t x, uint8_t y) {
    if (x >= col || y >= row)
        return nullptr;
    return &gridMap[y][x];  
}

void QuadGridMap::Serialize(const std::string& filename) const {
    std::ofstream ofs(filename, std::ios::binary);
    if (!ofs.is_open()) {
        Logger::getInstance().Error("Error opening file for serialization!");
        return;
    }
    this->Serialize(ofs);
    ofs.close();
}

void QuadGridMap::Serialize(std::ofstream& ofs) const {
    ofs.write(reinterpret_cast<const char*>(&version), sizeof(version));
    ofs.write(reinterpret_cast<const char*>(&row), sizeof(row));
    ofs.write(reinterpret_cast<const char*>(&col), sizeof(col));
    ofs.write(reinterpret_cast<const char*>(&seed), sizeof(seed));
    
    for (size_t i = 0; i < row; ++i) {
        for (size_t j = 0; j < col; ++j) {
            gridMap[i][j].Serialize(ofs);
        }
    }
}

void QuadGridMap::Deserialize(const std::string& filename) {
    std::ifstream ifs(filename, std::ios::binary);
    if (!ifs.is_open()) {
        Logger::getInstance().Error("Error opening file for deserialization!");
        return;
    }
    this->Deserialize(ifs);
    ifs.close();
}

void QuadGridMap::Deserialize(std::ifstream& ifs) {
    ifs.read(reinterpret_cast<char*>(&version), sizeof(version));
    ifs.read(reinterpret_cast<char*>(&row), sizeof(row));
    ifs.read(reinterpret_cast<char*>(&col), sizeof(col));
    ifs.read(reinterpret_cast<char*>(&seed), sizeof(seed));
    
    gridMap.resize(row, std::vector<QuadGrid>(col));
    
    for (size_t i = 0; i < row; ++i) {
        for (size_t j = 0; j < col; ++j) {
            gridMap[i][j].Deserialize(ifs);
        }
    }
}

void QuadGridMap::PrintMap() const {
    for (size_t i = 0; i < row; ++i) {
        for (size_t j = 0; j < col; ++j) {
            std::cout << gridMap[i][j] << " ";
        }
        std::cout << std::endl;
    }
}

void QuadGridMap::_randomization() {
    for (uint8_t i = 0; i < 50; ++i) {
        for (uint8_t j = 0; j < 50; ++j) {
            gridMap[i][j].height = i + j;
            gridMap[i][j].terrain = (i + j) % 3;
            gridMap[i][j].effect = (i + j) % 2;
            gridMap[i][j].objectid = 1234567890123456 + (i * 10 + j);
        }
    }
}