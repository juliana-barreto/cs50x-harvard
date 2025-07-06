# Minimum version of CMake required
cmake_minimum_required(VERSION 3.28)

# Project name and version
project(cs50x_harvard C)

# Set the C standard to C11 and ensure it is required
set(CMAKE_C_STANDARD 11)
set(CMAKE_C_STANDARD_REQUIRED ON)

# 1. Find all .c files in the specified directories
file(GLOB_RECURSE C_FILES
        "problem-sets/*.c"
        "practice/*.c"
)

# 2. Loop through each file found in the previous step
foreach(C_FILE ${C_FILES})

    # 3. Extract the filename without the path and extension
    get_filename_component(EXECUTABLE_NAME ${C_FILE} NAME_WE)

    # 4. Create an executable target for each .c file found
    add_executable(${EXECUTABLE_NAME} ${C_FILE}
            problem-sets/problem-set-03/teste.c)

    # Status message to indicate the executable created
    message(STATUS "Alvo criado: ${EXECUTABLE_NAME}")

endforeach() # End of foreach loop
