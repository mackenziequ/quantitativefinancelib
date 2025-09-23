set(qflib_SOURCES 
    empty.cpp 
)

add_library(qflib STATIC ${qflib_SOURCES})

target_include_directories(qflib PRIVATE 
    .. 
)

# compiler and linker option adjustments for targets
if(CMAKE_CXX_COMPILER_ID STREQUAL "MSVC")
    target_compile_options(qflib PRIVATE "/permissive-")
elseif(CMAKE_CXX_COMPILER_ID STREQUAL "GNU") 
    target_compile_options(qflib PRIVATE -fPIC)
endif()
