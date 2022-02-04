#pragma once
 

#if defined(_WIN32) && defined(_LUADBG_BUILD_DLL)
#define LUADBGAPI __declspec(dllexport)
#elif defined(_WIN32) && defined(LUADBG_DLL)
#define LUADBGAPI __declspec(dllimport)
#elif defined(__GNUC__) && defined(_LUADBG_BUILD_DLL)
#define LUADBGAPI __attribute__((visibility("default")))
#else
#define LUADBGAPI
#endif

 
#include <lua.hpp>

extern "C" LUADBGAPI int  luaopen_luadbg(lua_State * L);

