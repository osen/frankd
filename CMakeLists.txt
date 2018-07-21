cmake_minimum_required(VERSION 2.6)
project(FRANKD)

if(MSVC)
  include_directories(
    ${PROJECT_SOURCE_DIR}/contrib/windows-vc15-x86/include
  )

  link_directories(
    ${PROJECT_SOURCE_DIR}/contrib/windows-vc15-x86/lib
  )
else()
  include_directories(
    ${PROJECT_SOURCE_DIR}/contrib/windows-gcc-x86/include
  )

  link_directories(
    ${PROJECT_SOURCE_DIR}/contrib/windows-gcc-x86/lib
  )
endif()

add_executable(frankd
  src/Mob.cpp
  src/Font.cpp
  src/main.cpp
  src/Camera.cpp
  src/util.cpp
  src/Monster.cpp
  src/Foot.cpp
  src/Background.cpp
)

target_link_libraries(frankd SDL2 GLD ws plank ws2_32)
