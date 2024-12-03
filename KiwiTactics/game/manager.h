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
    // ���캯��1���������һ��ָ�����ȵĻ�����
    RandomBuffer(int len) : len(len), position(0) {
        buffer = new uint8_t[len];
        // ��������
        for (int i = 0; i < len; ++i) {
            buffer[i] = rand() % 256; // ���� 0 �� 255 ������ֽ�
        }
    }

    // ���캯��2��ʹ���ṩ�Ļ�������ʼ��
    RandomBuffer(uint8_t* p, int len) : buffer(p), len(len), position(0) {}

    // �����������ͷŶ�̬������ڴ�
    ~RandomBuffer() {
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
    void Serialize(std::ofstream& ofs) const {
        // �����л�����ĳ��ȡ�λ�úͻ���������
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
    uint8_t* buffer;  // �洢���ݵĻ�����
    int len;          // �������ĳ���
    int position;     // ��ǰ��ȡ��λ��
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
    // ���л����г�Ա����
    void Serialize(const std::string& filename) {
        std::ofstream ofs(filename, std::ios::binary);
        if (!ofs) {
            std::cerr << "Failed to open file for serialization." << std::endl;
            return;
        }
        // ���л��汾������
        ofs.write(VERSION.c_str(), VERSION.size());
        ofs.put('\0');  // Null terminator for string
        ofs.write(archive_name.c_str(), archive_name.size());
        ofs.put('\0');  // Null terminator for string
        // ���л� RandomBuffer ������
        randomBuffer->Serialize(ofs);
        map->Serialize(ofs);
        ofs.close();
        std::cout << "Serialization successful." << std::endl;
    }

    // �����л����г�Ա����
    void Deserialize(const std::string& filename) {
        std::ifstream ifs(filename, std::ios::binary);
        if (!ifs) {
            std::cerr << "Failed to open file for deserialization." << std::endl;
            return;
        }

        // �����л��汾������
        std::getline(ifs, VERSION, '\0');  // ��ȡֱ�� null terminator
        std::getline(ifs, archive_name, '\0');     // ��ȡֱ�� null terminator

        // �����л� RandomBuffer ������
        randomBuffer->Deserialize(ifs);

        ifs.close();
        std::cout << "Deserialization successful." << std::endl;
    }
	
};

//int main() {
//    // ���� QuadGridMap ������� QuadGridMap
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
//    // ���л����ļ�
//    myMap.Serialize("map.dat");
//
//    // ����һ���µ� QuadGridMap ���󣬲����ļ��з����л�
//    QuadGridMap newMap(0, 0, 0);  // version �ͳߴ��ʼΪ0
//    newMap.Deserialize("map.dat");
//
//    // ��ӡ�����л���� QuadGridMap ����
//    std::cout << "Deserialized Map: " << std::endl;
//    newMap.PrintMap();
//
//    return 0;
//}