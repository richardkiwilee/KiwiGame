#include "ModuleManager.h"

ModuleManager::ModuleManager(std::string path) {
    this->path = path;
}

void ModuleManager::Serialize(std::ofstream& ofs) {
    // TODO: Implement serialization
}

void ModuleManager::Deserialize(std::ifstream& ifs) {
    // TODO: Implement deserialization
}

void ModuleManager::ApplyMods() {
    // TODO: Implement mod application
}

void ModuleManager::EnableMod(const std::string& mod_name) {
    // TODO: Implement mod enabling
}

void ModuleManager::DisableMod(const std::string& mod_name) {
    // TODO: Implement mod disabling
}
