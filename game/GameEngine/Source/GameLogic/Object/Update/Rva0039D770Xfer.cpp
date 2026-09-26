// cl: /DNDEBUG /MD /EHsc /D_STLP_USE_STATIC_LIB
//
// The generated caller at 0x003A01E0 passes this method an Xfer object and
// two attribute-entry vectors.  The retail string at 0x010EBEC8 is `S:`.
// The caller and the string prove the serialization behavior, but no named
// owner has enough independent evidence yet, so the method keeps its RVA.

typedef unsigned short UnsignedShort;
typedef bool Bool;

class BFMERetailAsciiString;

class Xfer
{
public:
	virtual ~Xfer(void);
	virtual Bool isLoading(void);
	virtual Bool isSaving(void);
	virtual void slot03(void);
	virtual void slot04(void);
	virtual void slot05(void);
	virtual void slot06(void);
	virtual void slot07(void);
	virtual void slot08(void);
	virtual void slot09(void);
	virtual Xfer &xferVersion(void *version);
	virtual Xfer &xferTypeName(const char *const &name);
	virtual void slot12(void);
	virtual void slot13(void);
	virtual void slot14(void);
	virtual void slot15(void);
	virtual void slot16(void);
	virtual void slot17(void);
	virtual void slot18(void);
	virtual void slot19(void);
	virtual void slot20(void);
	virtual void slot21(void);
	virtual void slot22(void);
	virtual void slot23(void);
	virtual void slot24(void);
	virtual void slot25(void);
	virtual Xfer &xferAsciiString(BFMERetailAsciiString *value);
	virtual void slot26(void);
	virtual void slot27(void);
	virtual void slot28(void);
	virtual Xfer &xferUnsignedShort(UnsignedShort *value);
};

template <typename T>
class StringBase
{
public:
	void concat(const T *text, int length);
};

class BFMERetailAsciiString
{
public:
	BFMERetailAsciiString(const char *text);
	~BFMERetailAsciiString() { releaseBuffer(); }

	const char *str() const
	{
		return m_data ? (const char *)m_data + 8 : (const char *)0x0107388B;
	}

	int getLength() const
	{
		return m_data ? *(const unsigned short *)((const char *)m_data + 4) : 0;
	}

	void concat(const char *text, int length)
	{
		((StringBase<char> *)this)->concat(text, length);
	}

	void *m_data;

private:
	void releaseBuffer();
};

struct Rva0039D770Record
{
	char m_pad[0x20];
	BFMERetailAsciiString m_name;

	BFMERetailAsciiString *name()
	{
		return &m_name;
	}
};

struct Rva0039D770Vector
{
	Rva0039D770Record **m_start;
	Rva0039D770Record **m_finish;
	Rva0039D770Record **m_end;
};

class Rva0039D770Owner
{
public:
	void xfer(Xfer *xfer, Rva0039D770Vector *first,
		Rva0039D770Vector *second);
};

void Rva0039D770Owner::xfer(Xfer *xfer, Rva0039D770Vector *first,
	Rva0039D770Vector *second)
{
	unsigned int count = (first->m_finish - first->m_start) +
		(second->m_finish - second->m_start);
	xfer->xferUnsignedShort((UnsignedShort *)&count);
	Rva0039D770Record **it = first->m_start;
	Rva0039D770Record **end = first->m_finish;
	if (it != end)
	{
		do
		{
			BFMERetailAsciiString string((const char *)0x010EBEC8);
			BFMERetailAsciiString *value = ((Rva0039D770Record *)*it)->name();
			string.concat(value->str(), value->getLength());
			xfer->xferAsciiString(&string);
		}
		while (++it != first->m_finish);
	}
	for (Rva0039D770Record **it = second->m_start;
		it != second->m_finish; ++it)
		xfer->xferAsciiString(&(*it)->m_name);
}
