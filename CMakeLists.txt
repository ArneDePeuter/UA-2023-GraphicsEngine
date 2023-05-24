cmake_minimum_required(VERSION 3.5)

project(engine)

############################################################
# Set compiler flags
############################################################
# If supported by your compiler, you can add the -Wall, -Wextra, –fstack-protector-all and -g3 flags here.
set(OWN_GXX_FLAGS "-std=c++14")
set(CMAKE_CXX_FLAGS_DEBUG "${CMAKE_CXX_FLAGS_DEBUG} ${OWN_GXX_FLAGS}")
set(CMAKE_CXX_FLAGS_RELEASE "${CMAKE_CXX_FLAGS_RELEASE} ${OWN_GXX_FLAGS}")
set(CMAKE_CXX_FLAGS  "${CMAKE_CXX_FLAGS} ${OWN_GXX_FLAGS}")

############################################################
# List all sources
############################################################
set(engine_sources
        engine.cc
        ./Include/easy_image.cc
        ./Include/ini_configuration.cc
        ./Include/vector3d.cc ./Include/vector3d.h
        ./Include/l_parser.cc
        ./Include/obj_parser.cc

        ./Objects/Face.h
        ./Objects/Object3D.cpp ./Objects/Object3D.h
        ./Objects/Camera.h
        ./Objects/Line2D.h ./Objects/Point2D.h
        ./Objects/LSystem2D.cpp
        ./Objects/Calculator.cpp ./Objects/Calculator.h

        ./Objects/Face.cpp ./Objects/IniLoader.cpp ./Objects/IniLoader.h ./Objects/LSystem3D.cpp ./Objects/LSystem3D.h
        ./Objects/ZBuffer.cpp ./Objects/Scene.cpp ./Objects/Triangle.h Objects/Renderer.h Objects/Renderer.cpp Objects/Light.h Objects/Object3DFactory.cpp Objects/ClippingSettings.h Objects/Light.cpp Objects/ShadowLight.cpp Objects/ImageDetails.h)

############################################################
# Create an executable
############################################################
set(exe_name "engine")
add_executable( ${exe_name} ${engine_sources} )
