// cl: /DNDEBUG /MD /EHsc /D_STLP_USE_STATIC_LIB /D_STLP_NO_EXCEPTIONS
// stlport
// FlammableUpdateModuleData FireFXList field parser.

#include <vector>

extern "C" __declspec(dllimport) int __cdecl _strcmpi(const char *, const char *);

class AsciiString
{
public:
	AsciiString(const char *);
	AsciiString(const AsciiString &);
	~AsciiString();
	void set(const char *);

private:
	char *m_data;
};

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

class INIException
{
public:
	INIException(int, const char *, ...);
	INIException(const INIException &);

private:
	char *m_failureMessage;
	int m_argCount;
};

class FXList;

namespace _STL
{
struct Rva002949D0Element
{
	const FXList *fx;
	AsciiString boneName;

	Rva002949D0Element() : fx(0), boneName((const char *)0x0107301c) {}
};
}

class FlammableUpdateModuleData
{
public:
	char m_pad00[8];
	unsigned int m_burnedDelay;
	unsigned int m_aflameDuration;
	unsigned int m_aflameDamageDelay;
	int m_aflameDamageAmount;
	void *m_burningSoundName;
	float m_flameDamageLimitData;
	unsigned int m_flameDamageExpirationDelay;
	_STL::vector<_STL::Rva002949D0Element> fireFXList;
};

// ?parseFireFXList@@YAXPAVINI@@PAX1PBX@Z
void parseFireFXList(INI *ini, void *instance, void *, const void *)
{
	FlammableUpdateModuleData *self = (FlammableUpdateModuleData *)instance;
	_STL::Rva002949D0Element info;

	const char *token = ini->getNextToken(ini->getSepsColon());
	if (_strcmpi(token, "FX") != 0)
		throw INIException(3, "'fx' expected");

	INI::parseFXList(ini, instance, &info.fx, 0);

	token = ini->getNextTokenOrNull(ini->getSepsColon());
	if (token != 0 && _strcmpi(token, "BONE") == 0)
		info.boneName.set(ini->getNextTokenOrNull(0));

	self->fireFXList.push_back(info);
}
