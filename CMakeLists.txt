cmake_minimum_required(VERSION 3.23)
project(basics_of_system_programing)

set(CMAKE_C_STANDARD 99)
set(CMAKE_CXX_STANDARD 14)

add_executable(file_size files/file_size.c)
add_executable(files_coping files/files_coping.c)
add_executable(files_coping_revert files/files_coping_revert.cpp)
add_executable(files_revert files/files_revert.cpp)
add_executable(files_size files/files_size.c)

add_executable(processes processes/semaphores_and_processes.c)

add_executable(thread thread/mutex_thread.c)