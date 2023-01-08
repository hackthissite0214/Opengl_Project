cmake_minimum_required(VERSION 3.13)

set(PROJECT_NAME opengl_project)
set(CMAKE_CXX_STANDARD 17)

set(WINDOW_NAME "Opengl Engine")
set(WINDOW_WIDTH 960)
set(WINDOW_HEIGHT 540)

project(
  ${PROJECT_NAME}
  VERSION 0.1
  DESCRIPTION "3D 프로젝트"
  LANGUAGES CXX
  )
  
add_executable(${PROJECT_NAME} 
                      src/main.cpp
  src/common.h        src/common.cpp
  src/shader.h        src/shader.cpp
  src/Program.h       src/Program.cpp
  src/Engine.h        src/Engine.cpp
  src/Buffer.h        src/Buffer.cpp
  src/VertexLayout.h  src/VertexLayout.cpp
  src/Image.h         src/Image.cpp
  src/Texture.h       src/Texture.cpp
  )

include(Dependency.cmake)

# 우리 프로젝트에 include / lib 관련 옵션 추가
target_include_directories(${PROJECT_NAME} PUBLIC ${DEP_INCLUDE_DIR})
target_link_directories(${PROJECT_NAME} PUBLIC ${DEP_LIB_DIR})
target_link_libraries(${PROJECT_NAME} PUBLIC ${DEP_LIBS})

target_compile_definitions(${PROJECT_NAME} PUBLIC
  WINDOW_NAME="${WINDOW_NAME}"
  WINDOW_WIDTH=${WINDOW_WIDTH}
  WINDOW_HEIGHT=${WINDOW_HEIGHT}
  )

# Dependency들이 먼저 build 될 수 있게 관계 설정
add_dependencies(${PROJECT_NAME} ${DEP_LIST})