// cl: /DNDEBUG /DWIN32 /D_WINDOWS /MD /EHsc
// Clean C++ reconstruction of the BFME map-extraction helper at retail RVA
// 0x00112DA0.  The caller keeps its Xfer object live in ESI across this
// internal static helper; the local views below preserve the retail virtual
// slots and BFME AsciiString storage without changing shared headers.

typedef unsigned int UnsignedInt;

void *__cdecl operator new[](unsigned int size);
void __cdecl operator delete[](void *memory);

struct XferException
{
	void *text;
	int tag;
};

extern "C" XferException *__cdecl bfmeFormatText(
	XferException *result, int tag, const char *format, ...);
extern void __declspec(noreturn) __stdcall _CxxThrowException(
	void *object, void *throwInfo);

extern "C" __declspec(dllimport) void *__cdecl bfmeFopenVIF(
	const char *name, const char *mode);
extern "C" __declspec(dllimport) unsigned int __cdecl fwrite(
	const void *buffer, unsigned int size, unsigned int count, void *stream);
extern "C" __declspec(dllimport) void __cdecl bfmeFreeUXB(void *stream);

class BFMERetailAsciiString
{
public:
	void releaseBuffer();
};

class AsciiString
{
public:
	const char *str() const
	{
		return m_data ? m_data + 8 : (const char *)0x0107388B;
	}

	~AsciiString()
	{
		((BFMERetailAsciiString *)this)->releaseBuffer();
	}

private:
	char *m_data;
};

class Xfer
{
public:
	virtual void slot00();
	virtual void slot01();
	virtual void slot02();
	virtual void slot03();
	virtual void slot04();
	virtual int beginBlock(const char *name);
	virtual void endBlock();
	virtual void skipBlock(const char *name);
	virtual void slot08();
	virtual void xferUser(void *data, UnsignedInt size);
	virtual void slot10();
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
	virtual void xferUnsignedInt(UnsignedInt *value);
};

// ?extractAndSaveMap@@YAXVAsciiString@@PAVXfer@@@Z
static __declspec(noinline) void extractAndSaveMap(AsciiString mapToSave, Xfer *xfer)
{
	UnsignedInt dataSize;

	void *fp = bfmeFopenVIF(mapToSave.str(), "w+b");
	if (fp == 0)
	{
		XferException error;
		bfmeFormatText(&error, 5, 0);
		_CxxThrowException(&error, (void *)0x011DFE5C);
	}

	xfer->beginBlock("EmbeddedMap");
	xfer->xferUnsignedInt(&dataSize);

	char *buffer = (char *)::operator new[](dataSize);
	if (buffer == 0)
	{
		XferException error;
		bfmeFormatText(&error, 5, 0);
		_CxxThrowException(&error, (void *)0x011DFE5C);
	}

	xfer->xferUser(buffer, dataSize);
	if (fwrite(buffer, 1, dataSize, fp) != dataSize)
	{
		::operator delete[](buffer);
		XferException error;
		bfmeFormatText(&error, 5, 0);
		_CxxThrowException(&error, (void *)0x011DFE5C);
	}

	bfmeFreeUXB(fp);
	xfer->endBlock();
	::operator delete[](buffer);
}

// Internal-call anchor: the retail parent keeps Xfer in ESI across this
// static helper, which MSVC 7.1 reproduces only when the helper has a local
// caller in the same translation unit.
void forceExtractAndSaveMap(AsciiString mapToSave, Xfer *xfer)
{
	extractAndSaveMap(mapToSave, xfer);
}
