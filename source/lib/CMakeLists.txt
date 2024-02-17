# Create a library target called "utils"
add_library(utils
    src/net_utils.cpp
    src/InetAddress.cpp
    src/Socket.cpp)

# Specify where the library's header file is
target_include_directories(utils PUBLIC "${CMAKE_CURRENT_SOURCE_DIR}/include")