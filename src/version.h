#ifndef USBVIEW_VERSION_H_
#define USBVIEW_VERSION_H_

// This file is for specifying the target windows version, as well as application
// version constants. It is included by both the C sources and the .rc file.

/* Including SDKDDKVer.h defines the highest available Windows platform.
   If you wish to build your application for a previous Windows platform, include WinSDKVer.h and
   set the _WIN32_WINNT macro to the platform you wish to support before including SDKDDKVer.h. */

#ifndef __MINGW32__
 #include <WinSDKVer.h> // Doesn't exist in MinGW
#endif // __MINGW32__

#ifndef _WIN32_WINNT
 // The newer USB declarations that the Windows headers hide at this level
 // come from xhci.h instead.
 #define _WIN32_WINNT 0x0501 // Windows XP
#endif // _WIN32_WINNT
#ifndef _WIN64_WINNT
 #define _WIN64_WINNT 0x0502 // Minimum version for 64 bit, Windows Server 2003
#endif // _WIN64_WINNT
#ifndef _WIN32_IE
 #define _WIN32_IE 0x0501 // Minimum Internet Explorer version for common controls
#endif // _WIN32_IE

#ifndef __MINGW32__
 #include <SDKDDKVer.h> // Doesn't exist in MinGW
#endif // __MINGW32__

// Macro to convert to string
#if !defined(_STRINGIZER) && !defined(STRINGIZE)
 #define _STRINGIZER(in) #in
 #define STRINGIZE(in) _STRINGIZER(in)
#endif // !defined(_STRINGIZER) && !defined(STRINGIZE)

// These next few lines are where we control version number and copyright year.
// Microsoft's last USBView was 2.0; USBViewEx continues from there.
#define USBVIEW_MAJOR_VERSION   2
#define USBVIEW_MINOR_VERSION   1
#define USBVIEW_BUILD_VERSION   2

// "major.minor.build", e.g. "2.1.0". Built from the three numbers above, so
// those are the only place the version needs changing.
#define VERSION_STRING STRINGIZE(USBVIEW_MAJOR_VERSION) "." \
                       STRINGIZE(USBVIEW_MINOR_VERSION) "." \
                       STRINGIZE(USBVIEW_BUILD_VERSION)

// Branding strings, used by the .rc file.
// \251 is the (c) symbol, \256 is the (R) symbol
#define ABOUT_NAME      "USBViewEx"
#define ABOUT_TITLE     "About USBViewEx"
#define ABOUT_COPYRIGHT L"Copyright \251 2025-2026 Alex313031"
#define LEGAL_COPYRIGHT L"\251 1996-2026 Microsoft\256 and Alex313031"

#endif // USBVIEW_VERSION_H_
