// ?embedInUseMap@@YAXVAsciiString@@PAVXfer@@@Z
// cl: /DNDEBUG /DWIN32 /D_WINDOWS /MD /EHsc
// Clean C++ reconstruction of the BFME "in use" map embed helper at retail
// RVA 0x00112BF0, the sibling of the landed
// GameStateMap_extractAndSaveMap.cpp.  The retail parent keeps its Xfer object
// live in a callee-saved register across this internal static helper; the local
// views below preserve the retail virtual slots and BFME AsciiString storage
// without changing shared headers.  The retail body is this static helper, not
// a destructor: it passes the literal "InUseMap" to Xfer::beginBlock, and the
// Zero Hour reference carries the same function at
// GeneralsMD/Code/GameEngine/Source/Common/System/SaveGame/GameStateMap.cpp:135.
// See targets/game/reverse/identity_evidence/00112bf0-embedInUseMap.md.

typedef unsigned int UnsignedInt;
typedef int Int;

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
extern "C" __declspec(dllimport) int __cdecl fseek(void *stream, Int offset, int origin);
extern "C" __declspec(dllimport) Int __cdecl ftell(void *stream);
extern "C" __declspec(dllimport) unsigned int __cdecl fread(
	void *buffer, unsigned int size, unsigned int count, void *stream);
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

// ?embedInUseMap@@YAXVAsciiString@@PAVXfer@@@Z
static __declspec(noinline) void embedInUseMap(AsciiString map, Xfer *xfer)
{
	UnsignedInt size;
	void *fp = bfmeFopenVIF(map.str(), "rb");
	if (fp == 0)
	{
		XferException error;
		bfmeFormatText(&error, 5, 0);
		_CxxThrowException(&error, (void *)0x011DFE5C);
	}

	// how big is the map file
	fseek(fp, 0, 2 /* SEEK_END */);
	size = ftell(fp);

	// rewind file back to start
	fseek(fp, 0, 0 /* SEEK_SET */);

	char *buffer = (char *)::operator new[](size);
	if (buffer == 0)
	{
		XferException error;
		bfmeFormatText(&error, 5, 0);
		_CxxThrowException(&error, (void *)0x011DFE5C);
	}

	if (fread(buffer, 1, size, fp) != size)
	{
		::operator delete[](buffer);
		XferException error;
		bfmeFormatText(&error, 5, 0);
		_CxxThrowException(&error, (void *)0x011DFE5C);
	}

	xfer->beginBlock("InUseMap");
	xfer->xferUnsignedInt(&size);
	xfer->xferUser(buffer, size);
	xfer->endBlock();

	bfmeFreeUXB(fp);
	::operator delete[](buffer);
}

// Internal-call anchor: the retail parent keeps Xfer live in a callee-saved
// register across this static helper, which MSVC 7.1 reproduces only when the
// helper has a local caller in the same translation unit.
void forceEmbedInUseMap(AsciiString map, Xfer *xfer)
{
	embedInUseMap(map, xfer);
}
