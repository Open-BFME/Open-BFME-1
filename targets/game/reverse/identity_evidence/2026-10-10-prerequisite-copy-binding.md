# Prerequisite construct-shim callee

Retail 0x00784DB0 is 19 bytes ending in RET at +18. Its call at +13 reaches ILT 0x00038550, which jumps to 0x00783D50. The matched provider at that address is `Rva00783D50PodCopy` (game/GameEngine/Source/Common/Rva00783D50PodCopy.cpp). It copies three eight-byte entries and has no proven ProductionPrerequisite identity. The old TU-local `ProductionPrerequisiteRetailCopy` declaration was an adapter for this call, not independently established ownership. Use the provider's address-qualified name, preserving the receiver and const-reference ABI.

The caller's public ProductionPrerequisite shim identities and extents remain intact. All four source rows byte-verify. link_check.py reports 0/1 linked before (unresolved old copy constructor), 1/1 after, 53 linked bytes.
