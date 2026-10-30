# 0x006077C0 SoundState field callback and its FieldParse table VA 0x01115814

BFME 1 target facts (retail 1.03 unpacked image):

- 0x006077C0..0x006078E3 (291 B) ends at `ret` followed by int3 padding; its only
  reference is ILT 0x0001D55C, whose VA is the callback word of the FieldParse
  entry at RVA 0x00D15860 {token VA 0x01115850 "SoundState", 0x0041D55C, 0, 0}.
  The body therefore has the cdecl FieldParse callback contract
  `(INI *, void *instance, void *store, const void *userData)`; it reads only
  `ini` and `instance`.
- It constructs a 0x1F0-byte local through ILT 0x00043504 (-> 0x006070E0),
  parses its +0 flags through ILT 0x00033433 (-> 0x00209240, BitFlags<117>::parse
  with a null AsciiString*), builds a MultiIniFieldParse from table VA 0x01115814
  (offset 0) and ILT 0x0002698B (-> getVoiceFieldParse, offset 0x28), calls
  INI::initFromINIMulti on the local, then inlines vector push_back on
  instance+8: copy through ILT 0x00010AAA (-> 0x006071C0) or
  _M_insert_overflow through ILT 0x0003350A (-> 0x00607570). EH state 0 unwinds
  through ILT 0x000075EF (-> 0x00606F70), state 1 is placement delete (ILT
  0x0002AAA9).
- Table VA 0x01115814 (RVA 0x00D15814), 48 bytes: {VA 0x01092414
  "UnitSpecificSounds", 0x004417FE -> 0x00545FC0 parsePerUnitSounds, 0, 0x1DC},
  {VA 0x010924F4 "VoicePriority", 0x004348A1 -> 0x00606890 u4IniFlag00606890,
  0, 0x1E8}, all-zero terminator. Bytes 0x00D15844..0x00D1584F are zero padding
  before the "SoundState" literal at 0x00D15850.

Naming: the callback name keeps its address; "SoundState" is the retail INI
token that selects it. The element type has three disagreeing placeholder
spellings in the ledger (Gen00606F70 / pair<Gen_t_00607280_*> /
Rva00607770Element), so the ctor, flags parser and copy are called through the
ILT thunks' own names and the destructor through the existing
`??1Gen000075EF@@QAE@XZ` ILT pin; no new pin is added.
