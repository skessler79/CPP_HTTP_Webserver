

# Add executable targets
add_executable(http_server
    src/main.cpp
    src/HttpServer.cpp)

# Link the executable with the libraries
target_link_libraries(http_server utils)

# Specify where the header files are
target_include_directories(http_server PRIVATE "${CMAKE_CURRENT_SOURCE_DIR}/include")

# Add the /source directory to the include directories for the server target
# target_include_directories(server PRIVATE ${CMAKE_SOURCE_DIR}/source)