CMAKE_MINIMUM_REQUIRED(VERSION 3.3)

IF(LINUX)
ELSEIF(ANDROID)
	ADD_SUBDIRECTORY(android/)
ELSEIF(MAC_IOS)
	ADD_SUBDIRECTORY(ios/)
ELSE()
	MESSAGE(FATAL_ERROR "Set build platform, CMake will exit!  \"" ${CMAKE_SYSTEM_NAME} "\"")
ENDIF()
