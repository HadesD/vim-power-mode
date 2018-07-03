# compile_commands.json
set(CMAKE_EXPORT_COMPILE_COMMANDS ON)

# Gen compile_commands.json
if (${CMAKE_EXPORT_COMPILE_COMMANDS} STREQUAL ON)
  find_program(COMPDB compdb)
  if (COMPDB)
    execute_process(COMMAND ${CMAKE_COMMAND} -E
      remove ${CMAKE_CURRENT_SOURCE_DIR}/compile_commands.json
      )
    add_custom_target(gen_compile_commands
      SOURCES ${CMAKE_CURRENT_SOURCE_DIR}/compile_commands.json
      )
    add_custom_command(OUTPUT ${CMAKE_CURRENT_SOURCE_DIR}/compile_commands.json
      COMMAND
      ${COMPDB} -p ${CMAKE_CURRENT_BINARY_DIR}/ list > ${CMAKE_CURRENT_SOURCE_DIR}/compile_commands.json
      )
  else()
    message(AUTHOR_WARNING "'compdb' not found")
  endif()
endif()

