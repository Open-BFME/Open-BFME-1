// cl: /DNDEBUG /MD /EHsc
// Open-BFME5: clean C++ reconstruction of BoneFXUpdateModuleData::parseFXList.

#include <string.h>

typedef int Bool;
typedef float Real;

extern "C" __declspec(dllimport) int __cdecl _strcmpi(const char *, const char *);

class AsciiString
{
public:
	void set(const char *, int);

	AsciiString &operator=(const char *text)
	{
		set(text, text ? strlen(text) : 0);
		return *this;
	}

private:
	char *m_data;
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

class INI
{
public:
	const char *getNextToken(const char *seps = 0);
	const char *getSepsColon() const { return m_sepsColon; }

	static void parseBool(INI *, void *, void *, const void *);
	static void parseDurationReal(INI *, void *, void *, const void *);
	static void parseFXList(INI *, void *, void *, const void *);
	static void parseObjectCreationList(INI *, void *, void *, const void *);
	static void parseParticleSystemTemplate(INI *, void *, void *, const void *);

private:
	char m_prefix[0x41c];
	const char *m_sepsColon;
};

class GameClientRandomVariable
{
public:
	enum DistributionType
	{
		CONSTANT,
		UNIFORM
	};

	void setRange(Real low, Real high, DistributionType type = UNIFORM);

private:
	DistributionType m_type;
	Real m_low;
	Real m_high;
};

class GameLogicRandomVariable
{
public:
	enum DistributionType
	{
		CONSTANT,
		UNIFORM
	};

	void setRange(Real low, Real high, DistributionType type = UNIFORM);

private:
	DistributionType m_type;
	Real m_low;
	Real m_high;
};

class FXList;
class ObjectCreationList;
class ParticleSystemTemplate;

struct BoneLocInfo
{
	AsciiString boneName;
};

struct BaseBoneListInfo
{
	BoneLocInfo locInfo;
	GameClientRandomVariable gameClientDelay;
	GameLogicRandomVariable gameLogicDelay;
	Bool onlyOnce;
};

struct BoneFXListInfo : public BaseBoneListInfo
{
	const FXList *fx;
};

struct BoneOCLInfo : public BaseBoneListInfo
{
	const ObjectCreationList *ocl;
};

struct BoneParticleSystemInfo : public BaseBoneListInfo
{
	const ParticleSystemTemplate *particleSystemTemplate;
};

class BoneFXUpdateModuleDataParseFXListShim
{
public:
	static void parse(INI *, void *, void *, const void *);
};

class BoneFXUpdateModuleDataParseObjectCreationListShim
{
public:
	static void parse(INI *, void *, void *, const void *);
};

class BoneFXParseParticleSystemShim
{
public:
	static void parseParticleSystem(INI *, void *, void *, const void *);
};

static void parseFXLocInfo(INI *ini, void *, BoneLocInfo *locInfo)
{
	const char *token = ini->getNextToken(ini->getSepsColon());

	if (_strcmpi(token, "bone") == 0)
		locInfo->boneName = ini->getNextToken();
	else
		throw INIException(3, "'bone' expected");
}

static void parseGameLogicRandomDelay(
	INI *ini,
	void *instance,
	GameLogicRandomVariable *delay)
{
	Real min;
	Real max;

	INI::parseDurationReal(ini, instance, &min, 0);
	INI::parseDurationReal(ini, instance, &max, 0);
	delay->setRange(min, max, GameLogicRandomVariable::UNIFORM);
}

static void parseGameClientRandomDelay(
	INI *ini,
	void *instance,
	GameClientRandomVariable *delay)
{
	Real min;
	Real max;

	INI::parseDurationReal(ini, instance, &min, 0);
	INI::parseDurationReal(ini, instance, &max, 0);
	delay->setRange(min, max, GameClientRandomVariable::UNIFORM);
}

void BoneFXUpdateModuleDataParseFXListShim::parse(
	INI *ini,
	void *instance,
	void *store,
	const void *)
{
	BoneFXListInfo *info = static_cast<BoneFXListInfo *>(store);

	parseFXLocInfo(ini, instance, &info->locInfo);

	const char *token = ini->getNextToken(ini->getSepsColon());
	if (_strcmpi(token, "onlyonce") != 0)
		throw INIException(3, "'onlyonce' expected");

	INI::parseBool(ini, instance, &info->onlyOnce, 0);
	parseGameLogicRandomDelay(ini, instance, &info->gameLogicDelay);

	token = ini->getNextToken(ini->getSepsColon());
	if (_strcmpi(token, "fxlist") != 0)
		throw INIException(3, "'fxlist' expected");

	INI::parseFXList(ini, instance, &info->fx, 0);
}

void BoneFXUpdateModuleDataParseObjectCreationListShim::parse(
	INI *ini,
	void *instance,
	void *store,
	const void *)
{
	BoneOCLInfo *info = static_cast<BoneOCLInfo *>(store);

	parseFXLocInfo(ini, instance, &info->locInfo);

	const char *token = ini->getNextToken(ini->getSepsColon());
	if (_strcmpi(token, "onlyonce") != 0)
		throw INIException(3, "'onlyonce' expected");

	INI::parseBool(ini, instance, &info->onlyOnce, 0);
	parseGameLogicRandomDelay(ini, instance, &info->gameLogicDelay);

	token = ini->getNextToken(ini->getSepsColon());
	if (_strcmpi(token, "ocl") != 0)
		throw INIException(3, "'ocl' expected");

	INI::parseObjectCreationList(ini, instance, &info->ocl, 0);
}

void BoneFXParseParticleSystemShim::parseParticleSystem(
	INI *ini,
	void *instance,
	void *store,
	const void *)
{
	BoneParticleSystemInfo *info = static_cast<BoneParticleSystemInfo *>(store);

	parseFXLocInfo(ini, instance, &info->locInfo);

	const char *token = ini->getNextToken(ini->getSepsColon());
	if (_strcmpi(token, "onlyonce") != 0)
		throw INIException(3, "'onlyonce' expected");

	INI::parseBool(ini, instance, &info->onlyOnce, 0);
	parseGameClientRandomDelay(ini, instance, &info->gameClientDelay);

	token = ini->getNextToken(ini->getSepsColon());
	if (_strcmpi(token, "psys") != 0)
		throw INIException(3, "'psys' expected");

	INI::parseParticleSystemTemplate(
		ini,
		instance,
		&info->particleSystemTemplate,
		0);
}
