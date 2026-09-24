# 0x00517050 LAN start-position method

The `BfmeAptScreenLanLobby` constructor at 0x00519F90 installs the secondary
vtable at VA 0x01105A28; the matched destructor at 0x005199A0 confirms that
owner. Slot 7 of that retail vtable points through ILT 0x00026A6C to the
267-byte body at 0x00517050. Slot 5 similarly reaches the separately matched
`BfmeAptScreenLanLobby::applySlotTeam` at 0x00516F00.

The body takes `GameSlot *` and an integer, writes the integer to slot+0x10,
and later formats the retail literal at VA 0x010FF184, `StartPos=%d`, with the
same value. The layout witness names `GameSlot+0x10` `m_startPos`. These
independent vtable, field, and literal facts support the
`applySlotStartPos` name; adjacency alone was not used to name it.

The host path resets LAN acceptance, requests serialized game info, and sets
a byte at receiver+0x14. The meaning of that byte is not independently
proven, so the C++ source keeps an offset-labelled field. The non-host path
formats and sends `StartPos=%d`. Direct calls resolve to the matched
`BfmeThing935B::bfmeGo935B` thunk, AsciiString constructors and format, and
StringBase release; their physical targets were checked with `tools/callees.py`
before the body was written. The 267-byte C++ probe matches all instructions
with 14 aligned relocation sites; the strict gate is the acceptance check.
