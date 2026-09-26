// ?parseModuleName@ThingTemplate@@KAXPAVINI@@PAX1PBX@Z
// partial score=0.72 date=2026-09-09
// cl: /DNDEBUG /MD /EHsc /Oy- /ICode/Libraries/Source/WWVegas/WWLib
// BFME ThingTemplate::parseModuleName at retail RVA 0x001458A0.
//
// The callback is registered by ThingTemplate's Behavior/Body/Draw/
// ClientUpdate field tables.  BFME's ThingTemplate has four 12-byte
// ModuleInfo subobjects at +0x294, +0x2a0, +0x2ac and +0x2b8, rather than the
// three ZH members in the vendored header.  This TU keeps that ABI view local.

typedef int Int;
typedef bool Bool;
typedef unsigned int UnsignedInt;

#include "string_base.h"

struct FieldParse;

class AsciiString
{
public:
	AsciiString() { m_data = 0; }
	AsciiString(const char *text)
	{
		((StringBase<char> *)this)->StringBase<char>::StringBase(text);
	}
	~AsciiString()
	{
		((StringBase<char> *)this)->releaseBuffer();
	}

	void set(const char *text, Int length)
	{
		((StringBase<char> *)this)->set(text, length);
	}
	Int compare(const AsciiString &other) const
	{
		return ((const StringBase<char> *)this)->compare(
			*(const StringBase<char> *)&other);
	}

	const char *str() const
	{
		return m_data ? (const char *)m_data + 8 : (const char *)0x0107388b;
	}

	Bool isNotEmpty() const
	{
		return m_data != 0 && *(const unsigned short *)((const char *)m_data + 4) != 0;
	}

	Bool operator!=(const AsciiString &other) const
	{
		return compare(other) != 0;
	}

private:
	char *m_data;
};

class INIException
{
public:
	INIException(Int code, const char *message, ...);
	INIException(const INIException &other);

private:
	Int m_code;
	const char *m_message;
};

class INI
{
public:
	const char *getNextToken(const char *separators = 0);

	Int getLoadType() const
	{
		return *(const Int *)((const char *)this + 8);
	}
};

enum ModuleType
{
	MODULETYPE_BEHAVIOR = 0,
	MODULETYPE_DRAW = 1,
	MODULETYPE_CLIENT_UPDATE = 2
};

enum ModuleInterfaceType
{
	MODULEINTERFACE_BODY = 0x20
};

enum ModuleParseMode
{
	MODULEPARSE_NORMAL,
	MODULEPARSE_ADD_REMOVE_REPLACE,
	MODULEPARSE_INHERITABLE,
	MODULEPARSE_OVERRIDEABLE_BY_LIKE_KIND
};

class ThingTemplate;

class BfmeModuleData
{
public:
	virtual void bfmeSlot00();
	virtual void bfmeSlot04();
	virtual void bfmeSlot08();
	virtual void bfmeSlot0c();
	virtual Bool isAiModuleData() const;
	virtual Bool hasAiModuleData() const;
};

class BfmeModuleInfo
{
public:
	Bool clearCopiedFromDefaultEntries(Int interfaceMask);
	Bool clearAiModuleInfo();
	Bool clearModuleInfo();
	void addModuleInfo(ThingTemplate *thingTemplate,
		const AsciiString &name, const AsciiString &moduleTag,
		const BfmeModuleData *data, Int interfaceMask, Bool inheritable);

private:
	void *m_begin;
	void *m_end;
	void *m_capacity;
};

class BfmeModuleFactory
{
public:
	Int findModuleInterfaceMask(const AsciiString &name, ModuleType type);
	BfmeModuleData *newModuleDataFromINI(INI *ini, const AsciiString &name,
		ModuleType type, const AsciiString &moduleTag);
};

#define TheModuleFactory (*((BfmeModuleFactory **)0x012ef198))

class ThingTemplate
{
public:
	const AsciiString &getName() const { return m_nameString; }

protected:
	static void __cdecl parseModuleName(INI *ini, void *instance, void *store,
		const void *userData);

private:
	char m_unreconstructed00[0x20];
	AsciiString m_nameString;
	char m_unreconstructed24[0x50 - 0x24];
	AsciiString m_moduleBeingReplacedName;
	AsciiString m_moduleBeingReplacedTag;
	char m_unreconstructed58[0x294 - 0x58];
	BfmeModuleInfo m_behaviorModuleInfo;
	BfmeModuleInfo m_drawModuleInfo;
	BfmeModuleInfo m_clientUpdateModuleInfo;
	BfmeModuleInfo m_clientBehaviorModuleInfo;
	char m_unreconstructed2c4[0x498 - 0x2c4];
	char m_moduleParsingMode;
};

