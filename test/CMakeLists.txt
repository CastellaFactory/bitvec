set(TEST_SRC_DIR "${PROJECT_SOURCE_DIR}/src")

add_executable(bitvec_test bitvec_test.cpp)
target_link_libraries(bitvec_test gtest gtest_main)

add_test(
  NAME bitvec
  COMMAND $<TARGET_FILE:bitvec_test> --gtest_color=yes
)

