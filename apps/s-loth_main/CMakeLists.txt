###########################################################
# CMake Build Script for the 3d_interpolation_test_app executable

#link_directories(${SCHISM_LIBRARY_DIRS})

include_directories(${REND_INCLUDE_DIR}
                    ${COMMON_INCLUDE_DIR}
                    ${FREEIMAGE_INCLUDE_DIR}
		    ${GLUT_INCLUDE_DIRS}
	            ${OpenGL_INCLUDE_DIRS}
    		    ${X11_INCLUDE_DIRS}
                    ${EXT_INCLUDE_DIR}
                    ${Boost_INCLUDE_DIR}
		    ${SOIL_INCLUDE_PATH}
		    )


link_directories(${OpenGL_LIBRARY_DIRS}
                 ${Boost_LIBRARY_DIR})


include_directories(SYSTEM #${SCHISM_INCLUDE_DIRS}
                           ${Boost_INCLUDE_DIR})

InitApp(${CMAKE_PROJECT_NAME}_main)

############################################################
# Libraries

target_link_libraries(${PROJECT_NAME}
    ${PROJECT_LIBS}
    ${REND_LIBRARY}
    ${GLUT_LIBRARIES}
    ${GLEW_LIBRARY}
    ${OPENGL_LIBRARY}
    ${X11_LIBRARIES}
    ${EXT_LIBRARY}
    boost_filesystem
    boost_system
    ${SOIL_LIBRARY}
    )

MsvcPostBuild(${PROJECT_NAME})
