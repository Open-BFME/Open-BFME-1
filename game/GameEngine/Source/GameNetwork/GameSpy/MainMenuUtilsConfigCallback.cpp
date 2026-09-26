// cl: /DNDEBUG /MD /EHsc /O2 /Ob2
// ?configCallback@@YA?AW4GHTTPBool@@HW4GHTTPResult@@PAD_JPAX@Z at retail RVA 0x0062EEE0, 464 bytes.
// Zero Hour reference source: GeneralsMD/Code/GameEngine/Source/GameNetwork/GameSpy/MainMenuUtils.cpp
//
// Kept out of MainMenuUtils.cpp because that TU compiles against Zero Hour's
// AsciiString (inline getPath_UserData, format(const char *)), while retail
// calls the out-of-line GlobalData accessor and builds a by-value AsciiString
// for format(AsciiString, ...).
//
// BFME differences from Zero Hour: the GameSpy SDK's GHTTPByteCount is 64-bit,
// so bufferLen is an __int64; the file is "%sLoTRB4MEOnline\\Config.txt"; and the
// cancel window is a flag byte (retail 0x012F7178, the slot Zero Hour's
// onlineCancelWindow occupies) torn down through the ReleaseWindowLayout(0)
// wrapper at 0x004C5490. startOnline is the dump body at 0x0062EA60.
// The file statics mirror retail's .data block 0x012F7160..0x012F7178.

#include <stdio.h>
#include <string.h>

// The array forms are declared so new[]/delete[] reach retail's
// operator new[]/delete[] (0x00881F70 / 0x00881EF0) instead of the scalar pair.
void *__cdecl operator new[](size_t size);
void __cdecl operator delete[](void *ptr);

typedef int Int;
typedef bool Bool;

// upstream layout: inputs/reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/Libraries/Include/GameSpy/ghttp/ghttp.h
typedef enum { GHTTPFalse, GHTTPTrue } GHTTPBool;
typedef int GHTTPRequest;
typedef enum { GHTTPSuccess } GHTTPResult;

template <typename T> struct StringInlineData
{
	int m_refCount;
	int m_length;
	T m_text[1];
};

template <typename T> class StringBase
{
	friend class AsciiString;

private:
	StringBase() : m_data( 0 ) {}
	StringBase( const T *text );
	StringBase( const StringBase<T> &other );
	~StringBase();

	StringInlineData<T> *m_data;
};

extern const char Rva006A16B0Empty[];

// upstream layout: inputs/reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/GameEngine/Include/Common/AsciiString.h
class AsciiString : private StringBase<char>
{
public:
	AsciiString() : StringBase<char>() {}
	AsciiString( const char *text ) : StringBase<char>( text ) {}
	AsciiString( const AsciiString &other ) : StringBase<char>( other ) {}
	~AsciiString() {}

	const char *str() const
	{
		return m_data ? m_data->m_text : Rva006A16B0Empty;
	}

	void __cdecl format( AsciiString format, ... );
};

// upstream layout: inputs/reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/GameEngine/Include/Common/GlobalData.h
class GlobalData
{
public:
	AsciiString getPath_UserData() const;
};

extern GlobalData *TheWritableGlobalData;
#define TheGlobalData ((const GlobalData *)TheWritableGlobalData)

void Rva004C5490(void);		// ?Rva004C5490@@YAXXZ ReleaseWindowLayout(0) wrapper
void d_0062ea60(void);		// ?d_0062ea60@@YAXXZ retail startOnline (dump)

static Bool checkingForPatchBeforeGameSpy = false;	// 0x012F7160
static Int checksLeftBeforeOnline = 0;				// 0x012F7164
static Int timeThroughOnline = 0;					// 0x012F7168
static Bool cantConnectBeforeOnline = false;		// 0x012F716D
static char *configBuffer = NULL;					// 0x012F7174
static Bool s_rva012F7178 = false;					// 0x012F7178

GHTTPBool configCallback( GHTTPRequest request, GHTTPResult result,
						  char * buffer, __int64 bufferLen, void * param )
{
	Int run = (Int)param;
	if (run != timeThroughOnline)
	{
		return GHTTPTrue;
	}

	if (configBuffer)
	{
		delete[] configBuffer;
		configBuffer = NULL;
	}

	if (result != GHTTPSuccess || bufferLen < 100)
	{
		if (!checkingForPatchBeforeGameSpy)
			return GHTTPTrue;
		--checksLeftBeforeOnline;
		if (s_rva012F7178 && !checksLeftBeforeOnline)
		{
			Rva004C5490();
			s_rva012F7178 = false;
		}
		cantConnectBeforeOnline = true;
		if (!checksLeftBeforeOnline)
		{
			d_0062ea60();
		}
		return GHTTPTrue;
	}

	configBuffer = new char[(size_t)bufferLen];
	memcpy(configBuffer, buffer, (size_t)bufferLen);
	configBuffer[bufferLen-1] = 0;

	AsciiString fname;
	fname.format("%sLoTRB4MEOnline\\Config.txt", TheGlobalData->getPath_UserData().str());
	FILE *fp = fopen(fname.str(), "wb");
	if (fp)
	{
		fwrite(configBuffer, (size_t)bufferLen, 1, fp);
		fclose(fp);
	}

	--checksLeftBeforeOnline;
	if (s_rva012F7178 && !checksLeftBeforeOnline)
	{
		Rva004C5490();
		s_rva012F7178 = false;
	}

	if (!checksLeftBeforeOnline)
		d_0062ea60();

	return GHTTPTrue;
}
