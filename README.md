# :wrench: gmsv_network :gear:

💪 All in one Garry's Mod binary module for x86 (x32) Linux/Windows dedicated server that provide access to various SourceEngine/GMOD methods and callbacks. Make your serverside lua scripts more optimized, powerfull and secure!   
💡 Originally designed to replace the tracking of many events that require `gm_sourcenet` (which produces lua panic crashes, corrupted netchannel buffer read/write, and decreased optimization).  
🪛 Currently under development. Feel free to request any new lua bindings you need, I can probably add them!

## Available functions and hooks

Check [example](https://github.com/klen-list/gmsv_network/blob/main/examples.lua) for detailed usage. All functions placed in global `gmnetwork` table.

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

**LuaAutoRefresh**:  
`EnableLuaAutoRefreshHandle`  
[Hook] `GmNetwork.OnLuaRefresh (file_path: string) -> prevent_default: any bool`

**Other**:  
`Version (string)` `(nil|string) GetEnv (string)`

## Worklist
- [ ] Integrate bindings into existing glua classes/libraries, or create new ones.
- [x] Simplified version of `ClientLuaError` from `gm_luaerror`, allow parsing errors on lua side
- [x] Bindings for most of `CBaseServer` methods
  - [ ] Bindings for `CBaseServer` broadcast methods
- [ ] Bindings for most of `IVEngineServer` methods
  - [x] Binding to RawServerCommand
- [x] Binding a hook when client want execute serverside concommand (ProcessCmd) like binary module from myarena hosting, allow to block executing
- [ ] Some GmodDataPack bindings (personal request from one server owner)
  - [x] Binding a hook when datapack handle a lua file refresh
  - [ ] Block a lua refresh in this hook (probably needed too)
  - [ ] Binding to datapack HandleChange_Lua method like metastruct old code do
- [ ] Create method to mark entities with method like `SetTransmitControl`
- [ ] Binding a hook when marked entities change their PVS for players. Needed do a some magic with `sv_ents_write.cpp` (probably useful for own networked entity values system)
- [ ] Binding a hook when marked entities and their childrens about to be writen in `svc_PacketEntities`, allow to suppress. Useful for accurate admin vanish instead spamming `SetPreventTransmit` calls
- [ ] Bindings for `CGameEventManager` with ability suppress and create events. Also useful for ideal vanish
- [ ] Binding a hook when server handle new value of `FCVAR_USERINFO` convar from client. Allow handle changes without spamming `GetInfo/GetInfoNum` calls. (Requested by me #1995 in garrysmod-requests)
- [ ] Some bindings for `vphysics` (Most of this done in my other private module)
  - [ ] Bindings to some `CCollisionEvent` callbacks (detouring a friction system warning already used by my as good anticrash addition, i also seen this hook in metastruct old code)
  - [ ] Bindings to `IPhysicsObjectEvent` callbacks (related to `CCollisionEvent` bindings, just for #1923 in garrysmod-requests about adding hook when physobj going sleep)
  - [ ] Bindings to `CPhysicsObject`, including methods that are not exposed to `IPhysicsObject` (including #2234 in garrysmod-requests about adding `PhysObj:GetBuoyancyRatio`)
  - [ ] Binding to `PhysIsInCallback` (mentioned by #894 in garrysmod-requests)
  - [ ] Binding to `PhysicsGameSystem` and fields like `m_bPaused` that allow pause a physics
  - [ ] Bindings to `IPhysicsEnvironment` (probably)

## Requirements

1. [Garrysmod Common][1] - A framework to facilitate the creation of compilations files (Visual Studio, make, XCode, etc). Simply set the environment variable `GARRYSMOD_COMMON` or the premake option `--gmcommon=path` to the path of your local copy of [garrysmod\_common][1].
2. [Scanning Advanced][2] - My helpful module contains symbols for sigscanning with garrysmod\_common. Should be installed in `third-party` folder with name [gmc\_scanning\_advanced][2].
3. (Linux) Installed `gcc-multilib` and `g++-multilib` packages.

All requirements already added in repository as submodules. <ins>Make sure that you clone them with recursive!</ins>  
`git clone https://github.com/klen-list/gmsv_network --recursive`

## Compiling
1. Download or install [premake5](https://premake.github.io/download)
2. Enter the project folder and run:
- `./premake5.exe vs2019` (**Windows** with installed `Visual Studio 2019` and locally placed premake5.exe)
- `./premake5 gmake` (**Linux** with installed `build-essential` and locally placed premake5)  
⚠️ If you catch `Error: module 'premake-export-compile-commands/export-compile-commands' not found` you **didn't clone submodules correctly!** Read above about clone command.  
3. Move to `projects/{os_platform}/{vs2019|gmake}` and run `gm_network.sln` (Windows) or run `make` command (Linux)

## Stars

<a href="https://star-history.com/#klen-list/gmsv_network&Date">
  <picture>
    <source media="(prefers-color-scheme: dark)" srcset="https://api.star-history.com/svg?repos=klen-list/gmsv_network&type=Date&theme=dark" />
    <source media="(prefers-color-scheme: light)" srcset="https://api.star-history.com/svg?repos=klen-list/gmsv_network&type=Date" />
    <img alt="Star History Chart" src="https://api.star-history.com/svg?repos=klen-list/gmsv_network&type=Date" />
  </picture>
</a>


[1]: https://github.com/danielga/garrysmod_common
[2]: https://github.com/klen-list/gmc_scanning_advanced
