#ifndef GMNETWORK_PROCESSCMD_H
#define GMNETWORK_PROCESSCMD_H

#ifdef SYSTEM_WINDOWS
	#pragma once
#endif

#include "main.hpp"

namespace GmNetwork::ProcessCmd
{
	class CBaseClientProxy : public Detouring::ClassProxy<CBaseClient, CBaseClientProxy>
	{
	public:
		void Initialize(GarrysMod::Lua::ILuaInterface* LUA);
		bool EnableHook(bool enable);
		void Deinitialize(GarrysMod::Lua::ILuaInterface* LUA);

		static CBaseClientProxy Singleton;

	private:
		bool
#if defined (SYSTEM_WINDOWS) && defined(ARCHITECTURE_X86)
			__thiscall
#else
			__cdecl
#endif
			ProcessStringCmd(uintptr_t* cmd);

		ScanningAdvanced::CBaseClient_ProcessStringCmd_t ProcessStringCmd_original = nullptr;
		GarrysMod::Lua::ILuaInterface* lua = nullptr;
	};
}

#endif