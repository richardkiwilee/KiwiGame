#include <iostream>
#include <cstdlib>
#include <cstdint>
#include <cstring>
#include <unordered_map>
#include <string>
#include "QuadMap.h"
#include "Character.h"

class RandomBuffer {
public:
    // 构造函数1：随机生成一个指定长度的缓冲区
    RandomBuffer(int len) : len(len), position(0) {
        buffer = new uint8_t[len];
        // 填充随机数
        for (int i = 0; i < len; ++i) {
            buffer[i] = rand() % 256; // 生成 0 到 255 的随机字节
        }
    }

    // 构造函数2：使用提供的缓冲区初始化
    RandomBuffer(uint8_t* p, int len) : buffer(p), len(len), position(0) {}

    // 析构函数：释放动态分配的内存
    ~RandomBuffer() {
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

    // 重置位置，回到开头
    void Reset() {
        position = 0;
    }
    void Serialize(std::ofstream& ofs) const {
        // 先序列化对象的长度、位置和缓冲区数据
        ofs.write(reinterpret_cast<const char*>(&len), sizeof(len));
        ofs.write(reinterpret_cast<const char*>(&position), sizeof(position));
        ofs.write(reinterpret_cast<const char*>(buffer), len);
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

std::string VERSION = "0.0.1";

class ArchiveManager
{
public:
    std::string archive_name;
    ArchiveManager(std::string archive_name);
	~ArchiveManager();
	QuadGridMap* map;
    std::unordered_map<int64_t, Character*> units;

    RandomBuffer* randomBuffer;
    // 序列化所有成员对象
    void Serialize(const std::string& filename) {
        std::ofstream ofs(filename, std::ios::binary);
        if (!ofs) {
            std::cerr << "Failed to open file for serialization." << std::endl;
            return;
        }
        // 序列化版本和名称
        ofs.write(VERSION.c_str(), VERSION.size());
        ofs.put('\0');  // Null terminator for string
        ofs.write(archive_name.c_str(), archive_name.size());
        ofs.put('\0');  // Null terminator for string
        // 序列化 RandomBuffer 的数据
        randomBuffer->Serialize(ofs);
        map->Serialize(ofs);
        ofs.close();
        std::cout << "Serialization successful." << std::endl;
    }

    // 反序列化所有成员对象
    void Deserialize(const std::string& filename) {
        std::ifstream ifs(filename, std::ios::binary);
        if (!ifs) {
            std::cerr << "Failed to open file for deserialization." << std::endl;
            return;
        }

        // 反序列化版本和名称
        std::getline(ifs, VERSION, '\0');  // 读取直至 null terminator
        std::getline(ifs, archive_name, '\0');     // 读取直至 null terminator

        // 反序列化 RandomBuffer 的数据
        randomBuffer->Deserialize(ifs);

        ifs.close();
        std::cout << "Deserialization successful." << std::endl;
    }
	
};

//int main() {
//    // 创建 QuadGridMap 对象并填充 QuadGridMap
//    QuadGridMap myMap(1, 5, 5);  // version = 1, row = 5, col = 5
//    for (size_t i = 0; i < 5; ++i) {
//        for (size_t j = 0; j < 5; ++j) {
//            myMap.gridMap[i][j].height = i + j;
//            myMap.gridMap[i][j].terrain = (i + j) % 3;
//            myMap.gridMap[i][j].effect = (i + j) % 2;
//            myMap.gridMap[i][j].objectid = 1234567890123456 + (i * 10 + j);
//        }
//    }
//
//    // 序列化到文件
//    myMap.Serialize("map.dat");
//
//    // 创建一个新的 QuadGridMap 对象，并从文件中反序列化
//    QuadGridMap newMap(0, 0, 0);  // version 和尺寸初始为0
//    newMap.Deserialize("map.dat");
//
//    // 打印反序列化后的 QuadGridMap 内容
//    std::cout << "Deserialized Map: " << std::endl;
//    newMap.PrintMap();
//
//    return 0;
//}