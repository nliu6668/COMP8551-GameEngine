workspace "GameEngine"
	architecture "x64"

	configurations
	{
		"Debug",
		"Release",
		"Dist"
	}

project "GameEngine"
	location "GameEngine"
	kind "SharedLib"
	language "C++"

	files
	{
		"Dependencies/GLAD/include/glad/glad.h",
		"Dependencies/GLAD/include/KHR/khrplatform.h",
		"Dependencies/GLAD/src/glad.c"
	}

	includedirs
	{
		"%{prj.name}/Dependencies/GLAD/include",
		"%{prj.name}/Dependencies/GLFW/include"
	}

	libdirs
	{
		"%{prj.name}/Dependencies/GLFW/lib-vc2015"
	}

	filter "system:windows"
        systemversion "latest"
		links { "glfw3" }

    filter "configurations:Debug"
        runtime "Debug"
        symbols "on"

    filter "configurations:Release"
        runtime "Release"
        optimize "on"