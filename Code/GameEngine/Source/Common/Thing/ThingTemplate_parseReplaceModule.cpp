// cl: /DNDEBUG /MD /EHsc
// readable body of ?parseReplaceModule@ThingTemplate@@KAXPAVINI@@PAX1PBX@Z: Code/GameEngine/Source/Common/Thing/ThingTemplate.cpp
// Open-BFME7: Zero Hour's ThingTemplate::parseReplaceModule as real C++ (retail
// 0x00143320 315 B) replacing the byte-spray thunk.  Retail throws INIException(3 ...) where Zero Hour throws
// the bare INI_INVALID_DATA and the DEBUG_ASSERTCRASH text became the second
// exception's message.  BFME layout: m_nameString at +0x20 (str() reads the
// buffer eight bytes past the data pointer or the empty string constant) and
// the signed byte m_moduleParsingMode at +0x498 with the replaced-module name
// and tag strings at +0x50/+0x54 and the field table at VA 0x010910A0.  removeModuleInfo takes the
// module name as a const AsciiString reference so the token converts through
// a temporary that dies right after the call.

typedef int Int;
typedef bool Bool;

extern const char g_bfmeEmptyAscii[];

class AsciiString
{
public:
	AsciiString() : m_data( 0 ) {}
	AsciiString( const char *text );
	~AsciiString() { releaseBuffer(); }

	const char *str( void ) const { return m_data ? ((const char *)m_data) + 8 : g_bfmeEmptyAscii; }
	AsciiString &operator=( const AsciiString &other ) { set( other ); return *this; }
	AsciiString &operator=( const char *text );
	void set( const AsciiString &other );
	void clear( void ) { releaseBuffer(); }

private:
	void releaseBuffer( void );
	void *m_data;
};

class INIException
{
public:
	INIException( Int code, const char *msg, ... );
	INIException( const INIException &other );

private:
	Int m_code;
	const char *m_msg;
};

struct FieldParse;

class INI
{
public:
	const char *getNextToken( const char *seps = 0 );
	void initFromINI( void *what, const FieldParse *parseTable );
};

enum ModuleParseMode
{
	MODULEPARSE_NORMAL,
	MODULEPARSE_ADD_REMOVE_REPLACE,
	MODULEPARSE_MODIFY_ON_COPY
};

// upstream layout: reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/GameEngine/Include/Common/ThingTemplate.h
class ThingTemplate
{
public:
	const AsciiString &getName( void ) const { return m_nameString; }

protected:
	static void parseReplaceModule( INI *ini, void *instance, void *store, const void *userData );
	Bool removeModuleInfo( const AsciiString &moduleToRemove, AsciiString &removedModuleName );

	char m_unreconstructed00[ 0x20 ];
	AsciiString m_nameString;
	char m_unreconstructed24[ 0x50 - 0x24 ];
	AsciiString m_moduleBeingReplacedName;
	AsciiString m_moduleBeingReplacedTag;
	char m_unreconstructed58[ 0x498 - 0x58 ];
	char m_moduleParsingMode;

	static const FieldParse s_objectFieldParseTable[];
	static const FieldParse *getFieldParse( void ) { return s_objectFieldParseTable; }
};

// ?parseReplaceModule@ThingTemplate@@KAXPAVINI@@PAX1PBX@Z
void ThingTemplate::parseReplaceModule( INI *ini, void *instance, void *, const void * )
{
	ThingTemplate *self = (ThingTemplate *)instance;

	ModuleParseMode oldMode = (ModuleParseMode)self->m_moduleParsingMode;
	if( oldMode != MODULEPARSE_NORMAL )
		throw INIException( 3, "Expected oldMode to be MODULEPARSE_NORMAL" );

	self->m_moduleParsingMode = MODULEPARSE_ADD_REMOVE_REPLACE;

	const char *modToRemove = ini->getNextToken();
	AsciiString removedModuleName;
	Bool removed = self->removeModuleInfo( modToRemove, removedModuleName );
	if( !removed )
		throw INIException( 3, "ReplaceModule %s was not found for %s, cannot continue.", modToRemove, self->getName().str() );

	self->m_moduleBeingReplacedName = removedModuleName;
	self->m_moduleBeingReplacedTag = modToRemove;
	ini->initFromINI( self, self->getFieldParse() );
	self->m_moduleBeingReplacedName.clear();
	self->m_moduleBeingReplacedTag.clear();

	self->m_moduleParsingMode = oldMode;
}
