cmake_minimum_required(VERSION 3.15)
project(jadehare C CXX)

set(CMAKE_CXX_STANDARD 17)

include(FindVulkan)
IF (NOT Vulkan_FOUND)
    message(FATAL_ERROR "Could not find Vulkan library!")
ELSE()
    message(STATUS ${Vulkan_LIBRARY})
ENDIF()

add_subdirectory(external)
add_subdirectory(source)

#target_link_libraries(main glm)