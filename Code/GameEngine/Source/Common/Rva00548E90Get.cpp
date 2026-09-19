// cl: /O2 /DNDEBUG /DWIN32 /D_WINDOWS /MD

class Rva00548E90
{
public:
	int get() const;

private:
	char m_padding00[0x04];
	int m_value;
};

int Rva00548E90::get() const
{
	return m_value;
}
