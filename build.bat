mkdir build
cmake -S . -B build
cmake --build build --config Release
cmake --install build --prefix tmp