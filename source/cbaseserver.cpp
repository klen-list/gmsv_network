#include "cbaseserver.hpp"
#include <inetchannel.h>

CBaseServer* GmNetwork::BaseServer::p_BaseServer = nullptr;
class CBaseClient : public IGameEventListener2, public IClient, public IClientMessageHandler {};

LUA_SERVERFUNC_RETNUM(GetNumClients)
LUA_SERVERFUNC_RETNUM(GetNumProxies)
LUA_SERVERFUNC_RETNUM(GetNumFakeClients)
LUA_SERVERFUNC_RETNUM(GetMaxClients)
LUA_SERVERFUNC_RETNUM(GetUDPPort)
//virtual IClient* GetClient(int index)
LUA_SERVERFUNC_RETNUM(GetClientCount)
LUA_SERVERFUNC_RETNUM(GetTime)
LUA_SERVERFUNC_RETNUM(GetTick)
LUA_SERVERFUNC_RETNUM(GetTickInterval)
LUA_SERVERFUNC_RETSTR(GetName)
LUA_SERVERFUNC_RETSTR(GetMapName)
LUA_SERVERFUNC_RETNUM(GetSpawnCount)
LUA_SERVERFUNC_RETNUM(GetNumClasses)
LUA_SERVERFUNC_RETNUM(GetClassBits)

LUA_FUNCTION_STATIC(GetNetStats)
{
	float in = 0, out = 0;

	float& avgIn = in;
	float& avgOut = out;
	GmNetwork::BaseServer::p_BaseServer->GetNetStats(avgIn, avgOut);

	LUA->PushNumber(in);
	LUA->PushNumber(out);
	return 2;
}

LUA_SERVERFUNC_RETNUM(GetNumPlayers)

LUA_SERVERFUNC_RETNUM(GetCPUUsage)
LUA_SERVERFUNC_RETBOOL(IsActive)
LUA_SERVERFUNC_RETBOOL(IsLoading)
LUA_SERVERFUNC_RETBOOL(IsDedicated)
LUA_SERVERFUNC_RETBOOL(IsPaused)
LUA_SERVERFUNC_RETBOOL(IsMultiplayer)
LUA_SERVERFUNC_RETBOOL(IsPausable)
LUA_SERVERFUNC_RETBOOL(IsHLTV)
LUA_SERVERFUNC_RETBOOL(IsReplay)
//virtual void BroadcastMessage(INetMessage& msg, bool onlyActive = false, bool reliable = false) = 0;
//virtual void BroadcastMessage(INetMessage& msg, IRecipientFilter& filter) = 0;
//virtual void BroadcastPrintf(PRINTF_FORMAT_STRING const char* fmt, ...) FMTFUNCTION(2, 3) = 0;
LUA_SERVERFUNC_RETSTR(GetPassword)

LUA_FUNCTION_STATIC(SetMaxClients)
{
	GmNetwork::BaseServer::p_BaseServer->SetMaxClients(LUA->CheckNumber(1));
	return 0;
}

LUA_FUNCTION_STATIC(SetPaused)
{
	LUA->CheckType(1, GarrysMod::Lua::Type::Bool);
	GmNetwork::BaseServer::p_BaseServer->SetPaused(LUA->GetBool(1));
	return 0;
}

LUA_FUNCTION_STATIC(SetPassword)
{
	GmNetwork::BaseServer::p_BaseServer->SetPassword(LUA->CheckString(1));
	return 0;
}

LUA_FUNCTION_STATIC(DisconnectClient)
{
	int inUserID = LUA->CheckNumber(1);
	const char* reason = LUA->CheckString(2);

	if (inUserID <= 0) {
		LUA->PushBool(false);
		return 1;
	}
		
	for (auto nSlot = 0; nSlot < GmNetwork::BaseServer::p_BaseServer->GetMaxClients(); ++nSlot) {
		IClient* client = GmNetwork::BaseServer::p_BaseServer->GetClient(nSlot);
		if (!client->IsConnected()) continue;
		if (client->GetUserID() == inUserID) {
			GmNetwork::BaseServer::p_BaseServer->DisconnectClient(client, reason);
			LUA->PushBool(true);
			return 1;
		}
	}

	GmNetwork::ILuaServer->Msg("[GmNetwork] Client with userid %i not exists.\n", inUserID);

	LUA->PushBool(false);
	return 1;
}

