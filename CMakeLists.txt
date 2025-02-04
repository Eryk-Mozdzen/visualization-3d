cmake_minimum_required(VERSION 3.16)

project(server)

set(CMAKE_AUTOMOC ON)
set(CMAKE_AUTORCC ON)

find_package(Qt6 COMPONENTS
	Core
	Widgets
	Network
	3DCore
	3DRender
	3DExtras
REQUIRED)

add_executable(${PROJECT_NAME}
	"src/main.cpp"
	"src/Window.cpp"
	"src/Server.cpp"

	"src/cam/AbstractCamera.cpp"
	"src/cam/Orbit.cpp"
	"src/cam/Planar.cpp"

	"src/utils/Object.cpp"
	"src/utils/Material.cpp"
	"src/utils/Transform.cpp"

	"src/primitives/Ground.cpp"
	"src/primitives/Sphere.cpp"
	"src/primitives/Cylinder.cpp"
	"src/primitives/Cuboid.cpp"
	"src/primitives/Model.cpp"
	"src/primitives/Empty.cpp"
)

target_include_directories(${PROJECT_NAME} PRIVATE
	"src"
)

target_compile_options(${PROJECT_NAME} PRIVATE
	-O3
	-Wall
	-Wextra
	-Wpedantic
)

target_link_libraries(${PROJECT_NAME}
	Qt6::Core
	Qt6::Widgets
	Qt6::Network
	Qt6::3DCore
	Qt6::3DRender
	Qt6::3DExtras
)
