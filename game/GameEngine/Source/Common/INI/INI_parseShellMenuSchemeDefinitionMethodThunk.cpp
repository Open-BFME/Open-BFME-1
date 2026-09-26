// cl: /DNDEBUG /MD /EHsc
// Clean BFME layout reconstruction of INI::parseShellMenuSchemeDefinition.

typedef int Int;
extern "C" unsigned int __cdecl strlen(const char *text);

struct FieldParse;
class ShellMenuScheme;

class BfmeShellSchemeString
{
public:
	BfmeShellSchemeString() : m_data(0) {}
	BfmeShellSchemeString(const BfmeShellSchemeString &other) { copyFrom(other); }
	~BfmeShellSchemeString() { releaseBuffer(); }
	void set(const char *text, Int length);

private:
	void copyFrom(const BfmeShellSchemeString &other);
	void releaseBuffer();
	void *m_data;
};

class BfmeShellMenuSchemeManager
{
public:
	ShellMenuScheme *newShellMenuScheme(BfmeShellSchemeString name);
	const FieldParse *getFieldParse() const { return m_shellMenuSchemeFieldParseTable; }
	static const FieldParse m_shellMenuSchemeFieldParseTable[];
};

class BfmeShell
{
public:
	unsigned char m_pad[0x60];
	BfmeShellMenuSchemeManager *m_schemeManager;
};

extern BfmeShell *TheShell;

class INI
{
public:
	static void parseShellMenuSchemeDefinition(INI *ini);
	const char *getNextToken(const char *separators = 0);
	void initFromINI(void *object, const FieldParse *parseTable);
};

// ?parseShellMenuSchemeDefinition@INI@@SAXPAV1@@Z
void INI::parseShellMenuSchemeDefinition(INI *ini)
{
	BfmeShellSchemeString name;
	const char *text = ini->getNextToken();
	Int length = text ? strlen(text) : 0;
	name.set(text, length);

	BfmeShellMenuSchemeManager *manager = TheShell->m_schemeManager;
	if (manager) {
		BfmeShellSchemeString &argument = name;
		ShellMenuScheme *scheme = manager->newShellMenuScheme(argument);
		ini->initFromINI(scheme, manager->getFieldParse());
	}
}
