#ifndef GMNETWORK_ENGINESERVER_H
#define GMNETWORK_ENGINESERVER_H

#ifdef _WIN32
	#pragma once
#endif

#include "main.hpp"

#include <inetchannel.h>

namespace GmNetwork::EngineServer {
	extern IVEngineServer* p_EngineServer;
	void Initialize(GarrysMod::Lua::ILuaInterface* LUA);
	void OpenLib(GarrysMod::Lua::ILuaInterface* LUA);
	void Deinitialize(GarrysMod::Lua::ILuaInterface* LUA);
}

#endif