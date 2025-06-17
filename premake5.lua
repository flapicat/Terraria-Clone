workspace "Terraria-clone"
	architecture "x64"
	startproject "Sandbox"

	configurations
	{
		"Debug",
		"Release"
	}

outputdir = "%{cfg.buildcfg}-%{cfg.system}-%{cfg.architecture}"

IncludeDir = {}
IncludeDir["GLFW"] = "Terraria-clone/vendor/GLFW/include"
IncludeDir["Glad"] = "Terraria-clone/vendor/Glad/include"
IncludeDir["ImGui"] = "Terraria-clone/vendor/imgui"
IncludeDir["glm"] = "Terraria-clone/vendor/glm"

group "Dependencies"
	include "Terraria-clone/vendor/GLFW"
	include "Terraria-clone/vendor/Glad"
	include "Terraria-clone/vendor/imgui"
	include "Terraria-clone/vendor/glm"
group ""

project "Terraria-clone"
	location "Terraria-clone"
	kind "ConsoleApp"
	language "C++"
	cppdialect "C++17"
	staticruntime "off"

	targetdir ("bin/" .. outputdir .. "/%{prj.name}")
	objdir ("bin-int/" .. outputdir .. "/%{prj.name}")

	pchheader "trpch.h"
	pchsource "%{prj.name}/Source/trpch.cpp"

	files
	{
		"%{prj.name}/assets/**",
		"%{prj.name}/Source/App/**.h",
		"%{prj.name}/Source/App/**.cpp",
		"%{prj.name}/Source/Game/**.h",
		"%{prj.name}/Source/Game/**.cpp",
		"%{prj.name}/Source/**.h",
		"%{prj.name}/Source/**.cpp",

		"%{prj.name}/vendor/glm/glm/**.hpp",
		"%{prj.name}/vendor/glm/glm/**.inl",
	}

	defines
	{
		"_CRT_SECURE_NO_WARNINGS"
	}

	includedirs
	{
		"%{prj.name}/Source",
		"%{prj.name}/Source/App",
		"%{prj.name}/Source/Game",
		"%{prj.name}/vendor/spdlog/include",
		"%{IncludeDir.GLFW}",
		"%{IncludeDir.Glad}",
		"%{IncludeDir.ImGui}",
		"%{IncludeDir.glm}"
	}

	links 
	{ 
		"GLFW",
		"Glad",
		"ImGui",
		"glm",
		"opengl32.lib"
	}

	filter "system:windows"
		systemversion "latest"
		buildoptions "/utf-8"

		defines
		{
			"GLFW_INCLUDE_NONE"
		}

	filter "configurations:Debug"
		defines "DEBUG"
		runtime "Debug"
		symbols "on"

	filter "configurations:Release"
		defines "RELEASE"
		runtime "Release"
		optimize "on"
