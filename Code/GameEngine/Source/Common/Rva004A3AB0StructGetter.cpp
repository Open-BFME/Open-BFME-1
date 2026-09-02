// cl: /O2 /DNDEBUG /DWIN32 /D_WINDOWS /MD

struct BfmeSix4A3AB0
{
	int m_a;
	int m_b;
	int m_c;
	int m_d;
	int m_e;
	int m_f;
};

class BfmeThing4A3AB0
{
public:
	BfmeSix4A3AB0 getSomething() const;

private:
	char m_pad[0x15C];
	BfmeSix4A3AB0 m_value;
};

// ?getSomething@BfmeThing4A3AB0@@QBE?AUBfmeSix4A3AB0@@XZ
BfmeSix4A3AB0 BfmeThing4A3AB0::getSomething() const
{
	return m_value;
}
