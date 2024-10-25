#ifndef GMNETWORK_AUTOREFRESH_H
#define GMNETWORK_AUTOREFRESH_H

#ifdef SYSTEM_WINDOWS
	#pragma once
#endif

#include "main.hpp"

namespace GmNetwork::AutoRefresh {
	static Detouring::Hook DHook_HandleChange_Lua;
	void Initialize(GarrysMod::Lua::ILuaInterface* LUA);
	void __cdecl Detour_HandleLuaFileChange(const std::string& file);
	void Deinitialize(GarrysMod::Lua::ILuaInterface* LUA);
}

#endif