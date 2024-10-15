#include <pybind11/pybind11.h>
#include "character.h"

namespace py = pybind11;

PYBIND11_MODULE(character_module, m) {
    py::class_<Character>(m, "Character")
        .def(py::init<>())  // 绑定构造函数
        .def("move", &Character::Move)  // 绑定 Move 方法
        .def("attack", &Character::Attack)  // 绑定 Attack 方法
        .def("get_position", &Character::GetPosition);  // 绑定 GetPosition 方法
}
