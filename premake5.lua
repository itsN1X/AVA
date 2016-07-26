require "ninja"

-- sln

solution "avSln"
	location "ide"
	configurations {"debug", "release", "shipping"}

-- dll

project "avDllEditor"
	kind "SharedLib"
	location "ide"
	language "C++"
	targetdir "bin/%{cfg.buildcfg}"

	files {"src/editor/**.c*", "src/editor/**.h*"}
	includedirs {"src/editor/"}
	defines {"DLL_EXPORT"}

	filter "configurations:debug"
		defines {"DEBUG"}
		flags {"Symbols"}

	filter "configurations:release"
		defines {"NDEBUG"}
		optimize "On"

	filter "configurations:shipping"
		defines {"NDEBUG", "SHIPPING"}
		optimize "On"

project "avDllPlayer"
	kind "SharedLib"
	location "ide"
	language "C++"
	targetdir "bin/%{cfg.buildcfg}"

	files {"src/player/**.c*", "src/player/**.h*"}
	includedirs {"src/player/"}
	defines {"DLL_EXPORT2"}

	filter "configurations:debug"
		defines {"DEBUG"}
		flags {"Symbols"}

	filter "configurations:release"
		defines {"NDEBUG"}
		optimize "On"

	filter "configurations:shipping"
		defines {"NDEBUG", "SHIPPING"}
		optimize "On"

project "avDllGame"
	kind "SharedLib"
	location "ide"
	language "C++"
	targetdir "bin/%{cfg.buildcfg}"

	files {"src/game/**.c*", "src/game/**.h*"}
	includedirs {"src/game/"}
	defines {"DLL_EXPORT3"}

	filter "configurations:debug"
		defines {"DEBUG"}
		flags {"Symbols"}

	filter "configurations:release"
		defines {"NDEBUG"}
		optimize "On"

	filter "configurations:shipping"
		defines {"NDEBUG", "SHIPPING"}
		optimize "On"

-- app

project "avLauncher"
	kind "ConsoleApp"
	location "ide"
	language "C++"
	targetdir "bin/%{cfg.buildcfg}"

	files {"src/launcher/**.c*", "src/launcher/**.h*"}
	includedirs {"src/launcher/"}
	links {"avDllPlayer", "avDllEditor", "avDllGame"}

	configuration "windows"
		links { "user32", "gdi32" }

	configuration "linux"
		links { "pthread" }

	filter "configurations:debug"
		defines {"DEBUG"}
		flags {"Symbols"}

	filter "configurations:release"
		defines {"NDEBUG"}
		optimize "On"

	filter "configurations:shipping"
		defines {"NDEBUG", "SHIPPING"}
		optimize "On"

--[[
	kind "WindowedApp"
	filter "system:windows"
		flags {"WinMain"}
--]]
