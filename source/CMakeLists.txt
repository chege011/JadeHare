#add_subdirectory(utils)
#add_subdirectory(samples)

set(JADEHARE_CORE_SOURCE
  core/geometry.cpp
  core/medium.cpp)

set(JADEHARE_CORE_HEADER
  include/core/geometry.h
  include/core/medium.h
  )

set(JADEHARE_HEADER
  ${JADEHARE_CORE_HEADER}
  include/jadehare.h
  )

add_library(jadehare STATIC
  ${JADEHARE_HEADER}
  ${JADEHARE_CORE_SOURCE}
  )

add_library(jadehare::jadehare ALIAS jadehare)

target_include_directories(jadehare PUBLIC
  ${CMAKE_CURRENT_SOURCE_DIR}/include
  )

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