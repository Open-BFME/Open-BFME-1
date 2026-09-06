// cl: /DNDEBUG /DWIN32 /D_WINDOWS /MD /EHsc
// Open-BFME: INI::parseAnim2DDefinition, retail 0x005BB400.

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
	void releaseBuffer();

	void *m_data;

	friend class AsciiString;
};

class AsciiString
{
public:
	AsciiString() : m_string() {}
	~AsciiString() { m_string.releaseBuffer(); }

	void set(const char *text) { m_string.set(text); }

private:
	StringBase<char> m_string;
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
};

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
