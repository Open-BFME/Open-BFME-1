// cl: /DNDEBUG /MD /EHsc /D_STLP_USE_STATIC_LIB /D_STLP_NO_EXCEPTIONS
// stlport
// Attribute-handle serializer at 0x003A01E0, called through ILT 0x0001D4B2
// by the matched bfmeGoCGF and Rva0039B2B0 callers. Entries have stride 0x88.
// A temporary entry in the intern call must have its native C++ lifetime:
// retail constructs it, marks EH state 1, interns it, then destroys it.
// The old raw-storage bank omitted that unwind state and could not match.
typedef unsigned char UnsignedByte;
typedef unsigned int UnsignedInt;

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
	virtual void slot68();
	virtual void slot6C();
	virtual void slot70();
	virtual void slot74();
	virtual void xferInt(void *value);
	virtual void slot7C();
	virtual void slot80();
	virtual void slot84();
	virtual void slot88();
	virtual void xferBool(void *value);
};

struct BfmePtrVec
{
	void *m_start;
	void *m_finish;
	void *m_end;
};

class BfmeSeedTarget;
class Rva000D6CF0Field
{
public:
	void Rva000D6CF0(BfmeSeedTarget *xfer);

	UnsignedInt m_values[6];
};

// Preserve the established plain-block identity while binding its proven
// retail serializer through the existing address-qualified ABI declaration.
class BfmeAttributePlainBlock {
public:
 void xfer(Xfer *value) { ((Rva000D6CF0Field *)this)->Rva000D6CF0((BfmeSeedTarget *)value); }
 UnsignedInt m_values[6];
};

class Gen00043699
{
public:
	Gen00043699();
	~Gen00043699();

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
struct Gen_t_0039e9d0_p128pod {
 unsigned char operator==(const Gen_t_0039e9d0_p128pod &) const;
};
extern void bfmeDestroyAttributeEntry(Gen_t_0039e9d0_p128pod *entry);
struct Rva0039D770Vector;
class Rva0039D770Owner {
public: void xfer(Xfer *, Rva0039D770Vector *, Rva0039D770Vector *);
};

class BfmeOwnerCGF
{
public:
	void bfmeOneCGF(void *what);
	void transferAttributeStrings(Xfer *xfer, void *vector);

private:
	UnsignedInt m_handle;
};

void BfmeOwnerCGF::bfmeOneCGF(void *what)
{
	register Xfer *xfer = (Xfer *)what;
	register BfmeOwnerCGF *owner = this;
	BfmeVersion version = { 1, 1 };
	xfer->xferVersion(&version);
	Gen00043699 entry;
	register Gen00043699 *source;

	if (xfer->isSaving())
	{
		if (owner->m_handle == BFME_NO_ATTRIBUTE_HANDLE)
		{
			owner->m_handle = bfmeInternAttributeEntry(&Gen00043699());
		}

		source = TheBfmeAttributePool.m_start + owner->m_handle;
	}
	else
	{
		source = &entry;
	}

	((Xfer *)xfer)->xferBool((char *)source + 0x80);
	((Xfer *)xfer)->xferInt((char *)source + 0x78);
	source->m_firstPlain.xfer(xfer);
	source->m_secondPlain.xfer(xfer);
	((Xfer *)xfer)->xferInt((char *)source + 0x7C);

	if (xfer->isSaving())
	{
		((Rva0039D770Owner *)owner)->xfer(xfer, (Rva0039D770Vector *)((char *)source + 0x18),
			(Rva0039D770Vector *)((char *)source + 0x30));
		((Rva0039D770Owner *)owner)->xfer(xfer, (Rva0039D770Vector *)((char *)source + 0x24),
			(Rva0039D770Vector *)((char *)source + 0x3C));
	}
	else
	{
		transferAttributeStrings(xfer, (char *)source + 0x00);
		transferAttributeStrings(xfer, (char *)source + 0x0C);
		bfmeDestroyAttributeEntry((Gen_t_0039e9d0_p128pod *)source);

		int count = (int)(TheBfmeAttributePool.m_finish
			- TheBfmeAttributePool.m_start);
		int index = 0;
		if (count > 0)
		{
			Gen00043699 *candidate = TheBfmeAttributePool.m_start;
			do
			{
				if (*(Gen_t_0039e9d0_p128pod *)candidate == *(Gen_t_0039e9d0_p128pod *)source)
				{
					owner->m_handle = index;
					break;
				}
				++index;
				++candidate;
			}
			while (index < count);
		}
	}
}
