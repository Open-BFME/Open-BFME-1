// cl: /DNDEBUG /MD /EHsc
// Destructor pair at retail 0x0078CFB0 (destructor) and 0x0078D240 (scalar
// deleting destructor, slot 5 of vtable 0x01126DA0 via ILT 0x00039C52).
//
// These rows used to claim GameNetwork's User. That identity rested on the
// destructor destroying a UnicodeString at +4, read through a lift row that
// called 0x009409F0 UnicodeString::releaseBuffer. 0x009409F0 is in fact
// Render2DSentenceClass's destructor (identity_evidence/
// 009409f0-render2dsentence-dtor.md), so the member at +4 is a
// Render2DSentenceClass, which User does not have, and the base vtable
// 0x01126D84 (five pure-virtual slots, then the deleting destructor) is
// specific to this hierarchy rather than MemoryPoolObject's. The real class
// is not proven, so the name keeps the address.

class Render2DSentenceClass
{
public:
	virtual ~Render2DSentenceClass();		// retail 0x009409F0

private:
	char m_body[0xBC];
};

class Rva0078CFB0SentenceHolderBase
{
public:
	virtual void slot0() = 0;
	virtual void slot1() = 0;
	virtual void slot2() = 0;
	virtual void slot3() = 0;
	virtual void slot4() = 0;
	virtual ~Rva0078CFB0SentenceHolderBase() {}
};

class Rva0078CFB0SentenceHolder : public Rva0078CFB0SentenceHolderBase
{
public:
	virtual void slot0();
	virtual void slot1();
	virtual void slot2();
	virtual void slot3();
	virtual void slot4();
	virtual ~Rva0078CFB0SentenceHolder();

private:
	Render2DSentenceClass m_sentence;
};

// ??1Rva0078CFB0SentenceHolder@@UAE@XZ
Rva0078CFB0SentenceHolder::~Rva0078CFB0SentenceHolder()
{
}
