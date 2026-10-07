// cl: /DNDEBUG /MD /EHsc /Igame/Libraries/Source/WWVegas/WWLib
// ScriptEngine slot 16 resolves a canonical team name through TheTeamFactory.

#include "ascii_string.h"

class TeamPrototype;
class ScriptEngine;

// ILT 0x00036336 -> matched BfmeScriptEngineSlashName::bfmeName (0x003398F0).
class BfmeScriptEngineSlashName
{
public:
	AsciiString bfmeName(AsciiString &name);
};

class TeamFactory
{
public:
	TeamPrototype *findTeamPrototype(const AsciiString &name,
		const AsciiString &ownerName);
};

extern TeamFactory *TheTeamFactory;

class ScriptEngine
{
public:
	TeamPrototype *getTeamPrototypeNamed(AsciiString name);
};

// ?getTeamPrototypeNamed@ScriptEngine@@QAEPAVTeamPrototype@@VAsciiString@@@Z
TeamPrototype *ScriptEngine::getTeamPrototypeNamed(AsciiString name)
{
	AsciiString canonical =
		((BfmeScriptEngineSlashName *)this)->bfmeName(name);
	return TheTeamFactory->findTeamPrototype(canonical, name);
}
