#ifndef GMNETWORK_MAIN_H
#define GMNETWORK_MAIN_H

#ifdef WIN32
	#pragma once
#endif

#define _MODULE_VERSION_ "0.0.2"

#include <GarrysMod/Lua/Interface.h>
#include <GarrysMod/Lua/LuaInterface.h>
#include <GarrysMod/FunctionPointers.hpp>

#include <detouring/hook.hpp>

#include <player.h>

namespace GmNetwork {
	extern GarrysMod::Lua::ILuaInterface* ILuaServer;
}

#endif