// cl: /DNDEBUG /DWIN32 /D_WINDOWS /MD /EHsc
// Open-BFME7: the shared INI option-definition registration helper at
// retail RVA 0x00094010.  The two scalar definition parsers at 0x000940F0
// and 0x00094470 both call this routine through ILT 0x00023344.

typedef int Int;

extern const char Rva006A16B0Empty[];

class AsciiString
{
public:
	AsciiString(const char *text);

	~AsciiString() { releaseBuffer(); }

	const char *str() const
	{
		return m_data ? static_cast<const char *>(m_data) + 8 : Rva006A16B0Empty;
	}

private:
	void releaseBuffer();
	void *m_data;
};

class INI
{
public:
	AsciiString getFilename() const;
	Int getLineNum() const;
};

// Retail throwinfo at VA 0x011DFC30 names INIException.  Its 16-byte record
// points at unwind ILT VA 0x0041460F and a catchable type whose copy-function
// ILT is VA 0x00448621.  The real class layout is message pointer at offset 0
// and argument count at offset 4; the copy and destructor are metadata only in
// this TU because their real retail bodies are owned by their existing rows.
class INIException
{
public:
	INIException(Int argumentCount, const char *format, ...);
	INIException(const INIException &that);
	~INIException();

	private:
	char *mFailureMessage;
	Int m_argCount;
};

class BfmeThingBPA
{
public:
	void *bfmeGoBPA(void *what);
	void bfmeGoBFA(void *one, void *two, void *three);
};

class Rva000940F0Definition;

extern void *TheOptionGroupTarget;
extern AsciiString TheOptionGroupName;

// ?Rva00094010Register@@YAXPAVINI@@ABVAsciiString@@PAVRva000940F0Definition@@@Z
void Rva00094010Register(INI *ini, const AsciiString &name,
	Rva000940F0Definition *definition)
{
	if (static_cast<BfmeThingBPA *>(TheOptionGroupTarget)->bfmeGoBPA((void *)&name) != 0)
	{
		throw INIException(3,
			"\"%s\" Option registry value multiply defined at %s:%d",
			*reinterpret_cast<char *const *>(&name),
			ini->getFilename().str(), ini->getLineNum());
	}

	static_cast<BfmeThingBPA *>(TheOptionGroupTarget)->bfmeGoBFA(&TheOptionGroupName,
		(void *)&name, definition);
}
