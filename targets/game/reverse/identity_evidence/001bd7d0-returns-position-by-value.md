# 0x001BD7D0 returns the +0x48 position by value

Retail 0x001BD7D0 (24 bytes) is

    mov edx,[ecx+0x48]; mov eax,[esp+4]; mov [eax],edx
    mov edx,[ecx+0x4C]; mov [eax+4],edx
    mov ecx,[ecx+0x50]; mov [eax+8],ecx; ret 4

The row was `?copy@Rva001BD7D0@@QBEXPAH@Z`, a `void copy(int *dst) const`.
The bytes fit that, but the only known caller shows the ABI is a by-value
return through the hidden return slot. The caller is the matched
`?bfmeGetLastShotPosition@Object@@QBE?AUBfmeFiringPosition@@XZ` at 0x001BF970,
in game/GameEngine/Source/GameLogic/Object/ObjectDamageAndWeapons.cpp. It
calls through ILT 0x000228BD (`jmp 0x001BD7D0`), then at +0x36/+0x3C reads the
three result words through EAX, which is the pointer the callee returns. A
`void` out-parameter call leaves nothing in EAX to read. The symbols.csv pin
`?bfmeGetLastShotPosition@BfmeFiringTracker@@QBE?AUBfmeFiringPosition@@XZ` ->
0x000228BD records the same struct-returning shape.

The owner class is still unproven (FiringTracker+0x48 by the caller's
Object+0x1EC member, but no vtable or caller names the method), so the row
keeps an address-derived name. Only the signature is corrected:
`?get@Rva001BD7D0@@QBE?AUBfmeFiringPosition@@XZ`, a const getter returning the
three-word position the caller's view already names `BfmeFiringPosition`.
