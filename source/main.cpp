#include "main.hpp"
#include "luaquicks.hpp"
#include "errhandler.hpp"

using namespace GmNetwork;

GarrysMod::Lua::ILuaInterface* GmNetwork::ILuaServer;

LUA_FUNCTION_STATIC(Version)
{
	LUA->PushString(_MODULE_VERSION_);
	return 1;
}

GMOD_MODULE_OPEN()
{
	ILuaServer = reinterpret_cast<GarrysMod::Lua::ILuaInterface*>(LUA);

	ILuaServer->CreateTable();

		ILuaServer->PushCFunction(Version);
		ILuaServer->SetField(-2, "Version");

		ErrHandler::Initialize(ILuaServer);

	ILuaServer->SetField(GarrysMod::Lua::INDEX_GLOBAL, "gmnetwork");

	ILuaServer->MsgColour(Color(161, 170, 255, 255), "[GmNetwork] Version %s by Klen_list loaded.\n", _MODULE_VERSION_);

	return 0;
}

GMOD_MODULE_CLOSE()
{
	ErrHandler::Deinitialize(ILuaServer);
	LUA->PushNil();
	LUA->SetField(GarrysMod::Lua::INDEX_GLOBAL, "gmnetwork");
	return 0;
}