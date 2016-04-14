add_executable(bitvec_test bitvec_test.cpp)
target_link_libraries(bitvec_test)

add_test(
  NAME bitvec
  COMMAND $<TARGET_FILE:bitvec_test>
)

