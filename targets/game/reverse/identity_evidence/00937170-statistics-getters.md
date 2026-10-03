# Seven texture-statistics getters

Each entry at RVA00937170/180/190/1A0/1B0/1C0/1D0 is six complete bytes:
one EAX load or immediate address followed by RET, then ten INT3 bytes.
The prior aligned getter00937160 also has this boundary. Ghidra read_memory
at VA00D37170 and the baseline independently agree through all112 bytes.
No getter uses incoming ECX or a stack argument; none calls another body.

The Zero Hour `GeneralsMD/Code/Libraries/Source/WWVegas/WW3D2/statistics.cpp`
lines227..265 and statistics.h give the independent free-cdecl getter
contract: signed int counts/sizes, and `const StringClass&` for the final
string accessor. The latter returns the object's address, not its first
word or a character pointer. All entry names remain address-qualified.

Global identity is not guessed from adjacent data. The already-matched
957-byte `Record_Texture_End` at00937900 was strictly reverified before any
source edit. Its compiled DIR32 operands independently map the existing
TU-static variables to these retail homes:

| Getter RVA | Existing producer variable | VA | Producer relocation offset |
| --- | --- | --- | --- |
| 00937170 | lastFrameTextureCount | 01346DF4 | +21 |
| 00937180 | lastFrameTextureChangeCount | 01346E24 | +67 |
| 00937190 | lastFrameLightmapTextureMemory | 01346E34 | +51 |
| 009371A0 | lastFrameLightmapTextureCount | 01346DE8 | +5C |
| 009371B0 | lastFrameProceduralTextureMemory | 01346E3C | +44 |
| 009371C0 | lastFrameProceduralTextureCount | 01346E38 | +74 |
| 009371D0 | textureStatisticsString | 01346E74 | +6E and19 more uses |

The producer follows the upstream last-frame assignments, and its string
uses already include the canonical wwstring.h type. Keeping the getters in
that same TU makes ordinary DIR32 consistency verify each new read/address
against the existing writes and string operations. No duplicate data pin,
standalone extern alias, global definition or string type is introduced.
The producer and every individually added getter must retain strict gates.
