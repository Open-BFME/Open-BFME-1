# 0x004368D0: StringInfo::StringInfo, not the STLport pair ctor

BFME 1 target evidence (retail 1.03 unpacked):

- 0x004368D0 (16 B: `mov eax,ecx; mov [eax],0; mov [eax+4],0; ret`)
  was rowed as `?dup_004368d0@@YAXXZ` with object-symbol
  `??0?$pair@VAsciiString@@M@_STL@@QAE@XZ` (GameAudio.cpp pair use).
- The body is reached through ILT 0x00006604 (`e9 c7024300`).
  Three matched StringInfo array-new call sites pass exactly that
  address as the element constructor: GameTextManagerParseCSF.cpp
  (`new StringInfo[numLabels]`), GameTextManager_initMapStringFile_Thunk.cpp
  (`new StringInfo[m_mapTextCount]`), GameTextManager_init.cpp. A
  matched caller naming the symbol is the strongest evidence; three
  independent ones name it here.
- The pair reading has zero callers: GameAudio.cpp's `newPair` local
  inlines the pair constructor (its object references no pair-ctor
  symbol), so the pair COMDAT is emitted but never called. Its bytes
  match only because any 8-byte zeroing ctor compiles identically.
- The zeroing shape fits StringInfo exactly: BFME's StringInfo is
  8 bytes `{ AsciiString label; UnicodeString text; }` with no speech
  field (see GameText.cpp), and both members default to null stores.
  (AsciiString's default ctor is already proven inline in
  ascii_string.h; the UnicodeString header asymmetry is what made the
  old implicit copy wrong -- see below.)
- dir32_addresses.csv already records `??0StringInfo@@QAE@XZ` at the
  call address 0x00406604.

Donor evidence (open-bfme-2 beed8a16790a6812231ac7b05e3e6893e4cb5d1b,
Zero Hour GeneralsMD):

- Zero Hour's GameText.cpp StringInfo keeps a third `AsciiString
  speech` member (12 bytes); BFME 2's GameText.cpp StringInfo is the
  8-byte `{ label; text; }` pair, matching BFME 1. Donor confirms the
  struct, not the ctor body.

Correction:

- `?dup_004368d0@@YAXXZ` is re-homed to `??0StringInfo@@QAE@XZ` via
  add_match --correct-identity. GameAudio.cpp keeps emitting its
  pair-ctor COMDAT for its own (inlined, self-satisfying) use; with
  no row left under the pair name that copy is address-less and
  harmless.
- The provider TU StringInfoCtor.cpp keeps a TU-local void* member
  view (layout-identical; string semantics stay in the consumers),
  mirroring StringInfoDestructorThunk.cpp's TU-local member view.
  ParseCSF's struct now declares the ctor instead of emitting the
  non-retail implicit copy (which called the header's out-of-line
  UnicodeString ctor through 69 bytes of EH frame).
- A symbols.csv pin binds `??0StringInfo@@QAE@XZ` at ILT 0x00006604
  with route=0x004368D0 so the array-new references resolve to the
  call address retail encodes.
