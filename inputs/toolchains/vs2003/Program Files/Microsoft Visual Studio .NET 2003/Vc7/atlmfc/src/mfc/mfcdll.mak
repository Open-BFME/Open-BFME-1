# This is a part of the Microsoft Foundation Classes C++ library.
# Copyright (C) Microsoft Corporation
# All rights reserved.
#
# This source code is only intended as a supplement to the
# Microsoft Foundation Classes Reference and related
# electronic documentation provided with the library.
# See these sources for detailed information regarding the
# Microsoft Foundation Classes product.

# MFC71[D].DLL is a DLL
#  which exports all the MFC classes
#
# If you need a private build of the MFC DLL, be sure to rename
#  "MFC71.DLL" to something more appropriate for your application.
# Please do not re-distribute a privately built version with the
#  name "MFC71.DLL".
#
# Use nmake /f mfcdll.mak LIBNAME=<your name> to do this.
#
# Note: LIBNAME must be 6 characters or less.

!ifndef LIBNAME
!error LIBNAME is not defined. LIBNAME=MFC71 builds the prebuilt DLL.
!endif

!ifndef REGEN
REGEN=0
!endif

!if "$(DEBUG)" != "0"
CRTDLL=msvcrtd.lib
!else
CRTDLL=msvcrt.lib
!endif

TARGET=w
DLL=2
TARGDEFS=/D_AFX_CORE_IMPL
#LFLAGS=/nodefaultlib
RCFLAGS=/r

!if "$(UNICODE)" == "1"
TARGTYPE=U
RCDEFINES=$(RCDEFINES) /D_UNICODE
LFLAGS=$(LFLAGS) /opt:nowin98
!else
LFLAGS=$(LFLAGS) /opt:win98
!endif

!if "$(DEBUG)" != "0"
# Debug DLL build
TARGTYPE=$(TARGTYPE)D
RCDEFINES=$(RCDEFINES) /D_DEBUG
LFLAGS=$(LFLAGS)
!ifndef MONOLITHIC
MONOLITHIC=1
!endif
!ELSE
# Release DLL build
RCDEFINES=$(RCDEFINES)
LFLAGS=$(LFLAGS)
!ifndef MONOLITHIC
#!if "$(PLATFORM)" == "IA64"
#MONOLITHIC=0
#!else
MONOLITHIC=1
#!endif
!endif
!ENDIF

!if "$(MONOLITHIC)" == "1"
TARGDEFS=$(TARGDEFS) /D_AFX_OLE_IMPL /D_AFX_DB_IMPL /D_AFX_NET_IMPL /D_AFX_MONOLITHIC /D_MFC_DLL_BLD
RCDEFINES=$(RCDEFINES) /D_AFX_MONOLITHIC
!endif

CFNAME=$(LIBNAME)$(TARGTYPE)
TARG=$(LIBNAME)$(PF)$(TARGTYPE)
!if "$(LIBNAME)" != "MFC71"
TARG_STATIC=$(LIBNAME)S$(PF)$(TARGTYPE)
!else
TARG_STATIC=MFCS71$(PF)$(TARGTYPE)
!endif

# OPT:noref keeps unreferenced functions (ie. no dead-code elimination)
!if "$(REGEN)" == "0"
LFLAGS=$(LFLAGS) /opt:ref /opt:icf,32
!else
LFLAGS=$(LFLAGS) /opt:noref
!endif

DEFFILE=$(PLATFORM)\MFC71$(PF)$(TARGTYPE).DEF

!if "$(DEBUGTYPE)" == ""
DEBUGTYPE=cv
!endif

!if "$(CODEVIEW)" != "0"
!if "$(REGEN)" != "1"
LFLAGS=$(LFLAGS) /debug:full /debugtype:$(DEBUGTYPE)
!else
LFLAGS=$(LFLAGS) /debug:none
!endif
!if "$(NO_PDB)" != "1" && "$(REGEN)" != "1"
LFLAGS=$(LFLAGS) /pdb:$(PLATFORM)\$(TARG).pdb
# !else
#LFLAGS=$(LFLAGS) /pdb:none
!endif
!else
LFLAGS=$(LFLAGS) /debug:none
!if "$(INCREMENTAL)" != "1"
LFLAGS=$(LFLAGS) /incremental:no
!endif
!endif

