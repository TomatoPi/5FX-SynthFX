cmake_minimum_required(VERSION 3.19.0)
project(5FX-SynthFX VERSION 0.1.0)

set(CMAKE_CXX_STANDARD 20)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

set(HEADERS )
set(SOURCES )

add_executable(${PROJECT_NAME} 
  ${SOURCES} ${HEADERS}
  src/SynthFX.cpp)

target_link_libraries(${PROJECT_NAME} jack)
target_link_libraries(${PROJECT_NAME} lo)

target_include_directories(${PROJECT_NAME} PRIVATE src/)

install(TARGETS ${PROJECT_NAME})