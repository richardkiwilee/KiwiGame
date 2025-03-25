#pragma once
#include <iostream>
#include <fstream>
#include <cstdint>
#include <set>
#include <string>

class ModuleManager {
public:
    explicit ModuleManager(std::string path);
    
    void Serialize(std::ofstream& ofs);
    void Deserialize(std::ifstream& ifs);
    void ApplyMods();
    void EnableMod(const std::string& mod_name);
    void DisableMod(const std::string& mod_name);

private:
    std::string path;
};
