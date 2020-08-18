set(rttr_REV "34c4d0e889fb0fe721638975835e2505c1957539")

UpdateExternalLib("rttr" "https://github.com/rttrorg/rttr.git" ${rttr_REV})

add_subdirectory(rttr EXCLUDE_FROM_ALL)