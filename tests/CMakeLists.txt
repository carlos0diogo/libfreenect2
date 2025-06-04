CMAKE_MINIMUM_REQUIRED(VERSION 2.8.12.1)

project(libfreenect2_tests)

set(freenect2_ROOT_DIR ${libfreenect2_tests_SOURCE_DIR}/..)

if(TARGET freenect2)
  set(freenect2_LIBRARIES freenect2)
  set(freenect2_INCLUDE_DIR ${freenect2_ROOT_DIR}/include)
else()
  find_package(freenect2 REQUIRED)
endif()

include_directories(
  ${freenect2_INCLUDE_DIR}
)

add_executable(parse_frame_filename_test parse_frame_filename_test.cpp)
target_link_libraries(parse_frame_filename_test ${freenect2_LIBRARIES})

