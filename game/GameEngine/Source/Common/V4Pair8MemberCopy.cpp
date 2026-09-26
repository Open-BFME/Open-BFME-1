// One 24-byte __thiscall member that copies an eight-byte member out through a
// pointer argument:
//
//     mov edx,[ecx+0xBC] / mov eax,[esp+4] / mov [eax],edx
//     mov ecx,[ecx+0xC0] / mov [eax+4],ecx / ret 4
//
// WHAT THE BYTES SHOW.  Two dwords are moved from consecutive member offsets to
// consecutive offsets of the pointed-at object, with the destination pointer
// loaded once in between.  Integer `mov` for both halves and no x87 anywhere is
// how MSVC 7.1 copies a small POD STRUCT wholesale -- copying two float members
// one at a time would have used the x87 stack -- so this is one eight-byte
// member assigned to `*out`, not two separate field assignments.  The trailing
// `ret 4` pops the single pointer argument.
//
// The destructive load `mov ecx,[ecx+0xC0]` reuses the receiver register for the
// second half, which is only legal because `this` is dead afterwards: nothing
// else in the body touches it.
//
// IDENTITY IS NOT RECOVERED.  Both names are derived from an address.

struct GenPair8
{
	int m_at00;
	int m_at04;
};

class Rva003BD680
{
public:
	void     get( GenPair8 * out );
	char     m_pad00[ 0xBC ];
	GenPair8 m_at0BC;
};
void Rva003BD680::get( GenPair8 * out )
{
	*out = m_at0BC;
}