// ?parseModuleName@ThingTemplate@@KAXPAVINI@@PAX1PBX@Z
void __cdecl ThingTemplate::parseModuleName(INI *ini, void *instance,
	void *store, const void *userData)
{
	Int type = (Int)(UnsignedInt)userData;
	ThingTemplate *self = (ThingTemplate *)instance;
	BfmeModuleInfo *mi = (BfmeModuleInfo *)store;
	const char *token = ini->getNextToken();
	AsciiString tokenString = token;
	AsciiString moduleTagString;

	const char *moduleTag;
	Int tagLength;
	try
	{
		moduleTag = ini->getNextToken();
	}
	catch (...)
	{
		throw;
	}
	if (moduleTag != 0)
	{
		const char *tagStart = moduleTag + 1;
		const char *tagCursor = moduleTag;
		char tagChar;
		do
		{
			tagChar = *tagCursor;
			++tagCursor;
		} while (tagChar != 0);
		tagLength = (Int)(tagCursor - tagStart);
	}
	else
	{
		tagLength = 0;
	}
	moduleTagString.set(moduleTag, tagLength);

	Int interfaceMask;
	if (type == 999)
	{
		type = MODULETYPE_BEHAVIOR;
		interfaceMask = TheModuleFactory->findModuleInterfaceMask(tokenString,
			(ModuleType)type);
		if ((interfaceMask & MODULEINTERFACE_BODY) == 0)
		{
			throw INIException(3, "Only Body allowed here");
		}
	}
	else
	{
		interfaceMask = TheModuleFactory->findModuleInterfaceMask(tokenString,
			(ModuleType)type);
		if ((interfaceMask & MODULEINTERFACE_BODY) != 0)
		{
			throw INIException(3, "No Body allowed here");
		}
	}

	Int loadType = ini->getLoadType();
	if (loadType == 2)
	{
		if (self->m_moduleParsingMode != MODULEPARSE_ADD_REMOVE_REPLACE)
		{
			throw INIException(3, "You must use AddModule to add modules in override INI files.");
		}
	}
	else
	{
		self->m_behaviorModuleInfo.clearCopiedFromDefaultEntries(interfaceMask);
		self->m_drawModuleInfo.clearCopiedFromDefaultEntries(interfaceMask);
		self->m_clientUpdateModuleInfo.clearCopiedFromDefaultEntries(interfaceMask);
		self->m_clientBehaviorModuleInfo.clearCopiedFromDefaultEntries(interfaceMask);
	}

	if (self->m_moduleParsingMode == MODULEPARSE_ADD_REMOVE_REPLACE
			&& self->m_moduleBeingReplacedName.isNotEmpty()
			&& self->m_moduleBeingReplacedName != tokenString)
	{
		throw INIException(3,
			"ReplaceModule must replace modules with another module of the same type, but you are attempting to replace a %s with a %s for object %s.",
			self->m_moduleBeingReplacedName.str(), tokenString.str(), self->getName().str());
	}

	if (self->m_moduleParsingMode == MODULEPARSE_ADD_REMOVE_REPLACE
			&& self->m_moduleBeingReplacedTag.isNotEmpty()
			&& self->m_moduleBeingReplacedTag.compare(moduleTagString) == 0)
	{
		throw INIException(3,
			"ReplaceModule must specify a new, unique tag for the replaced module, but you are not doing so for %s (%s) for object %s.",
			moduleTagString.str(), self->m_moduleBeingReplacedName.str(), self->getName().str());
	}

	BfmeModuleData *data = TheModuleFactory->newModuleDataFromINI(
		ini, tokenString, (ModuleType)type, moduleTagString);
	Bool clearClientBehavior = ini->getLoadType() == 4;
	if (data->isAiModuleData())
	{
		mi->clearAiModuleInfo();
		if (data->hasAiModuleData() && clearClientBehavior)
		{
			mi->clearModuleInfo();
		}
	}

	Bool inheritable = self->m_moduleParsingMode == MODULEPARSE_INHERITABLE;
	mi->addModuleInfo(self, tokenString, moduleTagString, data, interfaceMask, inheritable);
}
