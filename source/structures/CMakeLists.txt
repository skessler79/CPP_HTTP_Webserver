
# Create a library target called "structures"
add_library(structures INTERFACE)

# Specify where the header files are
target_include_directories(structures INTERFACE "${CMAKE_CURRENT_SOURCE_DIR}/include")