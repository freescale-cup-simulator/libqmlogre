cmake_minimum_required(VERSION 2.8.7 FATAL_ERROR)

project(libqmlogre CXX C)

set(CMAKE_INCLUDE_CURRENT_DIR ON)

set(HDR
    ogre_engine.h
    camera_grabber.h
    camera.h
    abstract_node.h
    controlled_node.h
)

set(SRC
    ogre_engine.cc
    camera_grabber.cc
    camera.cc
    abstract_node.cc
    controlled_node.cc
)

find_package(OpenGL REQUIRED)
find_package(OIS REQUIRED)
find_package(OGRE REQUIRED)
find_package(Boost COMPONENTS system thread date_time REQUIRED)

find_package(Qt5Quick)
add_definitions(${Qt5Quick_DEFINITIONS})
set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} ${Qt5Quick_EXECUTABLE_COMPILE_FLAGS}")

include(CheckCXXCompilerFlag)
if("${CMAKE_CXX_COMPILER_ID}" STREQUAL "GNU" OR "${CMAKE_CXX_COMPILER_ID}" STREQUAL "Clang")
  CHECK_CXX_COMPILER_FLAG("-std=c++11" STDCPP11_SUPPORTED)
  if(STDCPP11_SUPPORTED)
    set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -std=c++11")
  else()
    CHECK_CXX_COMPILER_FLAG("-std=c++0x" STDCPP0X_SUPPORTED)
    if(STDCPP0X_SUPPORTED)
      set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -std=c++0x")
    else()
      message(FATAL_ERROR "Compiler doesn't appear to support C++11 or at least C++0x")
    endif()
  endif()
  set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -Os -ggdb3")
else()
  message(FATAL_ERROR "Unsupported compiler")
endif()


include_directories( 
        ${OPENGL_INCLUDE_DIRS}
        ${Boost_INCLUDE_DIR}
        ${OIS_INCLUDE_DIRS}
	${OGRE_INCLUDE_DIRS}
        ${OGRE_SAMPLES_INCLUDEPATH}
        ${Qt5Quick_INCLUDE_DIRS}
)

qt5_wrap_cpp(moc_output ${HDR})

add_library(qmlogre STATIC ${HDR} ${SRC} ${moc_output})

target_link_libraries(qmlogre
    ${Qt5Quick_LIBRARIES}
    ${OPENGL_LIBRARIES}
    ${OGRE_LIBRARIES} 
    ${OIS_LIBRARIES}
    ${Boost_LIBRARIES}
)
