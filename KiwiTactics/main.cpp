#include <pybind11/embed.h>  // pybind11 Ƕ�� Python ��ͷ�ļ�
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
    static py::scoped_interpreter guard{};  // ȷ��������ֻ��ʼ��һ��

    // ����һ��ģ��
    py::module_ m("ai_module");

    // ��ģ���а� C++ ��
    py::class_<AIModel>(m, "AIModel")
        .def(py::init<const std::string&>())
        .def("train", &AIModel::train)
        .def("predict", &AIModel::predict);

    // ��ģ����ӵ� sys.modules ��
    py::module_ sys = py::module_::import("sys");
    sys.attr("modules")["ai_module"] = m;

    // ���벢ִ�� Python �ű�
    try {
        py::module_::import(script.c_str());
    }
    catch (const std::exception& e) {
        std::cerr << "Error running AI script: " << e.what() << std::endl;
    }
}


int main() {
    // ���� runAI ��ִ�� Python �ű�
    runAI("ai_script");
    return 0;
}


