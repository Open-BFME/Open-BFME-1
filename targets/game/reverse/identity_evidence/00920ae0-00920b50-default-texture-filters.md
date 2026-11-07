# Magnification and mip texture default filters

BFME 1 puts the 109-byte default min selector at 0x00920A70, immediately
followed by its two distinct 109-byte siblings at 0x00920AE0 and
0x00920B50. INT3 padding establishes their boundaries. All three take one
four-byte argument and return with plain RET. The latter two use
0x01346C50 and 0x01346CF0 respectively. In each case, eight indexed
dword loads select column filter and eight dword stores set column
four over the exact 0x14-byte stage stride.

The retail _Init_Filters at 0x00920D10 independently distinguishes the
tables by the magnification and mip capability tests. The corresponding
BFME 2 selectors in Code/Libraries/Source/WWVegas/WW3D2/texturefilter.cpp
use the same table order and operations. Their independent code rows
are at 0x0013ED50 and 0x0013ED80 at the pinned revision
dbde7dbe3be16481b2c8d6f2f9577bc322f6b7ce. Zero Hour's texturefilter.cpp has both names and
declares the selector argument as TextureFilterClass::FilterType.
BFME 1's own texturefilter.h declares those same static methods.

0x00920AE0 ?Rva00920AE0SelectOption@@YAXH@Z -> ?_Set_Default_Mag_Filter@TextureFilterClass@@SAXW4FilterType@1@@Z
0x00920B50 ?Rva00920B50SelectOption@@YAXH@Z -> ?_Set_Default_Mip_Filter@TextureFilterClass@@SAXW4FilterType@1@@Z
