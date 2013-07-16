cmake_minimum_required(VERSION 2.8)

project(Survive)
set(CMAKE_DEBUG_POSTFIX _d)
set(SURVIVE_PATH "" CACHE PATH "Path to the root directory.")
set(SURVIVE_DEPS_PATH "" CACHE PATH "Path to the directory with dependencies.")
#set(SURVIVE_CONTENT_PATH "" CACHE PATH "Path to the root directory of the content")

set_property(GLOBAL PROPERTY USE_FOLDERS ON)

##########################################################################
# Install                             									 #
##########################################################################
if(WIN32)
	set(SURVIVE_RUNTIME_DIR bin/vc10_32)
	set(SURVIVE_LIBRARY_DIR lib/vc10_32)
	set(SURVIVE_ARCHIVE_DIR lib/vc10_32)
	set(CMAKE_RUNTIME_OUTPUT_DIRECTORY ${SURVIVE_PATH}/${SURVIVE_RUNTIME_DIR})
	set(CMAKE_ARCHIVE_OUTPUT_DIRECTORY ${SURVIVE_PATH}/${SURVIVE_ARCHIVE_DIR})
	set(CMAKE_LIBRARY_OUTPUT_PATH ${SURVIVE_PATH}/${SURVIVE_LIBRARY_DIR}) 
endif()

#installs items from the TARGETS(variable name)
function(survive_install TARGETS)
	set(tgt ${${TARGETS}})
	
	install(TARGETS ${tgt}
   		RUNTIME DESTINATION ${SURVIVE_RUNTIME_DIR}/Debug CONFIGURATIONS Debug  
    	LIBRARY DESTINATION ${SURVIVE_LIBRARY_DIR}/Debug CONFIGURATIONS Debug
    	ARCHIVE DESTINATION ${SURVIVE_ARCHIVE_DIR}/Debug CONFIGURATIONS Debug
	)
	
	install(TARGETS ${tgt}
   		RUNTIME DESTINATION ${SURVIVE_RUNTIME_DIR}/Release CONFIGURATIONS Release  
    	LIBRARY DESTINATION ${SURVIVE_LIBRARY_DIR}/Release CONFIGURATIONS Release
    	ARCHIVE DESTINATION ${SURVIVE_ARCHIVE_DIR}/Release CONFIGURATIONS Release
	)
endfunction(survive_install) 
##########################################################################
# Additional  include and library directories                            #
##########################################################################
include_directories(${PROJECT_SOURCE_DIR})
include_directories(${SURVIVE_PATH}/include)
include_directories(${SURVIVE_DEPS_PATH}/include)

if(WIN32)
	link_directories( ${SURVIVE_PATH}/lib/vc10_32/Release)
	link_directories( ${SURVIVE_PATH}/lib/vc10_32/Debug)
endif()

##########################################################################
# Project subdirectories												 #
##########################################################################
add_subdirectory(Survive)