cmake_minimum_required(VERSION 3.16...3.26)

include("${CMAKE_CURRENT_SOURCE_DIR}/cmake/common/bootstrap.cmake"
        NO_POLICY_SCOPE)

project(${_name} VERSION ${_version})

option(ENABLE_FRONTEND_API "Use obs-frontend-api for UI functionality" OFF)
option(ENABLE_QT "Use Qt functionality" OFF)

include(compilerconfig)
include(defaults)
include(helpers)

add_library(${CMAKE_PROJECT_NAME}_lib MODULE src/metaswitch_plugin/*.cpp)

find_package(libobs REQUIRED)
target_link_libraries(${CMAKE_PROJECT_NAME} PRIVATE OBS::libobs)

find_package(OBS REQUIRED) # find the OBS SDK and link it into our build
target_link_libraries(${CMAKE_PROJECT_NAME}_lib PRIVATE OBS::obs-plugin)

if(ENABLE_FRONTEND_API)
  find_package(obs-frontend-api REQUIRED)
  target_link_libraries(${CMAKE_PROJECT_NAME} PRIVATE OBS::obs-frontend-api)
endif()

if(ENABLE_QT)
  find_package(
    Qt5
    COMPONENTS Widgets Core
    REQUIRED) # Updated to explicitly find Qt5 and required components
  target_link_libraries(${CMAKE_PROJECT_NAME} PRIVATE Qt5::Core Qt5::Widgets)
  target_compile_options(
    ${CMAKE_PROJECT_NAME}
    PRIVATE
      $<$<C_COMPILER_ID:Clang,AppleClang>:-Wno-quoted-include-in-framework-header
      -Wno-comma>)
  set_target_properties(
    ${CMAKE_PROJECT_NAME}
    PROPERTIES AUTOMOC ON
               AUTOUIC ON
               AUTORCC ON)
endif()



set_target_properties(${CMAKE_PROJECT_NAME} PROPERTIES OUTPUT_NAME ${_name})



# Include directories for header files
target_include_directories(${CMAKE_PROJECT_NAME}_lib
                           PRIVATE ${CMAKE_SOURCE_DIR}/src/metaswitch_plugin/include)
