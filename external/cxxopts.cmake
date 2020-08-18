# Copyright (c) Microsoft Corporation. All rights reserved.
# Licensed under the MIT License.

set(cxxopts_REV "05ca8e1cacb5db9152411ad8df1d2d61f0fe82aa")

UpdateExternalLib("cxxopts" "https://github.com/jarro2783/cxxopts.git" ${cxxopts_REV})

set(CXXOPTS_BUILD_EXAMPLES OFF CACHE BOOL "" FORCE)
set(CXXOPTS_BUILD_TESTS OFF CACHE BOOL "" FORCE)

add_subdirectory(cxxopts EXCLUDE_FROM_ALL)