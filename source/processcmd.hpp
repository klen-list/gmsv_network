#ifndef GMNETWORK_PROCESSCMD_H
#define GMNETWORK_PROCESSCMD_H

#ifdef SYSTEM_WINDOWS
	#pragma once
#endif

#include "main.hpp"

namespace GmNetwork::ProcessCmd
{
	class CBaseClientProxy : public ScanningAdvanced::ClassProxyAdv<CBaseClient, CBaseClientProxy>
	{
	public:
		void Initialize(GarrysMod::Lua::ILuaInterface* LUA);
		void Deinitialize(GarrysMod::Lua::ILuaInterface* LUA);

		bool EnableHookInternal(bool enable);

		static CBaseClientProxy Singleton;

	private:
		bool TYPEDIFF_WIN86(__thiscall, __cdecl) ProcessStringCmd(uintptr_t* cmd);

		ScanningAdvanced::CBaseClient_ProcessStringCmd_t ProcessStringCmd_original = nullptr;
		GarrysMod::Lua::ILuaInterface* lua = nullptr;
	};
}

#endif