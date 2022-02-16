#################################################################
#
#     Copyright(C) 2018 Sonavex Inc., Baltimore MD.
#     All rights reserved.
#
#     Author: Xin "Ben" Kang
#
#################################################################

cmake_minimum_required(VERSION 3.15)

set(PROJECT_NAME testWidget)
project(${PROJECT_NAME} CXX)
set( CMAKE_CXX_STANDARD 17 )
set( CMAKE_CXX_STANDARD_REQUIRED ON)


set(CMAKE_ARCHIVE_OUTPUT_DIRECTORY "${CMAKE_BINARY_DIR}")
set(CMAKE_LIBRARY_OUTPUT_DIRECTORY "${CMAKE_BINARY_DIR}")
set(CMAKE_RUNTIME_OUTPUT_DIRECTORY "${CMAKE_BINARY_DIR}")

set(QT5_COMPONENTS Widgets MultimediaWidgets Concurrent)

find_package(Qt5 REQUIRED COMPONENTS ${QT5_COMPONENTS} NO_MODULE)

# Instruct CMake to run moc, rcc and uic automatically when needed.
set(CMAKE_AUTOMOC ON)
set(CMAKE_AUTORCC ON)
set(CMAKE_AUTOUIC ON)


#####################################################################
# Executable
#####################################################################
# EchoSure (GUI)
set(TARGET_NAME TestState)

file(GLOB ${TARGET_NAME}_HDR ${CMAKE_CURRENT_LIST_DIR}/*.h)
file(GLOB ${TARGET_NAME}_SRC ${CMAKE_CURRENT_LIST_DIR}/*.cpp)
file(GLOB ${TARGET_NAME}_QRC ${CMAKE_CURRENT_LIST_DIR}/*.qrc)


add_executable(${TARGET_NAME} "")
target_sources(${TARGET_NAME}
PRIVATE
  ${${TARGET_NAME}_HDR}
  ${${TARGET_NAME}_SRC}
  ${${TARGET_NAME}_QRC})
target_include_directories(${TARGET_NAME}
  PRIVATE "${CMAKE_CURRENT_LIST_DIR}"
  SYSTEM PRIVATE "${Boost_INCLUDE_DIRS}" "${CMAKE_CURRENT_BINARY_DIR}")
target_link_libraries(${TARGET_NAME} PRIVATE
                      Qt5::Widgets
                      Qt5::MultimediaWidgets
                      Qt5::Concurrent
                      )

if(MSVC)
  set_target_properties(${TARGET_NAME} PROPERTIES FOLDER modules
      VS_DEBUGGER_WORKING_DIRECTORY "${CMAKE_RUNTIME_OUTPUT_DIRECTORY}" )
  set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} /MP")
endif()

if(DEV_IGNORE_KNOWN_WARNING_CLASSES)
  set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} /wd4714")
endif()




# EOF
