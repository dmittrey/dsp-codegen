cmake_minimum_required(VERSION 3.11)
project(parser)

find_package(FLEX REQUIRED)

flex_target(scanner
  reglex.l
  ${CMAKE_CURRENT_BINARY_DIR}/lexer.cc
)

add_executable(${PROJECT_NAME} 
  reglex.cc  
  ${FLEX_scanner_OUTPUTS}
)
target_link_libraries(${PROJECT_NAME} PRIVATE utility)

target_compile_definitions(${PROJECT_NAME} PRIVATE
  $<$<CONFIG:Debug>:DEBUG_LEX=1>)

target_compile_features(${PROJECT_NAME} PRIVATE cxx_std_20)
target_include_directories(${PROJECT_NAME} PRIVATE ${CMAKE_CURRENT_BINARY_DIR})
target_include_directories(${PROJECT_NAME} PRIVATE ${CMAKE_CURRENT_SOURCE_DIR})