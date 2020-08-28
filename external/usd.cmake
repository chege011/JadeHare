set(usd_REV "71b4baace2044ea4400ba802e91667f9ebe342f0")

UpdateExternalLib("usd" "https://github.com/PixarAnimationStudios/USD.git" ${usd_REV})

set(PXR_BUILD_PRMAN_PLUGIN OFF CACHE BOOL "" FORCE)
set(PXR_BUILD_DOCUMENTATION OFF CACHE BOOL "" FORCE)

add_subdirectory(usd EXCLUDE_FROM_ALL)