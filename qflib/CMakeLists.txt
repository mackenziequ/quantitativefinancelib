set(qflib_SOURCES 
    math/stats/errorfunction.cpp
    pricers/simplepricers.cpp
)

add_library(qflib STATIC ${qflib_SOURCES})

target_include_directories(qflib PRIVATE 
    .. 
    ${THIRDPARTY_DIRECTORY}/armadillo-${ARMA_VERSION}/include
)

# compiler and linker option adjustments for targets
if(CMAKE_CXX_COMPILER_ID STREQUAL "MSVC")
    target_compile_options(qflib PRIVATE "/permissive-")
elseif(CMAKE_CXX_COMPILER_ID STREQUAL "GNU") 
    target_compile_options(qflib PRIVATE -fPIC)
endif()
