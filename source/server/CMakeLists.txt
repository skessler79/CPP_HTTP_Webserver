

# Add executable targets
add_executable(server src/main.cpp)

# Link the executable with the "net_utils" library
target_link_libraries(server PRIVATE net_utils)

# Add the /source directory to the include directories for the server target
# target_include_directories(server PRIVATE ${CMAKE_SOURCE_DIR}/source)