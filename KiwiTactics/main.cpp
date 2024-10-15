#include <pybind11/embed.h>  // pybind11 嵌入 Python 的头文件
#include "character.h"

namespace py = pybind11;

void runAI(const std::string& ai_script) {
    py::scoped_interpreter guard{};  // 启动 Python 解释器

    // 导入并执行 Python 脚本
    try {
        py::module_::import(ai_script.c_str());
    }
    catch (const std::exception& e) {
        std::cerr << "Error running AI script: " << e.what() << std::endl;
    }
}

int main() {
    // 创建一个角色
    Character player;

    // 调用 runAI 来执行 Python 脚本
    runAI("ai_script");

    return 0;
}
