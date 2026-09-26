// ?method@BfmeRva64290@@QAEXXZ
// partial score=0.15 date=2026-09-05
// cl: /DNDEBUG /MD /EHsc
// Open-BFME5: address-derived body, retail 0x00764290, 899 bytes. Neighbours
// (0x00764220 Rva00764220::setup, 0x00764700 Gen00764700 controlling-player
// notify, 0x00764780 AudioEventRTS dup) and the ZH twin
// reference/CnC_Generals_Zero_Hour/GeneralsMD/.../W3DModelDraw.cpp (the
// "*** ASSET ERROR: SubObject %s not found (%s)!" DEBUG_CRASH string at
// retail 0x01123990 is verbatim from W3DModelDraw::doHideShowSubObjs) place
// this in the W3DDevice GameClient Drawable Draw family. The body iterates
// TWO 0x18-byte-element vectors at this+0x40/0x44 and this+0x4c/0x50 (not
// ZH's single 8-byte HideShowSubObjInfo vector -- BFME widened the element
// with extra transition-blend floats), looks a sub-object up by name through
// m_renderObject (this+0x28), and on a miss builds the same DEBUG_CRASH
// string through a vtable-based Debug object at global 0x01336E5C (the
// debug-manager global also used by _bfme_debugRecordCallsite /
// _bfme_debugReportingEnabled). Identity of the owning method/class could not
// be proven within budget; landed under an address-derived name per
// IDENTITY POLICY.

extern "C" char *__cdecl strcpy(char *dest, const char *src);

class BfmeRva64290RenderObj
{
public:
	virtual void *s00(); virtual void *s01(); virtual void *s02(); virtual void *s03();
	virtual void *s04(); virtual void *s05(); virtual void *s06(); virtual void *s07();
	virtual void *s08(); virtual void *s09(); virtual void *s0a(); virtual void *s0b();
	virtual void *s0c(); virtual void *s0d(); virtual void *s0e(); virtual void *s0f();
	virtual void *s10(); virtual void *s11(); virtual void *s12(); virtual void *s13();
	virtual void *s14(); virtual void *s15(); virtual void *s16(); virtual void *s17();
	virtual void *s18(); virtual void *s19(); virtual void *s1a(); // pad to 0x68
	virtual int getSubObjectBoneIndex(int zero, int arg); // +0x6c
	virtual void *s1c(); virtual void *s1d(); virtual void *s1e(); virtual void *s1f();
	virtual void *getSubObjectByName(const char *name, int *outIndex); // +0x7c
	virtual void *s21(); virtual void *s22(); virtual void *s23();
	virtual int getNumSubObjects(); // +0x88
	virtual void *s25(); virtual void *s26(); virtual void *s27(); virtual void *s28();
	virtual void *s29(); virtual void *s2a(); virtual void *s2b(); virtual void *s2c();
	virtual void *s2d();
	virtual void *getBoneIndex2(int a, int b); // +0xbc
	virtual void *s2f(); virtual void *s30(); virtual void *s31(); virtual void *s32();
	virtual void *s33(); virtual void *s34(); virtual void *s35(); virtual void *s36();
	virtual void *s37(); virtual void *s38(); virtual void *s39(); virtual void *s3a();
	virtual void *getHTree(); // +0xe4
};

class BfmeRva64290SubObj
{
public:
	virtual void *s00(); virtual void *s01(); virtual void *s02(); virtual void *s03();
	virtual void *s04(); virtual void *s05(); virtual void *s06(); virtual void *s07();
	virtual void *s08(); virtual void *s09(); virtual void *s0a(); virtual void *s0b();
	virtual void *s0c(); virtual void *s0d(); virtual void *s0e(); virtual void *s0f();
	virtual void *s10(); virtual void *s11(); virtual void *s12(); virtual void *s13();
	virtual void *s14(); virtual void *s15(); virtual void *s16(); virtual void *s17();
	virtual void *s18(); virtual void *s19(); virtual void *s1a(); virtual void *s1b();
	virtual void *s1c(); virtual void *s1d(); virtual void *s1e(); virtual void *s1f();
	virtual void *s20(); virtual void *s21(); virtual void *s22(); virtual void *s23();
	virtual void *s24(); virtual void *s25(); virtual void *s26(); virtual void *s27();
	virtual void *s28(); virtual void *s29(); virtual void *s2a(); virtual void *s2b();
	virtual void *s2c(); virtual void *s2d(); virtual void *s2e(); virtual void *s2f();
	virtual void *s30(); virtual void *s31(); virtual void *s32(); virtual void *s33();
	virtual void *s34(); virtual void *s35(); virtual void *s36(); virtual void *s37();
	virtual void *s38(); virtual void *s39(); virtual void *s3a(); virtual void *s3b();
	virtual void *s3c(); virtual void *s3d(); virtual void *s3e(); virtual void *s3f();
	virtual void setHidden(unsigned char hide); // +0x100 (index 64)
};

// TU-local minimal view of the debug manager: only the slots this body calls.
class BfmeRva64290Debug
{
public:
	virtual void *s00(); virtual void *s01(); virtual void *s02(); virtual void *s03();
	virtual void *s04(); virtual void *s05(); virtual void *s06(); virtual void *s07();
	virtual void *s08(); virtual void *s09(); virtual void *s0a(); virtual void *s0b();
	virtual void *s0c(); virtual void *s0d(); virtual void *s0e(); virtual void *s0f();
	virtual void *s10(); virtual void *s11(); virtual void *s12(); virtual void *s13();
	virtual void *s14(); virtual void *s15(); virtual void *s16(); virtual void *s17();
	virtual void *getStream(int a, int b); // +0x60 -> the outer object at 0x1336e5c
};

