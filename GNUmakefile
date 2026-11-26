# Copyright 2026 Alex313031
#
# GNU Make build of USBViewEx with MinGW-w64 (GCC or Clang).
# GNU Make picks this file over "Makefile", which is for Microsoft nmake.
#
#   make                        32 bit Release build (i686-w64-mingw32-gcc)
#   make DEBUG=1                Debug build
#   make CROSS=x86_64-w64-mingw32-    64 bit build
#   make CROSS=                 Use the plain gcc/windres on PATH
#   make clean                  Remove this configuration's output directory
#
# Output goes to out/mingw/<x86|x64|...>/<Debug|Release>/usbview.exe

# Toolchain prefix. Defaults to 32 bit MinGW-w64, which works both for cross
# builds from Linux and for native MinGW-w64 installs on Windows.
CROSS   ?= i686-w64-mingw32-
CC      := $(CROSS)gcc
WINDRES := $(CROSS)windres

ifdef DEBUG
  CONFIG := Debug
else
  CONFIG := Release
endif

# Name the output directory after the compiler's target architecture.
MACHINE := $(shell $(CC) -dumpmachine)
ifneq ($(filter x86_64-%,$(MACHINE)),)
  ARCH := x64
else ifneq ($(filter i386-% i486-% i586-% i686-%,$(MACHINE)),)
  ARCH := x86
else
  ARCH := $(firstword $(subst -, ,$(MACHINE)))
endif

# Subsystem (and OS) version stamped into the exe: Windows XP. 64 bit Windows
# starts at 5.02 (XP x64 / Server 2003).
ifeq ($(ARCH),x86)
  SUBSYS_MINOR := 1
else
  SUBSYS_MINOR := 2
endif

SRCDIR := src
OUTDIR := out/mingw/$(ARCH)/$(CONFIG)
OBJDIR := $(OUTDIR)/obj
TARGET := $(OUTDIR)/usbview.exe

SOURCES := debug.c devnode.c dispaud.c display.c dispvid.c enum.c h264.c \
           uvcview.c
OBJECTS := $(SOURCES:%.c=$(OBJDIR)/%.o) $(OBJDIR)/uvcview.res.o

# Everything the resource script pulls in. windres reads the icons, cursor and
# manifest itself, so they have to be listed by hand.
RC_DEPS := $(SRCDIR)/uvcview.rc $(SRCDIR)/resource.h $(SRCDIR)/version.h \
           $(SRCDIR)/usbview.manifest \
           $(wildcard $(SRCDIR)/*.ico) $(wildcard $(SRCDIR)/*.cur)

# The sources are ANSI, so no -DUNICODE / -municode.
CPPFLAGS := -I$(SRCDIR) -D_MBCS
CFLAGS   := -std=c11 -Wall -Wno-unknown-pragmas -Wno-unused-but-set-variable
LDFLAGS  := -mwindows -static \
            -Wl,--major-os-version=5,--minor-os-version=$(SUBSYS_MINOR) \
            -Wl,--major-subsystem-version=5,--minor-subsystem-version=$(SUBSYS_MINOR)
RCFLAGS  := -I$(SRCDIR)
LIBS     := -lgdi32 -lshell32 -lcomctl32 -lcomdlg32 -lole32 -lcfgmgr32 \
            -lsetupapi -lshlwapi

ifdef DEBUG
  CPPFLAGS += -D_DEBUG
  CFLAGS   += -Og -g2
  RCFLAGS  += -D_DEBUG
else
  CPPFLAGS += -DNDEBUG
  CFLAGS   += -O2 -g0
  LDFLAGS  += -s
endif

# GNU Make on Windows runs recipes through cmd.exe unless it finds sh.exe on
# PATH; cmd.exe is the one that leaves the quotes in the echo below.
ifeq ($(shell echo "check_quotes"),"check_quotes")
  mkdir_p = if not exist "$(subst /,\,$(1))" mkdir "$(subst /,\,$(1))"
  rm_rf   = if exist "$(subst /,\,$(1))" rmdir /s /q "$(subst /,\,$(1))"
else
  mkdir_p = mkdir -p "$(1)"
  rm_rf   = rm -rf "$(1)"
endif

.PHONY: all clean

all: $(TARGET)

$(TARGET): $(OBJECTS)
	$(CC) $(LDFLAGS) -o $@ $(OBJECTS) $(LIBS)

$(OBJDIR)/%.o: $(SRCDIR)/%.c | $(OBJDIR)
	$(CC) $(CPPFLAGS) $(CFLAGS) -MMD -MP -c $< -o $@

$(OBJDIR)/uvcview.res.o: $(RC_DEPS) | $(OBJDIR)
	$(WINDRES) $(RCFLAGS) $(SRCDIR)/uvcview.rc -O coff -o $@

$(OBJDIR):
	$(call mkdir_p,$(OBJDIR))

clean:
	$(call rm_rf,$(OUTDIR))

# Header dependencies written by -MMD
-include $(OBJECTS:.o=.d)
