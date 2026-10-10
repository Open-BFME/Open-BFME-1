# AsciiString copy at RVA 0x0029C440 (37 bytes)
Old: `?bfmeGoDOC@BfmeThingDOC@@QAEPAVBfmeOtherDOC@@PAV2@H@Z`
New: `?rva0029C440@Rva0029C440@@QAE?AVAsciiString@@H@Z`

The body is a by-value getter: the hidden return slot is copy-constructed via 0x00887B60 from element `index` of a 4-byte-stride array at +0x38. Retail calls 0x00887B60 (and 0x00888BC0 where noted) directly;
those are the exported StringBase<char> constructors that AsciiString's inline
constructors reach (game/Libraries/Source/WWVegas/WWLib/ascii_string.h). The
old spelling called an invented pinned name at that address that nothing
defines, so the file could not link. tools/probe.py: EXACT with real
AsciiString. The owning class is unknown, so names keep the address.
