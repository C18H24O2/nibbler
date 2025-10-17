#ifndef NIBBLER_COMPILATION_PROFILE_HPP
#define NIBBLER_COMPILATION_PROFILE_HPP

#include <climits>
#include <cstdint>

// Try to identify the compiler
#if defined(__BORLANDC__)
	#define NB_COMPILER_BORDLAND
#elif defined(__clang__)
	#define NB_COMPILER_CLANG
	#ifdef __MINGW32__
		#define NB_COMPILER_MINGW
		#ifdef __MINGW64_VERSION_MAJOR
			#define NB_COMPILER_MINGW_W64
		#endif
	#endif
#elif defined(__GNUC__) || defined(__MINGW32__)
	#define NB_COMPILER_GCC
	#ifdef __MINGW32__
		#define NB_COMPILER_MINGW
		#ifdef __MINGW64_VERSION_MAJOR
			#define NB_COMPILER_MINGW_W64
		#endif
	#endif
#elif defined(__INTEL_COMPILER) || defined(__ICL)
	#define NB_COMPILER_INTEL
#elif defined(_MSC_VER)
	#define NB_COMPILER_MSVC
#else
	#define NB_COMPILER_UNKNOWN
	#warning "This compiler is not fully supported"
#endif

#if defined(_WIN32) || defined(__CYGWIN__)
	#define NB_PLAT_WINDOWS
#elif defined(__linux__)
	#define NB_PLAT_LINUX
	#define NB_PLAT_UNIX
#elif defined(__APPLE__) && defined(__MACH__)
	#define NB_PLAT_MACOS
#elif defined(unix) || defined(__unix__) || defined(__unix)
	#define NB_PLAT_UNIX
#else
	#error "Unknown environment (not Windows, not Linux, not MacOS, not Unix)"
#endif

#if defined(__GNUC__) || (defined(__MWERKS__) && (__MWERKS__ >= 0x3000)) || (defined(__ICC) && (__ICC >= 600)) || defined(__ghs__)
	#define NB_FUNC_SIG __PRETTY_FUNCTION__
#elif defined(__DMC__) && (__DMC__ >= 0x810)
	#define NB_FUNC_SIG __PRETTY_FUNCTION__
#elif (defined(__FUNCSIG__) || (_MSC_VER))
	#define NB_FUNC_SIG __FUNCSIG__
#elif (defined(__INTEL_COMPILER) && (__INTEL_COMPILER >= 600)) || (defined(__IBMCPP__) && (__IBMCPP__ >= 500))
	#define NB_FUNC_SIG __FUNCTION__
#elif defined(__BORLANDC__) && (__BORLANDC__ >= 0x550)
	#define NB_FUNC_SIG __FUNC__
#elif defined(__STDC_VERSION__) && (__STDC_VERSION__ >= 199901)
	#define NB_FUNC_SIG __func__
#elif defined(__cplusplus) && (__cplusplus >= 201103)
	#define NB_FUNC_SIG __func__
#else
	#define NB_FUNC_SIG "Unknown function"
#endif

#ifdef NB_PLAT_WINDOWS
	#ifdef NB_COMPILER_MSVC
		#define NB_EXPORT_API __declspec(dllexport)
		#define NB_IMPORT_API __declspec(dllimport)
	#elif defined(NB_COMPILER_GCC)
		#define NB_EXPORT_API __attribute__((dllexport))
		#define NB_IMPORT_API __attribute__((dllimport))
	#else
		#define NB_EXPORT_API
		#define NB_IMPORT_API
	#endif
#elif defined(NB_COMPILER_GCC)
	#define NB_EXPORT_API __attribute__((visibility("default")))
	#define NB_IMPORT_API __attribute__((visibility("default")))
#else
	#define NB_EXPORT_API
	#define NB_IMPORT_API
#endif

#if defined(NB_PLAT_WINDOWS)
	#define NB_LIB_EXTENSION ".dll"
#elif defined(NB_PLAT_UNIX)
	#define NB_LIB_EXTENSION ".so"
#elif defined(NB_PLAT_MACOS)
	#define NB_LIB_EXTENSION ".dylib"
#elif defined(NB_PLAT_WASM)
	#define NB_LIB_EXTENSION ".wasm"
#endif

#ifdef NB_COMPILER_MSVC
	#define NB_LIB_PREFIX ""
#else
	#define NB_LIB_PREFIX "lib"
#endif

#if !defined(NB_NO_FORCEINLINE) && !defined(NB_FORCEINLINE)
	#if defined(NB_COMPILER_CLANG) || defined(NB_COMPILER_GCC)
		#define NB_FORCEINLINE __attribute__((always_inline)) inline
	#elif defined(NB_COMPILER_MSVC)
		#define NB_FORCEINLINE __forceinline
	#else
		#define NB_FORCEINLINE inline
	#endif
#endif

#if !defined(NB_NO_WENB) && !defined(NB_WENB)
	#if defined(NB_COMPILER_CLANG) || defined(NB_COMPILER_GCC)
		#define NB_WEAK __attribute__((weak))
	#else
		#define NB_WEAK
	#endif
#endif

#if defined(__x86_64__) || defined(_M_X64) || defined(__ppc64__)
	#define NB_64BITS
#elif defined(i386) || defined(__i386__) || defined(__i386) || defined(_M_IX86)
	#define NB_32BITS
#elif UINTPTR_MAX == UINT32_MAX
	#define NB_32BITS
#elif UINTPTR_MAX == UINT64_MAX
	#define NB_64BITS
#endif

#define NB_UNUSED_PARAM(x)
#define NB_UNUSED(x) (void)(x)

// Checking common assumptions

#if !defined(NB_32BITS) && !defined(NB_64BITS)
	#error "Nibbler can only run on 32bit or 64bit architectures"
#endif

static_assert(CHAR_BIT == 8, "CHAR_BIT is expected to be 8");

static_assert(sizeof(int8_t)  == 1, "int8_t is not of the correct size" );
static_assert(sizeof(int16_t) == 2, "int16_t is not of the correct size");
static_assert(sizeof(int32_t) == 4, "int32_t is not of the correct size");
static_assert(sizeof(int64_t) == 8, "int64_t is not of the correct size");

static_assert(sizeof(uint8_t)  == 1, "uint8_t is not of the correct size" );
static_assert(sizeof(uint16_t) == 2, "uint16_t is not of the correct size");
static_assert(sizeof(uint32_t) == 4, "uint32_t is not of the correct size");
static_assert(sizeof(uint64_t) == 8, "uint64_t is not of the correct size");

#endif
