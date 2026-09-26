# This is a part of the Active Template Library.
# Copyright (C) Microsoft Corporation
# All rights reserved.
#
# This source code is only intended as a supplement to the
# Active Template Library Reference and related
# electronic documentation provided with the library.
# See these sources for detailed information regarding the
# Active Template Library product.

!ifndef DEBUG
DEBUG=1
!endif

TARGETNAME=atl$(MFC_VER)
IMPLIB=atl.lib
TARGETTYPE=DLL
DEFFILE=atl.def
RCFILE=atl.rc
RCINCLUDES=$(PLATFORM)\Release$(_OD_EXT)

# base address for atl$(MFC_VER).dll. Should change if the name of the DLL changes

LFLAGS=/base:0x7c120000

!if "$(UNICODE)" == "1"
LFLAGS=$(LFLAGS) /opt:nowin98
!endif

MIN_CRT=1

!include atlcommon.mak

OBJS=$(D)\RegObj.obj $(D)\atl.obj $(D)\stdafx.obj
LIBS=$(LIBS) atldload.lib ole32.lib oleaut32.lib advapi32.lib user32.lib gdi32.lib kernel32.lib shlwapi.lib
!if "$(DEBUG)" == "1"
LIBS=$(LIBS) atlsd.lib
!else
LIBS=$(LIBS) atls.lib
!endif

DELAYLOAD=ole32.dll;oleaut32.dll;advapi32.dll;user32.dll;gdi32.dll

!include atltarg.mak
