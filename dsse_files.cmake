
set(dsse_inc_dir "include/Dsse")
set(dsse_src_dir "src/Dsse")

target_sources(${PROJECT_NAME} PRIVATE
    # Headers
    ${dsse_inc_dir}/modules/ModuleBase.h

    ${dsse_inc_dir}/Config.h
    ${dsse_inc_dir}/DataTypes.h
    ${dsse_inc_dir}/DssEngine.h
    ${dsse_inc_dir}/TypeRegistry.h

    ${dsse_inc_dir}/datatypes/DataBox.h
    ${dsse_inc_dir}/datatypes/Boolean.h
    ${dsse_inc_dir}/datatypes/Float.h
    ${dsse_inc_dir}/datatypes/Double.h
    ${dsse_inc_dir}/datatypes/Int32.h
    ${dsse_inc_dir}/datatypes/Int64.h

    ${dsse_inc_dir}/nodes/NodeBase.h
    ${dsse_inc_dir}/nodes/StaticNode.h
    ${dsse_inc_dir}/nodes/DynamicNode.h

    ${dsse_inc_dir}/nodes/ContainerNode.h
    ${dsse_inc_dir}/nodes/TestNode.h
    ${dsse_inc_dir}/nodes/time/SysTimeNode.h

    ${dsse_inc_dir}/inoutlets/InletBase.h
    ${dsse_inc_dir}/inoutlets/OutletBase.h
    ${dsse_inc_dir}/inoutlets/SinglewayInlet.h
    ${dsse_inc_dir}/inoutlets/MultiwayInlet.h
    ${dsse_inc_dir}/inoutlets/SimpleOutlet.h

    # Sources
    ${dsse_src_dir}/DssEngine.cpp
    ${dsse_src_dir}/TypeRegistry.cpp

    ${dsse_src_dir}/datatypes/DataBox.cpp
    ${dsse_src_dir}/datatypes/Boolean.cpp
    ${dsse_src_dir}/datatypes/Float.cpp
    ${dsse_src_dir}/datatypes/Double.cpp
    ${dsse_src_dir}/datatypes/Int32.cpp
    ${dsse_src_dir}/datatypes/Int64.cpp

    ${dsse_src_dir}/nodes/NodeBase.cpp
    ${dsse_src_dir}/nodes/StaticNode.cpp
    ${dsse_src_dir}/nodes/DynamicNode.cpp

    ${dsse_src_dir}/nodes/ContainerNode.cpp
    ${dsse_src_dir}/nodes/TestNode.cpp
    ${dsse_src_dir}/nodes/LuaNode.cpp
    ${dsse_src_dir}/nodes/time/SysTimeNode.cpp

    ${dsse_src_dir}/inoutlets/InletBase.cpp
    ${dsse_src_dir}/inoutlets/OutletBase.cpp
    ${dsse_src_dir}/inoutlets/SinglewayInlet.cpp
    ${dsse_src_dir}/inoutlets/MultiwayInlet.cpp
    ${dsse_src_dir}/inoutlets/SimpleOutlet.cpp
)

# Recreate fodler structure in IDEs
function(assign_source_group)
    get_target_property(_srclist ${ARGN} SOURCES)
    foreach(_source IN ITEMS ${_srclist})
        if (IS_ABSOLUTE "${_source}")
            file(RELATIVE_PATH _source_rel "${CMAKE_CURRENT_SOURCE_DIR}" "${_source}")
        else()
            set(_source_rel "${_source}")
        endif()
        get_filename_component(_source_path "${_source_rel}" PATH)
        string(REPLACE "/" "\\" _source_path_msvc "${_source_path}")
        source_group("${_source_path_msvc}" FILES "${_source}")
    endforeach()
endfunction(assign_source_group)

assign_source_group(${PROJECT_NAME})
