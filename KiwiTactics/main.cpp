#include <pybind11/embed.h>  // pybind11 Ƕ�� Python ��ͷ�ļ�
#include <pybind11/pybind11.h>
#include <iostream>
#include <string>

namespace py = pybind11;

class AIModel {
public:
    std::string model_name;
    int a;  // ������ public ��Ա

    AIModel(const std::string& name, int value = 0) : model_name(name), a(value) {}

    void train() {
        std::cout << "Training model: " << model_name << std::endl;
    }

    std::string predict(const std::string& input) {
        return "Prediction for '" + input + "' using model: " + model_name;
    }
};

// ִ�� Python �ű����� C++ ���󽻻�
void runAI(AIModel& model, const std::string& script) {
    static py::scoped_interpreter guard{};  // ȷ��������ֻ��ʼ��һ��

    // ����һ��ģ��
    py::module_ m("ai_module");

    // ��ģ���а� C++ �࣬����¶��Ա����
    py::class_<AIModel>(m, "AIModel")
        .def(py::init<const std::string&, int>())  // �󶨹��캯��
        .def("train", &AIModel::train)            // ��¶ train ����
        .def("predict", &AIModel::predict)        // ��¶ predict ����
        .def_readwrite("a", &AIModel::a);         // ��¶��Ա���� a

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

int main() {
    // ���� C++ ����ʵ�������ݸ� Python �ű�
    AIModel model("ai_module", 10);

    // ���� runAI ��ִ�� Python �ű�
    runAI(model, "ai_script");  // ����ű���

    // �����Ա���� a ��ֵ
    std::cout << "C++ value of a after Python modification: " << model.a << std::endl;
    return 0;
}
