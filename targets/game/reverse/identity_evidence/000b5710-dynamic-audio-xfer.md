# RVA 000B5710 owner and setter audit

Audit and reconstruction, 2026-10-03. Independent PE/Capstone evidence and Ghidra MCP agree on the original bytes and references. All addresses below are RVA unless explicitly marked VA.

## Result

The receiver is the BFME dynamic audio-info subclass of AudioEventInfo. The combination of (1) independently traced audio dictionary caller, (2) constructor/base-constructor/vtable/destructor chain, (3) literal-backed audio-field tables, (4) original-name retention helper, and (5) EA's DynamicAudioEventInfo declarations supports **DynamicAudioEventInfo::xferNoName(Xfer*)** at B5710. This is not an identity inferred from adjacency or from a byte match.

The seven AF9xx helpers operate on the AudioEventInfo base fields. Their source-level base-member SPELLINGS are not supplied by the available vendor header. Preserve address-derived helper names rather than inventing setVolume/setMaxRange/etc. The conflicting PhysicsBehavior/MaterialPassClass/Shadow/GameInfo names are not supported by any original caller to these addresses.

## Independent caller, literal and float-ABI proof

Original B6030 obtains audio-info through TheAudio VA012ED668 vslot +118, allocates A4 bytes and calls constructor ILT 2C5B1 -> B5CB0. On the resulting receiver, it reads the following static NameKeys. Each is two DWORDs; second points to the indicated literal in the original PE:

| NameKey VA | Literal VA/text | Override call site | Route | Marked bit | Base helper |
|---|---|---|---|---|---|
| 012A78E0 | 0107D124 objectSoundAmbientLooping | B6279 | 203C9 -> B5650 | 2 | AF960 / AF980 |
| 012A78E8 | 0107D144 objectSoundAmbientMinVolume | B62A9 | 3B74B -> B56A0 | 10h | AF9B0 |
| 012A78F0 | 0107D168 objectSoundAmbientVolume | B62D9 | 333ED -> B5690 | 8 | AF9A0 |
| 012A78F8 | 0107D188 objectSoundAmbientMinRange | B6309 | 43342 -> B56B0 | 20h | AF9C0 |
| 012A7900 | 0107D1A8 objectSoundAmbientMaxRange | B6339 | 2BC24 -> B56C0 | 40h | AF9D0 |
| 012A7908 | 0107D1C8 objectSoundAmbientPriority | B6361 | 27877 -> B56D0 | 80h | AF9E0 |

For all four Real fields the dictionary accessor returns through ST(0): B6295/B62C5/B62F5/B6325 are FSTP DWORD PTR [esp+40h], then the unchanged DWORD is pushed into the relevant override helper. Each override marks its bit and tailjumps through the corresponding base-setter ILT without changing that argument. This independently proves the setter input is float, even though each ten-byte setter copies with integer MOVs. The priority accessor result EAX is pushed directly. B5650 reads the low argument byte as bool, marks bit 2, overwrites the argument with DWORD 1, then tailjumps to the flag-set/clear helper.

EA vendor evidence: GeneralsMD/Code/GameEngine/Source/GameLogic/Object/Object.cpp lines 3624-3727 describes this exact dynamic-audio dictionary customization sequence, including a DynamicAudioEventInfo copy of AudioEventInfo and overrideLoopFlag, overrideMinVolume, overrideVolume, overrideMinRange, overrideMaxRange, overridePriority. BFME omits the old LoopCount transfer/customization but preserves that bit position.

## Constructor, vtable, and original-name chain

- B5450: calls 1BB7B -> B0D10, the independently identified AudioEventInfo default constructor. Installs VA010827DC, clears +98 and +9C, writes the extra BFME argument at +A0; returns this, RET 4. The extra argument's semantics remain unclaimed.
- B5CB0: calls 13C73 -> B5B10, the independently identified AudioEventInfo copy constructor. Installs the same vtable and initializes +98/+9C/+A0; RET 8.
- VA010827DC has code references from these two constructors and B5240 only. B5240 destructor releases the string at +9C and calls AudioEventInfo destructor B0DF0.
- B5610: before renaming, copies original string +8 to +9C once, marks bit 1 at +98, then forwards the new string. Independent matched Drawable::mangleCustomAudioName at 417330 calls B5610 via 1D002 after formatting ` CUSTOM %d `. EA DynamicAudioEventInfo::overrideAudioName/getOriginalName has the same distinct protocol.
- B56F0 returns +9C when bit 1 at +98 is set, otherwise +8. This matches getOriginalName.
- Independent Drawable::xfer 41D290 calls 198CB -> B5710 at 41DE18 (the new derived object, after constructor and mangleCustomAudioName) and 41DF7D (saving existing custom audio). The caller serializes the original name separately through Xfer slot +68 before B5710.
- No `DynamicAudioEventInfo` class-name string exists in the PE. The conclusion is from the linked behavioral/constructor graph and EA's source, not a claimed RTTI hit.

