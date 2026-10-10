# AsciiString copy at RVA 0x002937B0 (26 bytes)
Old: `?bfmeInitBME@BfmeThingBME@@QAEPAV1@XZ`
New: `??0Rva002937B0@@QAE@XZ`

The body is a default constructor (returns this, no arguments) that zeroes +0 and builds the AsciiString at +4 via StringBase<char>(const char *) 0x00888BC0 (exported ??0?$StringBase@D@@AAE@PBD@Z) from the empty-string literal. Retail calls 0x00887B60 (and 0x00888BC0 where noted) directly;
those are the exported StringBase<char> constructors that AsciiString's inline
constructors reach (game/Libraries/Source/WWVegas/WWLib/ascii_string.h). The
old spelling called an invented pinned name at that address that nothing
defines, so the file could not link. tools/probe.py: EXACT with real
AsciiString. The owning class is unknown, so names keep the address.
