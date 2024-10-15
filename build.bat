cmake -H. -Bbuild -Ax64 -DCMAKE_BUILD_TYPE=Release -G "Visual Studio 17 2022"
cmake --build build --config Release -j
