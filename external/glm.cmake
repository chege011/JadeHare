set(glm_REV "2929ad5a663597139276c10ef905d91e568fdc48")

UpdateExternalLib("glm" "https://github.com/g-truc/glm.git" ${glm_REV})

add_subdirectory(glm EXCLUDE_FROM_ALL)