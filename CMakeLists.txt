cmake_minimum_required (VERSION 3.10)
project (cxluadbg VERSION 1.0.0 LANGUAGES C CXX)

find_package(LuaCJson) 
find_package(asio)


file(GLOB_RECURSE  SOURCES_CPP "src/*.cpp" "src/*.c")
file(GLOB_RECURSE  SOURCES_HEADER_PRI "src/*.h"  "src/*.hpp" "src/*.inl")
file(GLOB_RECURSE  SOURCES_HEADER_PUB "include/*.h" "include/*.inl" "include/*.lua")

source_group(TREE ${CMAKE_CURRENT_SOURCE_DIR}/src PREFIX "Source Files"  FILES ${SOURCES_CPP})
source_group(TREE ${CMAKE_CURRENT_SOURCE_DIR}/src PREFIX "Source Files"  FILES ${SOURCES_HEADER_PRI})
source_group(TREE ${CMAKE_CURRENT_SOURCE_DIR}/include PREFIX "Header Files"  FILES ${SOURCES_HEADER_PUB})

 


add_library(cxluadbg  SHARED
  ${SOURCES_HEADER_PUB}
  ${SOURCES_HEADER_PRI}
  src/lua_net.cpp
  src/net_thread_queue.cpp
  src/buffer.cpp
  src/luadbg.cpp
  src/luadbg.inl
)

target_compile_definitions(cxluadbg 
  PRIVATE 
    -D_LUADBG_BUILD_DLL
    -DVERSION="${PROJECT_VERSION}"
    -DLUA_COMPAT_5_2 
    -DLUA_COMPAT_5_1
)

target_include_directories(cxluadbg
    PUBLIC
        $<INSTALL_INTERFACE:include>
        $<BUILD_INTERFACE:${CMAKE_CURRENT_SOURCE_DIR}/include>
    PRIVATE
        ${CMAKE_CURRENT_SOURCE_DIR}/src
)

target_link_libraries(cxluadbg
  PUBLIC
    LuaCJson::LuaCJson
    asio
)
add_custom_command(TARGET cxluadbg
          POST_BUILD
          COMMAND ${CMAKE_COMMAND} -E copy ${CMAKE_CURRENT_SOURCE_DIR}/$<CONFIG>/cxluadbg.dll ${CMAKE_RUNTIME_OUTPUT_DIRECTORY}/$<CONFIG>/
)
include(cmake/HelperMacroFunction.cmake)
export_library_macro(cxluadbg cxluadbg "" lib/cmake/cxluadbg)

set_target_properties(cxluadbg PROPERTIES LIBRARY_OUTPUT_DIRECTORY  ${CMAKE_CURRENT_SOURCE_DIR})
set_target_properties(cxluadbg PROPERTIES RUNTIME_OUTPUT_DIRECTORY  ${CMAKE_CURRENT_SOURCE_DIR})
set_target_properties(cxluadbg PROPERTIES ARCHIVE_OUTPUT_DIRECTORY  ${CMAKE_CURRENT_SOURCE_DIR})


# add_custom_command(TARGET luadbg_shared
#           PRE_BUILD
#           COMMAND bash ${CMAKE_CURRENT_LIST_DIR}/generate_inl.sh ${CMAKE_CURRENT_LIST_DIR}
# )