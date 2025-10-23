#ifndef NIBBLER_NETWORK_BYTEBUFFER_HPP
#define NIBBLER_NETWORK_BYTEBUFFER_HPP

#include <bit>
#include <concepts>
#include <cstdint>
#include <expected>
#include <ostream>
#include <span>
#include <string>
#include <string_view>
#include <type_traits>
#include <vector>

#include <Common/Utils/NonCopyable.hpp>

#define DEFINE_SERIALIZER(name, type) \
	struct name \
	{ \
		using ValueType = type; \
		static void Serialize(ByteBuffer& buffer, const ValueType& value) noexcept; \
		static std::expected<ValueType, ByteBufferError> Deserialize(ByteBuffer& buffer) noexcept; \
	}

namespace Nb::Network
{
	enum class ByteBufferError
	{
		InsufficientData,
		BufferOverflow,
		InvalidStringLength,
		ValueTooLarge,
	};

	class ByteBuffer;

	template <typename S>
	concept Serializable = requires(ByteBuffer& buffer, const typename S::ValueType& value)
	{
		typename S::ValueType;
		{ S::Serialize(buffer, value) } -> std::same_as<void>;
		{ S::Deserialize(buffer) } -> std::same_as<std::expected<typename S::ValueType, ByteBufferError>>;
	};

	template <typename T>
	concept Primitive = std::is_arithmetic_v<T>;

	template <typename T>
	concept SerializableOrPrimitive = Serializable<T> || Primitive<T>;

	template<typename T>
	concept HasValueType = requires { typename T::ValueType; };

	template<SerializableOrPrimitive T>
	using SerializableValueType = std::conditional_t<HasValueType<T>, typename T::ValueType, T>;

	class ByteBuffer : public Utils::NonCopyable
	{
		using Error = ByteBufferError;

		public:
			explicit ByteBuffer(std::endian endianness = std::endian::big);
			explicit ByteBuffer(std::size_t defaultSize, std::endian endianness = std::endian::big);
			~ByteBuffer() override = default;

		public:
			template <SerializableOrPrimitive T>
			void Write(const SerializableValueType<T>& value) noexcept;

			void WriteString(std::string_view str) noexcept;
			void WriteBytes(std::span<const std::uint8_t> data) noexcept;

			template <SerializableOrPrimitive... Types>
			void WriteMultiple(const SerializableValueType<Types>&... values) noexcept;

		public:
			template <SerializableOrPrimitive T>
			[[nodiscard]] std::expected<SerializableValueType<T>, Error> Read() noexcept;

			[[nodiscard]] std::expected<std::string, Error> ReadString() noexcept;
			[[nodiscard]] std::expected<std::span<const std::uint8_t>, Error> ReadBytes(std::size_t count) noexcept;

			// template <typename... Types>
			// [[nodiscard]] auto ReadMultiple() noexcept -> std::expected<std::tuple<SerializableValueType<Types>...>, Error>;

		public:
			// template <std::integral T>
			// [[nodiscard]] std::expected<T, Error> Peek() const noexcept;

			[[nodiscard]] std::size_t Size() const noexcept;
			[[nodiscard]] std::size_t Position() const noexcept;
			[[nodiscard]] std::size_t Remaining() const noexcept;
			[[nodiscard]] bool Empty() const noexcept;
			[[nodiscard]] bool HasRemaining() const noexcept;

			void ResetPosition() noexcept;
			void Clear() noexcept;
			void Reserve(std::size_t capacity);
			void Seek(std::size_t pos) noexcept;
			void Skip(std::size_t bytes) noexcept;

			[[nodiscard]] std::span<const std::uint8_t> Data() const noexcept;
			[[nodiscard]] std::span<const std::uint8_t> RemainingData() const noexcept;
			[[nodiscard]] const std::uint8_t* Raw() const noexcept;

			[[nodiscard]] std::vector<std::uint8_t> Release() noexcept;

			friend std::ostream& operator<<(std::ostream& os, const Error& error);
			friend std::ostream& operator<<(std::ostream& os, const ByteBuffer& buffer);

		private:
			std::endian m_endian{std::endian::big};
			std::size_t m_position{0};
			std::vector<std::uint8_t> m_buffer;

			template <std::integral T>
			[[nodiscard]] static constexpr T Byteswap(T value) noexcept;

			// template <std::size_t Index, typename... Types>
			// bool ReadMultipleImpl(std::tuple<Types...>& result, Error& error, std::endian endian) noexcept;
	};
}

#include <Common/Network/ByteBuffer.inl>

#endif
