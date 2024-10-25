#include "main.hpp"
#include "luaquicks.hpp"
#include "errhandler.hpp"
#include "cbaseserver.hpp"
#include "engineserver.hpp"
#include "processcmd.hpp"
#include "autorefresh.hpp"

using namespace GmNetwork;

GarrysMod::Lua::ILuaInterface* GmNetwork::ILuaServer;

LUA_FUNCTION_STATIC(GetEnv)
{
	char* env = std::getenv(LUA->CheckString(1));
	
	if (!env)
		LUA->PushNil();
	else
		LUA->PushString(env);

	return 1;
}

GMOD_MODULE_OPEN()
{
	ILuaServer = reinterpret_cast<GarrysMod::Lua::ILuaInterface*>(LUA);
	
	ILuaServer->CreateTable();

	ILuaServer->PushString(_MODULE_VERSION_);
	ILuaServer->SetField(-2, "Version");

	ErrHandler::Initialize(ILuaServer);
	ProcessCmd::CBaseClientProxy::Singleton.Initialize(ILuaServer);
	BaseServer::Initialize(ILuaServer);
	EngineServer::Initialize(ILuaServer);
	AutoRefresh::Initialize(ILuaServer);

	PUSHFUNC(GetEnv);

	ILuaServer->SetField(GarrysMod::Lua::INDEX_GLOBAL, "gmnetwork");

	ILuaServer->MsgColour(Color(161, 170, 255, 255), "[GmNetwork] Version %s by Klen_list loaded!\n", _MODULE_VERSION_);

	return 0;
}

GMOD_MODULE_CLOSE()
{
	ErrHandler::Deinitialize(ILuaServer);
	ProcessCmd::CBaseClientProxy::Singleton.Deinitialize(ILuaServer);
	BaseServer::Deinitialize(ILuaServer);
	EngineServer::Deinitialize(ILuaServer);
	AutoRefresh::Deinitialize(ILuaServer);

	LUA->PushNil();
	LUA->SetField(GarrysMod::Lua::INDEX_GLOBAL, "gmnetwork");

	ILuaServer = nullptr;

	return 0;
}