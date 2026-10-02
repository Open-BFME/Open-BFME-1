# Container DieModuleInterface slot 0: TunnelContain::onDie

Retail lotrbfme.exe SHA-256
`1fbdc0ced8f283732c094c4f0804ce8dc1e3e3675b720bcab066c94fed964e75`.
All addresses below are RVAs except explicitly marked VAs. Facts were read
with pefile and Capstone directly from that baseline.

## Owner and slot

The registered TunnelContain factory 00116530 calls ILT 00002450 at
0011656E to constructor 0022EE70. The independent primary getter and
registration proof is recorded in containmodule-slot0-asopencontain.md.
The constructor calls OpenContain through ILT 00036E49 at 0022EE7F,
then installs primary table VA 010ADDB8 at 0022EE84 and the +0x28
DieModuleInterface table VA 010ADB14 at 0022EEA6.
Its sole slot is ILT VA 0040A9C0, a five-byte E9 to body 0022F300.
A whole-image aligned/un-aligned little-endian search finds this ILT VA
exactly once, at VA 010ADB14. This is TunnelContain's own override,
not an inherited shared implementation. The base OpenContain constructor
installs a different die table, VA 010AC014, whose sole slot reaches
00222640. The sixteen registered contain constructor census is in
damagemodule-slots0-1-callbacks.md; every table at +0x28 has this same
single-method interface role.

## Lexical twin and ABI

GeneralsMD GameEngine/Include/GameLogic/Module/TunnelContain.h:120-121
explicitly overrides public virtual `void onDie(const DamageInfo*)`,
with the comment that it overrides OpenContain's method.
GameEngine/Source/GameLogic/Object/Contain/TunnelContain.cpp:350 supplies
its body: DieMux applicability, registration flag, controlling player,
player tunnel tracker, onTunnelDestroyed, and clearing registration.
DieModuleInterface declares precisely this one virtual method. Thus the
full class and method names have a direct Zero Hour twin, and the public
virtual pointer-to-const ABI is `?onDie@TunnelContain@@UAEXPBVDamageInfo@@@Z`.

Retail agrees: ECX is the die subobject at complete-object +0x28; module
data and Object are loaded at ECX-0x24 and ECX-0x20. It calls DieMux
through ILT 000357D8 at 0022F312, checks flag at ECX+0xAD, calls
getControllingPlayer through ILT 00020824 at 0022F328, loads tracker at
player+0x22C, calls ILT 000304E0 at 0022F341, and clears the same flag.
The body ends with `pop esi; ret 4` at 0022F34D..0022F350, followed by
INT3 at 0022F351, proving the 81-byte extent. The old matched opaque
BfmeThing300::bfmeGo body is the same implementation, not another identity.

## Source and validation

The unmodified Zero Hour body reproduces the 81-byte instruction shape but
reads its own layout (Object at die-0x1C, registration at die+0x671,
tracker at player+0x15C). The local game TunnelContain.cpp uses the real
headers and a four-byte shifted view solely for the inline module-data and
Object accessors; its declaration's die base is +0x28. Explicit retail reads
use complete-object+0xD5 for registration (die+0xAD) and player+0x22C for
the tracker. No virtual call receives the shifted view and no header changes
or invented field names are needed. Address-qualified inline tracker access
preserves the native source's evaluation shape. tools/probe.py reports
81/81 EXACT modulo its three relocations; add_match performs the actual
callee binding check. The three semantic callees already have matched
rows: DieMuxData::isDieApplicable 002551F0, Object::getControllingPlayer
001BE3F0, and TunnelTracker::onTunnelDestroyed 000F8C20. No pins are added.
