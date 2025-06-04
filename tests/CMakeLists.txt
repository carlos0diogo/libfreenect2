CMAKE_MINIMUM_REQUIRED(VERSION 2.8.12.1)
PROJECT(libfreenect2_tests)

if(TARGET freenect2)
  set(freenect2_LIBRARIES freenect2)
else()
  find_package(freenect2 REQUIRED)
endif()

add_executable(test_parseFrameFilename test_parseFrameFilename.cpp)
target_link_libraries(test_parseFrameFilename ${freenect2_LIBRARIES})
add_test(NAME test_parseFrameFilename COMMAND test_parseFrameFilename)
