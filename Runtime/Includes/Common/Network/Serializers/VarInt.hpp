#ifndef NIBBLER_NETWORK_SERIALIZER_VARINT_HPP
#define NIBBLER_NETWORK_SERIALIZER_VARINT_HPP

#include <cstdint>
#include <Common/Network/ByteBuffer.hpp>

namespace Nb::Network::Serializers
{
	struct VarInt
	{
		using Error = ByteBuffer::Error;
		using ValueType = std::int32_t;

		static void
	};
}

#endif