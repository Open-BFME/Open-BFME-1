// cl: /O2 /Ob1 /DNDEBUG /DWIN32 /D_WINDOWS /MD
// ?get@Rva00629E70DwordGetter@@QBEHXZ
// Retail 0x00629E70 is a const thiscall getter for the dword at this+0x1c.
// The adjacent Team list bodies place this address in the same AI family,
// but the semantic field name is not proven, so the class keeps the RVA.

class Rva00629E70DwordGetter
{
public:
	int get() const;

private:
	unsigned char m_padding[0x1c];
	int m_value;
};

int Rva00629E70DwordGetter::get() const
{
	return m_value;
}
