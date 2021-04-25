cmake_minimum_required(VERSION 3.12)

project(TRex C)

set(CMAKE_C_STANDARD 11)

add_executable(${PROJECT_NAME}
	src/main.c src/main.h src/gameState.c src/gameState.h src/livesState.c src/livesState.h)

target_include_directories(${PROJECT_NAME} PUBLIC ${CMAKE_CURRENT_SOURCE_DIR}/src
    ${CMAKE_CURRENT_SOURCE_DIR}/SDL2_image ${CMAKE_CURRENT_SOURCE_DIR}/SDL2_ttf)

add_subdirectory(${CMAKE_CURRENT_SOURCE_DIR}/SDL2)
add_subdirectory(${CMAKE_CURRENT_SOURCE_DIR}/SDL2_image)
add_subdirectory(${CMAKE_CURRENT_SOURCE_DIR}/SDL2_ttf)

target_link_libraries(${PROJECT_NAME} PUBLIC m SDL2 SDL2_image SDL2_ttf)

if(WINDOWS)
    target_link_libraries(${PROJECT_NAME} PUBLIC SDL2main)
    add_definitions(-Dmain=SDL_main)
endif()

add_custom_command(
        TARGET ${PROJECT_NAME} PRE_BUILD
        COMMAND ${CMAKE_COMMAND} -E copy_directory
                ${CMAKE_CURRENT_SOURCE_DIR}/files
                ${CMAKE_CURRENT_BINARY_DIR}/files)
