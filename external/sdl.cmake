set(sdl_REV "0093214e25b5ec67c5f1a2767034675c7182aec9")

UpdateExternalLib("SDL" "https://github.com/SDL-mirror/SDL.git" ${sdl_REV})

add_subdirectory(SDL EXCLUDE_FROM_ALL)