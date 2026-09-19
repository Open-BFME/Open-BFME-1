// cl: /DNDEBUG /DWIN32 /D_WINDOWS /MD /EHsc
// The carved four-byte body reads the address-derived owner's field at +0x38.

class Rva003BC680Owner
{
public:
	void *fieldAt38();

private:
	char m_beforeField[0x38];
	void *m_field;
};

void *Rva003BC680Owner::fieldAt38()
{
	return m_field;
}
