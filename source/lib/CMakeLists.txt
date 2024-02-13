# Create a library target called "net_utils"
add_library(net_utils src/net_utils.cpp)
add_library(InetAddress src/InetAddress.cpp)

# Specify where the library's header file is
target_include_directories(net_utils PUBLIC "${CMAKE_CURRENT_SOURCE_DIR}/include")
target_include_directories(InetAddress PUBLIC "${CMAKE_CURRENT_SOURCE_DIR}/include")