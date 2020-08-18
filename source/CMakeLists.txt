add_executable(main main.cpp)

#add_subdirectory(utils)
#add_subdirectory(samples)

target_link_libraries(main cxxopts)

#target_link_libraries(main utils)
#target_link_libraries(01-init_instance utils)