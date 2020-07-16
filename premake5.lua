workspace "LasVegasSolver"
   configurations { "Debug", "Release" }

project "LasVegasSolver"
   kind "ConsoleApp"
   language "C++"
   targetdir "bin/%{cfg.buildcfg}"

   files { "**.hpp", "**.cpp" }

   architecture "x86_64"

   filter "configurations:Debug"
      defines { "DEBUG" }
      symbols "On"

   filter "configurations:Release"
      defines { "NDEBUG" }
      optimize "On"