!ifdef RELEASE # Release VERSION info
RCDEFINES=$(RCDEFINES) /DRELEASE
LFLAGS=$(LFLAGS) /release
!endif

LFLAGS=$(LFLAGS) /dll

!if "$(ORDER)" == "1"
!if exist($(PLATFORM)\$(TARG).prf)
DEFS=$(DEFS) /D_AFX_FUNCTION_ORDER
LFLAGS=$(LFLAGS) /order:@$(PLATFORM)\$(TARG).prf
!endif
!endif

!if "$(PLATFORM)" == "PPC"
LIBS=$(LIBS) int64.lib /force:multiple
!endif

!if "$(PLATFORM)" == "AXP64"
LFLAGS=$(LFLAGS) /machine:ALPHA64
!endif

dll_goal: create2.dir \
	$(PLATFORM)\$(TARG).dll ..\..\lib\$(PLATFORM)\$(TARG).lib ..\..\lib\$(PLATFORM)\$(TARG_STATIC).lib

#############################################################################
# import most rules and library files from normal makefile

!include makefile

create2.dir:
	@-if not exist $D\*.* mkdir $D

#############################################################################
# more flags and switches

LFLAGS=$(LFLAGS) /version:7.0
!if "$(UNICODE)" == "1"
LFLAGS=$(LFLAGS) /base:0x7C250000
!else
LFLAGS=$(LFLAGS) /base:0x7C140000
!endif
LIBS=$(CRTDLL) kernel32.lib gdi32.lib msimg32.lib user32.lib uuid.lib daouuid.lib htmlhelp.lib shlwapi.lib $(PROFLIB)

#############################################################################

STATICLINK_OBJS=$D\stdafx.obj $D\nolib.obj \
	$D\appmodul.obj $D\dllmodul.obj $D\oleexp.obj $D\dumpstak.obj $D\sockexp.obj

# Always compile /Zi (generate PDB) for mfcs71[u][d].lib, since we never get a chance to have the
# linker generate a PDB from /Z7 info

CVOPTS_STATIC=/Zi

CPPFLAGS_STATIC=\
	$(CL_MODEL) /D_AFX_MFCS $(CL_OPT:Z7=Zi) $(DEFS:/D_MFC_DLL_BLD=) $(OPT) $(EH) /Gy $(CVOPTS_STATIC) /Fd..\..\lib\$(PLATFORM)\$(TARG_STATIC).pdb

PCH_TARGET=$D\stdafx.obj

$D\stdafx.obj $D\stdafxs.pch: stdafx.cpp stdafx.h
	cl @<<
/c $(CPPFLAGS_STATIC) /Ycstdafx.h /Fp$D\stdafxs.pch stdafx.cpp
<<

$D\appmodul.obj: $D\stdafx.obj appmodul.cpp
	cl @<<
/c $(CPPFLAGS_STATIC) /Yustdafx.h /Fp$D\stdafxs.pch appmodul.cpp
<<

$D\dllmodul.obj: $D\stdafx.obj dllmodul.cpp
	cl @<<
/c $(CPPFLAGS_STATIC) /Yustdafx.h /Fp$D\stdafxs.pch dllmodul.cpp
<<

$D\oleexp.obj: $D\stdafx.obj oleexp.cpp
	cl @<<
/c $(CPPFLAGS_STATIC) /Yustdafx.h /Fp$D\stdafxs.pch oleexp.cpp
<<

$D\nolib.obj: $D\stdafx.obj nolib.cpp
	cl @<<
/c $(CPPFLAGS_STATIC) /Yustdafx.h /Fp$D\stdafxs.pch nolib.cpp
<<

$D\dumpstak.obj: $D\stdafx.obj dumpstak.cpp
	cl @<<
/c $(CPPFLAGS_STATIC) /Yustdafx.h /Fp$D\stdafxs.pch dumpstak.cpp
<<

$D\sockexp.obj: $D\stdafx.obj sockexp.cpp
	cl @<<
