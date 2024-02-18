
# Create a library target called "structures"
add_library(structures
    src/LruCache.cpp)

# Specify where the header files are
target_include_directories(structures PUBLIC "${CMAKE_CURRENT_SOURCE_DIR}/include")