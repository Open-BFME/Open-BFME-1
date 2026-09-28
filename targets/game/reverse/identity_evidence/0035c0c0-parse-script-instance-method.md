# The 0x0035C0C0 Script chunk reader is not `Script::ParseScript`

The 579-byte body at 0x0035C0C0 was filed as
`?ParseScript@Script@@SAPAV1@AAVDataChunkInput@@G@Z` by the Open-BFME5
`*Thunk.cpp` lift. The mangled name is contradicted by the body on three
independent counts, so the bytes keep an address-keyed name.

- `mov esi,ecx` at +0x24 followed by stores at `ES+0x04` .. `ES+0x1A`. The
  frame keeps ECX and writes through it, so the body is a `__thiscall`
  INSTANCE method. `SA` (static) cannot take a this pointer.
- The epilogue is `push esi / mov ecx,edi / call 0x00428BFA` and then
  `ret 8`, with the result of `DataChunkInput::parse` in AL. There is no
  `operator new` anywhere in the 579 bytes, so the return type is `bool`
  (`QAE_N`), not `Script *` (`SAPAV1@`). Retail does not allocate: the caller
  passes the object in.
- The only stack parameter read is `[esp+0x2c]`, compared as a WORD
  (`cmp word ptr [esp+0x2c],bx` with `ebx=2`) -- the `G` unsigned short the
  name already carried. The `ret 8` matches exactly two stack parameters, so
  the body is `(DataChunkInput &, unsigned short)`, not the name's shape in any
  other respect.

The CLASS is proven, so only the method name keeps the address token. The
member store pattern is the exact layout the landed BFME ctor
`ScriptCtor.cpp` carries:

| retail offset | store | landed member |
| --- | --- | --- |
| +0x04 | `StringBase<char>::set` 0x00887C90 fed by `readAsciiString` | `m_scriptName` |
| +0x08 | same | `m_comment` |
| +0x0C | same | `m_conditionComment` |
| +0x10 | `readInt` 0x0003A805 under `version >= 2` | `m_delayEvaluationSeconds` |
| +0x14 +0x15 | one `readByte` result stored twice | `m_isActive`, `m_isOneShot` |
| +0x16 | `readByte` | `m_easy` |
| +0x18 +0x19 +0x1A | `readByte` | `m_normal`, `m_hard`, `m_bfmeFlag` |
| +0x17 | `readByte`, last | `m_isSubroutine` |

The three nested parsers it registers name Script's own children: parent
`"Script"` (0x010E8470) with `"OrCondition"` (0x010E8AD4) through ILT 0x00416568
-> 0x0035B700 `?ParseOrConditionDataChunk@OrCondition@@` (landed,
OrCondition_ParseOrConditionDataChunk_Thunk.cpp), `"ScriptAction"`
(0x010E7CD0) through 0x0042F70C -> 0x00358FE0
`?ParseActionDataChunk@ScriptAction@@` (landed,
ScriptsParseActionDataChunkThunk.cpp), and `"ScriptActionFalse"`
(0x010E8520) through 0x00425DE2 -> 0x00359030
`?ParseActionDataChunk00359030@ScriptAction@@`, the false-action twin
(ScriptsParseActionFalseDataChunkThunk.cpp, reads the list head at +0x24).
The read order of the seven flags (0x14, 0x15, 0x16, 0x18, 0x19, 0x1A, 0x17)
differs from the member declaration order, which is what the landed ctor's
member list predicts and no other class in the tree predicts.

The body is landed as
`?Rva0035C0C0@Script@@QAE_NAAVDataChunkInput@@G@Z` in
game/GameEngine/Source/GameLogic/ScriptEngine/ScriptRva0035C0C0Parse.cpp, and
the naked lift file is deleted.
