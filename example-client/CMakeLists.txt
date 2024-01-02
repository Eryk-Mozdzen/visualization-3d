cmake_minimum_required(VERSION 3.16)

project(example-client)

add_executable(${PROJECT_NAME}
	"src/main.cpp"
	"src/Client.cpp"
)

target_include_directories(${PROJECT_NAME} PRIVATE
	"src"
)

target_compile_options(${PROJECT_NAME} PRIVATE
	-Wall
	-Wextra
	-Wpedantic
)
