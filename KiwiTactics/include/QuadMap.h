#pragma once
#include <iostream>
#include <vector>
#include <memory>
#include <optional>
#include <fstream>
#include <stdexcept>
#include <string>
#include "Character.h"

struct QuadGrid {
    uint8_t height = 0x00;         
    uint8_t terrain = 0x00;        
    uint8_t effect = 0x00;         
    uint64_t objectid = 0x00;      
    Character* unit = nullptr;

    void Serialize(std::ofstream& ofs) const;
    void Deserialize(std::ifstream& ifs);
    friend std::ostream& operator<<(std::ostream& os, const QuadGrid& grid);
    friend std::istream& operator>>(std::istream& is, QuadGrid& grid);
};

class QuadGridMap {
public:
    uint8_t version = 1;        
    uint8_t row = 0;            
    uint8_t col = 0;            
    int64_t seed = 0;           

    std::vector<std::vector<QuadGrid>> gridMap;  

    QuadGridMap(uint8_t version, uint8_t row, uint8_t col, int64_t seed);
    QuadGridMap() = default;

    QuadGrid* Get(uint8_t x, uint8_t y);
    void Serialize(const std::string& filename) const;
    void Serialize(std::ofstream& ofs) const;
    void Deserialize(const std::string& filename);
    void Deserialize(std::ifstream& ifs);
    void PrintMap() const;

private:
    void _randomization();
};
