from setuptools import setup, Extension
import pybind11

ext_modules = [
    Extension(
        "matrix1",
        ["matrix1_pybind.cpp"],
        include_dirs=[pybind11.get_include()],
        language="c++",
        extra_compile_args=["-std=c++20"],
    ),
]

setup(
    name="matrix1",
    version="1.0.0",
    ext_modules=ext_modules,
)