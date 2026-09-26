typedef unsigned char UnsignedByte;
typedef bool Bool;

struct XferVersion
{
	UnsignedByte m_version;
	UnsignedByte m_currentVersion;
};

class Xfer
{
public:
	virtual void slot00();
	virtual void slot01();
	virtual Bool isSaving();
	virtual void slot03();
	virtual Bool isLightCRC();
	virtual void slot05();
	virtual void slot06();
	virtual void slot07();
	virtual void slot08();
	virtual void slot09();
	virtual void xferVersion(XferVersion *);
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
	virtual void slot26();
	virtual void slot27();
	virtual void slot28();
	virtual void slot29();
	virtual void xferInt(int *);
};

class BfmePlayerBR
{
public:
	unsigned char m_bfmeHeadBR[0x24];
	int m_bfmeIdBR;
};

struct Rva002EE330PlayerList
{
	BfmePlayerBR *bfmeFindBR(int id);
};

extern Rva002EE330PlayerList *Rva002EE330ThePlayers;

class BfmeHostBR
{
public:
	void xfer(Xfer *x);

	unsigned char m_bfmeHeadBR[0xc];
	BfmePlayerBR *m_bfmePlayerBR;
};

void BfmeHostBR::xfer(Xfer *x)
{
	if (x->isLightCRC())
		return;

	XferVersion version;

	version.m_version = 1;
	version.m_currentVersion = 1;
	x->xferVersion(&version);

	int id;

	if (x->isSaving())
		id = m_bfmePlayerBR->m_bfmeIdBR;

	x->xferInt(&id);

	m_bfmePlayerBR = Rva002EE330ThePlayers->bfmeFindBR(id);
}
