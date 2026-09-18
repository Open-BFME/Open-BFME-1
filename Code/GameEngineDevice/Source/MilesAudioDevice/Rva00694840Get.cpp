// cl: /O2 /Ob0 /DNDEBUG /DWIN32 /D_WINDOWS /MD
// Retail 0x00694840 reads the dword at this + 0x30.

class Rva00694840
{
	unsigned char m_padding[0x30];
	unsigned m_value;

public:
	unsigned get();
};

unsigned Rva00694840::get()
{
	return m_value;
}
