
if (BUILD_TESTING)

  file(GLOB TEST_SRC "*.cpp")

  add_executable(test ${TEST_SRC})

  target_compile_options(test PRIVATE -Wall -Wextra -Wpedantic)
  target_link_libraries(test PRIVATE carrascone_modules Catch2::Catch2)

endif()