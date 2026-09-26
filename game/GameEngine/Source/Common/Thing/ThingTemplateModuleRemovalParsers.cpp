// cl: /DNDEBUG /MD /EHsc

// The two INI callbacks that take a module away before parsing continues:
//
//   parseRemoveModule  0x001431D0  drop a named module, then restore the mode
//   parseReplaceModule 0x00143320  drop it, remember its name and tag, re-parse
//
// They are 0x150 apart in the image and share their whole opening: read the mode
// byte at +0x498, refuse to nest, store MODULEPARSE_ADD_REMOVE_REPLACE, take the
// next token, call removeModuleInfo, and throw INIException(3, ...) naming the
// module and the template when it fails. They sat in two files with two accounts
// of AsciiString, of ThingTemplate and of the mode enum.
//
// ThingTemplate is the clearest gain. parseRemoveModule named m_nameString at
// +0x20 and then padded 0x474 bytes straight to the mode byte; parseReplaceModule
// named two more fields inside that pad -- m_moduleBeingReplacedName at +0x50 and
// m_moduleBeingReplacedTag at +0x54. One declaration names all four.
//
// AsciiString is where they actually contradicted each other, in two places:
//
//   str()'s empty case  parseRemoveModule returned the literal address
//                       (const char *)0x0107388B; parseReplaceModule returned the
//                       named extern g_bfmeEmptyAscii. Same constant, and the
//                       name is kept.
//   the destructor      parseRemoveModule declared it and left it out of line;
//                       parseReplaceModule defined it inline as releaseBuffer().
//                       They cannot both be the class's declaration, and the
//                       inline one is right: with it, parseReplaceModule's normal
//                       path calls releaseBuffer directly while
//                       parseRemoveModule's local is still destroyed through
//                       ~AsciiString from the unwind funclet, which is what each
//                       body's bytes show. The out-of-line spelling only ever
//                       described one of the two call sites.
//
// The mode enum is ZH's, settled in ThingTemplateModuleModeParsers.cpp:
// parseReplaceModule's third enumerator was MODULEPARSE_MODIFY_ON_COPY, which
// does not exist upstream, and parseRemoveModule used raw 0 and 1 with no enum at
// all. Neither body stores anything above 1, so naming the slots correctly costs
// nothing here and stops the invented name spreading.

typedef int Int;
typedef bool Bool;

// The empty-string constant at retail 0x0107388B.
extern const char g_bfmeEmptyAscii[];

// upstream layout: inputs/reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/GameEngine/Include/Common/AsciiString.h
class AsciiString
{
public:
	AsciiString() : m_data(0) {}
	AsciiString(const char *text);
	~AsciiString() { releaseBuffer(); }

	const char *str(void) const { return m_data ? ((const char *)m_data) + 8 : g_bfmeEmptyAscii; }
	AsciiString &operator=(const AsciiString &other) { set(other); return *this; }
	AsciiString &operator=(const char *text);
	void set(const AsciiString &other);
	void clear(void) { releaseBuffer(); }

private:
	void releaseBuffer(void);
	void *m_data;
};

// upstream layout: inputs/reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/GameEngine/Include/Common/INIException.h
class INIException
{
public:
	INIException(Int code, const char *msg, ...);
	INIException(const INIException &other);

private:
	Int m_code;
	const char *m_msg;
};

struct FieldParse;

// upstream layout: inputs/reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/GameEngine/Include/Common/INI.h
class INI
{
public:
	const char *getNextToken(const char *seps = 0);
	void initFromINI(void *what, const FieldParse *parseTable);
};

// upstream layout: inputs/reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/GameEngine/Include/Common/ThingTemplate.h
enum ModuleParseMode
{
	MODULEPARSE_NORMAL,
	MODULEPARSE_ADD_REMOVE_REPLACE,
	MODULEPARSE_INHERITABLE,
	MODULEPARSE_OVERRIDEABLE_BY_LIKE_KIND
};

// upstream layout: inputs/reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/GameEngine/Include/Common/ThingTemplate.h
class ThingTemplate
{
public:
	const AsciiString &getName(void) const { return m_nameString; }

protected:
	static void __cdecl parseRemoveModule(INI *ini, void *instance, void *store, const void *userData);
	static void parseReplaceModule(INI *ini, void *instance, void *store, const void *userData);
	Bool removeModuleInfo(const AsciiString &moduleToRemove, AsciiString &removedModuleName);

	char m_unreconstructed00[0x20];
	AsciiString m_nameString;				// +0x020
	char m_unreconstructed24[0x50 - 0x24];
	AsciiString m_moduleBeingReplacedName;			// +0x050
	AsciiString m_moduleBeingReplacedTag;			// +0x054
	char m_unreconstructed58[0x498 - 0x58];
	char m_moduleParsingMode;				// +0x498

	static const FieldParse s_objectFieldParseTable[];
	static const FieldParse *getFieldParse(void) { return s_objectFieldParseTable; }
};

// ?parseRemoveModule@ThingTemplate@@KAXPAVINI@@PAX1PBX@Z
void __cdecl ThingTemplate::parseRemoveModule(INI *ini, void *instance, void *store, const void *userData)
{
	ThingTemplate *self = (ThingTemplate *)instance;
	Int oldMode = (Int)self->m_moduleParsingMode;
	if (oldMode != 0)
		throw INIException(3, "Expected oldMode to be MODULEPARSE_NORMAL");

	self->m_moduleParsingMode = 1;
	const char *modToRemove = ini->getNextToken();
	AsciiString removedModuleName;
	Bool removed = self->removeModuleInfo(modToRemove, removedModuleName);
	if (!removed)
	{
		throw INIException(3, "RemoveModule %s was not found for %s.", modToRemove, self->getName().str());
	}

	self->m_moduleParsingMode = oldMode;
}

// ?parseReplaceModule@ThingTemplate@@KAXPAVINI@@PAX1PBX@Z
//
// removeModuleInfo takes the module name as a const AsciiString reference, so the
// token converts through a temporary that dies right after the call.
void ThingTemplate::parseReplaceModule(INI *ini, void *instance, void *store, const void *userData)
{
	ThingTemplate *self = (ThingTemplate *)instance;

	ModuleParseMode oldMode = (ModuleParseMode)self->m_moduleParsingMode;
	if (oldMode != MODULEPARSE_NORMAL)
		throw INIException(3, "Expected oldMode to be MODULEPARSE_NORMAL");

	self->m_moduleParsingMode = MODULEPARSE_ADD_REMOVE_REPLACE;

	const char *modToRemove = ini->getNextToken();
	AsciiString removedModuleName;
	Bool removed = self->removeModuleInfo(modToRemove, removedModuleName);
	if (!removed)
		throw INIException(3, "ReplaceModule %s was not found for %s, cannot continue.", modToRemove, self->getName().str());

	self->m_moduleBeingReplacedName = removedModuleName;
	self->m_moduleBeingReplacedTag = modToRemove;
	ini->initFromINI(self, self->getFieldParse());
	self->m_moduleBeingReplacedName.clear();
	self->m_moduleBeingReplacedTag.clear();

	self->m_moduleParsingMode = oldMode;
}
