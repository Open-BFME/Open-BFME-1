# WeaponSet update callee identities

Retail updateWeaponSet is RVA 0x001EBBC0, 379 bytes. Its ILT 0x000209FA reaches RVA 0x001BEF20, whose seven bytes implement `lea eax,[ecx+0x29c]; ret`. The existing matched provider is Rva001BEF20FieldAddress::get in Common/DispFieldAddressGetters.cpp. This is an Object field accessor, not a flags type.

ILT 0x00021044 reaches RVA 0x001467E0 (73 bytes): the existing ThingTemplate::findWeaponTemplateSet provider takes a const BitFlags<17> reference, accesses template fields +0x304/+0x2f8, and returns with ret 4. The removed empty WeaponSetFlags class was a local argument-type shim for the incorrectly named BfmeThingTemplate call. Its descriptive flags name is retained as a BitFlags<17> typedef. It was not renamed to Rva001BEF20FieldAddress; the name checker paired unrelated removed and added class declarations.

ILT 0x0000FED4 reaches RVA 0x001E9D60 (95 bytes), the existing Weapon::loadAmmoNow provider taking one Object pointer and returning with ret 4. The focused update body continues to verify at its original 379-byte extent.
