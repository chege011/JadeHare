set(shaderc_TAG "v2020.3")

UpdateExternalLibTag("shaderc" "https://github.com/google/shaderc.git" ${shaderc_TAG})

find_program(PYTHON_EXECUTABLE NAMES python)
if (NOT PYTHON_EXECUTABLE)
    message(FATAL_ERROR "Failed to find python.")
endif ()
execute_process(
        COMMAND ${PYTHON_EXECUTABLE} "git-sync-deps"
        WORKING_DIRECTORY "${CMAKE_CURRENT_SOURCE_DIR}/shaderc/utils"
        RESULT_VARIABLE py_result)

set(SHADERC_SKIP_TESTS ON CACHE BOOL "Skip building tests" FORCE)

add_subdirectory(shaderc EXCLUDE_FROM_ALL)
