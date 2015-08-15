# Set the name and the supported language of the project
project(sampleapp C)

# Set the minimum version of cmake required to build this project
cmake_minimum_required(VERSION 2.6)

#source directories
set (SOURCE_SHARE "share")

#install directories variables
include(GNUInstallDirs)

##directories where to find/install files.
#These path are used in with the install instruction which only supports
#relative path
set(SHAREDIR       ${CMAKE_INSTALL_DATADIR})
set(LOCALDIR       ${CMAKE_INSTALL_LOCALEDIR})
set(GLIB_SCHEMADIR "glib-2.0/schemas")
set(SCHEMADIR      ${CMAKE_INSTALL_DATADIR}/${GLIB_SCHEMADIR})

#These path are passed onto config.h.in to be used as preprocessor definitions
if(MINGW)
	set(SHARE_DIR "../share")
  set(LOCALE_DIR ${SHARE_DIR}/${PROJECT_NAME}/locale)
else(MINGW)
	set(SHARE_DIR ${CMAKE_INSTALL_FULL_DATADIR})
	set(LOCALE_DIR ${CMAKE_INSTALL_FULL_LOCALEDIR})
endif(MINGW)

#generate config.h from config.h.in
configure_file(config.h.in config.h)

############################################################
option(NSIS "Use NSIS generator to produce installer" OFF)

# Use the package PkgConfig to detect GTK+ headers/library files
find_package(PkgConfig REQUIRED)
pkg_check_modules(GTK3 REQUIRED gtk+-3.0)

# Setup CMake to use GTK+, tell the compiler where to look for headers
# and to the linker where to look for libraries
include_directories(${GTK3_INCLUDE_DIRS})
link_directories(${GTK3_LIBRARY_DIRS})
############################################################

#compiled binary output directory
set (CMAKE_RUNTIME_OUTPUT_DIRECTORY bin)

#set the pkg-config variable
set(PKG_CONFIG_EXECUTABLE pkg-config)

#find the glib prefix directory with pkg-config 
execute_process (
COMMAND ${PKG_CONFIG_EXECUTABLE} gio-2.0 --variable prefix
OUTPUT_VARIABLE GLIB_PREFIX OUTPUT_STRIP_TRAILING_WHITESPACE
)

#if we want to create a NSIS script
if(NSIS)
  set(CPACK_PACKAGE_EXECUTABLES ${PROJECT_NAME} ${PROJECT_NAME}.exe)
  set(CPACK_RESOURCE_FILE_LICENSE ${CMAKE_SOURCE_DIR}/LICENSE)
  set(CPACK_RESOURCE_FILE_README ${CMAKE_SOURCE_DIR}/README.md)
  include (NSIS.cmake)

  #install the Gtk DLLs from the Gtk's bin directory 
  set (GTK_BIN ${GLIB_PREFIX}/bin)
  
  #these are all the required dll listed in the GTK documentation
  #see http://www.gtk.org/download/win32_contentlist.php
  INSTALL(
    FILES
    ${GTK_BIN}/libatk-1.0-0.dll
	${GTK_BIN}/libfontconfig-1.dll
	${GTK_BIN}/libgdk-3-0.dll
	${GTK_BIN}/liblzma-5.dll
    ${GTK_BIN}/libcairo-2.dll
    ${GTK_BIN}/libcairo-gobject-2.dll
    ${GTK_BIN}/libffi-6.dll
    ${GTK_BIN}/libfreetype-6.dll
    ${GTK_BIN}/libgdk_pixbuf-2.0-0.dll
    ${GTK_BIN}/libgio-2.0-0.dll 
    ${GTK_BIN}/libglib-2.0-0.dll
    ${GTK_BIN}/libgmodule-2.0-0.dll 
    ${GTK_BIN}/libgobject-2.0-0.dll
    ${GTK_BIN}/libgtk-3-0.dll
    ${GTK_BIN}/libiconv-2.dll 
    ${GTK_BIN}/libintl-8.dll 
    ${GTK_BIN}/libpango-1.0-0.dll
    ${GTK_BIN}/libpango-1.0-0.dll 
    ${GTK_BIN}/libpangocairo-1.0-0.dll
    ${GTK_BIN}/libpangoft2-1.0-0.dll
    ${GTK_BIN}/libpangowin32-1.0-0.dll
    ${GTK_BIN}/libpixman-1-0.dll
    ${GTK_BIN}/libpng15-15.dll
    ${GTK_BIN}/libxml2-2.dll
    ${GTK_BIN}/pthreadGC2.dll
    ${GTK_BIN}/zlib1.dll 
    DESTINATION ${CMAKE_INSTALL_BINDIR})
