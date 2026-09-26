// cl: /DNDEBUG /MD /EHs-c-
// Open-BFME-1: the one-argument constructors of the two conversion holders whose
// init bodies are in W3AtlStringConversion.cpp.
//
// Each does exactly three things in this order: point the holder's pointer at
// its own inline buffer (`lea reg,[this+4] / mov [this],reg` -- this+4 is where
// the buffer starts, which is the layout the destructor at 0x0005D7B0 tests
// against), read the conversion code page out of the self-patching slot at
// [0x012A64C0], and hand both to the two-argument init. The leading
// `mov eax,ecx`-equivalent is the trailing `mov eax,esi`: a constructor returns
// its object.
//
// They CALL init rather than inline it, which is what says init is an opaque
// declaration here -- naming a callee defined in the same translation unit would
// have inlined it -- so these two constructors cannot share a file with their
// own init bodies.
//
// 0x0005E550 reaches the wide-to-ANSI init at 0x0005DA80 through the ILT thunk
// at 0x0000F62D, and 0x0005E580 reaches the ANSI-to-wide init at 0x0005DB10
// through 0x000022B1.
//
// Identity is address-derived.

typedef unsigned short WCHAR;
typedef unsigned int UINT;

typedef UINT (__stdcall *W3AtlAcpProc)(void);

extern W3AtlAcpProc g_pfnGetConversionAcp;							///< retail [0x012A64C0]

class Rva0005DA80WideToAnsi
{
public:
	Rva0005DA80WideToAnsi(const WCHAR *source);
	void init(const WCHAR *source, UINT codePage);					///< retail 0x0005DA80

	char *m_text;													///< retail this+0x00
	char m_buffer[128];												///< retail this+0x04
};

class Rva0005DB10AnsiToWide
{
public:
	Rva0005DB10AnsiToWide(const char *source);
	void init(const char *source, UINT codePage);					///< retail 0x0005DB10

	WCHAR *m_text;													///< retail this+0x00
	WCHAR m_buffer[128];											///< retail this+0x04
};

// ??0Rva0005DA80WideToAnsi@@QAE@PBG@Z
Rva0005DA80WideToAnsi::Rva0005DA80WideToAnsi(const WCHAR *source)
{
	m_text = m_buffer;
	init(source, g_pfnGetConversionAcp());
}

// ??0Rva0005DB10AnsiToWide@@QAE@PBD@Z
Rva0005DB10AnsiToWide::Rva0005DB10AnsiToWide(const char *source)
{
	m_text = m_buffer;
	init(source, g_pfnGetConversionAcp());
}
