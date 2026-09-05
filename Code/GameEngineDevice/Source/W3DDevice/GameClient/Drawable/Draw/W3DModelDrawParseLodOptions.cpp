// cl: /DNDEBUG /MD /O2 /Ob1 /EHsc
// stlport
// Open-BFME5: W3DModelDrawModuleData LodOptions field parser at 0x00753930 (261B).
// Reads LOW/MEDIUM/HIGH then initFromINI into object+0x15c+idx*20.
// Field table tokens: AllowMultipleModels MaxRandomTextures MaxRandomAnimations
// MaxAnimFrameDelta RandomStartFramePercent. No named caller.

typedef int Int;

extern "C" int __cdecl strcmp(const char *, const char *);
#pragma intrinsic(strcmp)

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
	StringBase() : m_data(0) {}
	StringBase(const StringBase<T> &other);
	~StringBase();

	StringInlineData<T> *m_data;

public:
	void toLower();
};

class AsciiString : private StringBase<char>
{
public:
	AsciiString() : StringBase<char>() {}
	AsciiString(const AsciiString &other) : StringBase<char>(other) {}
	~AsciiString() {}

	void toLower() { StringBase<char>::toLower(); }
	const char *str(void) const { return m_data ? m_data->m_text : ""; }
};

struct FieldParse
{
	const char *token;
	void (*parse)();
	const void *userData;
	unsigned int offset;
};

class INI
{
public:
	AsciiString getNextAsciiString();
	void initFromINI(void *store, const FieldParse *fields);
};

class INIException
{
public:
	INIException(Int code, const char *msg, ...);
	INIException(const INIException &other);

private:
	const char *m_msg;
	Int m_code;
};

extern const FieldParse TheLodOptionsFieldParse[];
extern int g_INIExceptionThrowInfo;
__declspec(noreturn) void __stdcall _CxxThrowException(void *object, void *throwInfo);

class W3DModelDrawModuleData
{
public:
	static void parseLodOptions(INI *ini, void *object, void *store, const void *userData);
};

void W3DModelDrawModuleData::parseLodOptions(INI *ini, void *object, void *, const void *)
{
	AsciiString token = ini->getNextAsciiString();
	token.toLower();
	int idx;
	if (strcmp(token.str(), "low") == 0)
		idx = 0;
	else if (strcmp(token.str(), "medium") == 0)
		idx = 1;
	else if (strcmp(token.str(), "high") == 0)
		idx = 2;
	else
	{
		INIException error(1, "Expected LOW, MEDIUM, or HIGH");
		_CxxThrowException(&error, &g_INIExceptionThrowInfo);
	}
	ini->initFromINI((char *)object + 0x15c + idx * 20, TheLodOptionsFieldParse);
}
