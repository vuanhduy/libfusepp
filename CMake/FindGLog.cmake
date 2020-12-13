# check if already in cache, be silent
IF (GLOG_INCLUDE_DIR AND GLOG_LIBRARIES)
    SET(GLOG_FIND_QUIETLY TRUE)
ENDIF ()

# find includes
FIND_PATH(GLOG_INCLUDE_DIR glog/logging.h
        /usr/local/include
        /usr/include
        )

SET(GLOG_NAMES glog)

FIND_LIBRARY(GLOG_LIBRARIES
        NAMES ${GLOG_NAMES}
        PATHS /lib64 /lib /usr/lib64 /usr/lib /usr/local/lib64 /usr/local/lib /usr/lib/x86_64-linux-gnu
        )

include("FindPackageHandleStandardArgs")
find_package_handle_standard_args("GLog" DEFAULT_MSG
        GLOG_INCLUDE_DIR GLOG_LIBRARIES)

mark_as_advanced(GLOG_INCLUDE_DIR GLOG_LIBRARIES)