#pragma once
#include <iostream>
#include <fstream>
#include <cstdint>
#include <set>

class BuildingCell {
public:
    BuildingCell();  // Default constructor
    ~BuildingCell();  // Default destructor

    int8_t Material;
    int8_t x;
    int8_t y;
    int8_t z;
};

class Building {
public:
    Building() = default;  // Default constructor
    ~Building() = default;  // Default destructor

    // Serialize to a file
    void Serialize(const std::string& filename) const;
    void Serialize(std::ofstream& ofs) const;
    void Deserialize(const std::string& filename);
    void Deserialize(std::ifstream& ifs);

    int64_t id;
    std::set<BuildingCell> cells;

private:
    int64_t building_id = 0;
    int8_t position_x = 0;
    int8_t position_y = 0;
    int8_t rotate = 0;
};
