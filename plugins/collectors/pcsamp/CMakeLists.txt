################################################################################
# Copyright (c) 2014 Krell Institute. All Rights Reserved.
#
# This program is free software; you can redistribute it and/or modify it under
# the terms of the GNU General Public License as published by the Free Software
# Foundation; either version 2 of the License, or (at your option) any later
# version.
#
# This program is distributed in the hope that it will be useful, but WITHOUT
# ANY WARRANTY; without even the implied warranty of MERCHANTABILITY or FITNESS
# FOR A PARTICULAR PURPOSE.  See the GNU General Public License for more
# details.
#
# You should have received a copy of the GNU General Public License along with
# this program; if not, write to the Free Software Foundation, Inc., 59 Temple
# Place, Suite 330, Boston, MA  02111-1307  USA
################################################################################

set(RT_SOURCES
        ${CMAKE_CURRENT_BINARY_DIR}/blobs.h
        ${CMAKE_CURRENT_BINARY_DIR}/blobs.c
	runtime.c
    )
set(PLUGIN_SOURCES
        ${CMAKE_CURRENT_BINARY_DIR}/blobs.h
        ${CMAKE_CURRENT_BINARY_DIR}/blobs.c
        PCSampCollector.hxx PCSampCollector.cxx
    )

add_custom_command(
    OUTPUT
        ${CMAKE_CURRENT_BINARY_DIR}/blobs.h
        ${CMAKE_CURRENT_BINARY_DIR}/blobs.c
    COMMAND rpcgen -h -o
        ${CMAKE_CURRENT_BINARY_DIR}/blobs.h
        ${CMAKE_CURRENT_BINARY_DIR}/blobs.x
    COMMAND rpcgen -c -o
        ${CMAKE_CURRENT_BINARY_DIR}/blobs.c
        ${CMAKE_CURRENT_BINARY_DIR}/blobs.x
    DEPENDS
        ${CMAKE_CURRENT_BINARY_DIR}/blobs.x
    )


add_definitions(
  -DOpenSpeedShop_LIBRARY_FILE_DIR="${CMAKE_INSTALL_PREFIX}/lib${LIB_SUFFIX}"
  )
  

include_directories(
    ${CMAKE_CURRENT_SOURCE_DIR}
    ${CMAKE_CURRENT_BINARY_DIR}
    ${PROJECT_SOURCE_DIR}/libopenss-runtime
    ${PROJECT_SOURCE_DIR}/libopenss-framework
    ${CMAKE_CURRENT_BINARY_DIR}/../../../libopenss-runtime
    )

add_library(pcsamp MODULE
        ${PLUGIN_SOURCES}
    )

target_link_libraries(pcsamp
	pthread
	openss-framework
	${CMAKE_DL_LIBS}
    )

set_target_properties(pcsamp PROPERTIES VERSION 1.1.0)

install(TARGETS pcsamp
	LIBRARY DESTINATION lib${LIB_SUFFIX}/openspeedshop
    )
set_target_properties(pcsamp PROPERTIES PREFIX "")

if(LIBMONITOR_FOUND)
    add_definitions(
	-DOpenSpeedShop_LIBRARY_FILE_DIR="${CMAKE_INSTALL_PREFIX}/lib${LIB_SUFFIX}"
	-DOPENSS_OFFLINE=1
    )

    include_directories(
	${CMAKE_CURRENT_SOURCE_DIR}
	${CMAKE_CURRENT_BINARY_DIR}
	${PROJECT_SOURCE_DIR}/libopenss-runtime
	${PROJECT_BUILD_DIR}/libopenss-runtime
	${PROJECT_SOURCE_DIR}/libopenss-runtime/offline
	${LibMonitor_INCLUDE_DIRS}
    )

    add_library(pcsamp-rt-offline SHARED
        ${RT_SOURCES}
	offline.c
    )

    target_link_libraries(pcsamp-rt-offline
	${CMAKE_DL_LIBS}
	rt
	pthread
        -Wl,-whole-archive
	openss-runtime-offline
        -Wl,-no-whole-archive
    )

    #set(CMAKE_SHARED_LINKER_FLAGS -Wl,-whole-archive)

    set_target_properties(pcsamp-rt-offline PROPERTIES VERSION 1.1.0)

    install(TARGETS pcsamp-rt-offline
	LIBRARY DESTINATION lib${LIB_SUFFIX}/openspeedshop
    )

    set_target_properties(pcsamp-rt-offline PROPERTIES PREFIX "")
endif()

file(COPY blobs.x DESTINATION .)