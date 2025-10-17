#ifndef NIBBLER_COMMON_NON_COPYABLE_HPP
#define NIBBLER_COMMON_NON_COPYABLE_HPP

namespace Nb::Common
{
	class NonMovable
	{
		protected:
			NonMovable() = default;
			virtual ~NonMovable() = default;

		public:
			NonMovable(const NonMovable&) = default;
			NonMovable(NonMovable&&) noexcept = delete;
			NonMovable& operator=(const NonMovable&) = default;
			NonMovable& operator=(NonMovable&&) noexcept = delete;
	};
}

#endif
