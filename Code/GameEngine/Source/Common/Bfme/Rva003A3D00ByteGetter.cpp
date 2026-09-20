// cl: /O2 /Ob0 /DNDEBUG /DWIN32 /D_WINDOWS /MD /EHs-c-

class Rva003A3D00ByteGetter
{
public:
	unsigned char get() const;

private:
	char m_padding[0x1c];
	unsigned char m_value;
};

// @?get@Rva003A3D00ByteGetter@@QBEEXZ 0x003A3D00
unsigned char Rva003A3D00ByteGetter::get() const
{
	return m_value;
}
