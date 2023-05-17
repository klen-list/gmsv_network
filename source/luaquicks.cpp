#include "luaquicks.hpp"

#pragma warning(disable: 4505)
#include <GarrysMod/Lua/Helpers.hpp>
#pragma warning(default: 4505)

bool GmNetwork::LuaQuicks::PushHookCall(GarrysMod::Lua::ILuaInterface* LUA, const char* eventName)
{
	LUA->PushCFunction(LuaHelpers::LuaErrorTraceback);

	LUA->GetField(GarrysMod::Lua::INDEX_GLOBAL, "hook");

	if (!LUA->IsType(-1, GarrysMod::Lua::Type::Table))
	{
		LUA->ErrorNoHalt("\n[GmNetwork] Error: Global 'hook' is not a table!\n\n");
		LUA->Pop();
		return false;
	}

	LUA->GetField(-1, "Run");
	LUA->Remove(-2);

	if (!LUA->IsType(-1, GarrysMod::Lua::Type::Function))
	{
		LUA->ErrorNoHalt("\n[GmNetwork] Error: Global 'hook.Run' is not a function!\n\n");
		LUA->Pop();
		return false;
	}

	LUA->PushString(eventName);

	return true;
}

bool GmNetwork::LuaQuicks::RunHookCall(GarrysMod::Lua::ILuaInterface* LUA, int argC, int retC)
{
	if (LUA->PCall(argC + 1, retC, -argC - 3) != 0)
	{
		LUA->ErrorNoHalt("\n[GmNetwork] Error: %s\n\n", LUA->GetString(-1));
		LUA->Pop(2);

		return false;
	}

	LUA->Pop(-retC - 1);

	return true;
}