#ifndef USBVIEW_GLOBALS_H_
#define USBVIEW_GLOBALS_H_

#include <windows.h>
#include <commctrl.h>
#include <tchar.h>

#include "version.h"

//*****************************************************************************
// MinGW _tcscat_s replacement
//*****
#ifdef __MINGW32__
#undef _stprintf_s
#undef _vstprintf_s
#undef _tcscat_s
#undef _tcscpy_s
[[maybe_unused]] inline static int stprintf_s_compat(
    LPTSTR buffer,
    size_t bufferCount,   // number of TCHARs, not bytes
    LPCTSTR format,
    ...
)
{
    if (!buffer || !format || bufferCount == 0)
        return -1;

    va_list args;
    va_start(args, format);

    int result;

#if defined(UNICODE) || defined(_UNICODE)
    result = _vsnwprintf(buffer, bufferCount, format, args);
#else
    result = _vsnprintf(buffer, bufferCount, format, args);
#endif

    va_end(args);

    // Ensure null termination (MSVC _stprintf_s guarantee)
    if (result < 0 || (size_t)result >= bufferCount)
    {
        buffer[bufferCount - 1] = _T('\0');
        return -1;
    }

    return result;
}

[[maybe_unused]] inline static int vstprintf_s_compat(
    LPTSTR buffer,
    size_t bufferCount,   // number of TCHARs (not bytes)
    LPCTSTR format,
    va_list args
)
{
    if (!buffer || !format || bufferCount == 0)
        return -1;

    int result;

#if defined(UNICODE) || defined(_UNICODE)
    result = _vsnwprintf(buffer, bufferCount, format, args);
#else
    result = _vsnprintf(buffer, bufferCount, format, args);
#endif

    // MSVC guarantees null-termination
    if (result < 0 || (size_t)result >= bufferCount)
    {
        buffer[bufferCount - 1] = _T('\0');
        return -1;
    }

    return result;
}

[[maybe_unused]] inline static int tcscat_s_compat(
    LPTSTR dest,
    size_t destSize,   // number of TCHARs, not bytes
    LPCTSTR src
)
{
    if (!dest || !src || destSize == 0)
        return EINVAL;

    size_t destLen = _tcslen(dest);
    size_t srcLen  = _tcslen(src);

    if (destLen + srcLen + 1 > destSize)
    {
        // Match MSVC behavior: null-terminate destination
        dest[0] = 0;
        return ERANGE;
    }

    _tcscat(dest, src);
    return 0;
}

[[maybe_unused]] inline static errno_t tcscpy_s_compat(
    LPTSTR dest,
    size_t destCount,   // number of TCHARs, not bytes
    LPCTSTR src
)
{
    if (!dest || !src || destCount == 0)
        return EINVAL;

#if defined(UNICODE) || defined(_UNICODE)
    size_t srcLen = wcslen(src);
#else
    size_t srcLen = strlen(src);
#endif

    if (srcLen + 1 > destCount)
    {
        dest[0] = _T('\0');   // MSVC behavior on overflow
        return ERANGE;
    }

    // Copy including null terminator
#if defined(UNICODE) || defined(_UNICODE)
    memcpy(dest, src, (srcLen + 1) * sizeof(wchar_t));
#else
    memcpy(dest, src, srcLen + 1);
#endif

    return 0;
}

#define _stprintf_s stprintf_s_compat
#define _vstprintf_s vstprintf_s_compat
#define _tcscat_s tcscat_s_compat
#define _tcscpy_s tcscpy_s_compat
#endif // __MINGW32__

//*****************************************************************************
// G L O B A L S
//*****************************************************************************

//
// USBVIEW.C
//

extern BOOL gDoConfigDesc;

//
// ENUM.C
//

extern PCTSTR ConnectionStatuses[];

// Both
extern int TotalHubs;

#endif // USBVIEW_GLOBALS_H_
