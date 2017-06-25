# Dreamshows engine example programs

set(APP_VERSION "0.1")
set(APP_COPYRIGHT "Copyright 2017 Lukas Jonyla")

include_directories(${DSSE_SOURCE_DIR}/include)

set(SAMPLE_NAME TestApp)
set(SAMPLE_SOURCES "${DSSE_SOURCE_DIR}/programs/TestApp/TestApp.cpp")
#set(SAMPLE_RESOURCES
#	"${DSSE_SOURCE_DIR}/programs/test/resource/gwen.png"
#	"${DSSE_SOURCE_DIR}/programs/test/resource/test16.png")
		
set(APP_RESOURCE_DIR "$<TARGET_FILE_DIR:${SAMPLE_NAME}>")
set(APP_RUNTIME_RESOURCE_DIR "")
		
add_definitions("-DGWORK_RESOURCE_DIR=\"${APP_RUNTIME_RESOURCE_DIR}\"")

add_executable(${SAMPLE_NAME} ${SAMPLE_SOURCES} ${SAMPLE_RESOURCES})

target_link_libraries(${SAMPLE_NAME} Dsse)

	# macro(CopyAppResource RES_FROM)
		# get_filename_component(FNANE "${RES_FROM}" NAME)
		# add_custom_command(
			# TARGET ${SAMPLE_NAME} POST_BUILD
			# COMMAND ${CMAKE_COMMAND} -E copy "${RES_FROM}" "${APP_RESOURCE_DIR}/${FNANE}"
			# COMMENT "Copying sample resource")
	# endmacro(CopyAppResource)

	# foreach(RESFILE ${SAMPLE_RESOURCES})
		# CopyAppResource(${RESFILE})
	# endforeach()