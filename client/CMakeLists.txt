cmake_minimum_required(VERSION 3.10)
project(puromeu)


macro (add_sources)
    file (RELATIVE_PATH _relPath "${PROJECT_SOURCE_DIR}" "${CMAKE_CURRENT_SOURCE_DIR}")
    foreach (_src ${ARGN})
        if (_relPath)
            list (APPEND SRCS "${_relPath}/${_src}")
        else()
            list (APPEND SRCS "${_src}")
        endif()
    endforeach()
    if (_relPath)
        # propagate SRCS to parent directory
        set (SRCS ${SRCS} PARENT_SCOPE)
    endif()
endmacro()


add_sources(main.cpp)
add_executable(puromeu ${SRCS})

find_package(Boost 1.66.0 REQUIRED system)
include_directories(${Boost_INCLUDE_DIRS})
target_link_libraries(puromeu ${Boost_LIBRARIES} -lpthread)
