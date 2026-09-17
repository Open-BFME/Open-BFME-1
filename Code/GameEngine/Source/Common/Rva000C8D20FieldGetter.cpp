// ?get@Rva000C8D20Owner@@QBEHXZ
// Retail loads the dword at this+0x14 and returns it.
// The carved boundary proves the body, but no evidence proves a semantic owner.
// cl: /O2 /MD /EHsc-

class Rva000C8D20Owner
{
public:
	int get() const;

	char m_padding[0x14];
	int m_value;
};

int Rva000C8D20Owner::get() const
{
	return m_value;
}
