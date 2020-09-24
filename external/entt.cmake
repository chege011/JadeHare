set(entt_REV "27209e4836ceabea6a8476ce7864a15745e25b6c")

UpdateExternalLib("entt" "https://github.com/skypjack/entt.git" ${entt_REV})

set(BUILD_DOCS ON CACHE BOOL "" FORCE)

add_subdirectory(entt EXCLUDE_FROM_ALL)