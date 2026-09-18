// ?value@Rva006962D0@@QAEHXZ
// The carved body reads the address-derived owner's field at this+0x10.
// cl: /O2 /Ob0 /DNDEBUG /DWIN32 /D_WINDOWS /MD

class Rva006962D0
{
	char m_padding[0x10];
	int m_value;

public:
	int value();
};

int Rva006962D0::value()
{
	return m_value;
}
