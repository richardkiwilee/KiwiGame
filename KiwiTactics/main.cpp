#include <pybind11/embed.h>  // pybind11 Ƕ�� Python ��ͷ�ļ�
#include "character.h"

namespace py = pybind11;

void runAI(const std::string& ai_script) {
    py::scoped_interpreter guard{};  // ���� Python ������

    // ���벢ִ�� Python �ű�
    try {
        py::module_::import(ai_script.c_str());
    }
    catch (const std::exception& e) {
        std::cerr << "Error running AI script: " << e.what() << std::endl;
    }
}

int main() {
    // ����һ����ɫ
    Character player;

    // ���� runAI ��ִ�� Python �ű�
    runAI("ai_script");

    return 0;
}