LUA_FUNCTION_STATIC(DisconnectClientSilent)
{
	int inUserID = LUA->CheckNumber(1);

	if (inUserID <= 0) {
		LUA->PushBool(false);
		return 1;
	}

	for (auto nSlot = 0; nSlot < GmNetwork::BaseServer::p_BaseServer->GetMaxClients(); ++nSlot) {
		IClient* client = GmNetwork::BaseServer::p_BaseServer->GetClient(nSlot);
		if (!client->IsConnected()) continue;
		if (client->GetUserID() == inUserID) {
			GmNetwork::BaseServer::p_BaseServer->RemoveClientFromGame(reinterpret_cast<CBaseClient*>(client));
			client->GetNetChannel()->Shutdown(NULL);
			client->Clear();
			LUA->PushBool(true);
			return 1;
		}
	}

	GmNetwork::ILuaServer->Msg("[GmNetwork] Client with userid %i not exists.\n", inUserID);

	LUA->PushBool(false);
	return 1;
}

void GmNetwork::BaseServer::OpenLib(GarrysMod::Lua::ILuaInterface* LUA)
{
	PUSHFUNC(GetNumClients)
	PUSHFUNC(GetNumProxies)
	PUSHFUNC(GetNumFakeClients)
	PUSHFUNC(GetMaxClients)
	PUSHFUNC(GetUDPPort)
	//virtual IClient* GetClient(int index)
	PUSHFUNC(GetClientCount)
	PUSHFUNC(GetTime)
	PUSHFUNC(GetTick)
	PUSHFUNC(GetTickInterval)
	PUSHFUNC(GetName)
	PUSHFUNC(GetMapName)
	PUSHFUNC(GetSpawnCount)
	PUSHFUNC(GetNumClasses)
	PUSHFUNC(GetClassBits)
	PUSHFUNC(GetNetStats)
	PUSHFUNC(GetNumPlayers)
	PUSHFUNC(GetCPUUsage)
	PUSHFUNC(IsActive)
	PUSHFUNC(IsLoading)
	PUSHFUNC(IsDedicated)
	PUSHFUNC(IsPaused)
	PUSHFUNC(IsMultiplayer)
	PUSHFUNC(IsPausable)
	PUSHFUNC(IsHLTV)
	PUSHFUNC(IsReplay)
	//virtual void BroadcastMessage(INetMessage & msg, bool onlyActive = false, bool reliable = false) = 0;
	//virtual void BroadcastMessage(INetMessage & msg, IRecipientFilter & filter) = 0;
	//virtual void BroadcastPrintf(PRINTF_FORMAT_STRING const char* fmt, ...) FMTFUNCTION(2, 3) = 0;
	PUSHFUNC(GetPassword)
	PUSHFUNC(SetMaxClients)
	PUSHFUNC(SetPaused)
	PUSHFUNC(SetPassword)
	PUSHFUNC(DisconnectClient)
	PUSHFUNC(DisconnectClientSilent)
}

void GmNetwork::BaseServer::Initialize(GarrysMod::Lua::ILuaInterface* LUA)
{
	IServer* p_IServer = InterfacePointers::Server();
	if (!p_IServer)
		LUA->ThrowError("Unable to locate IServer!");

	p_BaseServer = dynamic_cast<CBaseServer*>(p_IServer);
	if (!p_BaseServer)
		LUA->ThrowError("Unable to get CBaseServer!");

	OpenLib(LUA);

	LUA->MsgColour(Color(161, 170, 255, 255), "[GmNetwork] Loading: CBaseServer functions imported.\n");
}

void GmNetwork::BaseServer::Deinitialize(GarrysMod::Lua::ILuaInterface* LUA)
{
	p_BaseServer = nullptr;
	LUA->MsgColour(Color(161, 170, 255, 255), "[GmNetwork] Unloading: CBaseServer pointer destroyed.\n");
}