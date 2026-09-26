// ?mouseHasAnyCursorImage@@YAHXZ
struct Rva005A63D0Cursor { int m_pad0[6]; void* m_image; int m_pad1[2]; void* m_shadow; int m_pad2[2]; void* m_mask; };
struct Rva005A63D0Mouse { char m_pad[0x4d10]; Rva005A63D0Cursor m_cursor; };
extern Rva005A63D0Mouse* TheMouse;
int mouseHasAnyCursorImage()
{
	Rva005A63D0Cursor* c = &TheMouse->m_cursor;
	if (c && (c->m_image || c->m_shadow || c->m_mask))
		return 1;
	return 0;
}
