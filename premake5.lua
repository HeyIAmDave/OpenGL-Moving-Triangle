workspace "OpenGL"
	architecture "x86"
	
	configurations
	{
		"Debug",
		"Release"
	}
	
outputdir = "%{cfg.buildcfg}"

project "OpenGL_Triangle"
	location "OpenGL_Triangle"
	kind "ConsoleApp"
	language "C++"
	
	targetdir("bin/%{cfg.buildcfg}/%{prj.name}");
	objdir("obj/%{cfg.buildcfg}/%{prj.name}");
	
	files
	{
		"%{prj.name}/src/**.h",
		"%{prj.name}/src/**.cpp"
	}
	
	links
	{
		"opengl32.lib",
		"glfw3.lib",
		"glad.lib"
	}
	
	includedirs { "deps/include" }
	libdirs { "deps/lib/%{cfg.buildcfg}" }
	
	filter "system:windows"
		cppdialect "C++17"
		systemversion "latest"