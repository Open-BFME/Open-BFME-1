# 0x0013A4E0 and 0x009DB7A0 are StringClass's, not TeamsInfo's

Two bodies each carried a TeamsInfo name on top of a StringClass name:

| Address | Kept | Retired |
|---|---|---|
| 0x0013A4E0 (84 B) | `??_EStringClass@@QAEPAXI@Z` (rendobj.cpp) | `??_ETeamsInfo@@QAEPAXI@Z` (SidesList.cpp) |
| 0x009DB7A0 (117 B) | `?Free_String@StringClass@@AAEXXZ` (wwstring.cpp) | `??1TeamsInfo@@QAE@XZ`, an object-symbol alias of Free_String |

The vector deleting destructor pushes element size 4 and element destructor ILT
0x0001A41F. That ILT leads to 0x0013A050, whose whole body is `jmp 0x009DB7A0`, into
StringClass::Free_String. The scalar path calls 0x009DB7A0 directly. This is what
StringClass's inline `~StringClass() { Free_String(); }` compiles to: the out-of-line
copy is a tail jump, and the scalar path inlines it. rendobj.cpp reproduces both
halves under the StringClass name.

TeamsInfo holds a Dict, so its destructor ends in `Dict::releaseData` (0x000681C0,
ILT 0x00014475) and cannot reach Free_String. SidesList.cpp's row only matched
because the alias row made `??1TeamsInfo` resolve to Free_String's body, and the
`??1TeamsInfo` pin at 0x00008CBA (DefaultDrawModuleInfo's destructor ILT) was a third,
unrelated address. Retail contains no call to 0x0013A4E0 or to its ILT 0x00036764,
so no caller names the element type either way.
