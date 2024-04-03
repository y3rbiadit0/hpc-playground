cmake_minimum_required(VERSION 3.25)
project(hpc C)

# Set Architecture to x64 because llvm libraries "x86_64;arm64"
IF (APPLE)
    SET(CMAKE_OSX_ARCHITECTURES "x86_64" CACHE STRING "Build architectures for Mac OS X" FORCE)
ENDIF (APPLE)

set(CMAKE_C_COMPILER "/usr/local/Cellar/llvm/17.0.6_1/bin/clang")
set(CMAKE_CXX_COMPILER "/usr/local/Cellar/llvm/17.0.6_1/bin/clang++")
set(OPENMP_LIBRARIES "/usr/local/Cellar/llvm/17.0.6_1/lib")
set(OPENMP_INCLUDES "/usr/local/Cellar/llvm/17.0.6_1/include")

# arch -> arm64
#set(CMAKE_C_COMPILER "/Users/stormtrooper/Downloads/llvm/17.0.6_arm64/bin/clang")
#set(CMAKE_CXX_COMPILER "/Users/stormtrooper/Downloads/llvm/17.0.6_arm64/bin/clang++")
#set(OPENMP_LIBRARIES "/Users/stormtrooper/Downloads/llvm/17.0.6_arm64/lib")
#set(OPENMP_INCLUDES "/Users/stormtrooper/Downloads/llvm/17.0.6_arm64/include")


OPTION(USE_OpenMP "Use OpenMP to enable <omp.h>" ON)

# Find OpenMP
if (APPLE AND USE_OpenMP)
    if (CMAKE_C_COMPILER_ID MATCHES "Clang")
        set(OpenMP_C "${CMAKE_C_COMPILER}")
        set(OpenMP_C_FLAGS "-fopenmp=libomp -Wno-unused-command-line-argument")
        set(OpenMP_C_LIB_NAMES "libomp" "libgomp" "libiomp5")
        set(OpenMP_libomp_LIBRARY ${OpenMP_C_LIB_NAMES})
        set(OpenMP_libgomp_LIBRARY ${OpenMP_C_LIB_NAMES})
        set(OpenMP_libiomp5_LIBRARY ${OpenMP_C_LIB_NAMES})
    endif ()
    if (CMAKE_CXX_COMPILER_ID MATCHES "Clang")
        set(OpenMP_CXX "${CMAKE_CXX_COMPILER}")
        set(OpenMP_CXX_FLAGS "-fopenmp=libomp -Wno-unused-command-line-argument")
        set(OpenMP_CXX_LIB_NAMES "libomp" "libgomp" "libiomp5")
        set(OpenMP_libomp_LIBRARY ${OpenMP_CXX_LIB_NAMES})
        set(OpenMP_libgomp_LIBRARY ${OpenMP_CXX_LIB_NAMES})
        set(OpenMP_libiomp5_LIBRARY ${OpenMP_CXX_LIB_NAMES})
    endif ()
endif ()

if (USE_OpenMP)
    find_package(OpenMP REQUIRED)
endif (USE_OpenMP)

if (OPENMP_FOUND)
    include_directories("${OPENMP_INCLUDES}")
    link_directories("${OPENMP_LIBRARIES}")
    set(CMAKE_C_FLAGS "${CMAKE_C_FLAGS} ${OpenMP_C_FLAGS}")
    set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} ${OpenMP_CXX_FLAGS}")
    # set (CMAKE_EXE_LINKER_FLAGS "${CMAKE_EXE_LINKER_FLAGS} ${OpenMP_EXE_LINKER_FLAGS}")
endif (OPENMP_FOUND)


set(CMAKE_C_STANDARD 11)
set(CMAKE_C_FLAGS_RELEASE "${CMAKE_C_FLAGS_RELEASE} -O3")


add_executable(hpc main.c report.h report.c)
