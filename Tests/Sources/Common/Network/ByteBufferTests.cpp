#include <catch2/catch_test_macros.hpp>

#include <Common/Network/ByteBuffer.hpp>

TEST_CASE("ByteBuffer Write and Read Multiple", "[ByteBuffer]")
{
	Nb::Network::ByteBuffer buffer;

	buffer.WriteMultiple(std::uint8_t{1}, std::uint16_t{2}, std::uint32_t{3});

	REQUIRE(buffer.Size() == (1 + 2 + 4));
	REQUIRE(buffer.Position() == 0);

	// auto result = buffer.ReadMultiple<std::uint8_t, std::uint16_t, std::uint32_t>();
	// REQUIRE(result.has_value());
	//
	// auto [a, b, c] = *result;
	// REQUIRE(a == 1);
	// REQUIRE(b == 2);
	// REQUIRE(c == 3);
	//
	// REQUIRE(buffer.Position() == (1 + 2 + 4));
}

TEST_CASE("ByteBuffer Insufficient Data", "[ByteBuffer]")
{
	Nb::Network::ByteBuffer buffer;

	buffer.WriteMultiple(std::uint8_t{1}, std::uint16_t{2});

	// auto result = buffer.ReadMultiple<std::uint8_t, std::uint16_t, std::uint32_t>();
	// REQUIRE(!result.has_value());
	// REQUIRE(result.error() == Nb::Network::ByteBuffer::Error::InsufficientData);
}

TEST_CASE("ByteBuffer Empty Data", "[ByteBuffer]")
{
	Nb::Network::ByteBuffer buffer;

	REQUIRE(buffer.Empty());
	REQUIRE(buffer.Size() == 0);
	REQUIRE(buffer.Position() == 0);
	REQUIRE(!buffer.HasRemaining());

	auto result = buffer.Read<uint8_t>();
	REQUIRE(!result.has_value());
	REQUIRE(result.error() == Nb::Network::ByteBuffer::Error::InsufficientData);

	REQUIRE(buffer.Empty());
	REQUIRE(buffer.Size() == 0);
	REQUIRE(buffer.Position() == 0);
	REQUIRE(!buffer.HasRemaining());
}

TEST_CASE("ByteBuffer Serialize String", "[ByteBuffer]")
{
	Nb::Network::ByteBuffer buffer;

	const std::string testString = "Hello, ByteBuffer!";
	buffer.WriteString(testString);

	buffer.Seek(0);
	auto result = buffer.ReadString();
	REQUIRE(result.has_value());
	REQUIRE(*result == testString);

	REQUIRE(!buffer.HasRemaining());
}

TEST_CASE("ByteBuffer Write and Read Bytes", "[ByteBuffer]")
{
	Nb::Network::ByteBuffer buffer;

	const std::vector<std::uint8_t> testData = {0x01, 0x02, 0x03, 0x04, 0x05};
	buffer.WriteBytes(testData);

	buffer.Seek(0);
	auto result = buffer.ReadBytes(testData.size());
	REQUIRE(result.has_value());
	REQUIRE(std::equal(result->begin(), result->end(), testData.begin()));

	REQUIRE(!buffer.HasRemaining());
}
