# Quick-match request construction, 00509B30 / 1893 bytes

The full retail body starts00509B30 and ends0050A295 with RET4, followed by
INT3 alignment. Incoming ECX is the quick-match menu and its one stack
argument is unused. The independently matched System0050A470 calls it through
ILT0002AAB8 after its start-button comparison, passing the control pointer.
The menu constructor00505830, map-list member00507F70 and initializer005091F0
establish the same228..2AC control layout. The original WOLQuickMatchMenu.cpp
start-button branch establishes the request operation. The native method name
retains rva00509B30 because the original BFME member spelling is not proven.

The old dump is one1893-byte row; there is no banked body to start from despite
its24 historical verdicts. A fresh read-only Ghidra decompilation and complete
retail disassembly supplied the missing BFME differences. This pass began with
the original algorithm and already landed sibling types, and reached strict
1893/1893 after about11minutes, modelGPT-6. This replaces dumped bytes only;
no helper ownership or generated-native replacement is credited.

## Layout and behavior

PeerRequest is194 bytes, independently established by its370-byte copy
constructor00647470, assignment00648C00 and194-byte deque allocation stride.
Its17 narrow/wide STL strings precede qmMaps atD0; the176-byte union startsE4.
The quick-match payload uses the reference field order and three checksum
words134/138/13C. Unknown checksum fields retain their address offsets.
PSPlayerStats is1C4 bytes, using the layout already established by the landed
00659670 parser and00506720 update: disconnect/desync mapsB8/C4, map nodes'
second field+14. Compile-time size assertions enforce both extents.

BFME starts request kind16, copies selected maps, computes point bounds,
ping/disconnect limits, rank, ladder, faction, color and NAT, then sums the
statistics maps and saves a recent ladder. Its ladder-controlled random
faction branch uses PlayerTemplate vector stride124 and side at+8. The
Zero Hour ten-attempt random-side fallback is absent in retail and is omitted.
The random call carries the actual four arguments, including the shipped
source-path literal and source line1629. GameClientRandomValue's two apparent
arguments are a macro; treating it as a two-argument callee was incorrect.

The checksum path reads GlobalData+BD0, passes the identical scalar twice to
the independently matched100-byte Rva0009B4B0 wrapper, and stores the result;
BC8/BD4 are copied afterward. These remain address-derived fields, without
claiming a shipped INI value or speculative member name. The shared canonical
TheWritableGlobalData declaration is reused through a const layout view.
The hook slot is the independently authored BigObfSlot at012C233C; its pointers
at+0/+4/+88/+8C and32-byte Obf0009A430 constructor are established in
BigObfHookWrappers.cpp. No new assembly is used. A single caller input snapshot
and capturing the called hook only in the hot branch reproduce the native
argument spills and ECX-to-ESI lifetime. This does not claim additional helper
coverage or modify the already landed helper.

After enqueue, the caller invokes existing hideOptionsGadgets(true), then
hides2AC/264 and shows28C/294/2A4/29C. The request argument is intentionally
unused, consistent with RET4 and its System caller.

## Call and data contracts

The full inventory contains32 distinct direct callees, all already named.
The clean strict result has49 REL32 call sites,83 object relocations, zero
unresolved names and zero differing bytes. No symbols pins were added.

The local typed adapters preserve existing address-only ILT routes where
legacy declarations would assert the wrong contract:00037BD2 to000E1410 is
a const member taking an integer and returning a PlayerTemplate pointer;
000459B2 to00505670 is the existing145-byte member hide(bool), RET4, despite
the legacy free-function ledger label. Its full independent native owner in
WOLQuickMatchMenu.cpp already proves the228/23C/244/... gadget layout.
All other direct declarations use existing canonical headers or authored
callee contracts: PeerRequest constructor/destructor; PSPlayerStats destructor;
CalculateRank(const PSPlayerStats&); OptionPreferences ctor/dtor/firewall getter;
LadderPreferences ctor/dtor/loadProfile/write/addRecentLadder by16-byte value;
StringBase canonical string operations; vector<bool> erase/push_back; map
iterator increment; the real CRT strncpy and time imports; and the existing
obfuscated wrapper constructor/fallback. No caller-desired name was pinned.

Virtual slots reuse the independently landed online menu contracts. PS queue
+24 returns PSPlayerStats by hidden buffer; GameSpyInfo+70 returns profile ID
and+114 returns const AsciiString& (also stated in PeerDefsImplementation.h);
config+C/+1C/+20 are ping timeout, bot ID and QM channel; peer queue+18 takes
const PeerRequest&. The literal and native target checks remain part of the
normal add_match gate.

Data bases are consistent with the landed family: GameSpyInfo012F7194,
config012F70E4, PS queue012F76F0, peer queue012F71C8, ladder list012F70E8,
PlayerTemplate store012ED750, writable GlobalData012ED5C8, hook slot012C233C,
point bounds012B7224/012F481C, ping count012F4818 and disconnect table012B7228.
No new vtable or function-pointer identity is introduced.

Scratch receipts are build/four-hour-qmrequest/{retail.asm,callees.txt,
ghidra/0x00509b30.c,probe-clean.txt,strict-clean.txt,strict-result.json,
hide-options-retail.asm}. Earlier native forms and probes preserve the47-byte
CRC scheduling residue and the exact late-local/late-locals experiments.
