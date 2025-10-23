#include <Common/Network/Serializers/VarInt.hpp>

namespace Nb::Network::Serializers
{
	constexpr static auto SEGMENT_BITS = 0x7F;
	constexpr static auto CONTINUE_BIT = 0x80;

	template <std::integral T, std::size_t MaxBits, typename E>
	constexpr static std::expected<T, E> ReadVarIntegral(ByteBuffer& buffer) noexcept
	{
		T value = 0;
		auto pos = 0;
		std::int8_t currentByte;

		while (true)
		{
			auto result = buffer.Read<std::int8_t>();
			if (!result.has_value())
			{
				return result;
			}
			currentByte = *result;

			value |= ((T)(currentByte & SEGMENT_BITS)) << pos;
			if ((currentByte & CONTINUE_BIT) == 0)
			{
				break;
			}
			pos += 7;
			if (pos > MaxBits)
			{
				return std::unexpected(ByteBufferError::ValueTooLarge);
			}
		}

		return value;
	}

	template <std::integral T>
	constexpr static void WriteVarIntegral(ByteBuffer& buffer, T& value) noexcept
	{
		while (true)
		{
			if ((value & ~((T) SEGMENT_BITS)) == 0)
			{
				buffer.Write(std::uint8_t(value));
				break;
			}
			
			buffer.Write(std::uint8_t((value & SEGMENT_BITS) | CONTINUE_BIT));
			value >>= 7;
		}
	}

	void VarInt::Serialize(ByteBuffer& buffer, const VarInt::ValueType& value) noexcept { WriteVarIntegral<VarInt::ValueType>(buffer, value); }
	std::expected<VarInt::ValueType, VarInt::Error> VarInt::Deserialize(ByteBuffer& buffer) noexcept { return ReadVarIntegral<VarInt::ValueType, 31, VarInt::Error>(buffer); }

	void VarLong::Serialize(ByteBuffer& buffer, const VarLong::ValueType& value) noexcept { WriteVarIntegral<VarLong::ValueType>(buffer, value); }
	std::expected<VarLong::ValueType, VarLong::Error> VarLong::Deserialize(ByteBuffer& buffer) noexcept { return ReadVarIntegral<VarLong::ValueType, 63, VarLong::Error>(buffer); }
}
