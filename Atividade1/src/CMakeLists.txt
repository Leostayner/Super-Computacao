cmake_minimum_required(VERSION 3.9)
project (atividade_1)

set(SOURCE_FILES
    "main.cpp"
    "experimento.cpp"
    "log.cpp"
    "pow3.cpp"
    "pow3mult.cpp"
    "sqrt.cpp"
    "sum.cpp"
    )

add_executable(vector_O0N ${SOURCE_FILES})
target_compile_options (vector_O0N PRIVATE -std=c++11 -O0)
target_link_libraries (vector_O0N jsoncpp)

add_executable(vector_O1N ${SOURCE_FILES})
target_compile_options (vector_O1N PRIVATE -std=c++11 -O1)
target_link_libraries (vector_O1N jsoncpp)

add_executable(vector_O2N ${SOURCE_FILES})
target_compile_options (vector_O2N PRIVATE -std=c++11 -O2)
target_link_libraries (vector_O2N jsoncpp)

add_executable(vector_O3N ${SOURCE_FILES})
target_compile_options (vector_O3N PRIVATE -std=c++11 -O3)
target_link_libraries (vector_O3N jsoncpp)

add_executable(vector_O3F ${SOURCE_FILES})
target_compile_options (vector_O3F PRIVATE -std=c++11 -ftree-vectorize -ffast-math -mavx -O3)
target_link_libraries (vector_O3F jsoncpp)


 