endif(NSIS)

# Custom target for packaging.
if(MINGW)
  add_definitions(-DMINGW)
endif(MINGW)

# Add other flags to the compiler
add_definitions(${GTK3_CFLAGS_OTHER})
add_definitions(-Wall)

# files needed to compile the executable
add_executable(
  ${PROJECT_NAME}
  src/main.c
  src/app.c
  src/callbacks.c 
  )

# Link the target to the GTK+ libraries
target_link_libraries(${PROJECT_NAME} ${GTK3_LIBRARIES})

# Compiler flag needed to reach callback functions
set(GCC_COVERAGE_COMPILE_FLAGS "-rdynamic")

#Settings
include(GSettings.cmake)
if(MINGW)
  #under windows point to a directory with specific options and org files
  compile_schemas(${SCHEMADIR}/windows ${SCHEMADIR})
  
  #add a compiler definition
  add_definitions(-DMINGW)
else()
  compile_schemas(${SCHEMADIR} ${SCHEMADIR})
endif()

#under windows point to a directory with specifique options and org files
set(LOCAL_SCHEMADIR share/glib-2.0/schemas)

# INSTALL
##Install settings
###Compiled file
install(
  FILES ${SCHEMADIR}/gschemas.compiled
  DESTINATION ${SCHEMADIR}
  )

#The xml gschema not installed when creating an NSIS package because:
#In a standalone application using an installer, we only need the app schema
#Absolute install path are forbidden when creating a package
if(NOT NSIS)
###gschema.xml
install(
  FILES ${SCHEMADIR}/${PROJECT_NAME}.gschema.xml
  DESTINATION ${GLIB_PREFIX}/${SCHEMADIR}
  )
endif()

## Install UI definitions files
install(
  FILES
  ${CMAKE_INSTALL_DATADIR}/${PROJECT_NAME}/${PROJECT_NAME}.glade
  DESTINATION 
  ${CMAKE_INSTALL_DATADIR}/${PROJECT_NAME}
  )

## Install locales
###Français
install(
  FILES
  po/fr/${PROJECT_NAME}.mo
  DESTINATION ${CMAKE_INSTALL_LOCALEDIR}/fr/LC_MESSAGES/)

## Install icons
install(
  FILES ${SOURCE_SHARE}/${PROJECT_NAME}/${PROJECT_NAME}.png
  DESTINATION ${CMAKE_INSTALL_DATADIR}/icons)
install(
  FILES ${SOURCE_SHARE}/${PROJECT_NAME}/${PROJECT_NAME}.png
  DESTINATION ${CMAKE_INSTALL_DATADIR}/${PROJECT_NAME})

## Install desktop file
install(
  FILES com-gitub-gtk-sample-app.desktop
  DESTINATION ${CMAKE_INSTALL_DATADIR}/applications)

## Install programs 
## Set the output binary full path name variable
set(OUTPUT ${CMAKE_RUNTIME_OUTPUT_DIRECTORY}/${PROJECT_NAME})

#if the current system is Windows, the generated binary ends with .exe
if(MINGW)
  set(OUTPUT ${OUTPUT}.exe)
endif()

install(PROGRAMS ${OUTPUT} DESTINATION ${CMAKE_INSTALL_BINDIR})