cmake_minimum_required(VERSION 3.3.1)

project(game)

find_package(SFML 2.5 COMPONENTS graphics REQUIRED)

find_package(Catch2 3)

find_package(OpenCV 4.0 REQUIRED)

find_package(SFML 2.5 COMPONENTS audio system REQUIRED)

include_directories(${OpenCV_INCLUDE_DIRS})

add_executable(
		game
		game/game.cpp
		game/gameFunctions.h
		game/gameFunctions.cpp
		game/imageProcessing.h
		game/imageProcessing.cpp 
		game/globalVariables.h
)


target_link_libraries(
	game
	${OpenCV_LIBS}
	sfml-graphics
	sfml-audio 
	sfml-system
)

file(GLOB ASSET_FILES ${CMAKE_SOURCE_DIR}/assets/*)
foreach(ASSET_FILE ${ASSET_FILES})
    get_filename_component(FILE_NAME ${ASSET_FILE} NAME)
    configure_file(${ASSET_FILE} ${CMAKE_BINARY_DIR}/${FILE_NAME} COPYONLY)
endforeach()


add_subdirectory(Catch_tests)
