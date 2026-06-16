CXX = g++

PYTHON_INC = -IC:/msys64/mingw64/include/python3.14
PYBIND_INC = -IC:/msys64/mingw64/lib/python3.14/site-packages/pybind11/include
PYTHON_LIB = -LC:/msys64/mingw64/lib
PYTHON_LINK = -lpython3.14

CXXFLAGS = -std=c++2b -Wall -g -pthread $(PYTHON_INC) $(PYBIND_INC)# Añadido -pthread
LDFLAGS = -pthread # Añadido -pthread

TARGET = main
SRCS = main.cpp util.cpp \
       complex.cpp \
       shapes/shape.cpp \
       shapes/rectangle.cpp \
       shapes/circle.cpp \
       shapes/triangle.cpp \
       shapes/square.cpp \
       polimorfismo.cpp \
       BitSigno.cpp \
       Pointers.cpp \
       array1.cpp \
       DemoMatrix.cpp

OBJS = $(SRCS:.cpp=.o)

all: $(TARGET)

$(TARGET): $(OBJS)
	$(CXX) $(LDFLAGS) $^ -o $@

%.o: %.cpp
	$(CXX) $(CXXFLAGS) -c $< -o $@

pybind:
	$(CXX) $(CXXFLAGS) -shared matrix1_pybind.cpp \
	$(PYTHON_LIB) \
	$(PYTHON_LINK) \
	-o matrix1.pyd

clean:
	rm -f $(OBJS) $(TARGET) matrix1.pyd

.PHONY: all clean pybind