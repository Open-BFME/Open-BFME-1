// cl: /DNDEBUG /MD /O2 /EHsc
// SequentialScript::xfer, retail 0x00336D90.
// ZH twin: ScriptEngine.cpp SequentialScript::xfer. BFME adds skipTransfer0C
// early-out, stores two name strings on the object, and resolves the script
// through TheScriptEngine vcall +0xD4.

typedef unsigned char UnsignedByte;
typedef unsigned int UnsignedInt;
typedef int Int;
typedef unsigned int ObjectID;

struct XferVersion
{
	UnsignedByte m_version;
	UnsignedByte m_currentVersion;
};

class AsciiString
{
	char *m_data;
};

class Team
{
public:
	UnsignedInt getID(void) const { return m_id; }

	void *m_vptr;
	void *m_unmodelled;
	UnsignedInt m_id;
};

class Script;

class Xfer
{
public:
	virtual ~Xfer();
	virtual bool isLoading();
	virtual bool isSaving();
	virtual bool skipTransfer0C();
	virtual void slot04();
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
	virtual void xferAsciiString(AsciiString &);
	virtual void slot27();
	virtual void slot28();
	virtual void xferUnsignedInt(UnsignedInt &);
	virtual void xferInt(Int &);
	virtual void slot31();
	virtual void slot32();
	virtual void slot33();
	virtual void slot34();
	virtual void xferBool(bool &);
};

class Rva002BD630TeamFactory
{
public:
	void *find(int);
};

#define TheTeamFactory (*(Rva002BD630TeamFactory **)0x012ED810)

class ScriptEngine
{
public:
	virtual void s00();
	virtual void s01();
	virtual void s02();
	virtual void s03();
	virtual void s04();
	virtual void s05();
	virtual void s06();
	virtual void s07();
	virtual void s08();
	virtual void s09();
	virtual void s10();
	virtual void s11();
	virtual void s12();
	virtual void s13();
	virtual void s14();
	virtual void s15();
	virtual void s16();
	virtual void s17();
	virtual void s18();
	virtual void s19();
	virtual void s20();
	virtual void s21();
	virtual void s22();
	virtual void s23();
	virtual void s24();
	virtual void s25();
	virtual void s26();
	virtual void s27();
	virtual void s28();
	virtual void s29();
	virtual void s30();
	virtual void s31();
	virtual void s32();
	virtual void s33();
	virtual void s34();
	virtual void s35();
	virtual void s36();
	virtual void s37();
	virtual void s38();
	virtual void s39();
	virtual void s40();
	virtual void s41();
	virtual void s42();
	virtual void s43();
	virtual void s44();
	virtual void s45();
	virtual void s46();
	virtual void s47();
	virtual void s48();
	virtual void s49();
	virtual void s50();
	virtual void s51();
	virtual void s52();
	virtual Script *findScript(AsciiString &, AsciiString &, int);
};

extern ScriptEngine *TheScriptEngine;

struct XferException
{
	char *m_text;
	int m_tag;
};

union SequentialScriptXferLocal
{
	XferVersion version;
	XferException error;
};

extern "C" XferException *__cdecl bfmeFormatText(XferException *, int, const char *, ...);
extern void __declspec(noreturn) __stdcall _CxxThrowException(void *, void *);
extern void __cdecl xferObjectID0010C3C0(Xfer *, UnsignedInt *);
extern "C" int g_guardTargetTypeThrowInfo;

class SequentialScript
{
public:
	virtual void xfer(Xfer *xfer);

	Team *m_teamToExecOn;
	ObjectID m_objectID;
	AsciiString m_nameA;
	AsciiString m_nameB;
	Script *m_scriptToExecuteSequentially;
	Int m_currentInstruction;
	Int m_timesToLoop;
	Int m_framesToWait;
	bool m_dontAdvanceInstruction;
};


void SequentialScript::xfer(Xfer *xfer)
{
	if (xfer->skipTransfer0C())
		return;

	SequentialScriptXferLocal local;
	local.version.m_version = 1;
	local.version.m_currentVersion = 1;
	xfer->xferVersion(&local.version);

	UnsignedInt teamID = m_teamToExecOn ? m_teamToExecOn->getID() : 0;
	xfer->xferUnsignedInt(teamID);

	if (xfer->isLoading())
	{
		m_teamToExecOn = (Team *)TheTeamFactory->find((int)teamID);
		if (teamID != 0 && m_teamToExecOn == 0)
		{
			bfmeFormatText(&local.error, 5, 0);
			_CxxThrowException(&local.error, &g_guardTargetTypeThrowInfo);
		}
	}

	xferObjectID0010C3C0(xfer, &m_objectID);

	xfer->xferAsciiString(m_nameA);
	xfer->xferAsciiString(m_nameB);

	if (!xfer->isSaving())
		m_scriptToExecuteSequentially = TheScriptEngine->findScript(m_nameA, m_nameB, 0);

	xfer->xferInt(m_currentInstruction);
	xfer->xferInt(m_timesToLoop);
	xfer->xferInt(m_framesToWait);
	xfer->xferBool(m_dontAdvanceInstruction);
}
