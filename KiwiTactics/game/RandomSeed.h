#include <iostream>
#include <cstdlib>
#include <cstdint>
#include <cstring>
#include <unordered_map>
#include <string>
#include <fstream>

class RandomSeed {
public:
    // 构造函数1：随机生成一个指定长度的缓冲区
    RandomSeed(int len) : len(len), position(0) {
        buffer = new uint8_t[len];
        // 填充随机数
        for (int i = 0; i < len; ++i) {
            buffer[i] = rand() % 256; // 生成 0 到 255 的随机字节
        }
    }

    // 构造函数2：使用提供的缓冲区初始化
    RandomSeed(uint8_t* p, int len) : buffer(p), len(len), position(0) {}

    // 析构函数：释放动态分配的内存
    ~RandomSeed() {
        if (buffer) {
            delete[] buffer;
        }
    }

    // 获取下一个 1 字节的值
    int8_t GetInt8() {
        if (position >= len) {
            Reset(); // 如果读取到了尾部，重置为开头
        }
        return static_cast<int8_t>(buffer[position++]);
    }

    int8_t GetPct()
    {
		return int8_t(GetInt8() / 255.0);
	}
    // 获取下一个 2 字节的值，拼接到缓冲区的开始部分
    int16_t GetInt16() {
        if (position + 1 >= len) {
            Reset(); // 如果读取的长度不够，重置为开头
        }

        int16_t result = buffer[position];          // 获取当前字节
        result |= (static_cast<int16_t>(buffer[position + 1]) << 8); // 获取下一个字节并拼接
        position += 2;

        return result;
    }
    int64_t GetInt64()
    {
        int8_t c1 = GetInt8();
        int8_t c2 = GetInt8();
        int8_t c3 = GetInt8();
        int8_t c4 = GetInt8();
        int8_t c5 = GetInt8();
        int8_t c6 = GetInt8();
        int8_t c7 = GetInt8();
        int8_t c8 = GetInt8();
        return ((int64_t)c1 << 56) | ((int64_t)c2 << 48) | ((int64_t)c3 << 40) | ((int64_t)c4 << 32) | ((int64_t)c5 << 24) | ((int64_t)c6 << 16) | ((int64_t)c7 << 8) | c8;
    }
    // 重置位置，回到开头
    void Reset() {
        position = 0;
    }
    void Serialize(const std::string& filename) const {
        std::ofstream ofs(filename, std::ios::binary);
        if (!ofs.is_open()) {
            Logger::getInstance().Error("Error opening file for serialization!");
            return;
        }
        this->Serialize(ofs);
        ofs.close();
    }
    void Serialize(std::ofstream& ofs) const {
        // 先序列化对象的长度、位置和缓冲区数据
        ofs.write(reinterpret_cast<const char*>(&len), sizeof(len));
        ofs.write(reinterpret_cast<const char*>(&position), sizeof(position));
        ofs.write(reinterpret_cast<const char*>(buffer), len);
    }
    void Deserialize(const std::string& filename) {
        std::ifstream ifs(filename, std::ios::binary);
        if (!ifs.is_open()) {
            Logger::getInstance().Error("Error opening file for deserialization!");
            return;
        }
        this->Deserialize(ifs);
        ifs.close();
    }
    void Deserialize(std::ifstream& ifs) {
        ifs.read(reinterpret_cast<char*>(&len), sizeof(len));
        ifs.read(reinterpret_cast<char*>(&position), sizeof(position));
        delete[] buffer;
        buffer = new uint8_t[len];
        ifs.read(reinterpret_cast<char*>(buffer), len);
    }
    void SetPosition(int pos) {
        position = pos;
    }
    int GetPosition() {
        return position;
    }
    int GetLen() {
        return len;
    }
    uint8_t* GetBuffer() {
        return buffer;
    }
private:
    uint8_t* buffer;  // 存储数据的缓冲区
    int len;          // 缓冲区的长度
    int position;     // 当前读取的位置
};
