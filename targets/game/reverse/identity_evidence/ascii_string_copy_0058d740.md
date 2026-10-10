# AsciiString copy at RVA 0x0058D740 (37 bytes)
Old: `?bfmeGoDQC@BfmeThingDQC@@QAEPAVBfmeOtherDQC@@PAV2@@Z`
New: `?rva0058D740@Rva0058D740@@QAE?AVAsciiString@@XZ`

The body is a by-value getter: the hidden return slot is copy-constructed via 0x00887B60 from +0x84 of the object at this+4. Retail calls 0x00887B60 (and 0x00888BC0 where noted) directly;
those are the exported StringBase<char> constructors that AsciiString's inline
constructors reach (game/Libraries/Source/WWVegas/WWLib/ascii_string.h). The
old spelling called an invented pinned name at that address that nothing
defines, so the file could not link. tools/probe.py: EXACT with real
AsciiString. The owning class is unknown, so names keep the address.
