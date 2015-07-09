cmake_minimum_required(VERSION 2.6)
    if(COMMAND cmake_policy)
      cmake_policy(SET CMP0003 NEW)
    endif(COMMAND cmake_policy)
    
PROJECT(vtkKNNGraphFilter)
ENABLE_TESTING()

FIND_PACKAGE(VTK REQUIRED)
INCLUDE(${VTK_USE_FILE})

add_library(KNNGraphFilter
    vtkKNNGraphFilter.cxx)
target_link_libraries(KNNGraphFilter ${VTK_LIBRARIES})

SET(BUILD_PARAVIEW_PLUGIN OFF CACHE BOOL "Build Paraview plugin?")
if(BUILD_PARAVIEW_PLUGIN)
 SUBDIRS(plugin)
endif(BUILD_PARAVIEW_PLUGIN)

option(BUILD_EXAMPLES "Build examples?" OFF)
if(BUILD_EXAMPLES)
  message("Building examples...")
  ADD_EXECUTABLE(vtkKNNGraphFilterExample vtkKNNGraphFilterExample.cxx
  vtkKNNGraphFilter.cxx
  )
  TARGET_LINK_LIBRARIES(vtkKNNGraphFilterExample ${VTK_LIBRARIES})
endif()

option(BUILD_TESTING "Build tests?" OFF)
if(BUILD_TESTING)
  message("Building tests...")
  ADD_EXECUTABLE(vtkKNNGraphFilterTest vtkKNNGraphFilterTest.cxx
  vtkKNNGraphFilter.cxx
  )
  TARGET_LINK_LIBRARIES(vtkKNNGraphFilterTest ${VTK_LIBRARIES})
  ADD_TEST(vtkKNNGraphFilterTest vtkKNNGraphFilterTest ${CMAKE_SOURCE_DIR}/data/Input.vtp ${CMAKE_SOURCE_DIR}/data/GroundTruth.graph)
endif()





