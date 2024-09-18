# For more information about using CMake with Android Studio, read the
# documentation: https://d.android.com/studio/projects/add-native-code.html

# Sets the minimum version of CMake required to build the native library.

cmake_minimum_required(VERSION 3.22.1)

# Declares and names the project.

project("opengles_doc")

# Creates and names a library, sets it as either STATIC
# or SHARED, and provides the relative paths to its source code.
# You can define multiple libraries, and CMake builds them for you.
# Gradle automatically packages shared libraries with your APK.
# 遍历当前目录及其子目录下的所有 .cpp .c 文件，并将它们的路径存储在 SOURCE_FILES 变量中
file(GLOB GLES_SOURCE_FILE
        ${CMAKE_CURRENT_SOURCE_DIR}/gles2/*.cpp
        ${CMAKE_CURRENT_SOURCE_DIR}/gles2/*.c)

file(GLOB GLES3_SOURCE_FILE
        ${CMAKE_CURRENT_SOURCE_DIR}/gles3/*.cpp
        ${CMAKE_CURRENT_SOURCE_DIR}/gles3/render/*.cpp
        ${CMAKE_CURRENT_SOURCE_DIR}/gles3/*.c)

include_directories(${CMAKE_CURRENT_SOURCE_DIR}/gles2)
include_directories(${CMAKE_CURRENT_SOURCE_DIR}/gles3)
include_directories(${CMAKE_CURRENT_SOURCE_DIR}/gles3/render)
include_directories(${CMAKE_CURRENT_SOURCE_DIR})

add_library(
        # Sets the name of the library.
        opengles
        # Sets the library as a shared library.
        SHARED
        # Provides a relative path to your source file(s).
        ${GLES_SOURCE_FILE}
        ${GLES3_SOURCE_FILE}
)

# Searches for a specified prebuilt library and stores the path as a
# variable. Because CMake includes system libraries in the search path by
# default, you only need to specify the name of the public NDK library
# you want to add. CMake verifies that the library exists before
# completing its build.

find_library( # Sets the name of the path variable.
        log-lib

        # Specifies the name of the NDK library that
        # you want CMake to locate.
        log)

# Specifies libraries CMake should link to your target library. You
# can link multiple libraries, such as libraries you define in this
# build script, prebuilt third-party libraries, or system libraries.

target_link_libraries( # Specifies the target library.
        opengles
        android
        jnigraphics
        #GLESv2
        #v3版本兼容v2，所以链接v3既能保证使用v2的api又能同时使用v3的api
        GLESv3
        EGL
        # Links the target library to the log library
        # included in the NDK.
        ${log-lib})