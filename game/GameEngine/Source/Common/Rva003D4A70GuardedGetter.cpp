// cl: /DNDEBUG /DWIN32 /MD /D_STLP_USE_STATIC_LIB

struct Rva003D4A70Pointee
{
	unsigned char m_padding[0x18];
	int m_value;
};

class Rva003D4A70
{
public:
	Rva003D4A70Pointee *m_pointee;
	int get();
};

int Rva003D4A70::get()
{
	if (m_pointee)
		return m_pointee->m_value;
	return 0;
}
