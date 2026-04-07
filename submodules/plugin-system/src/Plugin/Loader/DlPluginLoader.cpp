/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   DlPluginLoader.cpp                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kiroussa <oss@dynamicdispat.ch>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/04/06 10:56:31 by kiroussa          #+#    #+#             */
/*   Updated: 2026/04/07 03:15:38 by kiroussa         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#if defined(_WIN32)
#define WIN32_LEAN_AND_MEAN
#include <windows.h>
#else
#include <dlfcn.h>
#endif

#include <functional>

#include <Nibbler/Logging/Logger.hpp>
#include <Nibbler/Plugin/Loader/DlPluginLoader.hpp>

namespace Nibbler::Plugin
{

static Logging::Logger logger("DlPluginLoader");

[[nodiscard]] static constexpr bool DlHandleIsValid(PluginHandle handle) noexcept
{
#if defined(_WIN32)
	return handle != nullptr;
#else
	return handle != nullptr;
#endif
}

static constexpr void UnloadImpl(PluginHandle handle) noexcept
{
	if (!DlHandleIsValid(handle))
		return;
#if defined(_WIN32)
	FreeLibrary(handle);
#else
	dlclose(handle);
#endif
}

[[nodiscard]] static constexpr PluginHandle DlOpen(const char* path) noexcept
{
#if defined(_WIN32)
	return LoadLibrary(path);
#else
	return dlopen(path, RTLD_LAZY);
#endif
}

[[nodiscard]] static constexpr void* DlSym(PluginHandle handle, const char* name) noexcept
{
#if defined(_WIN32)
	return GetProcAddress(handle, name);
#else
	return dlsym(handle, name);
#endif
}

std::expected<PluginContainer, PluginLoadError> DlPluginLoader::Load(std::filesystem::path path) noexcept
{
	logger.Trace().Emit("Trying to load plugin file '{}'", path.string());

	PluginHandle handle = DlOpen(path.string().c_str());
	if (!DlHandleIsValid(handle))
	{
		logger.Trace().Emit("Failed to load plugin file '{}'", path.string());
		return std::unexpected(PluginLoadError::LinkerError);
	}
	void *sym = DlSym(handle, PLUGIN_ENTRYPOINT_FUNC_NAME);
	if (!sym)
	{
		UnloadImpl(handle);
		return std::unexpected(PluginLoadError::SymbolNotFound);
	}
	auto fn = reinterpret_cast<Plugin* (*)()>(sym);
	auto plugin = fn();
	if (!plugin)
	{
		UnloadImpl(handle);
		return std::unexpected(PluginLoadError::MissingMetadata);
	}
	PluginContainer container {
		.metadata = plugin->GetMetadata(),
		.plugin = plugin,
		.handle = handle,
	};
	return container;
}

void DlPluginLoader::Unload(PluginContainer& container) noexcept
{
	UnloadImpl(container.handle);
}

}; // namespace Nibbler::Plugin
