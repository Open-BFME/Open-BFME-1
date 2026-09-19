// cl: /O2 /Ob1 /DNDEBUG /DWIN32 /D_WINDOWS /MD

// The carved body at 0x007E39F0 reads a dword at this plus 0x1c.
// The nearby bodies do not prove a semantic owner, so the class keeps the RVA.
class Rva007E39F0DwordGetter
{
public:
	int get() const;

private:
	unsigned char m_padding[0x1c];
	int m_value;
};

// ?get@Rva007E39F0DwordGetter@@QBEHXZ
int Rva007E39F0DwordGetter::get() const
{
	return m_value;
}
