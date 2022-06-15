pcall(require, "network")

if not istable(gmnetwork) then return end

do -- Client errors handle
	gmnetwork.EnableClientErrHandle(true)

	hook.Add("GmNetwork.OnClientErr", "Example", function(num_idx, str_err)
		print(Entity(num_idx)) -- Player
		print("Error: ", str_err)
		return true -- prevent default error action (console print and clientside_errors.txt log)
	end)
end

do -- Custom disconnect reason on server shutdown (built-in ply:Kick not works for this)
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
	local cmd = "rcon_password "
	for i = 12, 25 do
		cmd = cmd .. string.char(math.random(97, 122))
	end
	gmnetwork.GMOD_RawServerCommand(cmd)
end