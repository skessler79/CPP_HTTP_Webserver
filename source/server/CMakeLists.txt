

# Add executable targets
add_executable(server src/main.cpp)

# Link the executable with the libraries
target_link_libraries(server PRIVATE net_utils)
target_link_libraries(server PRIVATE InetAddress)
target_link_libraries(server PRIVATE Socket)

# Add the /source directory to the include directories for the server target
# target_include_directories(server PRIVATE ${CMAKE_SOURCE_DIR}/source)