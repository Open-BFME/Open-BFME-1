// ?bfmeOneCGF@BfmeOwnerCGF@@QAEXPAX@Z
// partial score=0.9 date=2026-09-10
// cl: /DNDEBUG /MD /EHsc /D_STLP_USE_STATIC_LIB /D_STLP_NO_EXCEPTIONS
// stlport

// Open-BFME5: BfmeOwnerCGF::bfmeOneCGF at retail 0x003A01E0.
// The 0x0001D4B2 thunk and the bfmeGoCGF and Rva0039B2B0 callers identify this
// method. It transfers the 136-byte attribute entry held by this object.

typedef unsigned char UnsignedByte;
typedef unsigned int UnsignedInt;

inline void *__cdecl operator new(unsigned int, void *where)
{
	return where;
}

enum { BFME_NO_ATTRIBUTE_HANDLE = 0xFFFFFFFF };

__declspec(align(4)) struct BfmeVersion
{
	UnsignedByte m_major;
	UnsignedByte m_minor;
};

class Xfer
{
public:
	virtual ~Xfer();
	virtual void slot04();
	virtual bool isSaving();
	virtual void slot0C();
	virtual void slot10();
	virtual void slot14();
	virtual void slot18();
	virtual void slot1C();
	virtual void slot20();
	virtual void slot24();
	virtual void xferVersion(BfmeVersion *version);
	virtual void slot2C();
	virtual void slot30();
	virtual void slot34();
	virtual void slot38();
	virtual void slot3C();
	virtual void slot40();
	virtual void slot44();
	virtual void slot48();
	virtual void slot4C();
	virtual void slot50();
	virtual void slot54();
	virtual void slot58();
	virtual void slot5C();
	virtual void slot60();
	virtual void slot64();
	virtual void xferBool(void *value);
	virtual void slot6C();
	virtual void slot70();
	virtual void slot74();
	virtual void xferInt(void *value);
	virtual void slot7C();
	virtual void slot80();
	virtual void slot84();
	virtual void slot88();
	virtual void slot8C();
};

struct BfmePtrVec
{
	void *m_start;
	void *m_finish;
	void *m_end;
};

class BfmeAttributePlainBlock
{
public:
	void xfer(Xfer *xfer);

	UnsignedInt m_values[6];
};

class Gen00043699
{
public:
	Gen00043699();
	Gen00043699(int) {}
	~Gen00043699();
	bool operator==(const Gen00043699 &other) const;

	BfmePtrVec m_names;
	BfmePtrVec m_values;
	BfmePtrVec m_list0;
	BfmePtrVec m_list1;
	BfmePtrVec m_list2;
	BfmePtrVec m_list3;
	BfmeAttributePlainBlock m_firstPlain;
	BfmeAttributePlainBlock m_secondPlain;
	UnsignedInt m_kind;
	UnsignedInt m_index;
	UnsignedByte m_enabled;
	UnsignedByte m_pad[3];
	UnsignedInt m_useCount;
};

struct BfmeAttributePool
{
	Gen00043699 *m_start;
	Gen00043699 *m_finish;
	Gen00043699 *m_end;
};

extern BfmeAttributePool TheBfmeAttributePool;
extern UnsignedInt bfmeInternAttributeEntry(Gen00043699 *entry);
extern void bfmeProcessAttributeEntry(Gen00043699 *entry);

class BfmeOwnerCGF
{
public:
	void bfmeOneCGF(void *what);
	void transferAttributeStrings(Xfer *xfer, void *vector);
	void transferAttributeVectors(Xfer *xfer, void *first, void *second);

private:
	UnsignedInt m_handle;
};

void BfmeOwnerCGF::bfmeOneCGF(void *what)
{
	register Xfer *xfer = (Xfer *)what;
	register BfmeOwnerCGF *owner = this;
	BfmeVersion version = { 1, 1 };
	xfer->xferVersion(&version);
	Gen00043699 temporary(0);
	Gen00043699 entry;
	register Gen00043699 *source = &entry;
	register int index;

	if (xfer->isSaving())
	{
		if (owner->m_handle == BFME_NO_ATTRIBUTE_HANDLE)
		{
			owner->m_handle = bfmeInternAttributeEntry(
				new (&temporary) Gen00043699);
			temporary.~Gen00043699();
		}

		source = TheBfmeAttributePool.m_start + owner->m_handle;
	}

	((Xfer *)xfer)->xferBool((char *)source + 0x80);
	((Xfer *)xfer)->xferInt((char *)source + 0x78);
	((BfmeAttributePlainBlock *)((char *)source + 0x48))->xfer(xfer);
	((BfmeAttributePlainBlock *)((char *)source + 0x60))->xfer(xfer);
	((Xfer *)xfer)->xferInt((char *)source + 0x7C);

	if (xfer->isSaving())
	{
		owner->transferAttributeVectors(xfer, (char *)source + 0x18,
			(char *)source + 0x30);
		owner->transferAttributeVectors(xfer, (char *)source + 0x24,
			(char *)source + 0x3C);
	}
	else
	{
		transferAttributeStrings(xfer, (char *)source + 0x00);
		transferAttributeStrings(xfer, (char *)source + 0x0C);
		bfmeProcessAttributeEntry(source);

		int count = (int)(TheBfmeAttributePool.m_finish
			- TheBfmeAttributePool.m_start);
		if (count > 0)
		{
			index = 0;
			Gen00043699 *candidate = TheBfmeAttributePool.m_start;
			do
			{
				if (*candidate == *source)
				{
					owner->m_handle = index;
					break;
				}
				++index;
				++candidate;
			}
			while (index < (UnsignedInt)count);
		}
	}
}
