# set location of python headers and libraries
if(CMAKE_CXX_COMPILER_ID STREQUAL "MSVC")           # VC++ on Windows
    set(PYTHON_HOME $ENV{LOCALAPPDATA}/Programs/Miniconda3/envs/qfgb)
    set(PYTHON_INCLUDE_DIRECTORY ${PYTHON_HOME}/include)
    set(NUMPY_INCLUDE_DIRECTORY ${PYTHON_HOME}/Lib/site-packages/numpy/core/include)
    set(PYTHON_LIBRARY_PATH ${PYTHON_HOME}/libs/python312.lib)
elseif(CMAKE_CXX_COMPILER_ID STREQUAL "GNU")       # GCC on Linux
    set(PYTHON_HOME $ENV{HOME}/miniconda3/envs/qfgb)
    set(PYTHON_INCLUDE_DIRECTORY ${PYTHON_HOME}/include/python3.12)
    set(NUMPY_INCLUDE_DIRECTORY ${PYTHON_HOME}/lib/python3.12/site-packages/numpy/core/include)
    set(PYTHON_LIBRARY_PATH ${PYTHON_HOME}/lib/libpython3.12.so)
else()
    message(FATAL_ERROR "Unsupported C++ compiler")

endif()

set(pyqflib_SOURCES
    pymodule.cpp 	
)

add_library(pyqflib SHARED ${pyqflib_SOURCES})

add_dependencies(pyqflib qflib)

target_include_directories(pyqflib PRIVATE
    .. 
    ${PYTHON_INCLUDE_DIRECTORY} 
    ${NUMPY_INCLUDE_DIRECTORY} 
)

# remove prefix from the DLL name
set_target_properties(pyqflib PROPERTIES PREFIX "")
set_target_properties(pyqflib PROPERTIES DEBUG_POSTFIX "")
# silence the numpy deprecation message
set_target_properties(pyqflib PROPERTIES COMPILE_DEFINITIONS "NPY_NO_DEPRECATED_API")

# linker option adjustments for supported compilers
if(CMAKE_CXX_COMPILER_ID STREQUAL "MSVC")         # VC++ on Windows
    # adjust suffix and output location
    set_target_properties(pyqflib PROPERTIES SUFFIX ".pyd")
    set_target_properties(pyqflib PROPERTIES RUNTIME_OUTPUT_DIRECTORY ${CMAKE_CURRENT_SOURCE_DIR}/qflib)   
    # link libraries and options
    target_link_libraries(pyqflib PRIVATE
        ${CMAKE_ARCHIVE_OUTPUT_DIRECTORY}/qflib${CMAKE_DEBUG_POSTFIX}.lib 
        ${PYTHON_LIBRARY_PATH}        
    )
    target_link_options(pyqflib PRIVATE /MANIFEST:NO /INCREMENTAL:NO /DEBUG)    
elseif(CMAKE_CXX_COMPILER_ID STREQUAL "GNU")       # GCC on Linux
    # adjust output location
    set_target_properties(pyqflib PROPERTIES LIBRARY_OUTPUT_DIRECTORY ${CMAKE_CURRENT_SOURCE_DIR}/qflib)
    # link libraries and options (assuming GNU)
    target_link_libraries(pyqflib PRIVATE 
        ${CMAKE_ARCHIVE_OUTPUT_DIRECTORY}/libqflib${CMAKE_DEBUG_POSTFIX}.a 
        ${PYTHON_LIBRARY_PATH} 
    )
endif()
