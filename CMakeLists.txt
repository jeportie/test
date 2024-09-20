cmake_minimum_required(VERSION 3.10)
project(ft_split_tests C)

# Enable testing with CTest
enable_testing()

# Find Check library (install if necessary)
find_package(PkgConfig REQUIRED)
pkg_check_modules(CHECK REQUIRED check)

# Add the test executable and include ft_split.c for linking
add_executable(test_ft_split test_ft_split.c ft_split.c)

# Link the Check library
target_link_libraries(test_ft_split ${CHECK_LIBRARIES})
target_include_directories(test_ft_split PUBLIC ${CHECK_INCLUDE_DIRS})

# Add the test to CTest
add_test(NAME ft_split_test COMMAND test_ft_split)

# Add custom CTest options
set_tests_properties(ft_split_test PROPERTIES
    TIMEOUT 5
)

