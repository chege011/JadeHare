set(UTILS_HEADER_FILES
        util.hpp
        util_init.hpp
        )

set(UTILS_SOURCE_FILES
        util.cpp
        util_init.cpp
        )

add_library(utils STATIC
        ${UTILS_HEADER_FILES}
        ${UTILS_SOURCE_FILES}
        )

set_target_properties(utils PROPERTIES LINKER_LANGUAGE CXX)
target_include_directories(utils INTERFACE  ./)
target_link_libraries(utils glm Vulkan::Vulkan)