# parseFont: canonical AsciiString declaration

RVA `0x00485B50`, 309 bytes, `?parseFont@@YA_NPADPAVWinInstanceData@@0PAX@Z`.
The existing source redefined AsciiString despite the canonical
`game/Libraries/Source/WWVegas/WWLib/ascii_string.h`. AGENTS.md requires
“never redeclare a type a header already covers: #include it”.

The Zero Hour twin is GameClient/GUI/GameWindowManagerScript.cpp:595–637,
registered by its window field table. This repair retains the existing name,
font-library pointer/Real ABI, and instance-data view; it introduces no new
identity, member, pin, extent, or shared-header change. This row itself is not
among the surviving August 1 claims. Fresh origin/master still has the old
local string declaration and the same row. The bounded full pickaxe query
expired after 15 seconds; the current origin source/row were checked directly.

Ghidra MCP at VA `0x00885B50` and the unpacked retail PE show the complete
309-byte SEH function: constructor call at RVA `0x00485C13` targets
StringBase<char>'s C-string constructor `0x00888BC0`; call `0x00485C40`
reaches ILT `0x0000ABC3` -> `0x004772D0`; the string cleanup at
`0x00485C56` reaches releaseBuffer `0x00887940`. RET is `0x00485C84`,
followed by five INT3 bytes starting `0x00485C85`. `tools/callees.py`
confirms those three direct call routes. The eight imported calls are
strtok/sscanf through the existing IAT bindings.

Use the canonical string header and an explicit scoped `AsciiString name`
with `&name` for the existing pointer parameter. The scope preserves cleanup
before testing/storing the returned font. The obsolete stringinline include
path is removed. Other pre-existing ABI views are unchanged; this note does
not assert universal type/header compliance for this translation unit.

Both scoped gates pass 1/1 functions, eight complete string references and
four recorded DIR32 references. This is a declaration hygiene repair, with
zero added byte coverage. Logs: `build/audit_v3/s5_parsefont_before.log` and
`s5_parsefont_after.log`; the unmodified source snapshot is
`s5_parsefont_before.cpp`. No ledger or baseline changes.
