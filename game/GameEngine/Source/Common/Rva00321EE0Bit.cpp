// cl: /O2 /Ob0 /DNDEBUG /DWIN32 /D_WINDOWS /MD

class Rva00321EE0
{
	unsigned char m_pad[0x344];
	unsigned char m_344;

public:
	int get() const;
};

int Rva00321EE0::get() const
{
	return (m_344 >> 2) & 1;
}
