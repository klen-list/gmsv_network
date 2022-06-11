#ifndef GMNETWORK_ERRHANDLER_H
#define GMNETWORK_ERRHANDLER_H

#ifdef SYSTEM_WINDOWS
	#pragma once
#endif

#include "main.hpp"

namespace GmNetwork::ErrHandler {
	extern Detouring::Hook DHook_HandleClientError;

	void Initialize(GarrysMod::Lua::ILuaInterface* LUA);
	void Detour_HandleClientError(CBasePlayer* ply, const char* err);
	void Deinitialize(GarrysMod::Lua::ILuaInterface* LUA);
}

#endif