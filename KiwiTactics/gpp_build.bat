g++ -O3 -Wall -shared -std=c++11 -fPIC `python3 -m pybind11 --includes` bindings.cpp -o character_module`python3-config --extension-suffix`
g++ main.cpp -o main -I/path/to/pybind11/include `python3-config --cflags --ldflags`
