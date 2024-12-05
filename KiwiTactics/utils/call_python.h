#include <pybind11/embed.h>  // pybind11 Ƕ�� Python ��ͷ�ļ�
#include <pybind11/pybind11.h>
#include <iostream>
#include <string>

namespace py = pybind11;

class AIModel_py {
public:
    std::string model_name;
    int a;  // ������ public ��Ա

    AIModel_py(const std::string& name, int value = 0) : model_name(name), a(value) {}

    void train() {
        std::cout << "Training model: " << model_name << std::endl;
    }

    std::string predict(const std::string& input) {
        return "Prediction for '" + input + "' using model: " + model_name;
    }
};

// ִ�� Python �ű����� C++ ���󽻻�
void runAI(AIModel_py& model, const std::string& script) {
    static py::scoped_interpreter guard{};  // ȷ��������ֻ��ʼ��һ��

    // ����һ��ģ��
    py::module_ m("ai_module");

    // ��ģ���а� C++ �࣬����¶��Ա����
    py::class_<AIModel_py>(m, "AIModel_py")
        .def(py::init<const std::string&, int>())  // �󶨹��캯��
        .def("train", &AIModel_py::train)            // ��¶ train ����
        .def("predict", &AIModel_py::predict)        // ��¶ predict ����
        .def_readwrite("a", &AIModel_py::a);         // ��¶��Ա���� a

    // ��ģ����ӵ� sys.modules ��
    py::module_ sys = py::module_::import("sys");
    sys.attr("modules")["ai_module"] = py::cast(&model);  // �ֶ�ע�� ai_module ģ��

    // ִ�� Python �ű�
    try {
        py::module_::import(script.c_str());  // ���벢ִ�нű�
    }
    catch (const std::exception& e) {
        std::cerr << "Error running AI script: " << e.what() << std::endl;
    }
}

int testPy() {
    // ���� C++ ����ʵ�������ݸ� Python �ű�
    AIModel_py model("ai_module", 10);

    // ���� runAI ��ִ�� Python �ű�
    runAI(model, "ai_script");  // ����ű���

    // �����Ա���� a ��ֵ
    std::cout << "C++ value of a after Python modification: " << model.a << std::endl;
    return 0;
}

void A1(int x) {
    std::cout << "C++ A1 is called with value: " << x << std::endl;
}

// ���庯��ָ�룬���ڶ�̬����
std::function<void(int)> A1_dynamic = A1;

void register_python_function(const std::string& module_name, const std::string& func_name) {
    // ȷ�� Python �������ѳ�ʼ��
    if (!Py_IsInitialized()) {
        std::cerr << "Python interpreter is not initialized!" << std::endl;
        return;
    }

    // ����ָ���� Python ģ��
    PyObject* pModule = PyImport_ImportModule(module_name.c_str());
    if (!pModule) {
        PyErr_Print();
        std::cerr << "Failed to load module: " << module_name << std::endl;
        return;
    }

    // ��ȡģ���еĺ���
    PyObject* pFunc = PyObject_GetAttrString(pModule, func_name.c_str());
    if (pFunc && PyCallable_Check(pFunc)) {
        // �� Python ������װΪһ�� C++ ����
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

    // ����
    Py_XDECREF(pFunc);
    Py_XDECREF(pModule);
}