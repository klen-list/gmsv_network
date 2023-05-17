#include "processcmd.hpp"
#include "luaquicks.hpp"

using namespace GmNetwork::ProcessCmd;

CBaseClientProxy CBaseClientProxy::Singleton;

LUA_FUNCTION_STATIC(EnableClientProcessCmd)
{
	LUA->CheckType(1, GarrysMod::Lua::Type::BOOL);
	LUA->PushBool(CBaseClientProxy::Singleton.EnableHookInternal(LUA->GetBool(1)));
	return 1;
}

void CBaseClientProxy::Initialize(GarrysMod::Lua::ILuaInterface* LUA)
{
	lua = LUA;

	ProcessStringCmd_original = ScanningAdvanced::CBaseClient_ProcessStringCmd();
	if (ProcessStringCmd_original == nullptr)
		lua->ThrowError("\n[GmNetwork] Failed to find CBaseClient::ProcessStringCmd!\n\n");

	if (!Hook(ProcessStringCmd_original, &CBaseClientProxy::ProcessStringCmd))
		lua->ThrowError("\n[GmNetwork] Failed to hook CBaseClient::ProcessStringCmd!\n\n");

	DisableHook(ProcessStringCmd_original);
	PUSHFUNC(EnableClientProcessCmd)

	lua->MsgColour(Color(161, 170, 255, 255), "[GmNetwork] Loading: CBaseClient::ProcessStringCmd.\n");
}

bool CBaseClientProxy::EnableHookInternal(bool enable)
{
	return (enable ? EnableHook(ProcessStringCmd_original) : DisableHook(ProcessStringCmd_original));
}

bool TYPEDIFF_WIN86(__thiscall, __cdecl) CBaseClientProxy::ProcessStringCmd(uintptr_t* cmd)
{
	auto& self = CBaseClientProxy::Singleton;
	CBaseClient* basecl = this->This();

	// same offset at linux and windows, ehh? ~
	// mov     [esp+4], ecx
	const char* buf = reinterpret_cast<const char*>(*(cmd + 4));

	int playerid = *(reinterpret_cast<uintptr_t*>(basecl) + TYPEDIFF_WIN(3, 5));

	if (!GmNetwork::LuaQuicks::PushHookCall(self.lua, "GmNetwork.ProcessCmd"))
		return Call(self.ProcessStringCmd_original, cmd);

	self.lua->PushNumber(playerid);
	self.lua->PushString(buf);

	if (!GmNetwork::LuaQuicks::RunHookCall(self.lua, 2, 1))
		return Call(self.ProcessStringCmd_original, cmd);

	if (self.lua->IsType(-1, GarrysMod::Lua::Type::Bool))
	{
		bool b = self.lua->GetBool();
		self.lua->Pop();
		return b;
	}

	self.lua->Pop();

	return Call(self.ProcessStringCmd_original, cmd);
}

void CBaseClientProxy::Deinitialize(GarrysMod::Lua::ILuaInterface* LUA)
{
	if (IsHooked(ProcessStringCmd_original))
	{
		UnHook(ProcessStringCmd_original);
		LUA->MsgColour(Color(161, 170, 255, 255), "[GmNetwork] Unloading: CBasePlayer::ProcessStringCmd\n");
	}
}
