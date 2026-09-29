The retail body at RVA 0x00893270 reads the pool pointer at VA 0x01337810. The pin in targets/game/reverse/symbols.csv names the global g_rva8CD130IdleHook and types it as Rva00899560Pool*.

The matched constructor in game/Libraries/Source/EA/Apt/Rva00899560AptValueCtor.cpp defines Rva00899560Pool with capacity at +0, count at +4, and items at +8. Retail body 0x00893270 reads those fields, stores the node through the items array when count is below capacity, and clears bit 0x40000000 when the array is full.

The banked type name BfmeRegistryKind1 came from a local struct declaration. No retail symbol pin or matched caller identifies a type by that name. The new source uses Rva00899560Pool, the pinned type of the global this body reads.
