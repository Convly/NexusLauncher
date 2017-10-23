### GENERAL SETTINGS
cmake_minimum_required(VERSION 2.8.11)

# Create project
set(APP_NAME "NexusLauncher")
project(${APP_NAME})

### USEFUL VARIABLES
set(CMAKE_INCLUDE_CURRENT_DIR ON)
set(APP_DIR ${PROJECT_SOURCE_DIR})
set(BIN_OUTPUT_DIR ${APP_DIR}/bin)
message("Starting generation for ${APP_NAME} in ${APP_DIR} - ${CMAKE_SYSTEM_NAME} (${CMAKE_SYSTEM_VERSION})")

### HEADERS FILES
include_directories(
    ${APP_DIR}/src/widget/class/MainWindow
  # --- SYSTEMS
	${APP_DIR}/src/systems/templates
	${APP_DIR}/src/systems/class/UISystem/
  # --- LAUNCHER
	${APP_DIR}/src/launcher/class/
  # --- ERRORS
	${APP_DIR}/src/standalone/errors/class/
)

# Enable debug symbols by default
if(NOT CMAKE_BUILD_TYPE)
  set(CMAKE_BUILD_TYPE Debug CACHE STRING "Choose the type of build (Debug or Release)" FORCE)
endif()

### APP TARGET
set(CMAKE_RUNTIME_OUTPUT_DIRECTORY ${BIN_OUTPUT_DIR})
set(CMAKE_RUNTIME_OUTPUT_DIRECTORY_DEBUG ${BIN_OUTPUT_DIR})
message("The executable will be generated at ${CMAKE_RUNTIME_OUTPUT_DIRECTORY}")

### COMPILATOR OPTIONS
set(CMAKE_CXX_STANDARD 14)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

# Running moc/uic/rcc automatically
set(CMAKE_AUTOMOC ON)
set(CMAKE_AUTOUIC ON)
set(CMAKE_AUTORCC ON)

message("Retrieving compilator options...")
set(CMAKE_MODULE_PATH ${CMAKE_MODULE_PATH} "${PROJECT_SOURCE_DIR}/cmake_modules")

if (WIN32)
	if (MSVC)
		message("MSVC found!")
	else (NOT MSVC)
		message(FATAL_ERROR "MSVC compilator not found")
	endif()
endif()

if(WIN32)
	set(CMAKE_PREFIX_PATH C:/Qt/5.9.1/msvc2015/lib/cmake)
elseif (UNIX AND NOT APPLE)
	set(CMAKE_PREFIX_PATH $ENV{HOME}/Qt/5.9.1/gcc_64)
endif()

### LIBRARIES
# QT COMPONENTS
find_package(Qt5 REQUIRED COMPONENTS Core Widgets)
# QT INCLUDES
include_directories(${Qt5Network_INCLUDE_DIRS} ${Qt5Widgets_INCLUDE_DIRS})

### APP SRCS
file(GLOB_RECURSE SOURCE_LAUNCHER_FILES			${APP_DIR}/src/*.cpp)
file(GLOB_RECURSE SOURCE_LAUNCHER_FILES_H		${APP_DIR}/src/*.h)
file(GLOB_RECURSE SOURCE_LAUNCHER_FILES_HPP		${APP_DIR}/src/*.hpp)

# APP HEADERS
file(GLOB_RECURSE HEADER_LAUNCHER_FILES_H		${APP_DIR}/include/*.h)
file(GLOB_RECURSE HEADER_LAUNCHER_FILES_HPP		${APP_DIR}/include/*.hpp)

# APP FORMS UI
## All *.ui file goes there as
qt5_wrap_ui(UIS_HDRS
    ${APP_DIR}/src/widget/class/MainWindow/mainwindow.ui
)

### EXECUTABLE
add_executable(${APP_NAME}
  ${SOURCE_LAUNCHER_FILES}
  ${HEADER_LAUNCHER_FILES_H}
  ${HEADER_LAUNCHER_FILES_HPP}
  ${SOURCE_LAUNCHER_FILES_H}
  ${SOURCE_LAUNCHER_FILES_HPP}
  ${UIS_HDRS}
)

# LIBRARIES LINKING
target_link_libraries(${APP_NAME} Qt5::Widgets)

# Windows specific build steps
if(WIN32)
	file(GLOB_RECURSE DLL_LIB_FILES ${PROJECT_SOURCE_DIR}/lib/win/dll/*.dll)
  if (DLL_LIB_FILES)
    add_custom_command(TARGET ${APP_NAME} POST_BUILD COMMAND ${CMAKE_COMMAND} -E copy ${DLL_LIB_FILES} ${CMAKE_RUNTIME_OUTPUT_DIRECTORY})
  endif()
endif()
