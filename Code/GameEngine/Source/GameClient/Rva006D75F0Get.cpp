// cl: /O2 /DNDEBUG /DWIN32 /D_WINDOWS /MD

class Rva006D75F0
{
public:
	int get() const;

private:
	char m_padding00[0x24];
	int m_value;
};

int Rva006D75F0::get() const
{
	return m_value;
}
