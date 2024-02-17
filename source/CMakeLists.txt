# Add executable targets
add_executable(main
    main.cpp)

# Link the executable with the libraries
target_link_libraries(main
    utils
    http
    server)

# Specify header file location
target_include_directories(main PRIVATE "{CMAKE_CURRENT_SOURCE_DIR}/include")