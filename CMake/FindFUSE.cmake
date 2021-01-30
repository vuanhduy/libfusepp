# check if already in cache, be silent
IF (FUSE_INCLUDE_DIR AND FUSE_LIBRARIES)
    SET(FUSE_FIND_QUIETLY TRUE)
ENDIF ()

# find includes
FIND_PATH(FUSE_INCLUDE_DIR fuse.h
        PATHS
        /usr/local/include
        /usr/local/include/fuse3
        /usr/local/include/fuse
        )

if (APPLE)
    SET(FUSE_NAMES libosxfuse.dylib fuse)
else (APPLE)
    SET(FUSE_NAMES fuse3)
endif (APPLE)
FIND_LIBRARY(FUSE_LIBRARIES
        NAMES ${FUSE_NAMES}
        PATHS
        /usr/lib/x86_64-linux-gnu
        /usr/local/lib/x86_64-linux-gnu/
        )

include("FindPackageHandleStandardArgs")
find_package_handle_standard_args("FUSE" DEFAULT_MSG
        FUSE_INCLUDE_DIR FUSE_LIBRARIES)

mark_as_advanced(FUSE_INCLUDE_DIR FUSE_LIBRARIES)