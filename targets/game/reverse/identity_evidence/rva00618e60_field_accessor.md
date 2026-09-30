# RVA 0x00618E60 field accessor

The complete four-byte retail body is `8D 41 14 C3`: LEA EAX from ECX+0x14 followed by RET. Eight INT3 bytes separate it from the next body. ILT 0x00040D31 jumps directly to this body.

LivingWorldLogic retail caller 0x003C3760 uses this ILT at instruction offset 0x87 with the region receiver returned by the independently matched LivingWorldRegionManager lookup 0x003C8A50. The returned field address is passed to the independently matched setter 0x00386090. The member is opaque: no original field or method name is claimed.

The former row ?a_00618e60@@YAXXZ was a gen-alias borrowing the object symbol AudioEventRTS::getEventName from another body. Equal instruction bytes establish a code pattern but do not establish AudioEventRTS ownership at this address. The replacement Rva00618E60FieldAddress::get() const names only the address and independently decoded thiscall ABI. The row is replaced rather than adding a second identity.