## Exact field witnesses and helper ABIs

Original INI FieldParse table VA010813F8 independently supplies these fields. Volume and MinVolume use percent-to-real parser VA00C52EE0; ranges use real parser VA00C52B20; Priority uses enum parser VA00C51050 and name table VA012A821C; Control uses bit-string parser VA00C50E70 and table VA012A8264.

| Body RVA | Size | ILT RVA | Witnessed receiver contract |
|---|---:|---|---|
| AF960 | 15 | 302E7 | thiscall, one 32-bit flag mask, [this+3C] |= mask, RET 4 |
| AF980 | 17 | 45179 | thiscall, one 32-bit flag mask, [this+3C] &= ~mask, RET 4 |
| AF9A0 | 10 | 242A3 | thiscall, float input, stores bits at +10 (Volume), RET 4 |
| AF9B0 | 10 | 2F699 | thiscall, float input, stores bits at +18 (MinVolume), RET 4 |
| AF9C0 | 10 | 16455 | thiscall, float input, stores bits at +74 (MinRange), RET 4 |
| AF9D0 | 10 | 1AD2A | thiscall, float input, stores bits at +78 (MaxRange), RET 4 |
| AF9E0 | 10 | 3990A | thiscall, 32-bit AudioPriority enum input, stores at +34, RET 4 |

Original B51C0 and B51D0 are FLD DWORD [ECX+74h/78h]; RET, corroborating the range types.

All seven bodies have only the one listed original ILT reference in Ghidra. Each ILT has only B5710 and the corresponding dynamic override helper as code users. In particular AF9D0 is NOT established as PhysicsBehavior::setExtraBounciness, and AF9E0 is NOT established as any of MaterialPassClass::Set_Cull_Volume, Shadow::setAngle, GameInfo::setLocalIP. Those ledger identities have no original caller evidence at these addresses; byte-identical assignment bodies are not identity evidence. Do not route audio calls through any of those named declarations.

## Actual Xfer slots, independently verified in PE

Existing game/GameEngine/Source/Common/System/xfer.h is the BFME declaration to reuse. Do not use the incompatible reference/shims/xfer/Common/Xfer.h.

Original base vtable VA01129258 contains:

| Slot offset | Original target | Contract and witness |
|---|---|---|
| +04 | ILT 4A7FA -> 6B1C0 | bool IsLoading() const (overridden by load implementations) |
| +28 | 9D6430 | Xfer& operator==(Xfer::Version&), two-byte version record |
| +6C | ILT 2A4D2 -> 6B360 | Xfer& operator==(float&); forwards 4 bytes with tag 7265616Ch (`real`) |
| +84 | ILT 2A306 -> 6B210 | Xfer& operator==(unsigned char&); forwards 1 byte with tag 75627974h (`ubyt`) |
| +8C | ILT 38866 -> 6B240 | Xfer& operator==(bool&); forwards 1 byte with tag 626F6F6Ch (`bool`) |

The scalar wrappers return this in EAX and RET 4. B5710's first virtual call passes ONE pointer to TWO bytes initialized to 1; the bank's uint/void virtual signatures happen to have compatible low-level call shapes but are not truthful contracts.

## Suggested narrow integration

- Include EA DynamicAudioEventInfo.h to reuse the real xferNoName(Xfer*) declaration; include existing BFME System/xfer.h for the actual Xfer ABI.
- Never access the inherited ZH fields through their vendor layout. The BFME base is 98h bytes and derived object A4h; use a separate address-derived BFME physical receiver view for the witnessed fields. Do not emit a new DynamicAudioEventInfo constructor/vtable from this TU.
- Reuse Rva000AF960Object::addFlags/removeFlags for the already honest flag-helper identities. For the five scalars, use address-derived receiver/helper names with float/AudioPriority inputs; this avoids claiming unavailable base-member source spellings. One TU-local physical view can hold the five helper declarations without changing a shared header.
- Retire/repair conflicting real-name ledger claims only with their own owner evidence. This audit proves the audio body ownership, not the true addresses of those unrelated real methods.
- Owner identity and field semantics do NOT justify broad semantic renaming outside the scoped body/dependencies.

## Reconstruction verification

The canonical vendor method declarations plus the existing BFME Xfer header
reproduce all 609 bytes. A single witnessed physical receiver view retains the
BFME offsets without redeclaring either real class or accessing ZH data fields.
The four Real setters and the priority setter are each exact at 10 bytes.
The five native DynamicAudioEventInfo override forwarders are exact at
12/12/12/12/15 bytes. Their existing no-argument Gen models accidentally
preserved tail-jump instruction bytes while losing the live stack argument.

The scalar helper source spellings remain unavailable, so only those helpers
use address-derived names. Existing Rva000AF960Object flag operations remain
canonical and are reused. No new shadow/physics/material/network alias is
introduced. Retired incompatible names are not evidence for the actual
addresses of those unrelated methods.
