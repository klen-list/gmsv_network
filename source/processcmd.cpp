#include "processcmd.hpp"
#include "luaquicks.hpp"

using namespace GmNetwork::ProcessCmd;

CBaseClientProxy CBaseClientProxy::Singleton;

LUA_FUNCTION_STATIC(EnableClientProcessCmd)
{
	LUA->CheckType(1, GarrysMod::Lua::Type::BOOL);
	LUA->PushBool(LUA->GetBool(1) ?
		CBaseClientProxy::Singleton.EnableHook(true) :
		CBaseClientProxy::Singleton.EnableHook(false));
	return 1;
}

void CBaseClientProxy::Initialize(GarrysMod::Lua::ILuaInterface* LUA)
{
	lua = LUA;

	ProcessStringCmd_original = ScanningAdvanced::CBaseClient_ProcessStringCmd();
	if (ProcessStringCmd_original == nullptr)
		LUA->ThrowError("\n[GmNetwork] Failed to find CBaseClient::ProcessStringCmd!\n\n");

	PUSHFUNC(EnableClientProcessCmd)

	lua->MsgColour(Color(161, 170, 255, 255), "[GmNetwork] Loading: CBaseClient::ProcessStringCmd.\n");
}

bool CBaseClientProxy::EnableHook(bool enable)
{
	auto& self = CBaseClientProxy::Singleton;

	if (enable && self.IsHooked(ProcessStringCmd_original))
	{
		if (!Hook(ProcessStringCmd_original, &CBaseClientProxy::ProcessStringCmd))
		{
			self.lua->ThrowError("\n[GmNetwork] Failed to hook CBaseClient::ProcessStringCmd!\n\n");
			return false;
		}
		return true;
	}
	else
	{
		if (!UnHook(ProcessStringCmd_original))
			return false;
		return true;
	}
}

bool
#if defined (SYSTEM_WINDOWS) && defined(ARCHITECTURE_X86)
__thiscall
#else
__cdecl
#endif
CBaseClientProxy::ProcessStringCmd(uintptr_t* cmd)
{
	auto& self = CBaseClientProxy::Singleton;
	CBaseClient* basecl = this->This();

	const char* buf;

	// same offset at linux and windows, ehh? ~
	// mov     [esp+4], ecx
	buf = reinterpret_cast<const char*>(*(cmd + 4));

	int playerid;

#ifdef SYSTEM_WINDOWS
	playerid = *(reinterpret_cast<uintptr_t*>(basecl) + 3);
#elif SYSTEM_LINUX
	playerid = *(reinterpret_cast<uintptr_t*>(basecl) + 5);
#endif

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
		LUA->MsgColour(Color(161, 170, 255, 255), "[GmNetwork] Unloading: CBasePlayer::HandleClientLuaError undetoured.\n");
	}
}