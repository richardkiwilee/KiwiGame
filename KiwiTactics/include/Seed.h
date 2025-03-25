#pragma once
#include <cstdint>
#include <fstream>
#include <string>

class Seed {
 public:
    // 构造函数1：随机生成一个指定长度的缓冲区
    Seed();
    Seed(int len);
    ~Seed();

    void Reset();
    
    void Serialize(const std::string& filename) const;
    void Serialize(std::ofstream& ofs) const;
    void Deserialize(const std::string& filename);
    void Deserialize(std::ifstream& ifs);
    
    void SetPosition(int pos);
    int GetPosition();
    int GetLen();
    uint8_t* GetBuffer();

 private:
    uint8_t* buffer;  // 存储数据的缓冲区
    int len;          // 缓冲区的长度
    int position;     // 当前读取的位置
};