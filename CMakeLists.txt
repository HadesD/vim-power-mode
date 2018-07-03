cmake_minimum_required(VERSION 2.8)

project("Particle")

# Declare variables {
set(INC_DIRS)
set(SRC_FILES)
set(LIBS_LIBRARIES)
set(LIBS_REQUIRED)
# }

# Load Modules {
set(CMAKE_MODULE_PATH "${CMAKE_CURRENT_SOURCE_DIR}/build/cmake_modules")

include(GenCompileCommands)
include(CompilerConfig)
include(BuildConfig)

include(LinkLibraries)

# include(Definitions)

include(IncludeDirectories)
include(SourceFiles)
# }

include_directories(${PROJECT_NAME} PRIVATE ${INC_DIRS})

add_executable(${PROJECT_NAME} ${SRC_FILES})
target_link_libraries(${PROJECT_NAME} ${LIBS_REQUIRED})
set_target_properties(${PROJECT_NAME} PROPERTIES OUTPUT_NAME "${PROJECT_NAME}.exe")

# PostBuild {
include(PostBuild)
# }

