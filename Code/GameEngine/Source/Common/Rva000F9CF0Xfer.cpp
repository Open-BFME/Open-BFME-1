// cl: /DNDEBUG /MD /EHsc
// Open-BFME5: versioned record xfer at 0x000F9CF0, 438 bytes.
// Neighbour copy-ctor Gen_000F9C60 / xfer Rva001C2E50 sits at +0x44.
// Image* at +4 is saved/loaded by name through TheMappedImageCollection.

typedef unsigned char UnsignedByte;
typedef unsigned int UnsignedInt;

class AsciiString
{
public:
	AsciiString() : m_data(0) {}
	~AsciiString();
	void set(const AsciiString &other);
	static const AsciiString TheEmptyString;

	char *m_data;
};

class XferVersion
{
public:
	XferVersion(UnsignedByte major, UnsignedByte minor) :
		m_major(major), m_minor(minor) {}

	UnsignedByte m_major;
	UnsignedByte m_minor;
};

class Xfer
{
public:
	virtual ~Xfer();
	virtual bool IsLoading();
	virtual bool IsStoring();
	virtual void slot03();
	virtual void slot04();
	virtual void slot05();
	virtual void slot06();
	virtual void slot07();
	virtual void slot08();
	virtual void slot09();
	virtual void xferVersion(XferVersion &value);
	virtual void slot11();
	virtual void slot12();
	virtual void slot13();
	virtual void slot14();
	virtual void slot15();
	virtual void slot16();
	virtual void slot17();
	virtual void slot18();
	virtual void slot19();
	virtual void slot20();
	virtual void slot21();
	virtual void slot22();
	virtual void slot23();
	virtual void slot24();
	virtual void slot25();
	virtual void xferAsciiString(AsciiString &value);
	virtual void xferReal(float &value);
	virtual void slot28();
	virtual void xferUnsignedInt(UnsignedInt &value);
	virtual void xferInt(int &value);
	virtual void slot31();
	virtual void slot32();
	virtual void slot33();
	virtual void slot34();
	virtual void xferBool(bool &value);
};

class Image
{
public:
	AsciiString getName() const;
};

class MappedImageCollection
{
public:
	const Image *findImageByName(const AsciiString &name);
};

extern MappedImageCollection *TheMappedImageCollection;

class Rva001C2E50
{
public:
	void xfer(Xfer *xfer);
	unsigned char m_raw[0x1C];
};

void __cdecl xferBlob_0010CC40(Xfer *xfer, void *field);

class Rva000F9CF0
{
public:
	void xfer(Xfer *xfer);

	AsciiString m_name;				// +0x00
	Image *m_image;					// +0x04
	float m_real08;					// +0x08
	int m_int0C;					// +0x0C
	int m_int10;					// +0x10
	unsigned char m_blob14[0x18];			// +0x14
	UnsignedInt m_u32_2C;				// +0x2C
	int m_int30;					// +0x30
	UnsignedInt m_u32_34;				// +0x34
	bool m_bool38;					// +0x38
	int m_int3C;					// +0x3C
	int m_int40;					// +0x40
	Rva001C2E50 m_rec44;				// +0x44
};

// ?xfer@Rva000F9CF0@@QAEXPAVXfer@@@Z
void Rva000F9CF0::xfer(Xfer *xfer)
{
	XferVersion version(1, 5);
	xfer->xferVersion(version);

	xfer->xferAsciiString(m_name);

	if (version.m_minor >= 4)
	{
		xfer->xferReal(m_real08);
	}
	else
	{
		int old = 0;
		xfer->xferInt(old);
		m_real08 = (float)old;
	}

	if (version.m_minor >= 5)
		xfer->xferInt(m_int10);

	xferBlob_0010CC40(xfer, m_blob14);

	xfer->xferUnsignedInt(m_u32_2C);
	xfer->xferInt(m_int30);
	xfer->xferUnsignedInt(m_u32_34);
	xfer->xferBool(m_bool38);
	xfer->xferInt(m_int3C);
	xfer->xferInt(m_int40);

	if (version.m_minor >= 2)
		m_rec44.xfer(xfer);
	else
		xfer->xferInt(*((int *)&m_rec44));

	if (version.m_minor >= 3)
		xfer->xferInt(m_int0C);

	AsciiString name;
	if (xfer->IsStoring())
	{
		if (m_image)
			name.set(m_image->getName());
		else
			name.set(AsciiString::TheEmptyString);
		xfer->xferAsciiString(name);
	}
	else
	{
		xfer->xferAsciiString(name);
		m_image = (Image *)TheMappedImageCollection->findImageByName(name);
	}
}
