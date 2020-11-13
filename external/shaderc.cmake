set(shaderc_TAG "v2020.3")

UpdateExternalLibTag("shaderc" "https://github.com/google/shaderc.git" ${shaderc_TAG})

set(SHADERC_SKIP_TESTS ON CACHE BOOL "Skip building tests" FORCE)

add_subdirectory(shaderc EXCLUDE_FROM_ALL)
