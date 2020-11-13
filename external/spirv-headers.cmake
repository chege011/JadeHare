set(spirv-headers_TAG "1.5.4")

UpdateExternalLibTag("SPIRV-Headers" "https://github.com/KhronosGroup/SPIRV-Headers.git" ${spirv-headers_TAG})

add_subdirectory(SPIRV-Headers EXCLUDE_FROM_ALL)