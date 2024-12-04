#include <iostream>
#include <fstream>
#include <vector>

class InventoryItem
{
public:
    void Serialize(std::ofstream& ofs) const {
        ofs.write(reinterpret_cast<const char*>(&item_id), sizeof(item_id));
        ofs.write(reinterpret_cast<const char*>(&item_count), sizeof(item_count));
    }

    void Deserialize(std::ifstream& ifs) {
        ifs.read(reinterpret_cast<char*>(&item_id), sizeof(item_id));
        ifs.read(reinterpret_cast<char*>(&item_count), sizeof(item_count));
    }

private:
    int64_t item_id;
    int32_t item_count;
};

class Inventory
{
public:
    void Serialize(std::ofstream& ofs) const {
        ofs.write(reinterpret_cast<const char*>(&food), sizeof(food));
        ofs.write(reinterpret_cast<const char*>(&wood), sizeof(wood));
        ofs.write(reinterpret_cast<const char*>(&stone), sizeof(stone));
        ofs.write(reinterpret_cast<const char*>(&gold), sizeof(gold));
        int8_t size = static_cast<int8_t>(items.size());
        ofs.write(reinterpret_cast<const char*>(&size), sizeof(size));
        for (const auto& item : items) {
            item.Serialize(ofs);
        }
    }

    void Deserialize(std::ifstream& ifs) {
        ifs.read(reinterpret_cast<char*>(&food), sizeof(food));
        ifs.read(reinterpret_cast<char*>(&wood), sizeof(wood));
        ifs.read(reinterpret_cast<char*>(&stone), sizeof(stone));
        ifs.read(reinterpret_cast<char*>(&gold), sizeof(gold));
        int8_t size;
        ifs.read(reinterpret_cast<char*>(&size), sizeof(size));
        items.clear();
        for (int i = 0; i < size; i++) {
            InventoryItem item;
            item.Deserialize(ifs);
            items.push_back(item);
        }
    }

private:
    int64_t food;
    int64_t wood;
    int64_t stone;
    int64_t gold;
    std::vector<InventoryItem> items;
};
