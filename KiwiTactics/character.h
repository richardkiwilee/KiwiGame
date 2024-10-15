#pragma once
#include <string>
#include <iostream>

class Character {
public:
    Character() : x(0), y(0) {}

    // 移动方法
    void Move(int newX, int newY) {
        x = newX;
        y = newY;
        std::cout << "Character moved to position (" << x << ", " << y << ").\n";
    }

    // 攻击方法
    void Attack() {
        std::cout << "Character attacks!\n";
    }

    // 获取当前的位置
    std::string GetPosition() const {
        return "Position: (" + std::to_string(x) + ", " + std::to_string(y) + ")";
    }

private:
    int x, y;  // 角色位置
};
