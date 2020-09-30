set(glm_TAG "0.9.9.8")

UpdateExternalLibTag("glm" "https://github.com/g-truc/glm.git" ${glm_TAG})

add_subdirectory(glm EXCLUDE_FROM_ALL)