class BfmeRva64290DebugStream
{
public:
	virtual void *s00(); virtual void *s01(); virtual void *s02(); virtual void *s03();
	virtual void *s04(); virtual void *s05(); virtual void *s06(); virtual void *s07();
	virtual void *s08(); virtual void *s09(); virtual void *s0a(); virtual void *s0b();
	virtual void *s0c(); virtual void *s0d();
	virtual void logFormat(void *format); // +0x38
	virtual void *s0f(); virtual void *s10(); virtual void *s11(); virtual void *s12();
	virtual void flushCrash(int severity); // +0x4c
};

class DebugFormat
{
	DebugFormat(const DebugFormat &);
	DebugFormat &operator=(const DebugFormat &);
	char m_buffer[512];

public:
	explicit DebugFormat(const char *format, ...);
};

extern BfmeRva64290Debug *g_BFMEIndexBufferDebug; // 0x01336E5C
extern bool _bfme_debugReportingEnabled();
extern void _bfme_debugRecordCallsite(int kind);
extern void ask_still_a_dump(); // placeholder, unused

struct BfmeRva64290WeaponBarrel
{
	char m_pad0[4];
	unsigned char m_hide; // +4
	char m_pad1[3];
	float m_f8;
	float m_fc;
	float m_f10;
	float m_f14;
};

extern void j_0001aec9(void); // still a dump target -> transition setter

class BfmeRva64290
{
public:
	void method();

	char m_pad0[0x28];
	BfmeRva64290RenderObj *m_renderObject; // +0x28
	char m_pad1[0x40 - 0x2c];
	BfmeRva64290WeaponBarrel *m_vecABegin; // +0x40
	BfmeRva64290WeaponBarrel *m_vecAEnd;   // +0x44
	char m_pad2[0x4c - 0x48];
	BfmeRva64290WeaponBarrel *m_vecBBegin; // +0x4c
	BfmeRva64290WeaponBarrel *m_vecBEnd;   // +0x50
	char m_pad3[0x9c - 0x54];
	int m_debugBudget; // +0x9c
	char m_pad4[0x164 - 0xa0];
	unsigned char m_flag164; // +0x164
	unsigned char m_flag165; // +0x165
};

typedef void *(BfmeRva64290WeaponBarrel::*BfmeRva64290TransitionFn)(BfmeRva64290SubObj *, unsigned char);

// ?d_00764290@@YAXXZ
void BfmeRva64290::method()
{
	m_flag164 = 0;
	m_flag165 = 0;
	if (m_vecABegin == 0)
		return;

	for (BfmeRva64290WeaponBarrel *cur = m_vecABegin; cur != m_vecAEnd; cur = (BfmeRva64290WeaponBarrel *)((char *)cur + 0x18))
	{
		int outIndex = 0;
		if (m_renderObject == 0)
			continue;

		BfmeRva64290SubObj *subObj = (BfmeRva64290SubObj *)m_renderObject->getSubObjectByName("", &outIndex);
		if (subObj == 0)
			continue;

		subObj->setHidden(cur->m_hide);

		void *htree = m_renderObject->getHTree();
		if (htree == 0)
			continue;

		int boneIdx = (int)(unsigned)m_renderObject->getBoneIndex2(0, outIndex);
		int numSubObjects = m_renderObject->getNumSubObjects();
		if (boneIdx <= 0 || boneIdx >= numSubObjects)
			continue;

		m_renderObject->getSubObjectBoneIndex(0, boneIdx);

		union { void *asVoid; BfmeRva64290TransitionFn asMember; } fn;
		fn.asVoid = (void *)j_0001aec9;
		(cur->*fn.asMember)(subObj, cur->m_hide);

		if (--m_debugBudget > 0)
			continue;

		if (_bfme_debugReportingEnabled())
		{
			_bfme_debugRecordCallsite(1);
			void *stream = g_BFMEIndexBufferDebug->getStream(0, 0);
			DebugFormat fmt("*** ASSET ERROR: SubObject %s not found (%s)!\n", "", "");
			((BfmeRva64290DebugStream *)stream)->logFormat(&fmt);
			((BfmeRva64290DebugStream *)stream)->flushCrash(2);
		}
	}

	// Second, structurally identical vector -- BFME-added twin of the loop
	// above; kept separate rather than folded into one pass because retail
	// keeps two full copies of the body with independent counters.
	for (BfmeRva64290WeaponBarrel *cur = m_vecBBegin; cur != m_vecBEnd; cur = (BfmeRva64290WeaponBarrel *)((char *)cur + 0x18))
	{
		int outIndex = 0;
		if (m_renderObject == 0)
			continue;

		BfmeRva64290SubObj *subObj = (BfmeRva64290SubObj *)m_renderObject->getSubObjectByName("", &outIndex);
		if (subObj == 0)
			continue;

		void *htree = m_renderObject->getHTree();
		(void)htree;

		union { void *asVoid; BfmeRva64290TransitionFn asMember; } fn;
		fn.asVoid = (void *)j_0001aec9;
		(cur->*fn.asMember)(subObj, cur->m_hide);
	}
}
