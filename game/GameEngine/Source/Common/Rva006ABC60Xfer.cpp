// cl: /O2 /DNDEBUG /DWIN32 /D_WINDOWS /MD
// Rva006ABC60::xfer, retail 0x006B0CB0 (258 bytes).

typedef bool Bool;

struct XferVersion
{
	unsigned char m_version;
	unsigned char m_currentVersion;
};

class Xfer
{
public:
	virtual void slot00();
	virtual void slot01();
	virtual void slot02();
	virtual void slot03();
	virtual void slot04();
	virtual void slot05();
	virtual void slot06();
	virtual void slot07();
	virtual void slot08();
	virtual void slot09();
	virtual Xfer &xferVersion(XferVersion *version);
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
	virtual Xfer &xferReal(float *value);
	virtual void slot28();
	virtual void slot29();
	virtual void slot30();
	virtual void slot31();
	virtual void slot32();
	virtual void slot33();
	virtual void slot34();
	virtual Xfer &xferBool(Bool *value);
};

extern void __cdecl xferTree(Xfer *xfer, void *tree);
extern void __cdecl xferMap(Xfer *xfer, void *map);

#pragma comment(linker, "/alternatename:?xferTree@@YAXPAVXfer@@PAX@Z=?j_00003544@@YAXXZ")
#pragma comment(linker, "/alternatename:?xferMap@@YAXPAVXfer@@PAX@Z=?j_000149d4@@YAXXZ")

class Rva006ABC60
{
public:
	void xfer(Xfer *xfer);
	void refreshPair(int a, int b);

private:
	char m_pad0[4];
	float m_baseAndProduct[18];
	char m_elements[0x48];
	float m_atten;
	float m_vol;
	float m_scale;
	char m_tree[0x0c];
	float m_tail0;
	float m_tail1;
	float m_tail2;
	float m_tail3;
	float m_tail4;
	float m_tail5;
	Bool m_enabled;
	char m_padC5[3];
	float m_slot[12][4];
	unsigned char m_dirty[48];
	char m_map[0x18];
};

#pragma comment(linker, "/alternatename:?refreshPair@Rva006ABC60@@QAEXHH@Z=?j_00019e6b@@YAXXZ")

void Rva006ABC60::xfer(Xfer *xfer)
{
	register Rva006ABC60 &record = *this;
	XferVersion version;
	version.m_version = 1;
	version.m_currentVersion = 1;
	xfer->xferVersion(&version);

	for (int i = 0; i < 6; ++i)
		for (int j = 0; j < 2; ++j)
			xfer->xferReal(&record.m_baseAndProduct[i * 2 + j]);

	xferTree(xfer, record.m_tree);
	xfer->xferReal(&record.m_scale);
	xfer->xferBool(&record.m_enabled);
	if (record.m_enabled)
	{
		xfer->xferReal(&record.m_tail0);
		xfer->xferReal(&record.m_tail1);
		xfer->xferReal(&record.m_tail2);
		xfer->xferReal(&record.m_tail3);
		xfer->xferReal(&record.m_tail4);
		xfer->xferReal(&record.m_tail5);
	}
	xferMap(xfer, record.m_map);

	for (int i = 0; i < 6; ++i)
		for (int j = 0; j < 2; ++j)
			record.refreshPair(i, j);
}
