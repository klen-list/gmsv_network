#ifndef GMNETWORK_LUAQUICKS_H
#define GMNETWORK_LUAQUICKS_H

#ifdef WIN32
	#pragma once
#endif

#include "main.hpp"

namespace GmNetwork::LuaQuicks {
	bool PushHookCall(GarrysMod::Lua::ILuaInterface* LUA, const char* eventName);
	bool RunHookCall(GarrysMod::Lua::ILuaInterface* LUA, int argC, int retC);
}

#endif