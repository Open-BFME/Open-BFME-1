# Vector erase at 000E5450

The complete 76-byte thiscall body takes two record pointers and returns the
first pointer, ending in ret 8. It calls the copy range helper through ILT
00027598 to 000E4AE0, destroys the tail through ILT0002F99B to 000E49E0,
and updates vector+4. The destruction loop advances by 12 bytes.

The complete 82-byte copy helper independently witnesses two DWORD fields at
record+0 and +4 and an owning AsciiString at +8. It copies the two DWORDs,
then calls the already pinned StringBase<char>::set at 00887C90. Its caller
pushes five cdecl arguments: source start, source end, destination, iterator
tag reference and null distance pointer. The helper reads the first three,
returns the advanced destination and uses plain ret. Canonical STLport emits
this helper exactly, including its call relocation through the existing pin.

The destructor is exactly eight bytes: add ecx,8 followed by a tail jump to
00887940, the independently matched narrow-string release routine. Byte nine
is INT3 padding. This disproves treating a differently routed destructor as
interchangeable merely because the vector instruction shape matched.

The game-level record identity remains unproven. Rva000E5450Record retains the
address and keeps both DWORD meanings opaque. Canonical STLport vector::erase
preserves the copy, destruction, end update and iterator-return order. New
pins name only the witnessed record destructor and typed copy helper at their
BODY addresses. The existing 76-byte claim is replaced, not additional
coverage. Existing copy-helper and destructor claims remain untouched.
