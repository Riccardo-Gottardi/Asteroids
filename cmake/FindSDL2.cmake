set(FIND_SDL2_PATHS /usr)

find_path(SDL2_INCLUDE_DIR SDL.h
        PATH_SUFFIXES include/SDL2
        PATHS ${FIND_SDL2_PATH})

find_library(SDL2_LIBRARY
        NAMES libSDL2.so
        PATH_SUFFIXES lib/x86_64-linux-gnu
        PATHS ${FIND_SDL2_PATH})