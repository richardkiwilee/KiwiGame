#include <iostream>
#include <fstream>
#include <cstdint>
#include <set>


class BuildingCell
{
public:
    BuildingCell() {Material = 0; x = 0; y = 0; z = 0;}  // Default constructor

    ~BuildingCell() = default;  // Default destructor

    // 比较运算符
    bool operator==(const BuildingCell& other) const {
        return this->x == other.x && this->y == other.y && this->z == other.z;
    }

    bool operator<(const BuildingCell& other) const {
        return this->x < other.x || (this->x == other.x && (this->y < other.y || (this->y == other.y && this->z < other.z)));
    }

    bool operator>(const BuildingCell& other) const {
        return this->x > other.x || (this->x == other.x && (this->y > other.y || (this->y == other.y && this->z > other.z)));
    }
    
    int8_t Material;
    int8_t x;
    int8_t y;
    int8_t z;
};


class Building
{
public:
    Building() = default;  // Default constructor

    ~Building() = default;  // Default destructor
    int64_t id;
    std::set<BuildingCell> cells;
    // Serialize to a file
    void Serialize(const std::string& filename) const {
        std::ofstream ofs(filename, std::ios::binary);
        if (!ofs.is_open()) {
            throw std::runtime_error("Error opening file for serialization: " + filename);
        }
        this->Serialize(ofs);
    }

    // Serialize to an output file stream
    void Serialize(std::ofstream& ofs) const {
        ofs.write(reinterpret_cast<const char*>(&id), sizeof(id));
        ofs.write(reinterpret_cast<const char*>(&building_id), sizeof(building_id));
        ofs.write(reinterpret_cast<const char*>(&position_x), sizeof(position_x));
        ofs.write(reinterpret_cast<const char*>(&position_y), sizeof(position_y));
        ofs.write(reinterpret_cast<const char*>(&rotate), sizeof(rotate));
    }

    // Deserialize from a file
    void Deserialize(const std::string& filename) {
        std::ifstream ifs(filename, std::ios::binary);
        if (!ifs.is_open()) {
            throw std::runtime_error("Error opening file for deserialization: " + filename);
        }
        this->Deserialize(ifs);
    }

    // Deserialize from an input file stream
    void Deserialize(std::ifstream& ifs) {
        ifs.read(reinterpret_cast<char*>(&id), sizeof(id));
        ifs.read(reinterpret_cast<char*>(&building_id), sizeof(building_id));
        ifs.read(reinterpret_cast<char*>(&position_x), sizeof(position_x));
        ifs.read(reinterpret_cast<char*>(&position_y), sizeof(position_y));
        ifs.read(reinterpret_cast<char*>(&rotate), sizeof(rotate));
    }

private:
    int64_t building_id = 0;
    int8_t position_x = 0;
    int8_t position_y = 0;
    int8_t rotate = 0;
};

