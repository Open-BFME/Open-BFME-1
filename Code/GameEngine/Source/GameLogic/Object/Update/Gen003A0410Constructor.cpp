// cl: /DNDEBUG /MD /EHsc

// Open-BFME5: constructor of an RVA-derived handle type Gen003A0410, retail
// 0x003A0410, 115 bytes. symbols.csv pins ?perform@Gen003A0410@@QAEXXZ here
// (address-derived void thiscall); the body returns this in EAX so it is a
// constructor. Same ctor/intern/dtor ILTs as BfmeSecondPlainMember::setSecondPlain:
// 0x00008067, 0x00037FD8, 0x00043699. Stores 0xFFFFFFFF then interns a default
// 0x88-byte attribute entry into the handle at this+0.

typedef unsigned int UnsignedInt;

enum { BFME_NO_ATTRIBUTE_HANDLE = 0xFFFFFFFF };

class Gen00043699
{
public:
	Gen00043699();
	~Gen00043699();

	unsigned char m_head[0x88];
};

extern UnsignedInt bfmeInternAttributeEntry(Gen00043699 *entry);

class Gen003A0410
{
public:
	Gen003A0410();

private:
	UnsignedInt m_handle;
};

// ??0Gen003A0410@@QAE@XZ
Gen003A0410::Gen003A0410()
{
	m_handle = BFME_NO_ATTRIBUTE_HANDLE;
	Gen00043699 entry;
	m_handle = bfmeInternAttributeEntry(&entry);
}
