set(spirv-tools_TAG "v2020.5")

UpdateExternalLibTag("SPIRV-Tools" "https://github.com/KhronosGroup/SPIRV-Tools.git" ${spirv-tools_TAG})

set(SPIRV_SKIP_TESTS ON CACHE BOOL "Skip building tests" FORCE)

add_subdirectory(SPIRV-Tools EXCLUDE_FROM_ALL)