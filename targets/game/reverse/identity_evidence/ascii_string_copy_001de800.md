# AsciiString copy at RVA 0x001DE800 (36 bytes)
Old: `?bfmeInitBWC@BfmeThingBWC@@QAEPAV1@PAX@Z`
New: `??0Rva001DE800@@QAE@ABVAsciiString@@@Z`

The body is a constructor (returns this, ret 4) that copy-constructs its leading AsciiString via 0x00887B60 and zeroes the five following words. Retail calls 0x00887B60 (and 0x00888BC0 where noted) directly;
those are the exported StringBase<char> constructors that AsciiString's inline
constructors reach (game/Libraries/Source/WWVegas/WWLib/ascii_string.h). The
old spelling called an invented pinned name at that address that nothing
defines, so the file could not link. tools/probe.py: EXACT with real
AsciiString. The owning class is unknown, so names keep the address.
