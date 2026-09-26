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

class AsciiString
{
public:
	AsciiString(void) : m_data(0) {}
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
extern void __declspec(noreturn) __stdcall _CxxThrowException(
	void *object, void *throwInfo);

class LargeGroupAudioKeyMap
{
public:
	void xfer(Xfer *xfer);
	AsciiString bfmeBuildKeyString(void);

private:
	void *m_wordsBegin;
	void *m_wordsEnd;
	void *m_wordsCapacity;
};

#pragma comment(linker, "/alternatename:?bfmeBuildKeyString@LargeGroupAudioKeyMap@@QAE?AVAsciiString@@XZ=?j_0002d7a9@@YAXXZ")

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
		_CxxThrowException(&error, (void *)0x011DFE5C);
	}

	AsciiString value = bfmeBuildKeyString();
	xfer->xferAsciiString(&value);
}
