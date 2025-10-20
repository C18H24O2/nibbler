add_repositories("local-repo Xmake")

set_version("0.0.1beta")

add_rules("mode.debug", "mode.release", "mode.releasedbg")
add_rules("plugin.compile_commands.autoupdate", {outputdir = "."})

set_allowedplats("windows", "mingw", "linux", "macosx")
set_allowedmodes("debug", "release")
set_defaultmode("release")

set_project("Nibbler")

if is_mode("debug") then
	add_defines("NB_DEBUG")
elseif is_mode("release") then
	add_defines("NB_RELEASE")
	add_vectorexts("sse", "sse2", "sse3", "ssse3")
end

add_includedirs("Runtime/Includes", "Build")

set_languages("cxx23")

local frontends = {
	GLFWVulkan = {
		option = "vulkan",
		packages = { "vulkan-headers", "kvf", "glfw" },
		custom = function()
			add_defines("GLFW_INCLUDE_NONE")
			add_defines("VK_NO_PROTOTYPES")
			if is_plat("windows", "mingw") then
				add_defines("VK_USE_PLATFORM_WIN32_KHR")
			elseif is_plat("linux") then
				add_defines("VK_USE_PLATFORM_XLIB_KHR")
				add_defines("VK_USE_PLATFORM_WAYLAND_KHR")
				add_packages("libxext", "wayland", { links = {} }) -- we only need X11 headers
			elseif is_plat("macosx") then
				add_defines("VK_USE_PLATFORM_METAL_EXT")
			end
		end
	},
	SDL_GPU = {
		option = "sdlgpu",
		packages = { "libsdl3" },
	},
	Raylib = {
	}
}

local sanitizers = {
	asan = "address",
	lsan = "leak",
	tsan = "thread",
}

for opt, policy in table.orderpairs(sanitizers) do
	option(opt, { description = "Enable " .. opt, default = false })

	if has_config(opt) then
		set_policy("build.sanitizer." .. policy, true)
	end
end

for name, module in pairs(frontends) do
	if module.option then
		option(module.option, { description = "Enables the " .. name .. " frontend", default = true })
		if has_config(module.option) then
			add_requires(table.unpack(module.packages))
		end
	end
end

for name, module in pairs(frontends) do
	if module.option and not has_config(module.option) then
		goto continue
	end

	target("nibbler_" .. name:lower(), function()
		set_kind("shared")

		if has_config("unitybuild") then
			add_rules("c++.unity_build", { batchsize = 6 })
		end

		add_defines("NB_" .. name:upper() .. "_BUILD")
		if is_mode("debug") then
			add_defines("NB_" .. name:upper() .. "_DEBUG")
		end

		for _, ext in ipairs({".h", ".hpp", ".inl"}) do
			add_headerfiles("Runtime/Includes/Common/**" .. ext)
			add_headerfiles("Runtime/Includes/Frontends/" .. name .. "/**" .. ext)
			add_headerfiles("Runtime/Sources/Frontends/" .. name .. "/**" .. ext, { prefixdir = "private", install = false })
			add_includedirs("Build/Frontends/" .. name .. "/**" .. ext, { prefixdir = "private", install = false })
		end


		remove_headerfiles("Runtime/Sources/Frontends/" .. name .. "/Resources/**.h")

		if module.packages then
			add_packages(table.unpack(module.packages))
		end

		if module.public_packages then
			for _, pkg in ipairs(module.public_packages) do
				add_packages(pkg, { public = true })
			end
		end

		if module.deps then
			add_deps(table.unpack(module.deps))
		end

		add_files("Runtime/Sources/Common/**.cpp")
		add_files("Runtime/Sources/Frontends/" .. name .. "/**.cpp")

		if module.custom then
			module.custom()
		end
	end)

	::continue::
end

target("nibbler_server")
	set_kind("binary")
	set_default(false)

	if has_config("unitybuild") then
		add_rules("c++.unity_build", { batchsize = 6 })
	end

	add_defines("NB_GAMESERVER_BUILD")
	if is_mode("debug") then
		add_defines("NB_GAMESERVER_DEBUG")
	end

	for _, ext in ipairs({".h", ".hpp", ".inl"}) do
		add_headerfiles("Runtime/Includes/Common/**" .. ext)
		add_headerfiles("Runtime/Includes/GameServer/**" .. ext)
		add_headerfiles("Runtime/Sources/GameServer/**" .. ext, { prefixdir = "private", install = false })
	end

	add_files("Runtime/Sources/Common/**.cpp")
	add_files("Runtime/Sources/GameServer/**.cpp")
target_end()

target("nibbler")
	set_kind("binary")

	if has_config("unitybuild") then
		add_rules("c++.unity_build", { batchsize = 6 })
	end

	add_defines("NB_GAME_BUILD")
	if is_mode("debug") then
		add_defines("NB_GAME_DEBUG")
	end

	for _, ext in ipairs({".h", ".hpp", ".inl"}) do
		add_headerfiles("Runtime/Includes/Common/**" .. ext)
		add_headerfiles("Runtime/Includes/Game/**" .. ext)
		add_headerfiles("Runtime/Sources/Game/**" .. ext, { prefixdir = "private", install = false })
	end

	add_files("Runtime/Sources/Common/**.cpp")
	add_files("Runtime/Sources/Game/**.cpp")

	for name, module in pairs(frontends) do
		if module.option and has_config(module.option) then
			add_deps("nibbler_" .. name:lower())
		end
	end
target_end()

add_requires("catch2")

target("nibbler_tests")
    set_kind("binary")
	set_default(false)

	if has_config("unitybuild") then
		add_rules("c++.unity_build", { batchsize = 6 })
	end

    add_packages("catch2")

    add_defines("NB_TESTS_BUILD")
    if is_mode("debug") then
        add_defines("NB_TESTS_DEBUG")
    end

    add_includedirs("Runtime/Includes")

    add_files("Tests/Sources/**.cpp")
	add_files("Runtime/Sources/Common/**.cpp")

    add_tests("default")
target_end()