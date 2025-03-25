#include "Seed.h"
#include "Logger.h"

Seed::Seed()
{
    len = 255;
    buffer = nullptr;
    position = 0;
    buffer = new uint8_t[len];
    // 填充随机数
    for (int i = 0; i < len; ++i) {
        buffer[i] = rand() % 256; // 生成 0 到 255 的随机字节
    }
}

Seed::Seed(int len)
{
    this->len = len;
    buffer = nullptr;
    position = 0;
    buffer = new uint8_t[len];
    // 填充随机数
    for (int i = 0; i < len; ++i) {
        buffer[i] = rand() % 256; // 生成 0 到 255 的随机字节
    }
}

Seed::~Seed()
{
    if (buffer)
        delete[] buffer;
}

void Seed::Reset()
{
    position = 0;
}

void Seed::Serialize(const std::string& filename) const {
    std::ofstream ofs(filename, std::ios::binary);
    if (!ofs.is_open()) {
        Logger::getInstance().Error("Error opening file for serialization!");
        return;
    }
    this->Serialize(ofs);
    ofs.close();
}

void Seed::Serialize(std::ofstream& ofs) const {
    ofs.write(reinterpret_cast<const char*>(&len), sizeof(len));
    ofs.write(reinterpret_cast<const char*>(&position), sizeof(position));
    ofs.write(reinterpret_cast<const char*>(buffer), len);
}

void Seed::Deserialize(const std::string& filename) {
    std::ifstream ifs(filename, std::ios::binary);
    if (!ifs.is_open()) {
        Logger::getInstance().Error("Error opening file for deserialization!");
        return;
    }
    this->Deserialize(ifs);
    ifs.close();
}

void Seed::Deserialize(std::ifstream& ifs) {
    ifs.read(reinterpret_cast<char*>(&len), sizeof(len));
    ifs.read(reinterpret_cast<char*>(&position), sizeof(position));
    delete[] buffer;
    buffer = new uint8_t[len];
    ifs.read(reinterpret_cast<char*>(buffer), len);
}

void Seed::SetPosition(int pos) {
    position = pos;
}

int Seed::GetPosition() {
    return position;
}

int Seed::GetLen() {
    return len;
}

uint8_t* Seed::GetBuffer() {
    return buffer;
}