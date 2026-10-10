# AsciiString copy at RVA 0x00469AD0 (41 bytes)
Old: `?bfmeInitCGA@BfmeThingCGA@@QAEPAV1@PAXPAUBfmeSrcCGA@@@Z`
New: `??0Rva00469AD0@@QAE@ABVAsciiString@@ABURva00469AD0Value@@@Z`

The body is a constructor (returns this, ret 8) that copy-constructs its leading AsciiString via 0x00887B60 and copies a counted reference (count at +4 bumped when non-null) plus one word. Retail calls 0x00887B60 (and 0x00888BC0 where noted) directly;
those are the exported StringBase<char> constructors that AsciiString's inline
constructors reach (game/Libraries/Source/WWVegas/WWLib/ascii_string.h). The
old spelling called an invented pinned name at that address that nothing
defines, so the file could not link. tools/probe.py: EXACT with real
AsciiString. The owning class is unknown, so names keep the address.
