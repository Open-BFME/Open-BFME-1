// cl: /O2 /Ob0 /DNDEBUG /DWIN32 /D_WINDOWS /MD

class Rva000D3F10
{
	char m_pad[0x110];
	unsigned m_bits[8];

public:
	int test(unsigned index);
};

int Rva000D3F10::test(unsigned index)
{
	return (m_bits[index >> 5] & (1u << (index & 31))) != 0;
}
