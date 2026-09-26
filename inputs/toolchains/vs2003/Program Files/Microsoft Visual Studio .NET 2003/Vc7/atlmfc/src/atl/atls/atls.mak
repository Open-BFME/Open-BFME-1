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

!if "$(DEBUG)" == "1"
TARGETNAME=atlsd
!else
TARGETNAME=atls
!endif
TARGETTYPE=LIB

!include ..\atlcommon.mak

OBJS= \
	$(D)\Allocate.obj \
	$(D)\atlbase.obj \
	$(D)\atlcommodule.obj \
	$(D)\AtlDebugAPI.obj \
	$(D)\atldebuginterfacesmodule.obj \
	$(D)\atlfuncs.obj \
	$(D)\atlimage.obj \
	$(D)\atlimage2.obj \
	$(D)\atlmem.obj \
	$(D)\atlstr.obj \
	$(D)\atltime.obj \
	$(D)\ATLComTime.obj \
	$(D)\atltrace.obj \
	$(D)\atltypes.obj \
	$(D)\AtlTraceModuleManager.obj \
	$(D)\atlwinmodule.obj \
	$(D)\Externs.obj \
	$(D)\LoadNSave.obj

!if "$(PLATFORM)" == "IA64"
OBJS= \
	$(OBJS) \
	$(D)\QIThunk.obj \
	$(D)\stdcallthunk.obj
!endif

!include ..\atltarg.mak
