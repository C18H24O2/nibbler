/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   Identifier.hpp                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kiroussa <oss@dynamicdispat.ch>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/03/25 16:27:08 by kiroussa          #+#    #+#             */
/*   Updated: 2026/03/28 11:37:24 by kiroussa         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#pragma once
 
#include <compare>
#include <expected>
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
	PathInvalidCharacter,
	NamespaceTooLong,
	NamespaceInvalidCharacter,
};

class Identifier
{
public:
	DEFAULT_CANONICAL_MEMBERS(Identifier);

	[[nodiscard]] static constexpr std::expected<Identifier, IdentifierError>
		From(std::string_view ns, std::string_view path)
	{
		if (ns.empty())   return std::unexpected(IdentifierError::EmptyNamespace);
		if (path.empty()) return std::unexpected(IdentifierError::EmptyPath);
		if (ns.size() > MAX_NAMESPACE_LENGTH)
			return std::unexpected(IdentifierError::NamespaceTooLong);
		if (!IsValidNamespace(ns))
			return std::unexpected(IdentifierError::NamespaceInvalidCharacter);
		if (path.find(SEPARATOR) != std::string_view::npos)
			return std::unexpected(IdentifierError::PathInvalidCharacter);

		std::string result;
		result.reserve(ns.size() + SEPARATOR.size() + path.size());
		result.append(ns);
		result.append(SEPARATOR);
		result.append(path);

		return Identifier(std::move(result), ns.size());
	}

	[[nodiscard]] static constexpr std::expected<Identifier, IdentifierError>
		From(std::string_view combined)
	{
		const std::size_t sep = combined.find(':');

		if (sep == std::string_view::npos)					 return std::unexpected(IdentifierError::MissingSeparator);
		if (sep == 0)										  return std::unexpected(IdentifierError::EmptyNamespace);
		if (sep == combined.size() - 1)						return std::unexpected(IdentifierError::EmptyPath);
		if (combined.find(':', sep + 1) != std::string_view::npos) return std::unexpected(IdentifierError::PathInvalidCharacter);

		return From(combined.substr(0, sep), combined.substr(sep + 1));
	}

	[[nodiscard]] constexpr std::string_view Namespace() const noexcept
	{
		return std::string_view(combined).substr(0, separatorIndex);
	}

	[[nodiscard]] constexpr std::string_view Path() const noexcept
	{
		return std::string_view(combined).substr(separatorIndex + 1);
	}

	[[nodiscard]] constexpr std::string_view ToString() const noexcept
	{
		return combined;
	}

	[[nodiscard]] constexpr auto operator<=>(const Identifier& other) const noexcept
	{
		return combined <=> other.combined;
	}

	[[nodiscard]] constexpr bool operator==(const Identifier& other) const noexcept
	{
		return combined == other.combined;
	}

	static constexpr std::string_view DEFAULT_NAMESPACE = "nibbler";
	static constexpr std::string_view SEPARATOR = ":";
	static constexpr std::size_t MAX_NAMESPACE_LENGTH = 64;

private:
	constexpr Identifier(std::string combined_, std::size_t separatorIndex_)
		: combined(std::move(combined_)), separatorIndex(separatorIndex_) {}

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

	std::string combined;
	std::size_t separatorIndex;
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
 
