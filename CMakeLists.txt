cmake_minimum_required(VERSION 3.20)

project(mathcalc VERSION 0.1.0 LANGUAGES CXX)

add_library(mathcalc STATIC src/calc_math_lib.cpp)
target_include_directories(mathcalc PUBLIC ${CMAKE_CURRENT_SOURCE_DIR}/include)

# clang-tidy
find_program(CLANG_TIDY_EXE NAMES clang-tidy)
if(CLANG_TIDY_EXE)
    set_target_properties(mathcalc PROPERTIES CXX_CLANG_TIDY ${CLANG_TIDY_EXE})
endif()

# clang-format
find_program(CLANG_FORMAT_EXE NAMES clang-format)
if(CLANG_FORMAT_EXE)
    file(GLOB_RECURSE ALL_CXX_SOURCE_FILES src/*.cpp include/*.hpp)
    add_custom_target(mathcalc-format COMMAND ${CLANG_FORMAT_EXE} -i -style=file ${ALL_CXX_SOURCE_FILES})
endif()

install(TARGETS mathcalc 
    ARCHIVE DESTINATION lib
    INCLUDES DESTINATION include
)

install(DIRECTORY ${CMAKE_CURRENT_SOURCE_DIR}/include/ DESTINATION include)