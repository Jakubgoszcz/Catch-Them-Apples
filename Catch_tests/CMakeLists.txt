cmake_minimum_required(VERSION 3.3.1)

project(Catch_tests_run)
add_executable(
	Catch_tests_run 
	main_test.cpp 
	../game/gameFunctions.h
	../game/gameFunctions.cpp 
	../game/imageProcessing.h
	../game/imageProcessing.cpp 
	../game/globalVariables.h
)
find_package(SFML 2.5 COMPONENTS graphics REQUIRED)

find_package(OpenCV 4.0 REQUIRED)
include_directories(${OpenCV_INCLUDE_DIRS})
target_link_libraries(
	Catch_tests_run
        Catch2::Catch2WithMain
        ${OpenCV_LIBS}
        sfml-graphics
)

set(SOURCE_DIR "${CMAKE_SOURCE_DIR}/Catch_tests/testRes")
set(DESTINATION_DIR "${CMAKE_BINARY_DIR}/Catch_tests/testRes")

file(GLOB SOURCE_FILES "${SOURCE_DIR}/*")

add_custom_command(
        TARGET Catch_tests_run POST_BUILD
        COMMAND ${CMAKE_COMMAND} -E copy_directory ${SOURCE_DIR} ${DESTINATION_DIR}
        COMMENT "Copying files from ${SOURCE_DIR} to ${DESTINATION_DIR}"
)

include(Catch)
catch_discover_tests(Catch_tests_run)
