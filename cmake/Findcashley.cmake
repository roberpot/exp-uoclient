SET(CASHLEY_SEARCH_PATHS
        ~/Library/Frameworks
        /Library/Frameworks
        /usr/local
        /usr/local/lib
        /usr
        /sw # Fink
        /opt/local # DarwinPorts
        /opt/csw # Blastwave
        /opt
        )

FIND_PATH(CASHLEY_INCLUDE_DIR cashley.h
        HINTS
        $ENV{CASHLEYDIR}
        PATH_SUFFIXES include/cashley include
        PATHS ${CASHLEY_SEARCH_PATHS}
        )

FIND_LIBRARY(CASHLEY_LIBRARY_TEMP
        NAMES cashley
        HINTS
        $ENV{CASHLEYDIR}
        PATH_SUFFIXES lib64 lib
        PATHS ${CASHLEY_SEARCH_PATHS}
        )

IF(CASHLEY_LIBRARY_TEMP)
    # For MinGW library
    IF(MINGW)
        SET(CASHLEY_LIBRARY_TEMP ${MINGW32_LIBRARY} ${CASHLEY_LIBRARY_TEMP})
    ENDIF(MINGW)
    # Set the final string here so the GUI reflects the final state.
    SET(CASHLEY_LIBRARY ${CASHLEY_LIBRARY_TEMP} CACHE STRING "Where the CAshley Library can be found")
    # Set the temp variable to INTERNAL so it is not seen in the CMake GUI
    SET(CASHLEY_LIBRARY_TEMP "${CASHLEY_LIBRARY_TEMP}" CACHE INTERNAL "")
ENDIF(CASHLEY_LIBRARY_TEMP)

INCLUDE(FindPackageHandleStandardArgs)

FIND_PACKAGE_HANDLE_STANDARD_ARGS(CASHLEY REQUIRED_VARS CASHLEY_LIBRARY CASHLEY_INCLUDE_DIR)