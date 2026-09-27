// ?bfmeCallDUL@@YGXPAXPBX@Z
// partial score=0.667 date=2026-09-27
// cl: /DNDEBUG /MD /EHsc
// The ILT pin at 0x0001D467 names this body bfmeCallDUL, and five callers pass Ping strings from BfmeConv785.cpp.
// The matched constructor at 0x0058BED0 takes an integer and allocates a 24-byte object. This draft passes the temporary string object's address as that value.
// The probe measured 133 bytes against retail's 170, with 65 non-relocation differences and four misaligned relocation sites.

class BFMERetailAsciiString
{
public:
	BFMERetailAsciiString(const char *text);
	~BFMERetailAsciiString() { releaseBuffer(); }
private:
	void releaseBuffer();
	char *m_data;
};

class Rva0058BF70Base
{
public:
	Rva0058BF70Base() : m_value(0) {}
	virtual ~Rva0058BF70Base() {}
	virtual void slot1();
	virtual void slot2();
protected:
	int m_value;
};

class Rva0058BF70Owner : public Rva0058BF70Base
{
public:
	Rva0058BF70Owner(int value);
	virtual ~Rva0058BF70Owner();
private:
	bool m_released;
	char m_pad09[3];
	void *m_block;
	int m_tail0;
	int m_tail1;
};

void __stdcall bfmeCallDUL(void *other, const void *what)
{
	new Rva0058BF70Owner((int)&BFMERetailAsciiString((const char *)what));
}
