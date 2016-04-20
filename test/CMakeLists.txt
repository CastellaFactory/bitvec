add_executable(bitvec_test bitvec_test.cpp)
target_link_libraries(bitvec_test ${Boost_UNIT_TEST_FRAMEWORK_LIBRARY})

add_test(
  NAME bitvec
  COMMAND $<TARGET_FILE:bitvec_test>
)

