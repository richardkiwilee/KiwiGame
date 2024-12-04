#include <pybind11/embed.h>  // pybind11 嵌入 Python 的头文件
#include <pybind11/pybind11.h>
#include <iostream>
#include <string>

namespace py = pybind11;

class AIModel {
public:
    std::string model_name;
    int a;  // 新增的 public 成员

    AIModel(const std::string& name, int value = 0) : model_name(name), a(value) {}

    void train() {
        std::cout << "Training model: " << model_name << std::endl;
    }

    std::string predict(const std::string& input) {
        return "Prediction for '" + input + "' using model: " + model_name;
    }
};

// 执行 Python 脚本并与 C++ 对象交互
void runAI(AIModel& model, const std::string& script) {
    static py::scoped_interpreter guard{};  // 确保解释器只初始化一次

    // 创建一个模块
    py::module_ m("ai_module");

    // 在模块中绑定 C++ 类，并暴露成员变量
    py::class_<AIModel>(m, "AIModel")
        .def(py::init<const std::string&, int>())  // 绑定构造函数
        .def("train", &AIModel::train)            // 暴露 train 方法
        .def("predict", &AIModel::predict)        // 暴露 predict 方法
        .def_readwrite("a", &AIModel::a);         // 暴露成员变量 a

    // 将模块添加到 sys.modules 中
    py::module_ sys = py::module_::import("sys");
    sys.attr("modules")["ai_module"] = py::cast(&model);  // 手动注册 ai_module 模块

    // 执行 Python 脚本
    try {
        py::module_::import(script.c_str());  // 导入并执行脚本
    }
    catch (const std::exception& e) {
        std::cerr << "Error running AI script: " << e.what() << std::endl;
    }
}

int main() {
    // 创建 C++ 对象实例并传递给 Python 脚本
    AIModel model("ai_module", 10);

    // 调用 runAI 来执行 Python 脚本
    runAI(model, "ai_script");  // 传入脚本名

    // 输出成员变量 a 的值
    std::cout << "C++ value of a after Python modification: " << model.a << std::endl;
    return 0;
}
