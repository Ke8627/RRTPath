add_executable(shell-app main.cpp
						 vertex.cpp
						 obstacle.cpp
						 map.cpp
						 rrt_path.cpp)
include_directories(
    ${CMAKE_SOURCE_DIR}/include
)
