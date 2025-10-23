#include <catch2/catch_test_macros.hpp>

#include <Common/Network/Serializers/VarInt.hpp>

using namespace Nb::Network::Serializers;

#include <iostream>

TEST_CASE("VarInt Write and Read", "[VarInt]")
{
	Nb::Network::ByteBuffer buffer;

	buffer.Write<VarInt>(std::int32_t{1});
	buffer.Write<VarInt>(std::int32_t{25565});
	buffer.Write<VarInt>(std::int32_t{-3});
	buffer.Write<VarInt>(std::int32_t{42069});

	std::cout << buffer << std::endl;

	buffer.Seek(0);
	// auto result = buffer.ReadMultiple<VarInt>();
	// 
	// REQUIRE(result.has_value());
	// auto [a, b, c, d] = *result;
	// REQUIRE(a == std::int32_t{1});
	// REQUIRE(b == std::int32_t{25565});
	// REQUIRE(c == std::int32_t{-3});
	// REQUIRE(d == std::int32_t{42069});
}

TEST_CASE("VarLong Write and Read", "[VarInt]")
{
	// Nb::Network::ByteBuffer buffer;
	//
	// buffer.WriteMultiple<VarLong, VarLong, VarLong, VarLong>(std::int64_t{1}, std::int64_t{25565}, std::int64_t{-3}, std::int64_t{42069});
	//
	// buffer.Seek(0);
	// auto result = buffer.ReadMultiple<VarLong>();
	// 
	// REQUIRE(result.has_value());
	// auto [a, b, c, d] = *result;
	// REQUIRE(a == std::int64_t{1});
	// REQUIRE(b == std::int64_t{25565});
	// REQUIRE(c == std::int64_t{-3});
	// REQUIRE(d == std::int64_t{42069});
}
