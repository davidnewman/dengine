file(GLOB SOURCES src/*.cpp)

add_library(${PROJECT_NAME} SHARED ${SOURCES})

target_link_libraries(dengine ${SDL2_LIBRARIES} ${SDL2IMAGE_LIBRARIES})
target_include_directories(dengine PUBLIC ${CMAKE_CURRENT_SOURCE_DIR}/include)
