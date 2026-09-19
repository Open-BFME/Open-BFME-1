// cl: /DNDEBUG /DWIN32 /D_WINDOWS /MD /EHsc
// The carved six-byte body returns the address-derived owner's first field plus 0x10.

class Rva004AFB70Owner
{
public:
	char *offset10();

private:
	char *m_base;
};

char *Rva004AFB70Owner::offset10()
{
	return m_base + 0x10;
}
