// ?mouseHasAnyCursorImage@@YAHXZ
struct Rva005A63D0Cursor { int m_pad0[6]; void* m_image; int m_pad1[2]; void* m_shadow; int m_pad2[2]; void* m_mask; };
struct Rva005A63D0Mouse { char m_pad[0x4d10]; Rva005A63D0Cursor m_cursor; };
// Retail's singleton at 0x012F4C5C is EA's Mouse *TheMouse; (defined once in
// GameClient/Input/Mouse.cpp).  This TU keeps its own view of the layout and
// casts at the use so the reference links to the one global.
class Mouse;
extern Mouse* TheMouse;
int mouseHasAnyCursorImage()
{
	Rva005A63D0Cursor* c = &((Rva005A63D0Mouse*)TheMouse)->m_cursor;
	if (c && (c->m_image || c->m_shadow || c->m_mask))
		return 1;
	return 0;
}
