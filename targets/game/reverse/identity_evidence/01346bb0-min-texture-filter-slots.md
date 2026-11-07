# Minimum texture filter slots at VA 0x01346BB0

The retail _Set_Default_Min_Filter body at RVA 0x00920A70 has eight
load/store pairs. The loads begin at 0x01346BB0 and advance by 0x14
per stage. The stores are at each stage's +0x10, ending at 0x01346C4C.
The array ends at the next verified table, 0x01346C50. The loader-mapped
.data supplies all 160 zero bytes. The initialization body at 0x00920D10
and the reader at 0x00920BC0 already use this same array name and shape.

The previous four-column definition compiled with the same opcode
sequence, but its 16 relocations implied nine different base addresses.
The corrected layout keeps every opcode and makes every relocation
land on the one recorded base plus the retail offset.

Pinned BFME 2 dbde7dbe3be16481b2c8d6f2f9577bc322f6b7ce uses the
corresponding _MinTextureFilters in Code/Libraries/Source/WWVegas/WW3D2/texturefilter.cpp.
BFME 1 independently proves its stride and uses the existing
Rva00920AE0Slot declaration from the sibling tables.
