// cl: /O2 /Ob0 /DNDEBUG /DWIN32 /D_WINDOWS /MD

class Rva005375F0
{
	unsigned char m_pad[4];
	unsigned m_value;

public:
	unsigned get() const;
};

unsigned Rva005375F0::get() const
{
	return m_value;
}
