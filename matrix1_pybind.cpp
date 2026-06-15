#include <pybind11/pybind11.h>
#include <pybind11/operators.h>
#include <pybind11/stl.h>
#include <sstream>
#include <string>
#include "types.h"
#include "matrix1.h"

namespace py = pybind11;
using Matrix = Matrix1<TD>;

PYBIND11_MODULE(matrix1, m)
{
    py::class_<Matrix>(m, "Matrix1")
        .def(py::init<size_t, size_t>(),
             py::arg("rows") = 0,
             py::arg("cols") = 0)

        .def("Create", &Matrix::Create)
        .def("Destroy", &Matrix::Destroy)

        .def("read",
            [](Matrix &self, const std::string &txt)
            {
                std::istringstream iss(txt);
                self.Read(iss);
            })

        .def("__str__",
            [](Matrix &self)
            {
                std::ostringstream oss;
                self.Print(oss);
                return oss.str();
            })

        .def("__getitem__",
            [](Matrix &self, std::pair<size_t,size_t> idx)
            {
                return self[idx.first][idx.second];
            })

        .def("__setitem__",
            [](Matrix &self,
               std::pair<size_t,size_t> idx,
               double value)
            {
                self[idx.first][idx.second] = value;
            })

        .def("__add__",
            [](const Matrix &a, const Matrix &b)
            {
                return a + b;
            })

        .def("__sub__",
            [](const Matrix &a, const Matrix &b)
            {
                return a - b;
            })

        .def("__mul__",
            py::overload_cast<const Matrix&>(&Matrix::operator*, py::const_))

        .def("__mul__",
            py::overload_cast<TD>(&Matrix::operator*, py::const_))

        .def("__rmul__",
            [](const Matrix &m, double value)
            {
                return m * value;
            });
}