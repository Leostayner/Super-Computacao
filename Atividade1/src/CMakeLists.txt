cmake_minimum_required(VERSION 3.9)
project (atividade_1)

set(SOURCE_FILES_2 
    "ex.cpp"
    "experimento.cpp"
    "log.cpp"
    "pow3.cpp"
    "pow3mult.cpp"
    "sqrt.cpp"
    "sum.cpp"
    )

file(GLOB SOURCE_FILES
    "*.cpp"
)

add_executable(vector_operations ${SOURCE_FILES})
target_compile_options (vector_operations PRIVATE -std=c++11)
target_compile_definitions(vector_operations PRIVATE O3)
target_link_libraries (vector_operations jsoncpp)


add_executable(vector_O3 ${SOURCE_FILES})
target_compile_options (vector_O3 PRIVATE -std=c++11)
target_compile_definitions(vector_O3 PRIVATE O0)
target_link_libraries (vector_O3 jsoncpp)

