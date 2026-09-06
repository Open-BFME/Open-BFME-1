// cl: /DNDEBUG /MD /EHsc /D_STLP_USE_STATIC_LIB /D_STLP_NO_EXCEPTIONS
// stlport
// Open-BFME5: ExperienceLevel LevelUpFx field parser.

#include <vector>

extern "C" __declspec(dllimport) int __cdecl _strcmpi(const char *, const char *);

// upstream layout: reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/GameEngine/Include/Common/AsciiString.h
class AsciiString
{
public:
	AsciiString() : m_data(0) {}
	AsciiString(const AsciiString &);
	~AsciiString();
	void set(const char *);

private:
	char *m_data;
};

// upstream layout: reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/GameEngine/Include/Common/INIException.h
class INIException
{
public:
	INIException(int, const char *, ...);
	INIException(const INIException &);

private:
	char *m_failureMessage;
	int m_argCount;
};

// upstream layout: reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/GameEngine/Include/Common/INI.h
class INI
{
public:
	const char *getNextToken(const char *seps = 0);
	const char *getNextTokenOrNull(const char *seps = 0);
	const char *getSepsColon() const { return m_sepsColon; }
	static void parseFXList(INI *, void *, void *, const void *);

private:
	char m_unreconstructed_000[0x41c];
	const char *m_sepsColon;
};

class FXList;

struct LevelUpFXInfo
{
	const FXList *fx;
	AsciiString boneName;
};

class ExperienceLevel
{
public:
	char m_unreconstructed_000[0x34];
	_STL::vector<LevelUpFXInfo> levelUpFx;
};

// ?parseLevelUpFx@@YAXPAVINI@@PAX1PBX@Z
void parseLevelUpFx(INI *ini, void *instance, void *, const void *)
{
	ExperienceLevel *self = (ExperienceLevel *)instance;
	LevelUpFXInfo info;

	const char *token = ini->getNextToken(ini->getSepsColon());
	if (_strcmpi(token, "FX") != 0)
		throw INIException(3, "'fx' expected");

	INI::parseFXList(ini, instance, &info.fx, 0);

	token = ini->getNextTokenOrNull(ini->getSepsColon());
	if (token != 0 && _strcmpi(token, "BONE") == 0)
		info.boneName.set(ini->getNextTokenOrNull(0));

	self->levelUpFx.push_back(info);
}
