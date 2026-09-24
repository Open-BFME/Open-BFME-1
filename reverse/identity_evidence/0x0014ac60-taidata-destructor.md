# TAiData complete destructor at 0x0014AC60

The matched `TAiData` constructor at 0x0014B150 installs vtable
0x01095754. Its slot zero reaches the matched scalar-deleting destructor
at 0x0014AD90 through retail ILT 0x00007941. That wrapper calls retail ILT
0x00004499, which jumps to the 215-byte body at 0x0014AC60. The body itself
installs vtable 0x01095754 and restores base vtable 0x01073744 before return.
These independent constructor, vtable and caller observations establish the
complete destructor's `TAiData` name and thiscall entry ABI.

The body clears and deletes three lists in order: head +0xEC with link
+0x1BC, head +0xF4 with link +0x10, and head +0xF0 with link +0x0C. It
then releases the one-word strings at +0xE0, +0xDC and +0xD8. The matched
`AI::newOverride` at 0x0014E2B0 independently identifies +0xEC as
`m_sideInfo`, +0xF0 as `m_sideBuildLists`, +0xF4 as `m_namedLists` and
+0xF8 as the previous `TAiData` link. Its copy loops read the same three
node-link offsets. This corrects the older local labels in `TAiDataCtor.cpp`
and `TAiDataAssign.cpp` that treated +0xF4 as `m_next` and +0xF8 as an
unidentified field; the new destructor uses the matched copy's field names.

The body has three direct calls to 0x00887940, whose canonical matched object
symbol is `StringBase<char>::releaseBuffer`. Virtual deletion of list nodes
uses slot zero with deleting flag one, as seen in the retail instructions.
