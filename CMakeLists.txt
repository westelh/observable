cmake_minimum_required(VERSION 3.15.3)
project(observable CXX)
set(CMAKE_CXX_STANDARD 17)

add_compile_options(
        -Wall -Wextra -Werror -pedantic -Wno-error=uninitialized
        $<$<CONFIG:RELEASE>:-Ofast>
        $<$<CONFIG:DEBUG>:-O0>
        $<$<CONFIG:DEBUG>:-ggdb3>
)
add_compile_definitions(
        $<$<CONFIG:RELEASE>:NDEBUG>
        $<$<CONFIG:RELEASE>:BOOST_DISABLE_ASSERTS>
)

add_library(observable_lib INTERFACE)
target_include_directories(observable_lib
        INTERFACE src/observable/headers
        )

add_subdirectory(Google_tests)