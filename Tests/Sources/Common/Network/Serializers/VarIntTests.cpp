#include <catch2/catch_test_macros.hpp>

#include <Common/Network/Serializers/VarInt.hpp>

using namespace Nb::Network;
using namespace Nb::Network::Serializers;

#include <iostream>

TEST_CASE("VarInt Write and Read", "[VarInt]")
{
	ByteBuffer buffer;
	auto nums = std::vector<std::int32_t>{0, 1, 2, 127, 128, 255, 25565, 2097151, std::numeric_limits<std::int32_t>::max(), -1, std::numeric_limits<std::int32_t>::min()};

	for (auto i : nums)
	{
		buffer.Write<VarInt>(i);
	}

	std::stringstream ss;
	ss << buffer;
	REQUIRE(ss.str() == "ByteBuffer{ *00 01 02 7f 80 01 ff 01 dd c7 01 ff ff 7f ff ff ff ff 07 ff ff ff ff 0f 80 80 80 80 08 }");

	buffer.Seek(0);

	for (auto i : nums)
	{
		auto result = buffer.Read<VarInt>();
		REQUIRE(result.has_value());
		REQUIRE(*result == i);
	}
	auto result = buffer.Read<VarInt>();
	REQUIRE(!result.has_value());
	REQUIRE(result.error() == ByteBufferError::InsufficientData);
}

TEST_CASE("VarLong Write and Read", "[VarInt]")
{
	ByteBuffer buffer;
	auto nums = std::vector<std::int64_t>{0, 1, 2, 127, 128, 255, 25565, 2097151, std::numeric_limits<std::int32_t>::max(), std::numeric_limits<std::int64_t>::max(), -1, std::numeric_limits<std::int32_t>::min(), std::numeric_limits<std::int64_t>::min()};

	for (auto i : nums)
	{
		buffer.Write<VarLong>(i);
	}

	std::stringstream ss;
	ss << buffer;
	REQUIRE(ss.str() == "ByteBuffer{ *00 01 02 7f 80 01 ff 01 dd c7 01 ff ff 7f ff ff ff ff 07 ff ff ff ff ff ff ff ff 7f ff ff ff ff ff ff ff ff ff 01 80 80 80 80 f8 ff ff ff ff 01 80 80 80 80 80 80 80 80 80 01 }");

	buffer.Seek(0);
	for (auto i : nums)
	{
		auto result = buffer.Read<VarLong>();
		REQUIRE(result.has_value());
		REQUIRE(*result == i);
	}
	auto result = buffer.Read<VarLong>();
	REQUIRE(!result.has_value());
	REQUIRE(result.error() == ByteBufferError::InsufficientData);
}

TEST_CASE("VarInt Read Valid Unoptimized Data", "[VarInt]")
{
	ByteBuffer buffer;

	buffer.WriteBytes(std::array<std::uint8_t, 3>{0x81, 0x80, 0x00});

	buffer.Seek(0);
	auto result = buffer.Read<VarInt>();
	REQUIRE(result.has_value());
	REQUIRE(*result == 1);

	REQUIRE(!buffer.HasRemaining());
}
