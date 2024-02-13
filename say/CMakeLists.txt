# Dectalk Say Application

cmake_minimum_required(VERSION 3.20)

project(Say)

add_executable(Say
	say.c
)

# Linker directories
target_link_directories(Say PUBLIC
	${DENNIS_LIB_DIR}
)

add_compile_definitions(Say "ENGLISH_US;ENGLISH")

# Libraries that we link to
target_link_libraries(Say
	DecTalk.lib
	Winmm.lib
)