/c $(CPPFLAGS_STATIC) /Yustdafx.h /Fp$D\stdafxs.pch sockexp.cpp
<<

#############################################################################
# Build target

$D\$(TARG).res: mfcdll.rc ..\..\include\atlbuild.h
	rc $(RCFLAGS) $(RCDEFINES) /fo $D\$(TARG).res mfcdll.rc

DLL_OBJS=$(OBJECT) $(OBJDIAG) $(INLINES) $(FILES) $(COLL1) $(COLL2) $(MISC) \
	$(WINDOWS) $(DIALOG) $(WINMISC) $(DOCVIEW) $(APPLICATION) $(OLEREQ) \
	$(INTERNET) $(DAO)

!if "$(MONOLITHIC)" == "1"
!if "$(PLATFORM)" == "IA64"
DLL_OBJS=$(DLL_OBJS) $(OLEDLL) $(SOCKETS)
!else
DLL_OBJS=$(DLL_OBJS) $(SOCKETS) $(OLEDLL) $(DB)
!endif
!else
!if "$(DEBUG)" == "0"
!if "$(PLATFORM)" != "IA64"
DLL_OBJS=$(DLL_OBJS) $(OLEDLL) $(SOCKETS)
!endif
!endif
!endif

DLL_OBJS=$(DLL_OBJS) $D\dllinit.obj

DLL_RESOURCES=$D\$(TARG).res

!if "$(PLATFORM)" == "AXP64" || "$(PLATFORM)" == "IA64"
$(PLATFORM)\$(TARG).dll ..\..\lib\$(PLATFORM)\$(TARG).lib: $(DLL_OBJS) $(DEFFILE) $(DLL_RESOURCES)
	link @<<
$(LFLAGS)
$(LIBS)
$(DLL_OBJS)
$(DLL_RESOURCES)
/def:$(DEFFILE)
/out:$(PLATFORM)\$(TARG).DLL
/map:$D\$(TARG).MAP
/implib:..\..\lib\$(PLATFORM)\$(TARG).LIB
/filealign:4096
/delayload:comdlg32.dll
/delayload:comctl32.dll
/delayload:shell32.dll
/delayload:advapi32.dll
/delayload:wininet.dll
/delayload:wsock32.dll
/delayload:WS2_32.dll
/delayload:ole32.dll
/delayload:oleaut32.dll
/delayload:oledlg.dll
/delayload:urlmon.dll
/delayload:odbc32.dll
/delayload:winspool.drv
/delayload:hhctrl.ocx
/delayload:msimg32.dll
/delayload:oleacc.dll
delayimp.lib
mfcdload.lib
/NOD:olepro32.lib
/NOD:libcmt.lib
<<
!else
$(PLATFORM)\$(TARG).dll ..\..\lib\$(PLATFORM)\$(TARG).lib: $(DLL_OBJS) $(DEFFILE) $(DLL_RESOURCES)
	link @<<
$(LFLAGS)
$(LIBS)
$(DLL_OBJS)
$(DLL_RESOURCES)
/def:$(DEFFILE)
/out:$(PLATFORM)\$(TARG).DLL
/map:$D\$(TARG).MAP
/implib:..\..\lib\$(PLATFORM)\$(TARG).LIB
/ignore:4037
/ignore:4065
/ignore:4199
/ignore:4089
/merge:.rdata=.text
/delayload:comdlg32.dll
/delayload:comctl32.dll
/delayload:shell32.dll
/delayload:advapi32.dll
/delayload:wininet.dll
/delayload:wsock32.dll
/delayload:WS2_32.dll
/delayload:ole32.dll
/delayload:oleaut32.dll
/delayload:oledlg.dll
/delayload:urlmon.dll
/delayload:odbc32.dll
/delayload:winspool.drv
/delayload:hhctrl.ocx
/delayload:msimg32.dll
/delayload:oleacc.dll
delayimp.lib
mfcdload.lib
<<
!endif

..\..\lib\$(PLATFORM)\$(TARG_STATIC).lib: $(STATICLINK_OBJS)
	lib /out:$@ $(STATICLINK_OBJS)

#############################################################################
