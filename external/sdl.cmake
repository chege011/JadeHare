set(sdl_TAG "release-2.0.10")

UpdateExternalLibTag("SDL" "https://github.com/SDL-mirror/SDL.git" ${sdl_TAG})

add_subdirectory(SDL EXCLUDE_FROM_ALL)