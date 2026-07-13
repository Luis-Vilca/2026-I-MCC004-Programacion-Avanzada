    #include <pybind11/pybind11.h>
    #include <pybind11/operators.h>
    #include <pybind11/stl.h>
    #include <sstream>
    #include <string>
    #include "types.h"
    #include "matrix1.h"

    namespace py = pybind11;
    

    template<typename T>
    void bind_matrix(py::module_ &m, const string &name){
        using Matrix = Matrix1<T>;

        py::class_<Matrix>(m, name.c_str())
            .def(py::init<size_t, size_t>(),
                py::arg("rows") = 0,
                py::arg("cols") = 0)

            .def("Create", &Matrix::Create)
            .def("Destroy", &Matrix::Destroy)
            .def("transpose", &Matrix::transpose)
            .def("determinant", &Matrix::determinant)

            .def("read", [](Matrix &self, const string &txt){
                    std::istringstream iss(txt);
                    self.Read(iss);
                })

            .def("__str__", [](Matrix &self){
                    std::ostringstream oss;
                    self.Print(oss);
                    return oss.str();
                })

            .def("__repr__",[](Matrix &self){
                    std::ostringstream oss;
                    self.Print(oss);
                    return oss.str();
                })

            .def("__getitem__", [](Matrix &self, pair<size_t,size_t> idx){ 
                return self[idx.first][idx.second];})

            .def("__setitem__", [](Matrix &self, pair<size_t,size_t> idx, T value){
                self[idx.first][idx.second] = value;})

            .def("__add__", [](const Matrix &a, const Matrix &b){ return a + b;})
            .def("__sub__", [](const Matrix &a, const Matrix &b){return a - b;})
            .def("__mul__", py::overload_cast<const Matrix&>(&Matrix::operator*, py::const_))
            .def("__mul__", py::overload_cast<T>(&Matrix::operator*, py::const_))
            .def("__rmul__", [](const Matrix &m, T value) { return m * value;});
    }

    PYBIND11_MODULE(matrix1, m)
    {
        bind_matrix<TD> (m, "Matrix1Double");
        bind_matrix<T3F>(m, "Matrix1Float");
        bind_matrix<TI> (m, "Matrix1Int");
    }