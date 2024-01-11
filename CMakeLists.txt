# CMakeLists.txt
cmake_minimum_required(VERSION 3.10..3.21)
project(example)

# Add the test
add_executable(test test/test.cc)
target_include_directories(test PUBLIC src/include)



