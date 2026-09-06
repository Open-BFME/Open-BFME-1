// cl: /DNDEBUG /MD /EHsc
// ThingTemplate::parseRemoveModule matches the reference implementation and
// the retail callback at 0x001431D0. The BFME build throws INIException with
// the retail error text when nested module parsing or removal fails.

typedef int Int;
typedef bool Bool;

// upstream layout: reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/GameEngine/Include/Common/INIException.h
class INIException
{
public:
	INIException(Int code, const char *message, ...);
	INIException(const INIException &other);

private:
	Int m_code;
	const char *m_message;
};

// upstream layout: reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/GameEngine/Include/Common/INI.h
class INI
{
public:
	const char *getNextToken(const char *separators = 0);
};

class AsciiString
{
public:
	AsciiString() : m_data(0) {}
	AsciiString(const char *text);
	~AsciiString();

	const char *str() const
	{
		return m_data ? (const char *)m_data + 8 : (const char *)0x0107388B;
	}

private:
	void *m_data;
};

// upstream layout: reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/GameEngine/Include/Common/ThingTemplate.h
class ThingTemplate
{
public:
	const AsciiString &getName() const
	{
		return m_nameString;
	}

protected:
	static void __cdecl parseRemoveModule(INI *ini, void *instance, void *store, const void *userData);
	Bool removeModuleInfo(const AsciiString &moduleToRemove, AsciiString &clearedModuleNameOut);

private:
	unsigned char m_prefix[0x20];
	AsciiString m_nameString;
	unsigned char m_betweenNameAndMode[0x474];
	char m_moduleParsingMode;
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
