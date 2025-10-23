#ifndef NIBBLER_NETWORK_SERIALIZER_VARINT_HPP
#define NIBBLER_NETWORK_SERIALIZER_VARINT_HPP

#include <cstdint>

#include <Common/Network/ByteBuffer.hpp>

namespace Nb::Network::Serializers
{
	DEFINE_SERIALIZER(VarInt, std::int32_t);
	DEFINE_SERIALIZER(VarLong, std::int64_t);
}

#endif
