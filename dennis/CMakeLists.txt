# Dennis Enhanced Edition - Copyright Aarik 2024 - All rights reserved #
# Dennis himself.

cmake_minimum_required(VERSION 3.20)

project(Dennis)

add_executable(Dennis WIN32
	main.cpp
	dennis.cpp
	dennis.h
	dectalk.cpp
	dectalk.h
	dennis.rc
)

# Linker directories
target_link_directories(Dennis PUBLIC
	${DENNIS_LIB_DIR}
)

add_compile_definitions(Dennis "ENGLISH_US;ENGLISH")

# Libraries that we link to
target_link_libraries(Dennis
	DecTalk.lib
	Winmm.lib
)