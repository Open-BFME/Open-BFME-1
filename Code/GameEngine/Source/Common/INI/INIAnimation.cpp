// cl: /DNDEBUG /DWIN32 /D_WINDOWS /MD /EHsc
#include <string.h>

typedef int Int;
struct FieldParse;

template <typename T>
class StringBase
{
public:
	StringBase() : m_data(0) {}
	void set(const T *text, Int length);
	void set(const T *text) { set(text, text ? (Int)strlen((const char *)text) : 0); }

private:
	StringBase(const T *text);
	~StringBase();
	void *m_data;
	friend class AsciiString;
};

class AsciiString : private StringBase<char>
{
public:
	AsciiString() : StringBase<char>() {}
	AsciiString(const char *text) : StringBase<char>(text) {}
	void set(const char *text) { StringBase<char>::set(text); }
};

// BFME adds an integer after the message pointer; its meaning is unresolved.
class INIException
{
public:
	INIException(Int, const char *, ...);
	INIException(const INIException &);
	~INIException();

private:
	char *m_message;
	Int m_unreconstructed04;
};

class Anim2DTemplate
{
public:
	static const FieldParse s_anim2DFieldParseTable[];
};

class Anim2DCollection
{
public:
	Anim2DTemplate *findTemplate(const AsciiString &name);
	Anim2DTemplate *newTemplate(const AsciiString &name);
};

extern Anim2DCollection *TheAnim2DCollection;

class INI
{
public:
	const char *getNextToken(const char *seps = 0);
	void initFromINI(void *what, const FieldParse *parseTable);
	static void parseAnim2DDefinition(INI *ini);
	static void parseAnim2DTemplate(INI *ini, void *instance, void *store, const void *userData);
};

// ?parseAnim2DDefinition@INI@@SAXPAV1@@Z
void INI::parseAnim2DDefinition( INI *ini )
{
	AsciiString name;
	Anim2DTemplate *animTemplate;

	const char *token = ini->getNextToken();
	name.set( token );

	if( !TheAnim2DCollection )
		return;

	animTemplate = TheAnim2DCollection->findTemplate( name );
	if( animTemplate == 0 )
	{
		animTemplate = TheAnim2DCollection->newTemplate( name );
		ini->initFromINI( animTemplate, Anim2DTemplate::s_anim2DFieldParseTable );
	}
}

// ?parseAnim2DTemplate@INI@@SAXPAV1@PAX1PBX@Z
void INI::parseAnim2DTemplate(INI *ini, void *instance, void *store, const void *userData)
{
	const char *token = ini->getNextToken();

	if (TheAnim2DCollection)
	{
		Anim2DTemplate **anim2DTemplate = (Anim2DTemplate **)store;
		*anim2DTemplate = TheAnim2DCollection->findTemplate(AsciiString(token));
	}
	else
	{
		throw INIException(9, "iniParseAnim2DTemplate - TheAnim2DCollection is NULL");
	}
}
