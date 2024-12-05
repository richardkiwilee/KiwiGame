#include <pybind11/embed.h>  // pybind11 嵌入 Python 的头文件
#include <pybind11/pybind11.h>
#include <iostream>
#include <string>

namespace py = pybind11;

class AIModel_py {
public:
    std::string model_name;
    int a;  // 新增的 public 成员

    AIModel_py(const std::string& name, int value = 0) : model_name(name), a(value) {}

    void train() {
        std::cout << "Training model: " << model_name << std::endl;
    }

    std::string predict(const std::string& input) {
        return "Prediction for '" + input + "' using model: " + model_name;
    }
};

// 执行 Python 脚本并与 C++ 对象交互
void runAI(AIModel_py& model, const std::string& script) {
    static py::scoped_interpreter guard{};  // 确保解释器只初始化一次

    // 创建一个模块
    py::module_ m("ai_module");

    // 在模块中绑定 C++ 类，并暴露成员变量
    py::class_<AIModel_py>(m, "AIModel_py")
        .def(py::init<const std::string&, int>())  // 绑定构造函数
        .def("train", &AIModel_py::train)            // 暴露 train 方法
        .def("predict", &AIModel_py::predict)        // 暴露 predict 方法
        .def_readwrite("a", &AIModel_py::a);         // 暴露成员变量 a

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

int testPy() {
    // 创建 C++ 对象实例并传递给 Python 脚本
    AIModel_py model("ai_module", 10);

    // 调用 runAI 来执行 Python 脚本
    runAI(model, "ai_script");  // 传入脚本名

    // 输出成员变量 a 的值
    std::cout << "C++ value of a after Python modification: " << model.a << std::endl;
    return 0;
}

void A1(int x) {
    std::cout << "C++ A1 is called with value: " << x << std::endl;
}

// 定义函数指针，用于动态调用
std::function<void(int)> A1_dynamic = A1;

void register_python_function(const std::string& module_name, const std::string& func_name) {
    // 确保 Python 解释器已初始化
    if (!Py_IsInitialized()) {
        std::cerr << "Python interpreter is not initialized!" << std::endl;
        return;
    }

    // 加载指定的 Python 模块
    PyObject* pModule = PyImport_ImportModule(module_name.c_str());
    if (!pModule) {
        PyErr_Print();
        std::cerr << "Failed to load module: " << module_name << std::endl;
        return;
    }

    // 获取模块中的函数
    PyObject* pFunc = PyObject_GetAttrString(pModule, func_name.c_str());
    if (pFunc && PyCallable_Check(pFunc)) {
        // 将 Python 函数包装为一个 C++ 函数
        A1_dynamic = [pFunc](int x) {
            PyObject* args = PyTuple_Pack(1, PyLong_FromLong(x));
            PyObject* result = PyObject_CallObject(pFunc, args);
            if (!result) {
                PyErr_Print();
            }
            Py_XDECREF(result);
            Py_XDECREF(args);
            };

        std::cout << "Python function " << func_name << " registered successfully!" << std::endl;
    }
    else {
        PyErr_Print();
        std::cerr << "Function " << func_name << " not found or not callable in module " << module_name << std::endl;
    }

    // 清理
    Py_XDECREF(pFunc);
    Py_XDECREF(pModule);
}