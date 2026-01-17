##==============================================================================
## General.
##==============================================================================
cmake_minimum_required(VERSION 3.19)
include(${CMAKE_CURRENT_LIST_DIR}/cmake/UnigineCMakeVariables.cmake)

set(target "TheGuidingThread_linux")
if (WIN32)
	set(target "TheGuidingThread_windows")
endif()

project(${target} LANGUAGES CXX)

set(CMAKE_CXX_STANDARD 14)
set(CMAKE_CXX_STANDARD_REQUIRED TRUE)
set(CMAKE_CXX_EXTENSIONS FALSE)

##==============================================================================
## Environment.
##==============================================================================
set(UNIGINE_DOUBLE 0)
set(UNIGINE_SDK_PATH ${PROJECT_SOURCE_DIR}/../)
set(UNIGINE_BIN_DIR ${UNIGINE_SDK_PATH}bin)
set(UNIGINE_LIB_DIR ${UNIGINE_SDK_PATH}lib)
set(UNIGINE_INCLUDE_DIR ${UNIGINE_SDK_PATH}include)

##==============================================================================
## Dependencies.
##==============================================================================
list(APPEND CMAKE_MODULE_PATH ${PROJECT_SOURCE_DIR}/cmake/modules)

# Engine.
find_package(Engine REQUIRED MODULE QUIET)

##==============================================================================
## Target.
##==============================================================================

if (WIN32)
	set(CMAKE_EXE_LINKER_FLAGS_RELEASE "${CMAKE_EXE_LINKER_FLAGS} /SUBSYSTEM:WINDOWS /ENTRY:wmainCRTStartup")
endif()

add_executable(${target}
		${CMAKE_CURRENT_LIST_DIR}/AppWorldLogic.cpp
		${CMAKE_CURRENT_LIST_DIR}/AppWorldLogic.h
		${CMAKE_CURRENT_LIST_DIR}/main.cpp
		${CMAKE_CURRENT_LIST_DIR}/AppSystemLogic.cpp
		${CMAKE_CURRENT_LIST_DIR}/AppEditorLogic.cpp
		${CMAKE_CURRENT_LIST_DIR}/AppEditorLogic.h
		${CMAKE_CURRENT_LIST_DIR}/AppSystemLogic.h
		${CMAKE_CURRENT_LIST_DIR}/components/MenuComponent.cpp
		${CMAKE_CURRENT_LIST_DIR}/controller/TopDownController.cpp
		${CMAKE_CURRENT_LIST_DIR}/AI/Enemy.h
		${CMAKE_CURRENT_LIST_DIR}/AI/Enemy.cpp
		${CMAKE_CURRENT_LIST_DIR}/components/IntroSplashScreenComponent.cpp
		${CMAKE_CURRENT_LIST_DIR}/UI/TileCounter.h
		${CMAKE_CURRENT_LIST_DIR}/UI/TileCounter.cpp
		${CMAKE_CURRENT_LIST_DIR}/UI/LevelNumberStartDisplay.h
		${CMAKE_CURRENT_LIST_DIR}/UI/LevelNumberStartDisplay.cpp
		${CMAKE_CURRENT_LIST_DIR}/UI/HealthDisplay.h
		${CMAKE_CURRENT_LIST_DIR}/UI/HealthDisplay.cpp
		${CMAKE_CURRENT_LIST_DIR}/game/GameState.h
		${CMAKE_CURRENT_LIST_DIR}/game/GameState.cpp
		${CMAKE_CURRENT_LIST_DIR}/game/GameLevel.h
		${CMAKE_CURRENT_LIST_DIR}/game/GameLevel.cpp
		${CMAKE_CURRENT_LIST_DIR}/game/GridMap.h
		${CMAKE_CURRENT_LIST_DIR}/game/GridMap.cpp
		${CMAKE_CURRENT_LIST_DIR}/helpers/waiter_key_press.cpp
		${CMAKE_CURRENT_LIST_DIR}/Roads2DGenerator/Roads2DGenerator.h
		${CMAKE_CURRENT_LIST_DIR}/Roads2DGenerator/Roads2DGenerator.cpp
)

