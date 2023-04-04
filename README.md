# :wrench: gmsv_network :gear:

A Garry's Mod binary serverside module that provide GLua access to basic server and client functions. Designed to replace the tracking of many events that require `gm_sourcenet` (which produces lua panic on many servers, corrupted message buffer reads, and decreased optimization). Currently under development.

## Available functions and hooks

Check [example](https://github.com/klen-list/gmsv_network/blob/main/premake5.lua) for detailed usage. All function placed in global `gmnetwork` table.

**CBaseServer**:  
`GetNumClients` `GetNumProxies` `GetNumFakeClients` `GetMaxClients` `GetUDPPort` `GetClientCount` `GetTime` `GetTick` `GetTickInterval` `GetName` `GetMapName` `GetSpawnCount` `GetNumClasses` `GetClassBits` `GetNetStats` `GetNumPlayers` `GetCPUUsage` `IsActive` `IsLoading` `IsDedicated` `IsPaused` `IsMultiplayer` `IsPausable` `IsHLTV` `IsReplay` `GetPassword` `SetMaxClients` `SetPaused` `SetPassword` `DisconnectClient` `DisconnectClientSilent`

**IVEngineServer**:  
`GMOD_RawServerCommand`

**HandleClientError**:  
`EnableClientErrHandle`  
[Hook] `GmNetwork.OnClientErr (ply_id: number, err: string) -> prevent_default: bool`

**ProcessCmd**:  
`EnableClientProcessCmd`  
[Hook] `GmNetwork.ProcessCmd (ply_id: number, cmd: string) -> prevent_default: any bool`

**Other**:  
`Version (string)`

## Planned
Hook for `GarrysMod::AutoRefresh::HandleLuaFileChange(std::string const&)`  
Ability to mark entities with function like `SetTransmitControl`  
Hook when marked entities about to writed in `svc_PacketEntities`

## Requirements

1. [Garrysmod Common][1] - A framework to facilitate the creation of compilations files (Visual Studio, make, XCode, etc). Simply set the environment variable `GARRYSMOD_COMMON` or the premake option `--gmcommon=path` to the path of your local copy of [garrysmod\_common][1].
2. [Scanning Advanced][2] - My helpful module contains symbols for sigscanning with garrysmod\_common. Should be installed in `third-party` folder with name [gmc\_scanning\_advanced][2].
3. (Linux) Installed `gcc-multilib` package.

All requirements already added in repository as submodules. <ins>Make sure that you them clone with recursive!</ins>  
`git clone https://github.com/klen-list/gmsv_network --recursive`

## Compiling
1. Download or install premake5
2. Enter the project folder and run:
- `./premake5 vs2019` (**Windows** with installed `Visual Studio 2019` and locally placed premake5.exe)
- `./premake5 gmake` (**Linux** with installed `build-essential` and locally placed premake5)  
⚠️ If you catch `Error: module 'premake-export-compile-commands/export-compile-commands' not found` you **didn't clone submodules correctly!** Read above about clone command.  
3. Move to `projects/{os_platform}/{vs2019|gmake}` and run `gm_network.sln` (Windows) or run `make` command (Linux)

[1]: https://github.com/danielga/garrysmod_common
[2]: https://github.com/klen-list/gmc_scanning_advanced
