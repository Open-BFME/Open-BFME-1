// cl: /O2 /Ob0 /DNDEBUG /DWIN32 /D_WINDOWS /MD

class Rva004A6500Owner
{
public:
	unsigned char *fieldAddress();

private:
	unsigned char m_pad[0x28];
	unsigned char m_field;
};

unsigned char *Rva004A6500Owner::fieldAddress()
{
	return &m_field;
}
