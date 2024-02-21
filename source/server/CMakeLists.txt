

# # Add executable targets
# add_executable(http_server
#     src/main.cpp
#     src/HttpServer.cpp)

# Create a library target called "server"
add_library(server
    src/HttpServer.cpp
    src/FileRouter.cpp
    src/TcpConnection.cpp)

# Link with other libraries
target_link_libraries(server
    utils
    http)

# Specify where the header files are
target_include_directories(server PUBLIC "${CMAKE_CURRENT_SOURCE_DIR}/include")

# Add the /source directory to the include directories for the server target
# target_include_directories(server PRIVATE ${CMAKE_SOURCE_DIR}/source)