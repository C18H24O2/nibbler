#include <Common/Network/ByteBuffer.hpp>

#include <algorithm>
#include <iomanip>

namespace Nb::Network
{
	ByteBuffer::ByteBuffer(const std::size_t defaultSize)
	{
		m_buffer.reserve(defaultSize);
	}

	void ByteBuffer::WriteString(std::string_view str) noexcept
	{
		Write(static_cast<std::uint32_t>(str.size()));
		m_buffer.append_range(str);
	}

	void ByteBuffer::WriteBytes(std::span<const std::uint8_t> data) noexcept
	{
		m_buffer.append_range(data);
	}

	std::expected<std::string, ByteBuffer::Error> ByteBuffer::ReadString() noexcept
	{
		auto length_result = Read<std::uint32_t>();
		if (!length_result)
		{
			return std::unexpected(length_result.error());
		}

		const auto length = *length_result;
		if (m_position + length > m_buffer.size())
		{
			return std::unexpected(Error::InsufficientData);
		}

		std::string result(m_buffer.begin() + m_position, m_buffer.begin() + m_position + length);
		m_position += length;
		return result;
	}

	std::expected<std::span<const std::uint8_t>, ByteBuffer::Error> ByteBuffer::ReadBytes(const std::size_t count) noexcept
	{
		if (m_position + count > m_buffer.size())
		{
			return std::unexpected(Error::InsufficientData);
		}

		auto result = std::span{m_buffer}.subspan(m_position, count);
		m_position += count;
		return result;
	}

	std::size_t ByteBuffer::Size() const noexcept
	{
		return m_buffer.size();
	}

	std::size_t ByteBuffer::Position() const noexcept
	{
		return m_position;
	}

	std::size_t ByteBuffer::Remaining() const noexcept
	{
		return m_buffer.size() - m_position;
	}

	bool ByteBuffer::Empty() const noexcept
	{
		return m_buffer.empty();
	}

	bool ByteBuffer::HasRemaining() const noexcept
	{
		return m_position < m_buffer.size();
	}

	void ByteBuffer::ResetPosition() noexcept
	{
		m_position = 0;
	}

	void ByteBuffer::Clear() noexcept
	{
		m_buffer.clear();
		m_position = 0;
	}

	void ByteBuffer::Reserve(const std::size_t capacity)
	{
		m_buffer.reserve(capacity);
	}

	void ByteBuffer::Seek(const std::size_t pos) noexcept
	{
		m_position = std::min(pos, m_buffer.size());
	}

	void ByteBuffer::Skip(const std::size_t bytes) noexcept
	{
		m_position = std::min(m_position + bytes, m_buffer.size());
	}

	std::span<const std::uint8_t> ByteBuffer::Data() const noexcept
	{
		return m_buffer;
	}

	std::span<const std::uint8_t> ByteBuffer::RemainingData() const noexcept
	{
		return std::span{m_buffer}.subspan(m_position);
	}

	const std::uint8_t* ByteBuffer::Raw() const noexcept
	{
		return m_buffer.data();
	}

	std::vector<std::uint8_t> ByteBuffer::Release() noexcept
	{
		m_position = 0;
		return std::move(m_buffer);
	}

	std::ostream& operator<<(std::ostream& os, const ByteBuffer::Error& error)
	{
		switch (error)
		{
			case ByteBuffer::Error::InsufficientData:
				os << "InsufficientData";
				break;
			case ByteBuffer::Error::BufferOverflow:
				os << "BufferOverflow";
				break;
			case ByteBuffer::Error::InvalidStringLength:
				os << "InvalidStringLength";
				break;
			default:
				os << "Unknown";
				break;
		}
		return os;
	}

	std::ostream& operator<<(std::ostream& os, const ByteBuffer& buffer)
	{
		os << "ByteBuffer{ ";
		const auto flags = os.flags();
                const auto fill = os.fill();
		const auto width = os.width();

		for (auto it = buffer.m_buffer.begin(); it != buffer.m_buffer.end(); ++it)
		{
			if (it == buffer.m_buffer.begin() + buffer.m_position)
			{
				os << "*";
			}
			os << std::hex << std::setfill('0') << std::setw(2) << static_cast<int>(*it) << " ";
		}
		os << "}";

		os.flags(flags);
		os.fill(fill);
		os.width(width);
		return os;
	}
}
