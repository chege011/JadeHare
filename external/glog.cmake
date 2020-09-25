set(glog_REV "0a2e5931bd5ff22fd3bf8999eb8ce776f159cda6")

UpdateExternalLib("glog" "https://github.com/google/glog.git" ${glog_REV})

add_subdirectory(glog EXCLUDE_FROM_ALL)

