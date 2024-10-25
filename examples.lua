require"network"

if not istable(gmnetwork) then return end

do -- Client error report handle
	gmnetwork.EnableClientErrHandle(true)

	hook.Add("GmNetwork.OnClientErr", "Example", function(num_idx, str_err)
		print(Entity(num_idx)) -- Player
		print("Error: ", str_err)

		return true -- prevent default error actions (console print, clientside_errors.txt log, lua_error_url send)
	end)
end

do -- Client request to server concommand handle
	gmnetwork.EnableClientProcessCmd(true)

	hook.Add("GmNetwork.ProcessCmd", "Example", function(num_userid, str_cmd)
		local ply = Player(num_userid)
		if not IsValid(ply) then return true end
		
		Msg(Format("[ProcessCmds] Player '%s' (id: %s | ip: %s) command: '%s'\n", ply:Nick(), ply:SteamID(), ply:IPAddress(), str_cmd))
		
		-- Request block example
		if str_cmd:find"status" then
			return true
		end
	end)
end

do -- Lua auto-refresh handle
	gmnetwork.EnableLuaAutoRefreshHandle(true)

	hook.Add("GmNetwork.OnLuaRefresh", "Example", function(file_path)
		print("Auto-refreshed: ", file_path)
		
		-- Refresh block example
		-- (blocking there didn't tested and not guaranted!)
		if file_path:find"myfile.lua" then
			return true
		end
	end)
end

do -- Custom disconnect reason on server shutdown (built-in 'ply:Kick' and 'game.KickID' can't do this)
	hook.Add("ShutDown", "Example", function()
		for _, ply in ipairs(player.GetAll()) do
			gmnetwork.DisconnectClient(ply:UserID(), "Server is restarting. This may take 2-5 min.")
		end
	end)
end

do -- Close connection with clients (aka without disconnect message) on server shutdown
	hook.Add("ShutDown", "Example2", function()
		for _, ply in ipairs(player.GetAll()) do
			gmnetwork.DisconnectClientSilent(ply:UserID())
		end
	end)
end

do -- Bypass command blacklist without alias
	-- Example 1
	local cmd = "rcon_password "
	local passEnv = gmnetwork.GetEnv"RCON_PASS"

	if passEnv then
		cmd = cmd .. passEnv
	else
		for i = 12, 25 do
			cmd = cmd .. string.char(math.random(97, 122))
		end
	end

	gmnetwork.GMOD_RawServerCommand(cmd)
	
	-- Example 2
	util.AddNetworkString"ingame_rcon"
	net.Receive("ingame_rcon", function(l, ply)
		if not IsValid(ply) then return end
		if not ply:IsFullyAuthenticated() then return end
		if not ply:IsSuperAdmin() then return end
		
		local rawcmd = net.ReadString()
		if not isstring(rawcmd) or rawcmd:len() == 0 then return end
			
		gmnetwork.GMOD_RawServerCommand(rawcmd)
	end)
end