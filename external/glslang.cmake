set(glslang_TAG "vulkan-1.1-rc9")

UpdateExternalLibTag("glslang" "https://github.com/KhronosGroup/glslang.git" ${glslang_TAG})

add_subdirectory(glslang EXCLUDE_FROM_ALL)