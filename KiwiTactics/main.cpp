#include <pybind11/embed.h>  // pybind11 嵌入 Python 的头文件
#include <pybind11/pybind11.h>
#include "character.h"

namespace py = pybind11;

class AIModel {
public:
    AIModel(const std::string& model_name) : model_name(model_name) {}

    void train() {
        std::cout << "Training model: " << model_name << std::endl;
    }

    std::string predict(const std::string& input) {
        return "Prediction for '" + input + "' using model: " + model_name;
    }

private:
    std::string model_name;
};

void runAI(const std::string& script) {
    static py::scoped_interpreter guard{};  // 确保解释器只初始化一次

    // 创建一个模块
    py::module_ m("ai_module");

    // 在模块中绑定 C++ 类
    py::class_<AIModel>(m, "AIModel")
        .def(py::init<const std::string&>())
        .def("train", &AIModel::train)
        .def("predict", &AIModel::predict);

    // 将模块添加到 sys.modules 中
    py::module_ sys = py::module_::import("sys");
    sys.attr("modules")["ai_module"] = m;

    // 导入并执行 Python 脚本
    try {
        py::module_::import(script.c_str());
    }
    catch (const std::exception& e) {
        std::cerr << "Error running AI script: " << e.what() << std::endl;
    }
}


int main() {
    // 调用 runAI 来执行 Python 脚本
    runAI("ai_script");
    return 0;
}


