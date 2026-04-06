/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   Identifier.hpp                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kiroussa <oss@dynamicdispat.ch>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/03/25 16:27:08 by kiroussa          #+#    #+#             */
/*   Updated: 2026/04/06 11:22:19 by kiroussa         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#pragma once
 
#include <compare>
#include <expected>
#include <format>
#include <functional>
#include <string>
#include <string_view>

#include <Nibbler/Util/Canonical.hpp>
 
namespace Nibbler::Util
{
 
enum class IdentifierError
{
	EmptyNamespace,
	EmptyPath,
	MissingSeparator,
	PathTooLong,
	PathInvalidCharacter,
	NamespaceTooLong,
	NamespaceInvalidCharacter,
};

class Identifier
{
public:
	DEFAULT_CANONICAL_MEMBERS(Identifier);
	constexpr Identifier() noexcept 
	{
		std::size_t i = 0;
		for (char c : DEFAULT_NAMESPACE)
			buffer[i++] = c;
		separatorIndex = DEFAULT_NAMESPACE.size();
		for (char c : "unset_identifier")
			buffer[i++] = c;
		totalLength = i;
	}

	[[nodiscard]] static constexpr std::expected<Identifier, IdentifierError>
		From(std::string_view ns, std::string_view path)
	{
		if (ns.empty())
			return std::unexpected(IdentifierError::EmptyNamespace);
		if (path.empty())
			return std::unexpected(IdentifierError::EmptyPath);
		if (ns.size() > MAX_NAMESPACE_LENGTH)
			return std::unexpected(IdentifierError::NamespaceTooLong);
		if (!IsValidNamespace(ns))
			return std::unexpected(IdentifierError::NamespaceInvalidCharacter);
		if (path.find(SEPARATOR) != std::string_view::npos)
			return std::unexpected(IdentifierError::PathInvalidCharacter);
		if (ns.size() + SEPARATOR.size() + path.size() > MAX_TOTAL_LENGTH)
			return std::unexpected(IdentifierError::PathTooLong);

		return Identifier(ns, path);
	}

	[[nodiscard]] static constexpr std::expected<Identifier, IdentifierError>
		From(std::string_view combined)
	{
		const std::size_t sep = combined.find(':');

		if (sep == std::string_view::npos)
			return std::unexpected(IdentifierError::MissingSeparator);
		if (sep == 0)
			return std::unexpected(IdentifierError::EmptyNamespace);
		if (sep == combined.size() - 1)
			return std::unexpected(IdentifierError::EmptyPath);
		if (combined.find(':', sep + 1) != std::string_view::npos)
			return std::unexpected(IdentifierError::PathInvalidCharacter);

		return From(combined.substr(0, sep), combined.substr(sep + 1));
	}

	[[nodiscard]] constexpr std::string_view Namespace() const noexcept
	{
		return {buffer.data(), separatorIndex};
	}

	[[nodiscard]] constexpr std::string_view Path() const noexcept
	{
		return {buffer.data() + separatorIndex + 1, totalLength - separatorIndex - 1};
	}

	[[nodiscard]] constexpr std::string_view ToString() const noexcept
	{
		return {buffer.data(), totalLength};
	}

	[[nodiscard]] constexpr auto operator<=>(const Identifier& other) const noexcept
	{
		auto result = Namespace() <=> other.Namespace();
		if (result != 0)
			return result;
		return Path() <=> other.Path();
	}

	[[nodiscard]] constexpr bool operator==(const Identifier& other) const noexcept
	{
		return ToString() == other.ToString();
	}

	static constexpr std::string_view DEFAULT_NAMESPACE = "nibbler";
	static constexpr std::string_view SEPARATOR = ":";
	static constexpr std::size_t MAX_NAMESPACE_LENGTH = 64;
	static constexpr std::size_t MAX_PATH_LENGTH = 256;
	static constexpr std::size_t MAX_TOTAL_LENGTH = MAX_NAMESPACE_LENGTH + 1 + MAX_PATH_LENGTH;

private:
	constexpr Identifier(std::string_view ns, std::string_view path) noexcept
	{
		std::size_t i = 0;
		for (char c : ns)
			buffer[i++] = c;
		buffer[i++] = ':';
		for (char c : path)
			buffer[i++] = c;
		totalLength = i;
		separatorIndex = ns.size();
	}

	static constexpr bool IsValidNamespace(std::string_view ns) noexcept
	{
		auto isAlpha = [](char c) {
			return (c >= 'a' && c <= 'z') || (c >= 'A' && c <= 'Z');
		};
		auto isAlnum = [isAlpha](char c) {
			return isAlpha(c) || (c >= '0' && c <= '9');
		};

		if (!isAlpha(ns[0])) return false;
		for (char c : ns.substr(1))
			if (!isAlnum(c) && c != '_') return false;
		return true;
	}

	std::array<char, MAX_TOTAL_LENGTH> buffer{};
	std::size_t totalLength{};
	std::size_t separatorIndex{};
};

}; // namespace Nibbler::Util

template<>
struct std::hash<Nibbler::Util::Identifier>
{
	[[nodiscard]] constexpr std::size_t operator()(const Nibbler::Util::Identifier& id) const noexcept
	{
		return std::hash<std::string_view>{}(id.ToString());
	}
};
 
template<>
struct std::formatter<Nibbler::Util::Identifier>
{
	constexpr auto parse(std::format_parse_context& ctx)
	{
		return ctx.begin();
	}

	[[nodiscard]] constexpr auto format(const Nibbler::Util::Identifier& id, std::format_context& ctx) const
	{
		return std::format_to(ctx.out(), "{}", id.ToString());
	}
};
