project "ImGui"
	kind "StaticLib"
	language "C++"
    staticruntime "off"

	targetdir ("bin/" .. outputdir .. "/%{prj.name}")
	objdir ("bin-int/" .. outputdir .. "/%{prj.name}")

	files
	{
		"%{prj.name}/",
		"imconfig.h",
		"imgui.h",
		"imgui.cpp",
		"imgui_draw.cpp",
		"imgui_internal.h",
		"imgui_tables.cpp",
		"imgui_widgets.cpp",
		"imstb_rectpack.h",
		"imstb_textedit.h",
		"imstb_truetype.h",
		"imgui_demo.cpp",

        "backends/imgui_impl_glfw.h",
        "backends/imgui_impl_glfw.cpp",
        "backends/imgui_impl_opengl3.h",
        "backends/imgui_impl_opengl3.cpp"
	}

	includedirs
	{
		"%{prj.name}/",
		"%{prj.name}/backends",
        "../GLFW/include"
	}
    
	links 
	{ 
		"GLFW",
		"opengl32.lib"
	}

	filter "system:windows"
		systemversion "latest"
		cppdialect "C++17"

	filter "system:linux"
		pic "On"
		systemversion "latest"
		cppdialect "C++17"

	filter "configurations:Debug"
		runtime "Debug"
		symbols "on"

	filter "configurations:Release"
		runtime "Release"
		optimize "on"
