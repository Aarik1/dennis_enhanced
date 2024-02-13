# Dennis Enhanced Edition - Copyright Aarik 2024 - All rights reserved #
# This executable starts up with windows and watches for dennis incase it crashes
# If it does crash it will bring it back online.

cmake_minimum_required(VERSION 3.20)

project(Dennis_Watcher)

add_executable(Dennis_Watcher WIN32
	watch.cpp
)

# Linker directories
target_link_directories(Dennis_Watcher PUBLIC
	${DENNIS_LIB_DIR}
)

# Libraries that we link to
target_link_libraries(Dennis_Watcher
	advapi32.lib
)