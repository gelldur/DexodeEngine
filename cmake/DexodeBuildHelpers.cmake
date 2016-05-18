#WINDOWS 	= 	Windows Desktop
#WINRT 		= 	Windows RT
#WP8 	  	= 	Windows Phone 8
#ANDROID    =	Android
#IOS		=	iOS
#MACOSX		=	MacOS X
#LINUX      =   Linux

IF(${CMAKE_SYSTEM_NAME} MATCHES "Windows")
	IF(WINRT)
		SET(SYSTEM_STRING "Windows RT")
	ELSEIF(WP8)
		SET(SYSTEM_STRING "Windows Phone 8")
	ELSE()
		SET(WINDOWS TRUE)
		SET(SYSTEM_STRING "Windows Desktop")
	ENDIF()
ELSEIF(${CMAKE_SYSTEM_NAME} MATCHES "Linux")
	IF(ANDROID)
		SET(SYSTEM_STRING "Android")
	ELSE()
		SET(LINUX TRUE)
		SET(SYSTEM_STRING "Linux")
	ENDIF()
ELSEIF(${CMAKE_SYSTEM_NAME} MATCHES "Darwin")
		SET(MAC_IOS TRUE)
	IF(IOS)
		SET(SYSTEM_STRING "IOS")
	ELSE()
		SET(MACOSX TRUE)
		SET(APPLE TRUE)
		SET(SYSTEM_STRING "Mac OSX")
	ENDIF()
ELSE()
	MESSAGE(FATAL_ERROR "Unknown build platform, CMake will exit. \"" ${CMAKE_SYSTEM_NAME} "\"")
ENDIF()

IF("${CMAKE_CXX_COMPILER_ID}" STREQUAL "Clang")
	SET(COMPILER_STRING ${CMAKE_CXX_COMPILER_ID})
	SET(CLANG TRUE)
ELSEIF("${CMAKE_CXX_COMPILER_ID}" STREQUAL "GNU")
	IF(MINGW)
		SET(COMPILER_STRING "Mingw GCC")
	ELSE()
		SET(COMPILER_STRING "GCC")
	ENDIF()
ELSEIF("${CMAKE_CXX_COMPILER_ID}" STREQUAL "Intel")
	SET(COMPILER_STRING "${CMAKE_CXX_COMPILER_ID} C++")
ELSEIF("${CMAKE_CXX_COMPILER_ID}" STREQUAL "MSVC")
	SET(COMPILER_STRING "Visual Studio C++")
ENDIF()

IF(CMAKE_CROSSCOMPILING)
	SET(BUILDING_STRING "It appears you are cross compiling for ${SYSTEM_STRING} with ${COMPILER_STRING}")
ELSE()
	SET(BUILDING_STRING "It appears you are builing natively for ${SYSTEM_STRING} with ${COMPILER_STRING}")
ENDIF()