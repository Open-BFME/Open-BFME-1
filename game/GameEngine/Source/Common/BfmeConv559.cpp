class BfmeThingBZD
{
public:
	void bfmeGoBZD(const char *text, int value);
	unsigned char m_bfmeHead[0x50];
	char m_bfmeBuf[0x80];
	int m_bfmeVal;
};

// Retail calls the strncpy import thunk at 0x009F70BA directly.  That thunk is
// landed as a no-argument jump stub, so its caller supplies strncpy's three
// arguments on the stack; see Y4FeslFavGameAddress.cpp for the same convention.
void __cdecl ji_009f70ba();
typedef char *(__cdecl *Rva009F70BACopy)(
	char *dest, const char *text, unsigned int size);

void BfmeThingBZD::bfmeGoBZD(const char *text, int value)
{
	reinterpret_cast<Rva009F70BACopy>(&ji_009f70ba)(m_bfmeBuf, text, 0x40);
	m_bfmeVal = value;
}
