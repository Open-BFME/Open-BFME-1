// cl: /O2 /Ob0 /DNDEBUG /DWIN32 /D_WINDOWS /MD

class Rva00493E90
{
	unsigned char m_pad[0x20];
	unsigned char m_20 : 1;

public:
	unsigned char get() const;
};

unsigned char Rva00493E90::get() const
{
	return m_20;
}
