add_executable(main main.cpp core/math/geometry.cpp include/math/geometry.h)

#add_subdirectory(utils)
#add_subdirectory(samples)

target_include_directories(main PUBLIC
        $<BUILD_INTERFACE: ${CMAKE_CURRENT_SOURCE_DIR}/include/math>
        $<INSTALL_INTERFACE: include/math>  # <prefix>/include/mylib
        )
target_link_libraries(main cxxopts EnTT)

#target_link_libraries(main utils)
#target_link_libraries(01-init_instance utils)