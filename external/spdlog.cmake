set(spdlog_TAG "v1.8.0")

UpdateExternalLibTag("spdlog" "https://github.com/gabime/spdlog.git" ${spdlog_TAG})

add_subdirectory(spdlog EXCLUDE_FROM_ALL)

