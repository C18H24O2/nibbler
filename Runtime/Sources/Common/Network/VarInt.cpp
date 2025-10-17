#include <Common/Network/VarInt.hpp>

#include <algorithm>

namespace Nb::Common::Network
{
	std::expected<std::int32_t, VarInt::Error> VarInt::Read(ByteBuffer& buffer) noexcept
	{
		std::int32_t result = 0;
		std::size_t bytes_read = 0;

		while (bytes_read < MAX_BYTES) {
			auto byte_result = buffer.Read<std::uint8_t>();
			if (!byte_result) {
				return std::unexpected(Error::InsufficientData);
			}

			std::uint8_t byte = *byte_result;
			result |= (byte & 0x7F) << (7 * bytes_read);
			bytes_read++;

			if ((byte & 0x80) == 0) {
				return result;
			}
		}

		return std::unexpected(Error::TooLong);
	}

	std::expected<std::int64_t, VarInt::Error> VarInt::ReadLong(ByteBuffer& buffer) noexcept
	{
		std::int64_t result = 0;
		std::size_t bytes_read = 0;

		while (bytes_read < MAX_BYTES_LONG) {
			auto byte_result = buffer.Read<std::uint8_t>();
			if (!byte_result) {
				return std::unexpected(Error::InsufficientData);
			}

			std::uint8_t byte = *byte_result;
			result |= static_cast<std::int64_t>(byte & 0x7F) << (7 * bytes_read);
			bytes_read++;

			if ((byte & 0x80) == 0) {
				return result;
			}
		}

		return std::unexpected(Error::TooLong);
	}

	void VarInt::Write(std::int32_t value, ByteBuffer& buffer) noexcept
	{
		std::uint32_t uvalue = static_cast<std::uint32_t>(value);

		do {
			std::uint8_t byte = uvalue & 0x7F;
			uvalue >>= 7;

			if (uvalue != 0) {
				byte |= 0x80;
			}

			buffer.Write(byte);
		} while (uvalue != 0);
	}

	void VarInt::WriteLong(std::int64_t value, ByteBuffer& buffer) noexcept
	{
		std::uint64_t uvalue = static_cast<std::uint64_t>(value);

		do {
			std::uint8_t byte = uvalue & 0x7F;
			uvalue >>= 7;

			if (uvalue != 0) {
				byte |= 0x80;
			}

			buffer.Write(byte);
		} while (uvalue != 0);
	}
} // namespace Nb::Common::Network
