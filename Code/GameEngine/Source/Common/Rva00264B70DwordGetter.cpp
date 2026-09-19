// cl: /O2 /Ob0

// Retail 0x00264B70 returns the dword at this+4. The carved boundary and ILT
// thunk 0x00013106 prove the member ABI, but no evidence names the owner.

class Rva00264B70DwordField
{
public:
	unsigned int get() const;

private:
	unsigned char m_padding[4];
	unsigned int m_value;
};

unsigned int Rva00264B70DwordField::get() const
{
	return m_value;
}
