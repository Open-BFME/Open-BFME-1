# This is a part of the Active Template Library.
# Copyright (C) Microsoft Corporation
# All rights reserved.
#
# This source code is only intended as a supplement to the
# Active Template Library Reference and related
# electronic documentation provided with the library.
# See these sources for detailed information regarding the
# Active Template Library product.

!if "$(LIBNAME)" != ""
_LIBNAME = LIBNAME=$(LIBNAME)
!endif

!if "$(PLATFORM)" == ""
!message setting PLATFORM=INTEL
PLATFORM=INTEL
!endif

!if "$(CLEAN)" != ""
_CLEAN = CLEAN
!else
_CLEAN =
!endif

!if !exist(atlmfc.mak)
!error Run this makefile from the directory it is loacted in.
!endif


all : createdir ATLSRC MFCSRC

atl : createdir ATLSRC

mfc : createdir MFCSRC

createdir :
# create or clean destination directory
!if "$(CLEAN)" == ""
	if not exist ..\lib\$(PLATFORM)$(_OD_EXT) md ..\lib\$(PLATFORM)$(_OD_EXT)
!endif

ATLSRC :
	cd atl

# build the atl static libraries
	cd atls
	$(MAKE) /$(MAKEFLAGS) /f atls.mak DEBUG=1 _OD_EXT=$(_OD_EXT) UNICODE= $(_CLEAN) PLATFORM=$(PLATFORM)
	$(MAKE) /$(MAKEFLAGS) /f atls.mak DEBUG=0 _OD_EXT=$(_OD_EXT) UNICODE= $(_CLEAN) PLATFORM=$(PLATFORM)
	cd ..
!if "$(CLEAN)" == ""
	copy atls\$(PLATFORM)\debug$(_OD_EXT)\atlsd.lib ..\..\lib\$(PLATFORM)$(_OD_EXT)
	copy atls\$(PLATFORM)\debug$(_OD_EXT)\atlsd.pdb ..\..\lib\$(PLATFORM)$(_OD_EXT)
	copy atls\$(PLATFORM)\release$(_OD_EXT)\atls.lib ..\..\lib\$(PLATFORM)$(_OD_EXT)
	copy atls\$(PLATFORM)\release$(_OD_EXT)\atls.pdb ..\..\lib\$(PLATFORM)$(_OD_EXT)
!endif
	
# build mincrt static lib	
	cd atlmincrt
	$(MAKE) /$(MAKEFLAGS) /f atlmincrt.mak DEBUG=0 _OD_EXT=$(_OD_EXT) UNICODE= $(_CLEAN) PLATFORM=$(PLATFORM)
	cd ..
!if "$(CLEAN)" == ""
	copy atlmincrt\$(PLATFORM)\release$(_OD_EXT)\atlmincrt.lib ..\..\lib\$(PLATFORM)$(_OD_EXT)
	copy atlmincrt\$(PLATFORM)\release$(_OD_EXT)\atlmincrt.pdb ..\..\lib\$(PLATFORM)$(_OD_EXT)
!endif

# build atl71.dll	
	$(MAKE) /$(MAKEFLAGS) /f atlidl.mak DEBUG=0 _OD_EXT=$(_OD_EXT) $(_CLEAN) PLATFORM=$(PLATFORM)
	$(MAKE) /$(MAKEFLAGS) /f atlidl.mak _OD_EXT=$(_OD_EXT) $(_CLEAN) PLATFORM=$(PLATFORM)
	$(MAKE) /$(MAKEFLAGS) /f atldll.mak UNICODE=1 DEBUG=0 _OD_EXT=$(_OD_EXT) $(_CLEAN) PLATFORM=$(PLATFORM)
	$(MAKE) /$(MAKEFLAGS) /f atldll.mak DEBUG=0 _OD_EXT=$(_OD_EXT) $(_CLEAN) PLATFORM=$(PLATFORM)
	$(MAKE) /$(MAKEFLAGS) /f atldll.mak UNICODE=1 DEBUG=1 _OD_EXT=$(_OD_EXT) $(_CLEAN) PLATFORM=$(PLATFORM)
	$(MAKE) /$(MAKEFLAGS) /f atldll.mak DEBUG=1 _OD_EXT=$(_OD_EXT) $(_CLEAN) PLATFORM=$(PLATFORM)
!if "$(CLEAN)" == ""
	copy $(PLATFORM)\release$(_OD_EXT)U\atl.lib ..\..\lib\$(PLATFORM)$(_OD_EXT)
	copy $(PLATFORM)\release$(_OD_EXT)U\atl71.pdb ..\..\lib\$(PLATFORM)$(_OD_EXT)
!endif

	cd ..
	
MFCSRC : 
	cd mfc
# static libs	
	$(MAKE) /$(MAKEFLAGS) DEBUG=0 _OD_EXT=$(_OD_EXT) $(_CLEAN) PLATFORM=$(PLATFORM)
	$(MAKE) /$(MAKEFLAGS) DEBUG=1 _OD_EXT=$(_OD_EXT) $(_CLEAN) PLATFORM=$(PLATFORM)
	$(MAKE) /$(MAKEFLAGS) DEBUG=0 UNICODE=1 _OD_EXT=$(_OD_EXT) $(_CLEAN) PLATFORM=$(PLATFORM)
	$(MAKE) /$(MAKEFLAGS) DEBUG=1 UNICODE=1 _OD_EXT=$(_OD_EXT) $(_CLEAN) PLATFORM=$(PLATFORM)
	
# isapi libs
	$(MAKE) /$(MAKEFLAGS) /f mfcisapi.mak DEBUG=0 _OD_EXT=$(_OD_EXT) $(_CLEAN) PLATFORM=$(PLATFORM)
	$(MAKE) /$(MAKEFLAGS) /f mfcisapi.mak DEBUG=1 _OD_EXT=$(_OD_EXT) $(_CLEAN) PLATFORM=$(PLATFORM)
	
# dlls
	$(MAKE) /$(MAKEFLAGS) /f mfcdll.mak $(_LIBNAME) debug=0 _OD_EXT=$(_OD_EXT) $(_CLEAN) PLATFORM=$(PLATFORM)
	$(MAKE) /$(MAKEFLAGS) /f mfcdll.mak $(_LIBNAME) debug=1 _OD_EXT=$(_OD_EXT) $(_CLEAN) PLATFORM=$(PLATFORM)
	$(MAKE) /$(MAKEFLAGS) /f mfcdll.mak $(_LIBNAME) debug=0 UNICODE=1 _OD_EXT=$(_OD_EXT) $(_CLEAN) PLATFORM=$(PLATFORM)
	$(MAKE) /$(MAKEFLAGS) /f mfcdll.mak $(_LIBNAME) debug=1 UNICODE=1 _OD_EXT=$(_OD_EXT) $(_CLEAN) PLATFORM=$(PLATFORM)

# localized dlls
	$(MAKE) /$(MAKEFLAGS) /f mfcintl.mak fra
	$(MAKE) /$(MAKEFLAGS) /f mfcintl.mak deu
	$(MAKE) /$(MAKEFLAGS) /f mfcintl.mak jpn
	$(MAKE) /$(MAKEFLAGS) /f mfcintl.mak ita
	$(MAKE) /$(MAKEFLAGS) /f mfcintl.mak esp
	$(MAKE) /$(MAKEFLAGS) /f mfcintl.mak chs
	$(MAKE) /$(MAKEFLAGS) /f mfcintl.mak cht
	$(MAKE) /$(MAKEFLAGS) /f mfcintl.mak kor
	$(MAKE) /$(MAKEFLAGS) /f mfcintl.mak enu
	cd ..
