#pragma once
#include <iostream>
#include <vector>
#include <set>
#include <memory>
#include <optional>
#include <fstream>
#include <cstdint>
#include <stdexcept>
#include <string>
#include "Character.h"
#include "Building.h"
#include "Anchor.h"

struct QuadGrid {
    uint8_t x = 0x00;
    uint8_t y = 0x00;
    uint8_t z = 0x00;
    uint8_t entity = 0x00;     // 单元格类型 空 实心固体 水 沙 等填充整个单元格的
    uint8_t ground_effect = 0x00;   // 地面效果 燃烧 雪面
    uint8_t fill_effect = 0x00;     // 悬浮效果 雾气
    Character* unit = nullptr;        // 占据单元格中的单位
    Building* building = nullptr;     // 占据单元格中的建筑
    Anchor* anchor = nullptr;         // 占据单元格中的锚点
};

class QuadGridMap {
public:
    uint8_t row = 0;    // Map的最大行数
    uint8_t col = 0;    // Map的最大列数
    uint8_t height = 0;    // Map的最大高度
    uint64_t seed = 0;           

    std::vector<std::vector<std::vector<QuadGrid>>> gridMap;  // 三维网格地图

    QuadGridMap(uint8_t row, uint8_t col, uint8_t height, uint64_t seed);    
    QuadGridMap() = default;

    QuadGrid* Get(uint8_t x, uint8_t y, uint8_t z);     // 根据三维坐标获取单元格
    QuadGrid* Get(uint8_t x, uint8_t y);                 // 根据二维坐标获取高度最高的非空单元格
    bool InSight(QuadGrid* starter, QuadGrid* target);      // 判断目标单元格是否在起始单元格的视野内
    // std::set<Character*> GetSurrounding(QuadGrid* cell, uint8_t rangeType);  // 获取指定单元格为中心 rangeType类型的空间内所有的单位
    // std::set<Building*> GetSurroundingBuilding(QuadGrid* cell, uint8_t rangeType);  // 获取指定单元格为中心 rangeType类型的空间内所有的建筑
    // std::set<Anchor*> GetSurroundingAnchor(QuadGrid* cell, uint8_t rangeType);  // 获取指定单元格为中心 rangeType类型的空间内所有的锚点

    void Serialize(const std::string& filename) const;
    void Serialize(std::ofstream& ofs) const;
    void Deserialize(const std::string& filename);
    void Deserialize(std::ifstream& ifs);

private:
    void _randomization();
};
