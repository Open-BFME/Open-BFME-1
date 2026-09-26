// cl: /O2 /Ob0 /DNDEBUG /DWIN32 /D_WINDOWS /MD

class Rva00412FA0
{
	char m_pad0[0x38];
	int m_38;
	char m_pad1[0x16C - 0x38 - 4];
	int m_16C;
	char m_pad2[0x185 - 0x16C - 4];
	unsigned char m_185;

public:
	void *select() const;
};

void *Rva00412FA0::select() const
{
	if (m_185)
		return (void *)&m_16C;
	else
		return (void *)&m_38;
}
