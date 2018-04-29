#pragma once

/// <summary>
/// Platform independent macro definistions for API export and types.
/// </summary>

#if defined _MSC_VER
// -----------------------------------------------------------------------------
// Microsoft compiler
// -----------------------------------------------------------------------------

// Export macro
#ifdef ATB_COMMON_API_EXPORT
// If windows and no definistion of ATB_NETWORKING_API
#define ATB_COMMON_API __declspec(dllexport)
#else
#define ATB_COMMON_API __declspec(dllimport)
#endif

#elif defined(__GNUC__) || defined(__GNUG__)
// -----------------------------------------------------------------------------
// GCC / G++
// -----------------------------------------------------------------------------

// If not windows. It is linux
#define ATB_COMMON_API
#endif