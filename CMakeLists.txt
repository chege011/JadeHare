cmake_minimum_required(VERSION 3.15)
project(VulkanPBR C CXX)

set(CMAKE_CXX_STANDARD 14)

include(FindVulkan)

add_subdirectory(external)
add_subdirectory(source)

target_link_libraries(main glm)