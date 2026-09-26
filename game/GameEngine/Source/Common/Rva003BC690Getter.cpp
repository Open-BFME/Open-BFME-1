// cl: /DNDEBUG /DWIN32 /D_WINDOWS /MD /EHsc
// The carved four-byte body reads the address-derived owner's field at +0x3c.

class Rva003BC690Owner
{
public:
	void *fieldAt3C();

private:
	char m_beforeField[0x3c];
	void *m_field;
};

void *Rva003BC690Owner::fieldAt3C()
{
	return m_field;
}
