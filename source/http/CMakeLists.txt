# Create a library target called "http"
add_library(http
    src/HttpResponse.cpp)

# Link with other libraries
target_link_libraries(http
    server
    utils)

# Specify where the library's header file is
target_include_directories(http PUBLIC "${CMAKE_CURRENT_SOURCE_DIR}/include")