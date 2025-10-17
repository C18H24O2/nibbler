#ifndef NIBBLER_NETWORK_BYTEBUFFER_INL
#define NIBBLER_NETWORK_BYTEBUFFER_INL

#include <Common/Network/ByteBuffer.hpp>

namespace Nb::Common::Network
{
	template<std::integral T>
	void ByteBuffer::Write(T value, std::endian endian) noexcept
	{
		if (endian != std::endian::native) {
			value = Byteswap(value);
		}

		const auto bytes = std::bit_cast<std::array<std::uint8_t, sizeof(T)>>(value);
		m_buffer.append_range(bytes);
	}

	template<std::floating_point T>
	void ByteBuffer::Write(T value, std::endian endian) noexcept
	{
		using IntType = std::conditional_t<sizeof(T) == 4, std::uint32_t, std::uint64_t>;
		Write(std::bit_cast<IntType>(value), endian);
	}
	template<std::integral T>
	[[nodiscard]] std::expected<T, ByteBuffer::Error> ByteBuffer::Read(std::endian endian) noexcept
	{
		if (m_position + sizeof(T) > m_buffer.size()) {
			return std::unexpected(Error::InsufficientData);
		}

		std::array<std::uint8_t, sizeof(T)> bytes;
		std::ranges::copy_n(m_buffer.begin() + m_position, sizeof(T), bytes.begin());
		m_position += sizeof(T);

		T value = std::bit_cast<T>(bytes);
		if (endian != std::endian::native) {
			value = Byteswap(value);
		}

		return value;
	}

	template<std::floating_point T>
	[[nodiscard]] std::expected<T, ByteBuffer::Error> ByteBuffer::Read(std::endian endian) noexcept
	{
		using IntType = std::conditional_t<sizeof(T) == 4, std::uint32_t, std::uint64_t>;

		auto int_result = Read<IntType>(endian);
		if (!int_result) {
			return std::unexpected(int_result.error());
		}

		return std::bit_cast<T>(*int_result);
	}

	template<typename... Types>
	[[nodiscard]] std::expected<std::tuple<Types...>, ByteBuffer::Error> ByteBuffer::ReadMultiple(std::endian endian) noexcept
	{
		std::tuple<Types...> result;
		Error error;
		bool success = ReadMultipleImpl<0, Types...>(result, error, endian);
		if (!success) {
			return std::unexpected(error);
		}
		return result;
	}

	template<std::integral T>
	[[nodiscard]] std::expected<T, ByteBuffer::Error> ByteBuffer::Peek(std::endian endian) const noexcept
	{
		if (m_position + sizeof(T) > m_buffer.size()) {
			return std::unexpected(Error::InsufficientData);
		}

		std::array<std::uint8_t, sizeof(T)> bytes;
		std::ranges::copy_n(m_buffer.begin() + m_position, sizeof(T), bytes.begin());

		T value = std::bit_cast<T>(bytes);
		if (endian != std::endian::native) {
			value = Byteswap(value);
		}

		return value;
	}

	template<std::integral T>
	[[nodiscard]] constexpr T ByteBuffer::Byteswap(T value) noexcept
	{
		if constexpr (sizeof(T) == 1) {
			return value;
		} else {
			return std::byteswap(value);
		}
	}

	template<std::size_t Index, typename... Types>
	bool ByteBuffer::ReadMultipleImpl(std::tuple<Types...>& result, Error& error, std::endian endian) noexcept
	{
		if constexpr (Index < sizeof...(Types)) {
			using CurrentType = std::tuple_element_t<Index, std::tuple<Types...>>;

			if constexpr (std::same_as<CurrentType, std::string>) {
				auto value = ReadString();
				if (!value) {
					error = value.error();
					return false;
				}
				std::get<Index>(result) = std::move(*value);
			} else {
				auto value = Read<CurrentType>(endian);
				if (!value) {
					error = value.error();
					return false;
				}
				std::get<Index>(result) = *value;
			}

			return ReadMultipleImpl<Index + 1, Types...>(result, error, endian);
		}
		return true;
	}
}

#endif
