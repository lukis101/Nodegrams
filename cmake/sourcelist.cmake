
set(ndgm_inc_dir "include/Nodegrams")
set(ndgm_src_dir "src/Nodegrams")

target_sources(${PROJECT_NAME} PRIVATE
    # Headers
    ${ndgm_inc_dir}/modules/ModuleBase.h

    ${ndgm_inc_dir}/Config.h
    ${ndgm_inc_dir}/DataTypes.h
    ${ndgm_inc_dir}/Nodegrams.h
    ${ndgm_inc_dir}/TypeRegistry.h
    ${ndgm_inc_dir}/Serializer.h
    ${ndgm_inc_dir}/Deserializer.h

    ${ndgm_inc_dir}/datatypes/DataBox.h
    ${ndgm_inc_dir}/datatypes/Event.h
    ${ndgm_inc_dir}/datatypes/Boolean.h
    ${ndgm_inc_dir}/datatypes/Float.h
    ${ndgm_inc_dir}/datatypes/Double.h
    ${ndgm_inc_dir}/datatypes/Int32.h
    ${ndgm_inc_dir}/datatypes/Int64.h

    ${ndgm_inc_dir}/nodes/NodeBase.h
    ${ndgm_inc_dir}/nodes/StaticNode.h
    ${ndgm_inc_dir}/nodes/DynamicNode.h

    ${ndgm_inc_dir}/nodes/ContainerNode.h
    ${ndgm_inc_dir}/nodes/TestNode.h
    ${ndgm_inc_dir}/nodes/time/SysTimeNode.h
    ${ndgm_inc_dir}/nodes/logic/gates/Gate2i1o.h
    ${ndgm_inc_dir}/nodes/logic/gates/ANDGate.h
    ${ndgm_inc_dir}/nodes/logic/gates/ORGate.h
    ${ndgm_inc_dir}/nodes/logic/gates/XORGate.h

    ${ndgm_inc_dir}/inoutlets/InletBase.h
    ${ndgm_inc_dir}/inoutlets/OutletBase.h
    ${ndgm_inc_dir}/inoutlets/SinglewayInlet.h
    ${ndgm_inc_dir}/inoutlets/MultiwayInlet.h
    ${ndgm_inc_dir}/inoutlets/SimpleOutlet.h

    # Sources
    ${ndgm_src_dir}/Nodegrams.cpp
    ${ndgm_src_dir}/TypeRegistry.cpp

    ${ndgm_src_dir}/datatypes/DataBox.cpp
    ${ndgm_src_dir}/datatypes/Event.cpp
    ${ndgm_src_dir}/datatypes/Boolean.cpp
    ${ndgm_src_dir}/datatypes/Float.cpp
    ${ndgm_src_dir}/datatypes/Double.cpp
    ${ndgm_src_dir}/datatypes/Int32.cpp
    ${ndgm_src_dir}/datatypes/Int64.cpp

    ${ndgm_src_dir}/nodes/NodeBase.cpp
    ${ndgm_src_dir}/nodes/StaticNode.cpp
    ${ndgm_src_dir}/nodes/DynamicNode.cpp

    ${ndgm_src_dir}/nodes/ContainerNode.cpp
    ${ndgm_src_dir}/nodes/TestNode.cpp
    ${ndgm_src_dir}/nodes/time/SysTimeNode.cpp
    ${ndgm_src_dir}/nodes/logic/gates/Gate2i1o.cpp

    ${ndgm_src_dir}/inoutlets/InletBase.cpp
    ${ndgm_src_dir}/inoutlets/OutletBase.cpp
    ${ndgm_src_dir}/inoutlets/SinglewayInlet.cpp
    ${ndgm_src_dir}/inoutlets/MultiwayInlet.cpp
    ${ndgm_src_dir}/inoutlets/SimpleOutlet.cpp
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