target_include_directories(${target}
	PRIVATE
	${UNIGINE_INCLUDE_DIR}
	${CMAKE_CURRENT_LIST_DIR}/helpers/
	${CMAKE_CURRENT_LIST_DIR}/Roads2DGenerator/
	${CMAKE_CURRENT_LIST_DIR}/game/
	${CMAKE_CURRENT_LIST_DIR}/UI/
	${CMAKE_CURRENT_LIST_DIR}/components/
	)

target_link_libraries(${target}
	PRIVATE
	Unigine::Engine
	)

target_compile_definitions(${target}
	PRIVATE
	$<$<BOOL:${UNIX}>:_LINUX>
	$<$<CONFIG:Debug>:DEBUG>
	$<$<NOT:$<CONFIG:Debug>>:NDEBUG>
	)

##==============================================================================
## Compiler constants.
##==============================================================================
if(CMAKE_CXX_COMPILER_ID STREQUAL "MSVC")
  set(UNIGINE_COMPILER_IS_MSVC TRUE)
elseif(CMAKE_CXX_COMPILER_ID STREQUAL "Clang")
  set(UNIGINE_COMPILER_IS_CLANG TRUE)
elseif(CMAKE_CXX_COMPILER_ID STREQUAL "GNU")
  set(UNIGINE_COMPILER_IS_GNU TRUE)
endif()

if (UNIGINE_COMPILER_IS_MSVC)
    target_compile_definitions(${target}
	PRIVATE
	_CRT_SECURE_NO_DEPRECATE
	)
    include(ProcessorCount)
    ProcessorCount(proc_count)
    target_compile_options(${target}
	PRIVATE
	/TP               # Specifies all source files are C++.
	/FS               # Forces writes to the program database (PDB) file to be serialized through MSPDBSRV.EXE.
	/fp:fast          # Specifies floating-point behavior.
	/bigobj           # Increases the number of addressable sections in an .obj file.
	/EHsc             # Specifies the kind of exception handling used by the compiler.
	/MP${proc_count}  # Build with Multiple Processes.
	)
    unset(proc_count)
    target_link_options(${target} INTERFACE "/FIXED:NO")

elseif(UNIGINE_COMPILER_IS_GNU OR UNIGINE_COMPILER_IS_CLANG)

    target_compile_options(${target}
	PRIVATE
	-m64
	-march=athlon64
	-msse4.2
	# Optimizations.
	-ffast-math
	-fno-strict-aliasing
	$<$<NOT:$<CONFIG:Debug>>:-fomit-frame-pointer>
	# Warnings.
	$<$<CONFIG:Debug>:-Wall>
	$<$<CONFIG:Debug>:-Wno-unknown-pragmas>
	$<$<CONFIG:Debug>:-Wno-unused-parameter>
	)
endif ()

set(binary_name ${target})
string(APPEND binary_name "_x64")
set_target_properties(${target} PROPERTIES DEBUG_POSTFIX "d")
set_target_properties(${target} PROPERTIES OUTPUT_NAME ${binary_name})

set_target_properties(${target}
	PROPERTIES
	RUNTIME_OUTPUT_DIRECTORY ${UNIGINE_BIN_DIR}
	RUNTIME_OUTPUT_DIRECTORY_DEBUG ${UNIGINE_BIN_DIR}
	RUNTIME_OUTPUT_DIRECTORY_RELEASE ${UNIGINE_BIN_DIR}
	RUNTIME_OUTPUT_DIRECTORY_RELWITHDEBINFO ${UNIGINE_BIN_DIR}
	RUNTIME_OUTPUT_DIRECTORY_MINSIZEREL ${UNIGINE_BIN_DIR}
	)
