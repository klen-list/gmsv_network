#include "engineserver.hpp"

IVEngineServer* GmNetwork::EngineServer::p_EngineServer = nullptr;

LUA_FUNCTION_STATIC(GMOD_RawServerCommand)
{
	GmNetwork::EngineServer::p_EngineServer->GMOD_RawServerCommand(LUA->CheckString());
	return 0;
}

void GmNetwork::EngineServer::OpenLib(GarrysMod::Lua::ILuaInterface* LUA)
{
	PUSHFUNC(GMOD_RawServerCommand)
}

void GmNetwork::EngineServer::Initialize(GarrysMod::Lua::ILuaInterface* LUA)
{
	p_EngineServer = InterfacePointers::VEngineServer();
	if (!p_EngineServer)
		LUA->ThrowError("Unable to locate IVEngineServer!");

	OpenLib(LUA);

	LUA->MsgColour(Color(161, 170, 255, 255), "[GmNetwork] Loading: IVEngineServer functions\n");
}

void GmNetwork::EngineServer::Deinitialize(GarrysMod::Lua::ILuaInterface* LUA)
{
	p_EngineServer = nullptr;
	LUA->MsgColour(Color(161, 170, 255, 255), "[GmNetwork] Unloading: IVEngineServer functions\n");
}