cmake_minimum_required(VERSION 2.8.9 FATAL_ERROR)

project(libqmlogre CXX)

set(CMAKE_INCLUDE_CURRENT_DIR ON)

set(HDR
    ogre_engine.h
    camera_grabber.h
    camera.h
    abstract_node.h
    controlled_node.h
    image_node.h
)

set(SRC
    ogre_engine.cc
    camera_grabber.cc
    camera.cc
    abstract_node.cc
    controlled_node.cc
    image_node.cc
)

set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -std=c++11 -Os -ggdb3 -Wextra")

find_package(OpenGL REQUIRED)
find_package(OIS REQUIRED)
find_package(OGRE REQUIRED)
find_package(Boost COMPONENTS system thread date_time REQUIRED)
find_package(Qt5 REQUIRED Core Qml Quick OpenGL)

include_directories( 
        ${OPENGL_INCLUDE_DIRS}
        ${Boost_INCLUDE_DIR}
        ${OIS_INCLUDE_DIRS}
	${OGRE_INCLUDE_DIRS}
	${OGRE_SAMPLES_INCLUDEPATH}
)

qt5_wrap_cpp(moc_output ${HDR})

add_library(qmlogre STATIC ${HDR} ${SRC} ${moc_output})

target_link_libraries(qmlogre
    Qt5::Core
    Qt5::Qml
    Qt5::Quick
    Qt5::OpenGL
    ${OPENGL_LIBRARIES}
    ${OGRE_LIBRARIES} 
    ${OIS_LIBRARIES}
    ${Boost_LIBRARIES}
)
