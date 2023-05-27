cmake_minimum_required(VERSION 3.5)

project(liveRender)

############################################################
# Set compiler flags
############################################################
# If supported by your compiler, you can add the -Wall, -Wextra, -fstack-protector-all, and -g3 flags here.
set(OWN_GXX_FLAGS "-std=c++14")
set(CMAKE_CXX_FLAGS_DEBUG "${CMAKE_CXX_FLAGS_DEBUG} ${OWN_GXX_FLAGS}")
set(CMAKE_CXX_FLAGS_RELEASE "${CMAKE_CXX_FLAGS_RELEASE} ${OWN_GXX_FLAGS}")
set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} ${OWN_GXX_FLAGS}")

############################################################
# List all sources
############################################################
set(engine_sources
        ../Include/easy_image.cc
        ../Include/ini_configuration.cc
        ../Include/vector3d.cc
        ../Include/l_parser.cc
        ../Include/obj_parser.cc
        ../Objects/Face.h
        ../Objects/Object3D.cpp
        ../Objects/Object3D.h
        ../Objects/Camera.h
        ../Objects/Line2D.h
        ../Objects/Point2D.h
        ../Objects/LSystem2D.cpp
        ../Objects/Calculator.cpp
        ../Objects/Calculator.h
        ../Objects/Face.cpp
        ../Objects/IniLoader.cpp
        ../Objects/IniLoader.h
        ../Objects/LSystem3D.cpp
        ../Objects/LSystem3D.h
        ../Objects/ZBuffer.cpp
        ../Objects/Scene.cpp
        ../Objects/Triangle.h
        ../Objects/Renderer.h
        ../Objects/Renderer.cpp
        ../Objects/Light.h
        ../Objects/Object3DFactory.cpp
        ../Objects/ClippingSettings.h
        ../Objects/Light.cpp
        ../Objects/ShadowLight.cpp
        ../Objects/ImageDetails.h
        ../Objects/ImageDetails.cpp
        LiveRender.cpp
        )

set(ENV{OPENCV_DIR} "C:/opencv/build")
set(CMAKE_MODULE_PATH ${CMAKE_MODULE_PATH} "${CMAKE_SOURCE_DIR}/cmake/")

find_package(OpenCV REQUIRED)
include_directories(${OpenCV_INCLUDE_DIRS})

add_executable(liveRender main.cpp ${engine_sources})

set(OpenCV_LIBS opencv_world460)

target_link_libraries(liveRender ${OpenCV_LIBS})
