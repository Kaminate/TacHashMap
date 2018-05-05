project(Shell)
set(TacTarget "Shell")

add_executable(${TacTarget}
  main.cpp
  )

set_target_properties( ${TacTarget} PROPERTIES OUTPUT_NAME "Example Project" )

target_sources(${TacTarget} PRIVATE
  ${TacCommon})

set_target_properties(${TacTarget} PROPERTIES
  VS_DEBUGGER_WORKING_DIRECTORY "${CMAKE_SOURCE_DIR}"
  VS_STARTUP_PROJECT ${TacTarget}
  LINKER_LANGUAGE CXX)

