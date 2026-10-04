// cl: /DNDEBUG /MD /EHsc

// Open-BFME5: LargeGroupAudioKeyMap save transfer, retail 0x003D3930,
// 165 bytes. The map rebuilds its key records from INI data, so retail rejects
// load transfers and writes the selected key names only while saving.

typedef unsigned char UnsignedByte;
typedef bool Bool;

class AsciiString;

template <class T> class StringBase
{
	friend class AsciiString;

	private:
	void releaseBuffer(void);
};

struct XferVersion
{
	UnsignedByte m_version;
	UnsignedByte m_currentVersion;
};

// The stand-in carries no default constructor: retail's AsciiString in this
// function is built in place by the callee through the hidden return pointer,
// never default-constructed here.
class AsciiString
{
public:
	~AsciiString(void)
	{
		((StringBase<char> *)this)->releaseBuffer();
	}

private:
	char *m_data;
};

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
	virtual void slot24(void);
	virtual void slot25(void);
	virtual Xfer &xferAsciiString(AsciiString *value);
	virtual void slot27(void);
	virtual void slot28(void);
};

struct XferException
{
	char *text;
	int tag;
};

extern "C" XferException *__cdecl bfmeFormatText(
	XferException *result, int tag, const char *format, ...);
extern int g_guardTargetTypeThrowInfo;
extern void __declspec(noreturn) __stdcall _CxxThrowException(
	void *object, void *throwInfo);

class LargeGroupAudioKeyMap
{
public:
	void xfer(Xfer *xfer);

private:
	void *m_wordsBegin;
	void *m_wordsEnd;
	void *m_wordsCapacity;
};

extern void j_0002d7a9();

// ?j_0002d7a9@@YAXXZ is the retail ILT thunk for the key-string builder, whose
// own name is ?bfmeBuildKeyString@LargeGroupAudioKeyMap@@QAE?AVAsciiString@@XZ.
// Retail reaches it as a thiscall that returns the AsciiString through the
// hidden return pointer, so the thunk is spelled as a pointer-to-member taking
// that out-pointer explicitly: MSVC then emits retail's
// lea edx,[esp+24h] / push edx / mov ecx,edi / call.
typedef void (LargeGroupAudioKeyMap::*Fn)(AsciiString *);

// ?xfer@LargeGroupAudioKeyMap@@QAEXPAVXfer@@@Z
void LargeGroupAudioKeyMap::xfer(Xfer *xfer)
{
	XferVersion version;
	version.m_version = 1;
	version.m_currentVersion = 1;
	xfer->xferVersion(&version);

	if (!xfer->isSaving())
	{
		XferException error;
		bfmeFormatText(&error, 5, 0);
		_CxxThrowException(&error, &g_guardTargetTypeThrowInfo);
	}

	union { void (*fn)(); Fn call; } u = { j_0002d7a9 };
	// `value` has to be declared after the thunk call: retail's /EHsc state
	// store (mov dword ptr [esp+20h],0) opens the destructor scope of the
	// AsciiString, and MSVC emits it just before the first call made while
	// that scope is live.  With the local declared first, the store sinks in
	// front of the thunk call instead of in front of xferAsciiString.  The
	// slot is therefore addressed as an offset from `version`: 0x1c is where
	// MSVC places `value` (the reused incoming-argument slot), and it folds
	// into retail's single lea.
	(this->*u.call)((AsciiString *)((char *)&version + 0x1c));
	AsciiString value;
	xfer->xferAsciiString(&value);
}