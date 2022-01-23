#ifndef GMNETWORK_SERVER_H
#define GMNETWORK_SERVER_H

#ifdef _WIN32
	#pragma once
#endif

#include "main.hpp"
#include "gamesrc/baseserver.h"

#define LUA_SERVERFUNC_RETNUM(name) \
LUA_FUNCTION_STATIC(name) \
{ \
	LUA_PUSHTYPEONCE(Number, GmNetwork::BaseServer::p_BaseServer->name()) \
}

#define LUA_SERVERFUNC_RETSTR(name) \
LUA_FUNCTION_STATIC(name) \
{ \
	LUA_PUSHTYPEONCE(String, GmNetwork::BaseServer::p_BaseServer->name()) \
}

#define LUA_SERVERFUNC_RETBOOL(name) \
LUA_FUNCTION_STATIC(name) \
{ \
	LUA_PUSHTYPEONCE(Bool, GmNetwork::BaseServer::p_BaseServer->name()) \
}

namespace GmNetwork::BaseServer {
	extern CBaseServer* p_BaseServer;
	void Initialize(GarrysMod::Lua::ILuaInterface* LUA);
	void OpenLib(GarrysMod::Lua::ILuaInterface* LUA);
	void Deinitialize(GarrysMod::Lua::ILuaInterface* LUA);
}

#endif