#include <pybind11/pybind11.h>
#include <pybind11/stl.h>
#include "bno055_wrapper.hpp"

namespace py = pybind11;

PYBIND11_MODULE(bno055, m) {
    m.doc() = "BNO055 sensor interface";

    py::class_<BNO055::Vector3>(m, "Vector3")
        .def_readwrite("x", &BNO055::Vector3::x)
        .def_readwrite("y", &BNO055::Vector3::y)
        .def_readwrite("z", &BNO055::Vector3::z);

    py::class_<BNO055::EulerAngles>(m, "EulerAngles")
        .def_readwrite("heading", &BNO055::EulerAngles::heading)
        .def_readwrite("roll", &BNO055::EulerAngles::roll)
        .def_readwrite("pitch", &BNO055::EulerAngles::pitch);

    py::class_<BNO055::Quaternion>(m, "Quaternion")
        .def_readwrite("w", &BNO055::Quaternion::w)
        .def_readwrite("x", &BNO055::Quaternion::x)
        .def_readwrite("y", &BNO055::Quaternion::y)
        .def_readwrite("z", &BNO055::Quaternion::z);

    py::class_<BNO055>(m, "BNO055")
        .def(py::init<const std::string&, const std::string&>(),
             py::arg("i2c_bus") = "/dev/i2c-1",
             py::arg("address") = "0x28")
        .def("reset", &BNO055::reset)
        .def("set_mode", &BNO055::set_mode_from_string)  // Use string version for Python
        .def("get_mode", &BNO055::get_mode)
        .def("set_power_mode", &BNO055::set_power_mode)
        .def("get_power_mode", &BNO055::get_power_mode)
        .def("get_euler", &BNO055::get_euler)
        .def("get_quaternion", &BNO055::get_quaternion)
        .def("get_accelerometer", &BNO055::get_accelerometer)
        .def("get_magnetometer", &BNO055::get_magnetometer)
        .def("get_gyroscope", &BNO055::get_gyroscope)
        .def("get_gravity", &BNO055::get_gravity)
        .def("get_linear_acceleration", &BNO055::get_linear_acceleration)
        .def("is_fully_calibrated", &BNO055::is_fully_calibrated)
        .def("save_calibration", &BNO055::save_calibration)
        .def("load_calibration", &BNO055::load_calibration);
}