# Copyright 2026 Alex313031
#
# Microsoft nmake build of USBViewEx with the Visual C++ command line tools.
# Run it from a Visual Studio "Developer Command Prompt" (x86 or x64).
# GNU Make does not read this file; it uses "GNUmakefile" instead.
#
#   nmake                   Release build
#   nmake DEBUG=1           Debug build
#   nmake clean             Remove this configuration's output directory
#
# Output goes to out\nmake\<x86|x64>\<Debug|Release>\usbview.exe

# Name the output directory after the architecture of the developer prompt.
# Override with "nmake ARCH=x64" if your prompt does not set VSCMD_ARG_TGT_ARCH.
!IFNDEF ARCH
!IFDEF VSCMD_ARG_TGT_ARCH
ARCH = $(VSCMD_ARG_TGT_ARCH)
!ELSE
ARCH = x86
!ENDIF
!ENDIF

!IFDEF DEBUG
CONFIG = Debug
!ELSE
CONFIG = Release
!ENDIF

SRCDIR = src
OUTDIR = out\nmake\$(ARCH)\$(CONFIG)
OBJDIR = $(OUTDIR)\obj
TARGET = $(OUTDIR)\usbview.exe

OBJECTS = \
    $(OBJDIR)\debug.obj \
    $(OBJDIR)\devnode.obj \
    $(OBJDIR)\dispaud.obj \
    $(OBJDIR)\display.obj \
    $(OBJDIR)\dispvid.obj \
    $(OBJDIR)\enum.obj \
    $(OBJDIR)\h264.obj \
    $(OBJDIR)\uvcview.obj \
    $(OBJDIR)\uvcview.res

HEADERS = \
    $(SRCDIR)\codeanalysis.h \
    $(SRCDIR)\h264.h \
    $(SRCDIR)\langidlist.h \
    $(SRCDIR)\resource.h \
    $(SRCDIR)\usbdesc.h \
    $(SRCDIR)\usbviddesc.h \
    $(SRCDIR)\uvcdesc.h \
    $(SRCDIR)\uvcview.h \
    $(SRCDIR)\version.h \
    $(SRCDIR)\vndrlist.h \
    $(SRCDIR)\xhci.h

RC_DEPS = \
    $(SRCDIR)\uvcview.rc \
    $(SRCDIR)\resource.h \
    $(SRCDIR)\version.h \
    $(SRCDIR)\usbview.manifest \
    $(SRCDIR)\res\*.ico \
    $(SRCDIR)\res\*.cur

# The sources are ANSI, so no /DUNICODE.
# The C runtime is linked statically (/MT, /MTd below), so the exe does not
# need the Visual C++ redistributable.
# /std:c11 is ISO C11, same as the MinGW and gn-legacy builds.
CFLAGS  = /nologo /W4 /std:c11 /I$(SRCDIR) /DWIN32 /D_WINDOWS /D_MBCS \
          /D_CRT_SECURE_NO_WARNINGS
RCFLAGS = /nologo /i $(SRCDIR)

# Subsystem version: Windows XP. 64 bit Windows starts at 5.02 (XP x64 /
# Server 2003), and the linker rejects anything lower there.
!IF "$(ARCH)" == "x86"
SUBSYSTEM_VER = 5.01
!ELSE
SUBSYSTEM_VER = 5.02
!ENDIF

# /MANIFEST:NO because uvcview.rc already embeds usbview.manifest.
LDFLAGS = /NOLOGO /SUBSYSTEM:WINDOWS,$(SUBSYSTEM_VER) /MANIFEST:NO
LIBS    = kernel32.lib user32.lib gdi32.lib shell32.lib comctl32.lib \
          comdlg32.lib ole32.lib cfgmgr32.lib setupapi.lib shlwapi.lib

!IFDEF DEBUG
CFLAGS  = $(CFLAGS) /Od /Zi /MTd /D_DEBUG /Fd$(OBJDIR)\vc.pdb
RCFLAGS = $(RCFLAGS) /d _DEBUG
LDFLAGS = $(LDFLAGS) /DEBUG /PDB:$(OUTDIR)\usbview.pdb
!ELSE
CFLAGS  = $(CFLAGS) /O2 /Gy /MT /DNDEBUG
LDFLAGS = $(LDFLAGS) /OPT:REF /OPT:ICF
!ENDIF

all: $(TARGET)

$(TARGET): $(OBJDIR) $(OBJECTS)
	link $(LDFLAGS) /OUT:$@ $(OBJECTS) $(LIBS)

{$(SRCDIR)}.c{$(OBJDIR)}.obj:
	$(CC) $(CFLAGS) /c /Fo$(OBJDIR)\ $<

$(OBJDIR)\uvcview.res: $(RC_DEPS)
	rc $(RCFLAGS) /fo $@ $(SRCDIR)\uvcview.rc

# Any header change rebuilds every object; the project is small enough.
$(OBJECTS): $(HEADERS)

$(OBJDIR):
	if not exist "$(OBJDIR)" mkdir "$(OBJDIR)"

clean:
	if exist "$(OUTDIR)" rmdir /s /q "$(OUTDIR)"
