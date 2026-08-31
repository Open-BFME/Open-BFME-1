// cl: /DNDEBUG /MD /EHsc

typedef unsigned char UnsignedByte;
typedef unsigned short WideChar;

class AsciiString
{
public:
	AsciiString() : m_data(0) {}
	~AsciiString();

private:
	char *m_data;
};

class UnicodeString
{
public:
	void translate(const AsciiString &text);

private:
	WideChar *m_data;
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
	virtual void slot01();
	virtual void slot02();
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
	virtual void xferUnicodeString(UnicodeString &value);
	virtual void xferAsciiString(AsciiString &value);
	virtual void slot27();
	virtual void slot28();
	virtual void slot29();
	virtual void xferInt(int &value);
	virtual void slot31();
	virtual void slot32();
	virtual void slot33();
	virtual void slot34();
	virtual void xferBool(bool &value);
};

class Rva001C2E50
{
public:
	void xfer(Xfer *xfer);

private:
	int m_field0;
	int m_field4;
	int m_field8;
	int m_fieldC;
	bool m_flag10;
	unsigned char m_pad11[3];
	UnicodeString m_text14;
	AsciiString m_text18;
};

void Rva001C2E50::xfer(Xfer *xfer)
{
	XferVersion version(1, 4);
	xfer->xferVersion(version);

	xfer->xferInt(m_field0);
	xfer->xferInt(m_field8);
	xfer->xferInt(m_field4);
	xfer->xferInt(m_fieldC);

	if (version.m_minor >= 3)
	{
		xfer->xferUnicodeString(m_text14);
	}
	else
	{
		AsciiString oldText;
		xfer->xferAsciiString(oldText);
		m_text14.translate(oldText);
	}

	if (version.m_minor >= 2)
	{
		xfer->xferAsciiString(m_text18);
	}

	if (version.m_minor >= 4)
	{
		xfer->xferBool(m_flag10);
	}
}
