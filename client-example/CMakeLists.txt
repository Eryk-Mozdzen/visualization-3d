cmake_minimum_required(VERSION 3.16)

project(client-example)

add_executable(${PROJECT_NAME}
	"main.cpp"
	"Client.cpp"
)

target_include_directories(${PROJECT_NAME} PRIVATE
	"."
)
