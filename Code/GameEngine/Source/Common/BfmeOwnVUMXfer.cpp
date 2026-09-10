// cl: /DNDEBUG /MD /EHsc
// Retail 0x00361030. The adjacent BfmeOwnVUM destructor at 0x00360F90
// fixes the class vftable and the five string fields used by this method.

typedef unsigned char UnsignedByte;

class AsciiString
{
public:
	AsciiString() : m_data(0) {}
	~AsciiString();

	char *m_data;
};

class UnicodeString
{
public:
	void translate(const AsciiString &source);

	char *m_data;
};

struct BfmeInfoBH
{
	BfmeInfoBH(UnsignedByte version, UnsignedByte currentVersion) :
		m_version(version), m_currentVersion(currentVersion) {}

	UnsignedByte m_version;
	UnsignedByte m_currentVersion;
};

class BfmeAgentBH
{
public:
	virtual ~BfmeAgentBH();
	virtual void slot01();
	virtual void slot02();
	virtual void slot03();
	virtual void slot04();
	virtual void slot05();
	virtual void slot06();
	virtual void slot07();
	virtual void slot08();
	virtual void slot09();
	virtual void bfmeFillBH(BfmeInfoBH *version);
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
	virtual void bfmeMarkBH(void *value);
	virtual void bfmeAsciiBH(AsciiString &value);
	virtual void bfmeRealBH(float &value);
	virtual void slot28();
	virtual void slot29();
	virtual void bfmeIntBH(int &value);
	virtual void slot31();
	virtual void slot32();
	virtual void slot33();
	virtual void slot34();
	virtual void bfmeByteBH(unsigned char *value);
};

class Xfer;

class BfmeSubOneBH
{
public:
	void bfmeSaveBH(BfmeAgentBH *xfer);

	unsigned char m_padding[0x28];
};

class BfmeSubTwoBH
{
public:
	void bfmeSaveBH(BfmeAgentBH *xfer);

	unsigned char m_padding[0x0c];
};

extern void __cdecl xferBlob_0010CC40(Xfer *xfer, void *field);

class BfmeOwnVUM
{
public:
	void bfmeSaveBH(BfmeAgentBH *xfer);

	void *m_vtable;
	AsciiString m_04;
	float m_08;
	int m_0c;
	unsigned int m_10[6];
	BfmeSubTwoBH m_28;
	int m_34;
	unsigned char m_38;
	unsigned char m_39;
	int m_3c;
	int m_40Value;
	int m_44Value;
	int m_48Value;
	AsciiString m_4c;
	BfmeSubOneBH m_50;
	UnicodeString m_78;
	unsigned int m_7c[6];
	unsigned int m_94[6];
	AsciiString m_ac;
	AsciiString m_b0;
};

void BfmeOwnVUM::bfmeSaveBH(BfmeAgentBH *xfer)
{
	BfmeInfoBH version(1, 8);
	xfer->bfmeFillBH(&version);

	if (version.m_currentVersion >= 8)
	{
		xfer->bfmeRealBH(m_08);
	}
	else
	{
		int oldValue = 0;
		xfer->bfmeIntBH(oldValue);
		m_08 = (float)oldValue;
	}

	xfer->bfmeIntBH(m_34);
	xfer->bfmeByteBH(&m_38);
	xfer->bfmeIntBH(m_3c);
	xfer->bfmeAsciiBH(m_04);

	if (version.m_currentVersion >= 6)
	{
		xfer->bfmeMarkBH(&m_78);
	}
	else
	{
		AsciiString oldValue;
		xfer->bfmeAsciiBH(oldValue);
		m_78.translate(oldValue);
	}

	m_28.bfmeSaveBH(xfer);
	m_50.bfmeSaveBH(xfer);
	xferBlob_0010CC40((Xfer *)xfer, m_10);
	xferBlob_0010CC40((Xfer *)xfer, m_7c);
	xferBlob_0010CC40((Xfer *)xfer, m_94);

	if (version.m_currentVersion >= 2)
	{
		xfer->bfmeAsciiBH(m_ac);
		xfer->bfmeAsciiBH(m_b0);
	}

	if (version.m_currentVersion >= 3)
	{
		xfer->bfmeIntBH(m_40Value);
		xfer->bfmeIntBH(m_44Value);
		xfer->bfmeIntBH(m_48Value);
	}

	if (version.m_currentVersion >= 4)
	{
		xfer->bfmeAsciiBH(m_4c);
	}

	if (version.m_currentVersion >= 5)
	{
		xfer->bfmeIntBH(m_0c);
	}

	if (version.m_currentVersion >= 7)
	{
		xfer->bfmeByteBH(&m_39);
	}
}
