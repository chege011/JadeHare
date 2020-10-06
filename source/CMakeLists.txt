#add_subdirectory(utils)
#add_subdirectory(samples)

set(JADEHARE_INCLUDE_DIR
        ${jadehare_SOURCE_DIR}/include
        )

message(STATUS "SOURCE PATH: ${jadehare_SOURCE_DIR}")

set(JADEHARE_HEADER
        ${JADEHARE_INCLUDE_DIR}/jadehare.h
        ${JADEHARE_INCLUDE_DIR}/util/vecmath.h
        ${JADEHARE_INCLUDE_DIR}/util/check.h
        )


set(JADEHARE_CORE_SOURCE
        util/vecmath.cpp
        )

add_library(jadehare STATIC
        ${JADEHARE_CORE_SOURCE}
        )

add_library(jadehare::jadehare ALIAS jadehare)

target_include_directories(jadehare PUBLIC
        ${JADEHARE_INCLUDE_DIR}
        )

message(STATUS "INCLUDE PATH: ${JADEHARE_INCLUDE_DIR}")

target_link_libraries(jadehare
        EnTT::EnTT
        cxxopts::cxxopts
        spdlog::spdlog
        glm::glm
        )

add_executable(main
        main.cpp
        )

#target_include_directories(main PUBLIC
#  $<BUILD_INTERFACE: ${CMAKE_CURRENT_SOURCE_DIR}/include>
#  $<INSTALL_INTERFACE: include>
#  )

target_link_libraries(main jadehare::jadehare)

#target_link_libraries(main utils)
#target_link_libraries(01-init_instance utils)