cmake_minimum_required(VERSION 3.13)

set(PROJECT_NAME opengl_project)
set(CMAKE_CXX_STANDARD 17)

project(
  ${PROJECT_NAME}
  VERSION 0.1
  DESCRIPTION "3D 프로젝트"
  LANGUAGES CXX)
  
add_executable(${PROJECT_NAME} src/main.cpp)