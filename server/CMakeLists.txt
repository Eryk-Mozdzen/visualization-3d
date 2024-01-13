cmake_minimum_required(VERSION 3.16)

project(server)

set(CMAKE_AUTOMOC ON)
set(CMAKE_AUTORCC ON)

find_package(Qt5 COMPONENTS
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
	"src/CameraController.cpp"
	"src/Server.cpp"

	"src/objects/Ground.cpp"
	"src/objects/Sphere.cpp"
	"src/objects/Cylinder.cpp"
	"src/objects/Cuboid.cpp"
	"src/objects/Model.cpp"

	"src/utils/Object.cpp"
	"src/utils/Material.cpp"
	"src/utils/Transform.cpp"
	"src/utils/ArgumentStream.cpp"
)

target_include_directories(${PROJECT_NAME} PRIVATE
	"src"
	"src/objects"
	"src/utils"
)

target_compile_options(${PROJECT_NAME} PRIVATE
	-Wall
	-Wextra
	-Wpedantic
)

target_link_libraries(${PROJECT_NAME}
	Qt5::Core
	Qt5::Widgets
	Qt5::Network
	Qt5::3DCore
	Qt5::3DRender
	Qt5::3DExtras
)
