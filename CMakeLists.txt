cmake_minimum_required(VERSION 3.10.0)
project(plotalot)

include(CTest)
enable_testing()

include(CPack)
set(CPACK_PROJECT_NAME ${PROJECT_NAME})
set(CMAKE_CXX_STANDARD 17)

include_directories(${PROJECT_SOURCE_DIR})
add_executable(plotalot test/main.cpp src/Config.cpp src/JobMan.cpp src/PlotJob.cpp)