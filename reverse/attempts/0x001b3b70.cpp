// ?xfer@Gen_001B3B70@@QAEXPAVXfer@@@Z (identity unknown)
// partial score=0.6 date=2026-09-07

typedef unsigned int UnsignedInt;

struct XferVersion
{
	unsigned char m_version;
	unsigned char m_currentVersion;
};

struct XferException
{
	char *m_text;
	int m_tag;
};

union XferLocal
{
	XferVersion m_version;
	XferException m_error;
};

class BfmeObject
{
public:
	char m_bfmeHead[0x74];
	UnsignedInt m_bfmeID;
};

class Xfer
{
public:
	virtual void slot00(void);
	virtual bool isLoading(void);
	virtual void slot02(void);
	virtual void slot03(void);
	virtual bool isLightCRC(void);
	virtual void slot05(void);
	virtual void slot06(void);
	virtual void slot07(void);
	virtual void slot08(void);
	virtual void slot09(void);
	virtual Xfer &xferVersion(XferVersion *version);
	virtual void slot11(void);
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
	virtual void xferAt60(void *value);
	virtual void slot24(void);
	virtual void slot25(void);
	virtual void xferAt6C(void *value);
};

class GameLogic
{
public:
	BfmeObject *findObjectByID(UnsignedInt id);
};

#define TheGameLogic (*(GameLogic **)0x012F0898)

extern "C" void __cdecl bfmeCalcTGC(void *xfer, int *value);
extern "C" XferException *__cdecl bfmeFormatText(
	XferException *result, int tag, const char *format, ...);
extern void __declspec(noreturn) __stdcall _CxxThrowException(
	void *object, void *throwInfo);
extern "C" int g_guardTargetTypeThrowInfo;

class Gen_001B3B70
{
public:
	void xfer(Xfer *xfer);

	char m_bfmeHead[0x0c];
	BfmeObject *m_bfmeObject;
	char m_bfmeField10[0x0c];
	char m_bfmeField1c;
};

void Gen_001B3B70::xfer(Xfer *xfer)
{
	if (xfer->isLightCRC())
		return;

	XferLocal local;
	local.m_version.m_version = 1;
	local.m_version.m_currentVersion = 1;
	xfer->xferVersion(&local.m_version);

	register int objectID = 0;
	if (m_bfmeObject != 0)
		objectID = m_bfmeObject->m_bfmeID;
	bfmeCalcTGC(xfer, (int *)&objectID);

	if (xfer->isLoading())
	{
		const int id = objectID;
		GameLogic * const logic = TheGameLogic;
		m_bfmeObject = logic->findObjectByID(id);
		if (id != 0 && m_bfmeObject == 0)
		{
			bfmeFormatText(&local.m_error, 5, 0);
			_CxxThrowException(&local.m_error, &g_guardTargetTypeThrowInfo);
		}
	}

	xfer->xferAt6C(&m_bfmeField1c);
	xfer->xferAt60(&m_bfmeField10);
}
