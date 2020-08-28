set(entt_REV "27209e4836ceabea6a8476ce7864a15745e25b6c")

UpdateExternalLib("entt" "https://github.com/skypjack/entt.git" ${entt_REV})

add_subdirectory(entt EXCLUDE_FROM_ALL)