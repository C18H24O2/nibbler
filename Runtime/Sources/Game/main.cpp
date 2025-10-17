#include <iostream>
#include <Common/Network/ByteBuffer.hpp>
#include <Common/Network/VarInt.hpp>

using namespace Nb::Common;

int main()
{
	Network::ByteBuffer buffer;

	buffer.Write(std::uint8_t(1));
	buffer.Write(std::uint16_t(2));
	buffer.Write(std::uint32_t(3));

	buffer.Seek(0);
	std::cout << buffer << std::endl;

	if (auto result = buffer.ReadMultiple<std::uint8_t, std::uint16_t, std::uint32_t>()) {
		auto [a, b, c] = *result;
		std::cout << static_cast<int>(a) << " " << b << " " << c << std::endl;
	} else {
		std::cout << result.error() << std::endl;
	}

#define TEST_VARINT(value) \
	buffer.Clear(); \
	Network::VarInt::Write(value, buffer); \
	std::cout << buffer << std::endl; \
	{ \
		auto resul = Network::VarInt::Read(buffer); \
		if (!resul || *resul != value) { \
			std::cout << "Failed to read value " << value << std::endl; \
			exit(1); \
		} else { \
			std::cout << "Read value " << *resul << std::endl; \
		} \
	}

#define TEST_VARLONG(value) \
	buffer.Clear(); \
	Network::VarInt::WriteLong(value, buffer); \
	std::cout << buffer << std::endl; \
	{ \
		auto resul = Network::VarInt::ReadLong(buffer); \
		if (!resul || *resul != value) { \
			std::cout << "Failed to read value " << (long long) value << std::endl; \
			exit(1); \
		} else { \
			std::cout << "Read value " << (long long) *resul << std::endl; \
		} \
	}

	TEST_VARINT(0);
	TEST_VARINT(1);
	TEST_VARINT(127);
	TEST_VARINT(128);
	TEST_VARINT(255);
	TEST_VARINT(256);
	TEST_VARINT(32767);
	TEST_VARINT(32768);
	TEST_VARINT(65535);
	TEST_VARINT(65536);
	TEST_VARINT(2097151);
	TEST_VARINT(2147483647);
	TEST_VARINT(-1);
	TEST_VARINT(-2147483648);

	TEST_VARLONG(0);
	TEST_VARLONG(1);
	TEST_VARLONG(127);
	TEST_VARLONG(128);
	TEST_VARLONG(255);
	TEST_VARLONG(256);
	TEST_VARLONG(32767);
	TEST_VARLONG(32768);
	TEST_VARLONG(65535);
	TEST_VARLONG(65536);
	TEST_VARLONG(2097151);
	TEST_VARLONG(2147483647);
	TEST_VARLONG(-1);
	TEST_VARLONG(-2147483648);

	TEST_VARLONG(4294967295);
	TEST_VARLONG(-4294967296);
	TEST_VARLONG(std::numeric_limits<std::int64_t>::min());
	TEST_VARLONG(std::numeric_limits<std::int64_t>::max());

	return 0;
}
