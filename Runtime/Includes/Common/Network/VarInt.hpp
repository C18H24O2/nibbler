#ifndef NIBBLER_NETWORK_VARINT_HPP
#define NIBBLER_NETWORK_VARINT_HPP

#include <cstdint>
#include <expected>
#include <span>
#include <vector>

#include <Common/Network/ByteBuffer.hpp>
#include <Common/Utils/NonCopyable.h>

namespace Nb::Common::Network
{
	class VarInt : public Common::NonCopyable
	{
		public:
			static constexpr std::size_t MAX_BYTES = 5;
			static constexpr std::size_t MAX_BYTES_LONG = 10;

			enum class Error
			{
				TooLong,
				InsufficientData
			};

		public:
			VarInt() = default;
			~VarInt() = default;

		public:
			[[nodiscard]] static std::expected<std::int32_t, VarInt::Error> Read(ByteBuffer& buffer) noexcept;
			[[nodiscard]] static std::expected<std::int64_t, VarInt::Error> ReadLong(ByteBuffer& buffer) noexcept;

			static void Write(std::int32_t value, ByteBuffer& buffer) noexcept;
			static void WriteLong(std::int64_t value, ByteBuffer& buffer) noexcept;

			friend std::ostream& operator<<(std::ostream& os, const VarInt& varint);
			friend std::ostream& operator<<(std::ostream& os, const VarInt::Error& error);
	};
}

#endif // NIBBLER_NETWORK_VARINT_HPP
