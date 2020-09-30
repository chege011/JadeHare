set(entt_TAG "v3.5.2")

UpdateExternalLibTag("entt" "https://github.com/skypjack/entt.git" ${entt_TAG})

set(BUILD_DOCS ON CACHE BOOL "" FORCE)

add_subdirectory(entt EXCLUDE_FROM_ALL)