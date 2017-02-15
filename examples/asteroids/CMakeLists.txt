add_executable(asteroids main.cpp)

target_link_libraries(asteroids ${SDL2_LIBRARIES} ${SDL2IMAGE_LIBRARIES} dengine)
