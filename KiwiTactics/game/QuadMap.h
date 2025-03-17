#include <iostream>
#include <vector>
#include <memory>
#include <optional>
#include <fstream>
#include <stdexcept>
#include <string>


// 鍦版牸
struct QuadGrid {
    uint8_t height = 0x00;         // 涓嶅鐞嗙被浼兼嫳闂ㄧ殑绌烘礊缁撴瀯锛屽彧鑰冭檻鍦伴潰楂樺害
    uint8_t terrain = 0x00;        // 鍦板舰绫诲瀷
    uint8_t effect = 0x00;         // 鍦版牸鏁堟灉 灞炰簬绌轰腑鏁堟灉 绫讳技鐕冪儳鍜屾祿闆句笉鑳藉叡瀛?
    uint64_t objectid = 0x00;      // 鍗犵敤瀵硅薄 鍖呮嫭寤虹瓚鏂瑰潡銆佸崟浣嶃€佽祫婧愮瓑

    // 搴忓垪鍖? 灏?QuadGrid 瀵硅薄鐨勫瓧娈靛啓鍏ユ枃浠?
    void Serialize(std::ofstream& ofs) const {
        ofs.write(reinterpret_cast<const char*>(&height), sizeof(height));
        ofs.write(reinterpret_cast<const char*>(&terrain), sizeof(terrain));
        ofs.write(reinterpret_cast<const char*>(&effect), sizeof(effect));
        ofs.write(reinterpret_cast<const char*>(&objectid), sizeof(objectid));
    }

    // 鍙嶅簭鍒楀寲: 浠庢枃浠惰鍙栨暟鎹苟鎭㈠ QuadGrid 瀵硅薄鐨勫瓧娈?
    void Deserialize(std::ifstream& ifs) {
        ifs.read(reinterpret_cast<char*>(&height), sizeof(height));
        ifs.read(reinterpret_cast<char*>(&terrain), sizeof(terrain));
        ifs.read(reinterpret_cast<char*>(&effect), sizeof(effect));
        ifs.read(reinterpret_cast<char*>(&objectid), sizeof(objectid));
    }

    // 閲嶈浇杈撳嚭娴佽繍绠楃浠ユ敮鎸佸簭鍒楀寲杈撳嚭
    friend std::ostream& operator<<(std::ostream& os, const QuadGrid& grid) {
        os << "Height: " << +grid.height << ", "
            << "Terrain: " << +grid.terrain << ", "
            << "Effect: " << +grid.effect << ", "
            << "ObjectID: " << grid.objectid << "\n";
        return os;
    }

    // 閲嶈浇杈撳叆娴佽繍绠楃浠ユ敮鎸佸弽搴忓垪鍖栬緭鍏?
    friend std::istream& operator>>(std::istream& is, QuadGrid& grid) {
        is >> grid.height >> grid.terrain >> grid.effect >> grid.objectid;
        return is;
    }
};

class QuadGridMap {
public:
    uint8_t version = 1;        // 鍦板浘鐗堟湰
    uint8_t row = 0;            // 鍦板浘鐨勮鏁?(楂樺害)
    uint8_t col = 0;            // 鍦板浘鐨勫垪鏁?(瀹藉害)
    int64_t seed = 0;           // 闅忔満绉嶅瓙
    std::vector<std::vector<QuadGrid>> gridMap;  // 缁勬垚鍦板浘鐨勪簩缁寸綉鏍?

    QuadGridMap(uint8_t version, uint8_t row, uint8_t col, int64_t seed)
        : version(version), row(row), col(col) {
        gridMap.resize(row, std::vector<QuadGrid>(col));  // 琛屾暟涓?row锛屽垪鏁颁负 col
        seed = seed;
        _randomization();
    }

    QuadGridMap() {    };

    // 鑾峰彇鎸囧畾浣嶇疆鐨?QuadGrid 鎸囬拡
    QuadGrid* Get(uint8_t x, uint8_t y)
    {
        if (x >= col || y >= row)  // 妫€鏌ユ槸鍚﹁秺鐣?
            return nullptr;
        return &gridMap[y][x];  // 杩斿洖 gridMap 涓搴斾綅缃殑鎸囬拡
    }

    // 搴忓垪鍖? 灏?QuadGridMap 瀵硅薄鐨勫瓧娈典互鍙?QuadGridMap 鏁扮粍鍐欏叆鏂囦欢
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
        // 鍐欏叆鐗堟湰鍙凤紝row 鍜?col
        ofs.write(reinterpret_cast<const char*>(&version), sizeof(version));
        ofs.write(reinterpret_cast<const char*>(&row), sizeof(row));
        ofs.write(reinterpret_cast<const char*>(&col), sizeof(col));
        ofs.write(reinterpret_cast<const char*>(&seed), sizeof(seed));
        // 閬嶅巻骞跺簭鍒楀寲浜岀淮缃戞牸
        for (size_t i = 0; i < row; ++i) {
            for (size_t j = 0; j < col; ++j) {
                gridMap[i][j].Serialize(ofs);
            }
        }
    }

    // 鍙嶅簭鍒楀寲: 浠庢枃浠惰鍙栨暟鎹苟鎭㈠ QuadGridMap 瀵硅薄鐨勫瓧娈典互鍙?QuadGridMap 鏁扮粍
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
        // 璇诲彇鐗堟湰鍙凤紝row 鍜?col
        ifs.read(reinterpret_cast<char*>(&version), sizeof(version));
        ifs.read(reinterpret_cast<char*>(&row), sizeof(row));
        ifs.read(reinterpret_cast<char*>(&col), sizeof(col));
        ifs.read(reinterpret_cast<char*>(&seed), sizeof(seed));
        // 璋冩暣 gridMap 鐨勫ぇ灏?
        gridMap.resize(row, std::vector<QuadGrid>(col));
        // 閬嶅巻骞跺弽搴忓垪鍖栦簩缁寸綉鏍?
        for (size_t i = 0; i < row; ++i) {
            for (size_t j = 0; j < col; ++j) {
                gridMap[i][j].Deserialize(ifs);
            }
        }
    }
    // 鎵撳嵃鏁翠釜 QuadGridMap 淇℃伅
    void PrintMap() const {
        for (size_t i = 0; i < row; ++i) {
            for (size_t j = 0; j < col; ++j) {
                std::cout << gridMap[i][j] << " ";
            }
            std::cout << std::endl;
        }
    }
private:
    void _randomization()
    {
        for (uint8_t i = 0; i < 50; ++i) {
            for (uint8_t j = 0; j < 50; ++j) {
                gridMap[i][j].height = i + j;
                gridMap[i][j].terrain = (i + j) % 3;
                gridMap[i][j].effect = (i + j) % 2;
                gridMap[i][j].objectid = 1234567890123456 + (i * 10 + j);
            }
        }
    }

};
