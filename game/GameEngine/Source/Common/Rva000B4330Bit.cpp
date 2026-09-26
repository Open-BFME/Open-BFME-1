// cl: /O2 /Ob0 /DNDEBUG /DWIN32 /D_WINDOWS /MD

class Rva000B4330
{
	unsigned char m_pad[0x94];
	unsigned m_94;

public:
	int get() const;
};

int Rva000B4330::get() const
{
	return (~(m_94 >> 19)) & 1;
}
