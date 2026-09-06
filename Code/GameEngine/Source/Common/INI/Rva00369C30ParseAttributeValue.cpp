// cl: /DNDEBUG /DWIN32 /MD /EHsc
// Open-BFME7: INI field parser at 0x00369C30 (144 B): reads an attribute name
// resolves it through the attribute name table (0x003678E0 reached through
// TheAttributeModifierDefinitionStore) throws "Attribute '%s' not found" when
// the lookup yields nothing then reads a value token (getNextTokenPreprocess
// 0x008525C0 so macros expand) that may carry a percent sign and stores the
// (attribute value) pair into the instance (the owning vector) via the set-or-append routine
// at 0x00369B90.  The value is built in an (attribute value) entry local:
// that is what parks the scanned real in the upper half of the 8-byte frame
// (a plain Real local reuses the lower half).  Class names are address-derived.

typedef int Int;
typedef float Real;

extern "C" __declspec(dllimport) char *__cdecl strchr(const char *s, int c);

class INIException
{
public:
	INIException(Int code, const char *msg, ...);
	INIException(const INIException &other);

private:
	Int m_code;
	const char *m_msg;
};

class INI
{
public:
	const char *getNextToken(const char *seps = 0);
	const char *getNextTokenPreprocess(const char *seps = 0);
	static Real scanReal(const char *token);
	static Real scanPercentToReal(const char *token);
};

class Rva003678E0AttributeLookup
{
public:
	int find( const char *name ) const;
};

extern Rva003678E0AttributeLookup *TheAttributeModifierDefinitionStore;

class Rva00369B90AttributeValues
{
public:
	void set( int attribute, Real value );
};

class Rva00369C30
{
public:
	static void parseAttributeValue( INI *ini, void *instance, void *store, const void *userData );
};

struct Rva00369C30Entry
{
	int m_attribute;
	Real m_value;
};

// ?parseAttributeValue@Rva00369C30@@SAXPAVINI@@PAX1PBX@Z
void Rva00369C30::parseAttributeValue( INI *ini, void *instance, void *, const void * )
{
	Rva00369C30Entry entry;
	const char *name = ini->getNextToken();
	entry.m_attribute = TheAttributeModifierDefinitionStore->find( name );
	if( !entry.m_attribute )
		throw INIException( 3, "Attribute '%s' not found", name );

	const char *token = ini->getNextTokenPreprocess();
	if( strchr( token, '%' ) )
		entry.m_value = INI::scanPercentToReal( token );
	else
		entry.m_value = INI::scanReal( token );

	((Rva00369B90AttributeValues *)instance)->set( entry.m_attribute, entry.m_value );
}
