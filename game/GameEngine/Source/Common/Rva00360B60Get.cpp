// cl: /O2 /Ob0 /DNDEBUG /DWIN32 /D_WINDOWS /MD

class Rva00360B60
{
	unsigned char m_pad[4];
	char *m_4;

public:
	char *get() const;
};

char *Rva00360B60::get() const
{
	return m_4 - 0x58;
}
