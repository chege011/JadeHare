set(spirv-headers_TAG "1.5.4")

UpdateExternalLib("SPIRV-Headers" "https://github.com/KhronosGroup/SPIRV-Headers.git" "3fdabd0da2932c276b25b9b4a988ba134eba1aa6")

add_subdirectory(SPIRV-Headers EXCLUDE_FROM_ALL)