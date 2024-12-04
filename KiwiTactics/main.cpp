#include "game/Manager.h"

int main() {
    // 创建 QuadGridMap 对象并填充 QuadGridMap
    ArchiveManager manager = ArchiveManager("test.sav");
    manager.module = new ModuleManager();
    manager.randomBuffer = new RandomSeed(255);
    manager.inventory = new Inventory();
    manager.buildings = new ObjectsManager<Building>();
    manager.alias = new ObjectsManager<Character>();
    manager.neutrals = new ObjectsManager<Character>();
    manager.emeries = new ObjectsManager<Character>();
    manager.map = new QuadGridMap(1, 5, 5);
    for (size_t i = 0; i < 5; ++i) {
        for (size_t j = 0; j < 5; ++j) {
            manager.map->gridMap[i][j].height = i + j;
            manager.map->gridMap[i][j].terrain = (i + j) % 3;
            manager.map->gridMap[i][j].effect = (i + j) % 2;
            manager.map->gridMap[i][j].objectid = 1234567890123456 + (i * 10 + j);
        }
    }
    manager.map->PrintMap();

    // 序列化到文件
    manager.Serialize("test.sav");

    return 0;
}