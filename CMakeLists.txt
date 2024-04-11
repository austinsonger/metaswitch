cmake_minimum_required(VERSION 3.16...3.26)

include("${CMAKE_CURRENT_SOURCE_DIR}/cmake/common/bootstrap.cmake" NO_POLICY_SCOPE)


project(MetaSwitch VERSION 1.0.0)

option(ENABLE_FRONTEND_API "Use obs-frontend-api for UI functionality" ON)
option(ENABLE_QT "Use Qt functionality" ON) # Assuming you're not using Qt, adjust if necessary

include(compilerconfig)
include(defaults)
include(helpers)

add_library(${CMAKE_PROJECT_NAME} MODULE)

# Specifying source files
set(SOURCE_FILES
    src/metaswitch_plugin/devices/enumerate.c
    src/metaswitch_plugin/devices/enumerate_win.c
    src/metaswitch_plugin/ui/countdown_ui.cpp
    src/metaswitch_plugin/ui/metaswitch_ui.cxx
    src/metaswitch_plugin/render/capture.cpp
    src/metaswitch_plugin/render/capture_win.cpp
    src/metaswitch_plugin/render/renderer.cpp
)

if(WIN32)
  list(APPEND SOURCE_FILES src/metaswitch_plugin/devices/enumerate_win.c src/metaswitch_plugin/render/capture_win.cpp)
else()
  list(APPEND SOURCE_FILES src/metaswitch_plugin/devices/enumerate.c src/metaswitch_plugin/render/capture.cpp)
endif()

target_sources(${CMAKE_PROJECT_NAME} PRIVATE ${SOURCE_FILES})

find_package(libobs REQUIRED)
target_link_libraries(${CMAKE_PROJECT_NAME} PRIVATE OBS::libobs)

if(ENABLE_FRONTEND_API)
  find_package(obs-frontend-api REQUIRED)
  target_link_libraries(${CMAKE_PROJECT_NAME} PRIVATE OBS::obs-frontend-api)
endif()

if(ENABLE_QT)
  find_package(Qt5 COMPONENTS Widgets Core REQUIRED)
  target_link_libraries(${CMAKE_PROJECT_NAME} PRIVATE Qt5::Core Qt5::Widgets)
  target_compile_options(
    ${CMAKE_PROJECT_NAME} PRIVATE $<$<C_COMPILER_ID:Clang,AppleClang>:-Wno-quoted-include-in-framework-header
                                  -Wno-comma>)
  set_target_properties(
    ${CMAKE_PROJECT_NAME}
    PROPERTIES AUTOMOC ON
               AUTOUIC ON
               AUTORCC ON)
endif()

set_target_properties(${CMAKE_PROJECT_NAME} PROPERTIES OUTPUT_NAME "metaswitch_plugin")

# Include directories for project header files
target_include_directories(${CMAKE_PROJECT_NAME} PRIVATE include)






