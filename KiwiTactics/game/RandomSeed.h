#include <iostream>
#include <cstdlib>
#include <cstdint>
#include <cstring>
#include <unordered_map>
#include <string>
#include <fstream>

class RandomSeed {
public:
    // ���캯��1���������һ��ָ�����ȵĻ�����
    RandomSeed(int len) : len(len), position(0) {
        buffer = new uint8_t[len];
        // ��������
        for (int i = 0; i < len; ++i) {
            buffer[i] = rand() % 256; // ���� 0 �� 255 ������ֽ�
        }
    }

    // ���캯��2��ʹ���ṩ�Ļ�������ʼ��
    RandomSeed(uint8_t* p, int len) : buffer(p), len(len), position(0) {}

    // �����������ͷŶ�̬������ڴ�
    ~RandomSeed() {
        if (buffer) {
            delete[] buffer;
        }
    }

    // ��ȡ��һ�� 1 �ֽڵ�ֵ
    int8_t GetInt8() {
        if (position >= len) {
            Reset(); // �����ȡ����β��������Ϊ��ͷ
        }
        return static_cast<int8_t>(buffer[position++]);
    }

    // ��ȡ��һ�� 2 �ֽڵ�ֵ��ƴ�ӵ��������Ŀ�ʼ����
    int16_t GetInt16() {
        if (position + 1 >= len) {
            Reset(); // �����ȡ�ĳ��Ȳ���������Ϊ��ͷ
        }

        int16_t result = buffer[position];          // ��ȡ��ǰ�ֽ�
        result |= (static_cast<int16_t>(buffer[position + 1]) << 8); // ��ȡ��һ���ֽڲ�ƴ��
        position += 2;

        return result;
    }

    // ����λ�ã��ص���ͷ
    void Reset() {
        position = 0;
    }
    void Serialize(const std::string& filename) const {
        std::ofstream ofs(filename, std::ios::binary);
        if (!ofs.is_open()) {
            std::cerr << "Error opening file for serialization!" << std::endl;
            return;
        }
        this->Serialize(ofs);
        ofs.close();
    }
    void Serialize(std::ofstream& ofs) const {
        // �����л�����ĳ��ȡ�λ�úͻ���������
        ofs.write(reinterpret_cast<const char*>(&len), sizeof(len));
        ofs.write(reinterpret_cast<const char*>(&position), sizeof(position));
        ofs.write(reinterpret_cast<const char*>(buffer), len);
    }
    void Deserialize(const std::string& filename) {
        std::ifstream ifs(filename, std::ios::binary);
        if (!ifs.is_open()) {
            std::cerr << "Error opening file for deserialization!" << std::endl;
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
    uint8_t* buffer;  // �洢���ݵĻ�����
    int len;          // �������ĳ���
    int position;     // ��ǰ��ȡ��λ��
};