#ifndef NIBBLER_NETWORK_BYTEBUFFER_HPP
#define NIBBLER_NETWORK_BYTEBUFFER_HPP

#include <bit>
#include <concepts>
#include <cstdint>
#include <expected>
#include <iomanip>
#include <iostream>
#include <iterator>
#include <ostream>
#include <ranges>
#include <span>
#include <string>
#include <string_view>
#include <vector>

#include <Common/Utils/NonCopyable.h>

namespace Nb::Common::Network
{
	class ByteBuffer : public Common::NonCopyable
	{
		public:
			enum class Error
			{
				InsufficientData,
				BufferOverflow,
				InvalidStringLength
			};

		public:
			ByteBuffer();
			explicit ByteBuffer(std::size_t defaultSize);
			virtual ~ByteBuffer() = default;

		public:
			template<std::integral T>
			void Write(T value, std::endian endian = std::endian::big) noexcept
			{
				if (endian != std::endian::native) {
					value = Byteswap(value);
				}

				const auto bytes = std::bit_cast<std::array<std::uint8_t, sizeof(T)>>(value);
				m_buffer.append_range(bytes);
			}

			template<std::floating_point T>
			void Write(T value, std::endian endian = std::endian::big) noexcept
			{
				using IntType = std::conditional_t<sizeof(T) == 4, std::uint32_t, std::uint64_t>;
				Write(std::bit_cast<IntType>(value), endian);
			}

			void WriteString(std::string_view str) noexcept;
			void WriteBytes(std::span<const std::uint8_t> data) noexcept;

			template<std::integral T>
			[[nodiscard]] std::expected<T, Error> Read(std::endian endian = std::endian::big) noexcept
			{
				if (m_position + sizeof(T) > m_buffer.size()) {
					return std::unexpected(Error::InsufficientData);
				}

				std::array<std::uint8_t, sizeof(T)> bytes;
				std::ranges::copy_n(m_buffer.begin() + m_position, sizeof(T), bytes.begin());
				m_position += sizeof(T);

				T value = std::bit_cast<T>(bytes);
				if (endian != std::endian::native) {
					value = Byteswap(value);
				}

				return value;
			}

			template<std::floating_point T>
			[[nodiscard]] std::expected<T, Error> Read(std::endian endian = std::endian::big) noexcept
			{
				using IntType = std::conditional_t<sizeof(T) == 4, std::uint32_t, std::uint64_t>;

				auto int_result = Read<IntType>(endian);
				if (!int_result) {
					return std::unexpected(int_result.error());
				}

				return std::bit_cast<T>(*int_result);
			}

			[[nodiscard]] std::expected<std::string, Error> ReadString() noexcept;
			[[nodiscard]] std::expected<std::span<const std::uint8_t>, Error> ReadBytes(std::size_t count) noexcept;

			template<typename... Types>
			[[nodiscard]] std::expected<std::tuple<Types...>, Error> ReadMultiple(std::endian endian = std::endian::big) noexcept
			{
				std::tuple<Types...> result;
				Error error;
				bool success = ReadMultipleImpl<0, Types...>(result, error, endian);
				if (!success) {
					return std::unexpected(error);
				}
				return result;
			}

			template<std::integral T>
			[[nodiscard]] std::expected<T, Error> Peek(std::endian endian = std::endian::big) const noexcept
			{
				if (m_position + sizeof(T) > m_buffer.size()) {
					return std::unexpected(Error::InsufficientData);
				}

				std::array<std::uint8_t, sizeof(T)> bytes;
				std::ranges::copy_n(m_buffer.begin() + m_position, sizeof(T), bytes.begin());

				T value = std::bit_cast<T>(bytes);
				if (endian != std::endian::native) {
					value = Byteswap(value);
				}

				return value;
			}

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

			friend std::ostream& operator<<(std::ostream& os, const ByteBuffer::Error& error);
			friend std::ostream& operator<<(std::ostream& os, const ByteBuffer& buffer);

		private:
			std::vector<std::uint8_t> m_buffer;
			std::size_t m_position{0};

			template<std::integral T>
			[[nodiscard]] static constexpr T Byteswap(T value) noexcept
			{
				if constexpr (sizeof(T) == 1) {
					return value;
				} else {
					return std::byteswap(value);
				}
			}

			template<std::size_t Index, typename... Types>
			bool ReadMultipleImpl(std::tuple<Types...>& result, Error& error, std::endian endian) noexcept
			{
				if constexpr (Index < sizeof...(Types)) {
					using CurrentType = std::tuple_element_t<Index, std::tuple<Types...>>;

					if constexpr (std::same_as<CurrentType, std::string>) {
						auto value = ReadString();
						if (!value) {
							error = value.error();
							return false;
						}
						std::get<Index>(result) = std::move(*value);
					} else {
						auto value = Read<CurrentType>(endian);
						if (!value) {
							error = value.error();
							return false;
						}
						std::get<Index>(result) = *value;
					}

					return ReadMultipleImpl<Index + 1, Types...>(result, error, endian);
				}
				return true;
			}
	};
} // namespace Nb::Common::Network

#endif // NIBBLER_NETWORK_BYTEBUFFER_HPP
