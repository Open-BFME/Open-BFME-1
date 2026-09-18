// cl: /DNDEBUG /DWIN32 /MD
//
// The carved body returns the dword at this plus 0x24. Its semantic owner is
// unknown, so the source class keeps the retail address.

class Rva007E3A00
{
public:
	int get() const;

private:
	char m_unknown[ 0x24 ];
	int m_value;
};

// ?get@Rva007E3A00@@QBEHXZ
int Rva007E3A00::get() const
{
	return m_value;
}
