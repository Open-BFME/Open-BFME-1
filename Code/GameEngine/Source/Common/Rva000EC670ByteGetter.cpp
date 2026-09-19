// cl: /O2 /DNDEBUG /DWIN32 /D_WINDOWS /MD

class Rva000EC670ByteField
{
private:
	unsigned char m_pad[0x16];
	unsigned char m_value;

public:
	unsigned char get() const;
};

unsigned char Rva000EC670ByteField::get() const
{
	return m_value;
}
