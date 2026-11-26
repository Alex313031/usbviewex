# USBViewEx <img src="assets/icon.png" alt="USBViewEx icon" width="32" height="32">

A fork of [Microsoft's USBView](https://github.com/Microsoft/Windows-driver-samples/tree/main/usb/usbview) Windows Driver Kit sample, a small Win32 app that shows detailed USB device info.

## Synopsis

It contains the nice to haves of the latest source, while preserving the styling and legacy OS support of the original [7.1 WDK](https://www.microsoft.com/en-us/download/details.aspx?id=11800) one.

I wanted a version of USBView that ran on XP, with no .NET Framework dependencies, but still supported xHCI/USB 3.x.

Other people have also forked USBView, including the popular [USBTreeView](https://www.uwe-sieber.de/usbtreeview_e.html).

## What's different from upstream

 - Runs on Windows XP and up; upstream needs Windows 7+.
 - No .NET Framework dependency. That came from the XML export, which has been removed
   ("Save As (xml)" in the File menu, and the `/savexml` command line switch). Saving as text still works.
 - Window layout and icons from the 7.1 WDK version, plus a minimum window size and a few keyboard shortcuts
   (Esc to exit, Alt+? for About).
 - Its own version number, continuing from Microsoft's 2.0.
 - Builds with MSVC, GN, and GNU Make, without needing the WDK.

## Usage
Download a pre-built .exe from [Releases](https://github.com/Alex313031/usbviewex/releases).  
One can follow usage instructions (as well as download upstream USBView) [Here](https://learn.microsoft.com/en-us/windows-hardware/drivers/debugger/usbview).
Those instructions are for upstream, so see the differences above.

## Building
USBViewEx supports many build systems, including [MSVC](https://visualstudio.microsoft.com/downloads/), [GN](https://gn.googlesource.com/gn/) (via my
[gn-legacy repo](https://github.com/Alex313031/gn-legacy#readme)), and [GNU Make](https://www.gnu.org/software/make/) (with [MinGW](https://www.mingw-w64.org/)).

The MinGW builds (GNU Make and GN) are the ones meant for Windows XP, and are what the releases are built with.
The MSVC builds are mainly for development; they are not guaranteed to run on anything older than Vista.

#### GNU Make (MinGW)
Uses the `GNUmakefile`. Output goes to `out/mingw/<arch>/<Debug|Release>/usbview.exe`.

```bash
make                              # 32 bit release build, using i686-w64-mingw32-gcc
make DEBUG=1                      # Debug build
make CROSS=x86_64-w64-mingw32-    # 64 bit build
make CROSS=                       # Use the plain gcc/windres on your PATH
make clean
```

#### GN (gn-legacy)
Clone this repo into `src/usbviewex` of a [gn-legacy](https://github.com/Alex313031/gn-legacy#readme) checkout, then build the `usbview` target:

```bash
./gn args out/Release
./ninja -C out/Release usbview
```

#### MSVC
Either open `usbview.sln` in Visual Studio, or use the nmake `Makefile` from a Visual Studio Developer Command Prompt.
Output goes to `out\<arch>\<Debug|Release>\` for the solution, and `out\nmake\<arch>\<Debug|Release>\` for nmake.

```bat
nmake
nmake DEBUG=1
nmake clean
```

## License
USBViewEx is licensed under the [Microsoft Public License](LICENSE.md), as is the original.
