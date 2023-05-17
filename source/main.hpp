#ifndef GMNETWORK_MAIN_H
#define GMNETWORK_MAIN_H

#ifdef SYSTEM_WINDOWS
	#pragma once
#endif

#define _MODULE_VERSION_ "0.0.9"

#include <GarrysMod/Lua/Interface.h>
#include <GarrysMod/Lua/LuaInterface.h>
#include <GarrysMod/FunctionPointers.hpp>
#include <GarrysMod/InterfacePointers.hpp>

#include <detouring/hook.hpp>

#include <scanning/scanadv.h>
#include <scanning/advproxy.h>

#include <player.h>
#include <iclient.h>

#define LUA_PUSHTYPEONCE(type, data) \
LUA->Push##type(data); \
return 1;

#define PUSHFUNC(name) \
LUA->PushCFunction(name); \
LUA->SetField(-2, #name);

namespace GmNetwork {
	extern GarrysMod::Lua::ILuaInterface* ILuaServer;
}

#endif
