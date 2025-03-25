#include "Building.h"

BuildingCell::BuildingCell() {
    Material = 0;
    x = 0;
    y = 0;
    z = 0;
}

BuildingCell::~BuildingCell() {
}


void Building::Serialize(const std::string& filename) const {
    std::ofstream ofs(filename, std::ios::binary);
    if (!ofs.is_open()) {
        throw std::runtime_error("Error opening file for serialization: " + filename);
    }
    this->Serialize(ofs);
}

void Building::Serialize(std::ofstream& ofs) const {
    ofs.write(reinterpret_cast<const char*>(&id), sizeof(id));
    ofs.write(reinterpret_cast<const char*>(&building_id), sizeof(building_id));
    ofs.write(reinterpret_cast<const char*>(&position_x), sizeof(position_x));
    ofs.write(reinterpret_cast<const char*>(&position_y), sizeof(position_y));
    ofs.write(reinterpret_cast<const char*>(&rotate), sizeof(rotate));
}

void Building::Deserialize(const std::string& filename) {
    std::ifstream ifs(filename, std::ios::binary);
    if (!ifs.is_open()) {
        throw std::runtime_error("Error opening file for deserialization: " + filename);
    }
    this->Deserialize(ifs);
}

void Building::Deserialize(std::ifstream& ifs) {
    ifs.read(reinterpret_cast<char*>(&id), sizeof(id));
    ifs.read(reinterpret_cast<char*>(&building_id), sizeof(building_id));
    ifs.read(reinterpret_cast<char*>(&position_x), sizeof(position_x));
    ifs.read(reinterpret_cast<char*>(&position_y), sizeof(position_y));
    ifs.read(reinterpret_cast<char*>(&rotate), sizeof(rotate));
}
