set(usd_TAG "v20.08")

UpdateExternalLibTag("usd" "https://github.com/PixarAnimationStudios/USD.git" ${usd_TAG})

set(PXR_BUILD_PRMAN_PLUGIN OFF CACHE BOOL "" FORCE)
set(PXR_BUILD_DOCUMENTATION OFF CACHE BOOL "" FORCE)

add_subdirectory(usd EXCLUDE_FROM_ALL)