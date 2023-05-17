#include "autorefresh.hpp"
#include "luaquicks.hpp"

LUA_FUNCTION_STATIC(EnableLuaAutoRefreshHandle)
{
	LUA->PushBool(LUA->GetBool() ?
		GmNetwork::AutoRefresh::DHook_HandleChange_Lua.Enable() :
		GmNetwork::AutoRefresh::DHook_HandleChange_Lua.Disable());

	return 1;
}

ScanningAdvanced::GModAutoRefresh_HandleLuaFileChange_t HandleLuaFileChange;

void __cdecl GmNetwork::AutoRefresh::Detour_HandleLuaFileChange(void* Src)
{
	const char* file = TYPEDIFF_WIN((const char*), *(const char**))Src;

	GmNetwork::LuaQuicks::PushHookCall(ILuaServer, "GmNetwork.OnLuaRefresh");
	ILuaServer->PushString(file);
	GmNetwork::LuaQuicks::RunHookCall(ILuaServer, 1, 1);

	if (ILuaServer->IsType(-1, GarrysMod::Lua::Type::Bool))
	{
		ILuaServer->Pop();
		return;
	}

	ILuaServer->Pop();

	DHook_HandleChange_Lua.GetTrampoline<ScanningAdvanced::GModAutoRefresh_HandleLuaFileChange_t>()(Src);
}

void GmNetwork::AutoRefresh::Initialize(GarrysMod::Lua::ILuaInterface* LUA)
{
	HandleLuaFileChange = ScanningAdvanced::GModAutoRefresh_HandleLuaFileChange();
	if (!HandleLuaFileChange)
		LUA->ThrowError("\n[GmNetwork] Unable to locate GModAutoRefresh::HandleLuaFileChange!\n\n");

	if (!DHook_HandleChange_Lua.Create(
		Detouring::Hook::Target(reinterpret_cast<void*>(HandleLuaFileChange)),
		reinterpret_cast<void*>(&Detour_HandleLuaFileChange)
	))
		LUA->ThrowError("\n[GmNetwork] Unable to detour GModAutoRefresh::HandleLuaFileChange!\n\n");

	PUSHFUNC(EnableLuaAutoRefreshHandle)

	LUA->MsgColour(Color(161, 170, 255, 255), "[GmNetwork] Loading: GModAutoRefresh::HandleLuaFileChange\n");
}

void GmNetwork::AutoRefresh::Deinitialize(GarrysMod::Lua::ILuaInterface* LUA)
{
	DHook_HandleChange_Lua.Destroy();
	LUA->MsgColour(Color(161, 170, 255, 255), "[GmNetwork] Unloading: GModAutoRefresh::HandleLuaFileChange\n");
}