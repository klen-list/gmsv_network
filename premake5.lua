PROJECT_GENERATOR_VERSION = 3

newoption {
    trigger = "gmcommon",
    description = "Sets the path to the garrysmod_common (https://github.com/danielga/garrysmod_common) directory",
    value = "path to garrysmod_common directory"
}

local gmcommon = _OPTIONS.gmcommon or os.getenv "GARRYSMOD_COMMON"

if not gmcommon then
	print "You didn't provide a path to your garrysmod_common (https://github.com/danielga/garrysmod_common) directory, using submodule directory instead."
end

include(gmcommon or "third-party/garrysmod_common")
include "third-party/gmc_scanning_advanced"

CreateWorkspace { name = "network" }
	CreateProject { serverside = true }
		IncludeHelpersExtended()
		IncludeSDKCommon()
		IncludeSDKTier0()
		IncludeSDKTier1()
		IncludeScanning()
		IncludeScanningAdvanced()
		IncludeDetouring()