SET(BB10_FILES
	bar-descriptor.xml
	icon-114.png
)

SET_SOURCE_FILES_PROPERTIES(
	bar-descriptor.xml
	icon-114.png
	PROPERTIES TARGET_PATH "."
)

LIST(APPEND LIBRARIES -lcpp -lbbsystem )

SET(QNX_TARGET $ENV{QNX_TARGET} CACHE PATH "Path to QNX_TARGET")
SET(DEBUG_TOKEN "" CACHE FILEPATH "Path to the debug token to sign with")
SET(DEVICE_PASSWORD "" CACHE FILEPATH "Password to the device")
SET(DEVICE_IP "169.254.0.1" CACHE STRING "IP address to the device")
SET(SIGNING_PASSWORD "" CACHE FILEPATH "Password for the signing keys")
INCLUDE_DIRECTORIES( "${QNX_TARGET}/usr/include" )

FOREACH(file ${BB10_FILES})
	GET_FILENAME_COMPONENT(filename ${file} NAME)
	GET_SOURCE_FILE_PROPERTY(path ${file} TARGET_PATH)
	ADD_CUSTOM_COMMAND(OUTPUT ${CMAKE_BINARY_DIR}/${path}/${filename}
		COMMAND ${CMAKE_COMMAND} -E copy ${CMAKE_SOURCE_DIR}/Platforms/BB10/${file} ${CMAKE_BINARY_DIR}/${path}/${filename}
		MAIN_DEPENDENCY ${CMAKE_SOURCE_DIR}/Platforms/BB10/${file}
		COMMENT "Copying ${file}"
	)
	LIST(APPEND SOURCES ${CMAKE_BINARY_DIR}/${path}/${filename})
ENDFOREACH()

FUNCTION(COMPILE target)
	ADD_CUSTOM_TARGET(run
		blackberry-nativepackager -package ${target}-debug.bar -devMode -debugToken ${DEBUG_TOKEN} -installApp -launchApp -device ${DEVICE_IP} -password ${DEVICE_PASSWORD} ${BB10_FILES} ${target}
		DEPENDS ${target}
		COMMENT "Package and deploy ${target}-debug.bar file"
	)
	ADD_CUSTOM_TARGET(release
		COMMAND blackberry-nativepackager -package ${target}-release.bar ${BB10_FILES} ${target}
		COMMAND blackberry-signer -storepass ${SIGNING_PASSWORD} ${target}-release.bar
		DEPENDS ${target}
		COMMENT "Package and sign ${target}-release.bar file"
	)
ENDFUNCTION()
