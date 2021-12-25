#include "errhandler.hpp"
#include "luaquicks.hpp"

Detouring::Hook GmNetwork::ErrHandler::DHook_HandleClientError;

void GmNetwork::ErrHandler::Detour_HandleClientError(CBasePlayer* ply, const char* err)
{
	if (!LuaQuicks::PushHookCall(ILuaServer, "GmNetwork.OnClientErr"))
		return DHook_HandleClientError.GetTrampoline<FunctionPointers::CBasePlayer_HandleClientLuaError_t>()(ply, err);

	ILuaServer->PushNumber(ply->entindex());
	ILuaServer->PushString(err);

	if (!LuaQuicks::RunHookCall(ILuaServer, 2, 1))
		return DHook_HandleClientError.GetTrampoline<FunctionPointers::CBasePlayer_HandleClientLuaError_t>()(ply, err);

	if (ILuaServer->IsType(-1, GarrysMod::Lua::Type::Bool) && ILuaServer->GetBool())
		return ILuaServer->Pop(); // we confirm handle it

	ILuaServer->Pop();

	return DHook_HandleClientError.GetTrampoline<FunctionPointers::CBasePlayer_HandleClientLuaError_t>()(ply, err);
}

LUA_FUNCTION_STATIC(EnableClientErrHandle)
{
	LUA->CheckType(1, GarrysMod::Lua::Type::BOOL);
	LUA->PushBool(LUA->GetBool(1) ?
		GmNetwork::ErrHandler::DHook_HandleClientError.Enable() :
		GmNetwork::ErrHandler::DHook_HandleClientError.Disable());
	return 1;
}

void GmNetwork::ErrHandler::Initialize(GarrysMod::Lua::ILuaInterface* LUA)
{
	const auto HandleClientLuaError = FunctionPointers::CBasePlayer_HandleClientLuaError();
	if (!HandleClientLuaError)
		LUA->ThrowError("Unable to locate CBasePlayer::HandleClientLuaError!");

	if (!DHook_HandleClientError.Create(
		Detouring::Hook::Target(reinterpret_cast<void*>(HandleClientLuaError)),
		reinterpret_cast<void*>(&Detour_HandleClientError)
	))
		LUA->ThrowError("Unable to detour CBasePlayer::HandleClientLuaError!");

	PUSHFUNC(EnableClientErrHandle)

	LUA->MsgColour(Color(161, 170, 255, 255), "[GmNetwork] Loading: HandleClientLuaError detoured.\n");
}

void GmNetwork::ErrHandler::Deinitialize(GarrysMod::Lua::ILuaInterface* LUA)
{
	DHook_HandleClientError.Destroy();
	LUA->MsgColour(Color(161, 170, 255, 255), "[GmNetwork] Unloading: HandleClientLuaError undetoured.\n");
}