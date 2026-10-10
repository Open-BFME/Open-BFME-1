# AsciiString copy at RVA 0x00094790 (26 bytes)
Old: `?bfmeGoBMA@BfmeThingBMA@@QAEPAV1@PAX0@Z`
New: `??0Rva00094790@@QAE@ABVAsciiString@@PAX@Z`

The body is a constructor (returns this, ret 8) that copy-constructs its leading AsciiString from the first argument via StringBase<char> copy ctor 0x00887B60 (exported ??0?$StringBase@D@@AAE@ABV0@@Z) and stores the second word at +4. Retail calls 0x00887B60 (and 0x00888BC0 where noted) directly;
those are the exported StringBase<char> constructors that AsciiString's inline
constructors reach (game/Libraries/Source/WWVegas/WWLib/ascii_string.h). The
old spelling called an invented pinned name at that address that nothing
defines, so the file could not link. tools/probe.py: EXACT with real
AsciiString. The owning class is unknown, so names keep the address.
